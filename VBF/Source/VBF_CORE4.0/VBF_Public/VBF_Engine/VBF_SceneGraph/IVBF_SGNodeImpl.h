#ifndef OSG_NODE
#define OSG_NODE 1

//#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>


//#include <string>
//#include <vector>


#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h>



namespace osg 
{

/** META_Node宏定义了标准的clone、isSameKindAs、className、accept等方法。 便于IVBF_SGNodeImpl的子类实现纯虚函数。*/
#define META_Node(library,name) \
        virtual osg::CVBF_Object* cloneType() const { return new name (); } \
        virtual osg::CVBF_Object* clone(const osg::CopyOp& copyop) const { return new name (*this,copyop); } \
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
        virtual const char* className() const { return #name; } \
        virtual const char* libraryName() const { return #library; } \
        virtual void accept(osg::NodeVisitor& nv) { if (nv.validNodeMask(*this)) { nv.pushOntoNodePath(this); nv.apply(*this); nv.popFromNodePath(); } } \
        



/** 场景图节点的基类，提供了公用的节点操作接口。*/
template<class T>
class IVBF_SGNodeImpl : public T
{
    public:
  		// 1、与构造函数有关的内容
      
		/** parent list为空, 名字为""，bounding sphere dirty flag为true.*/
        IVBF_SGNodeImpl();

        /** 拷贝构造函数, 通过CopyOp控制动态数据的shallow vs deep拷贝。*/
        IVBF_SGNodeImpl(const IVBF_SGNodeImpl&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		// 2、与基本信息有关的内容

        /** 创建一个同类型（IVBF_SGNodeImpl）的指针，与本对象在数据上没有关系*/
//        virtual CVBF_Object* cloneType() const { return new IVBF_SGNodeImpl<IVBF_SGNode>(); }

        /** 克隆一个对象，与 本对象数据相同（由CopyOp决定）。*/
//        virtual CVBF_Object* clone(const CopyOp& copyop) const { return new IVBF_SGNodeImpl<IVBF_SGNode>(*this,copyop); }

        /** 如果this和obj是同类对象返回true。*/
 //       virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const IVBF_SGNode*>(obj)!=NULL; }

        /** 返回所在的库的名字。*/
        virtual const char* libraryName() const { return "osg"; }

        /** 返回类的名字。*/
        virtual const char* className() const { return "Node"; }



		// 3、类型转化，!!!去掉，在使用时改为dynamic_cast<XXX*>(this)形式，降低性能（降低多少？）但代码结构清晰

 


		// 4、与遍历操作相关的内容

         virtual void accept(NodeVisitor& nv);

        /** 向上遍历 : 调用父亲的accept方法 with NodeVisitor.*/
        virtual void ascend(NodeVisitor& nv);

        /** 向下遍历 : 调用孩子的accept方法 with NodeVisitor.*/
        virtual void traverse(NodeVisitor& /*nv*/) {}       



		// 5、与父子关系有关的内容


        /** 获取节点的父节点列表 */
        virtual const osg::CVBF_NodeParentList& getParents() const { return _parents; }

        /** 获取父节点列表的拷贝，使用拷贝可以防止父节点列表被更改。*/
        virtual osg::CVBF_NodeParentList getParents() { return _parents; }

		/** 获取第i个父节点。 */
		virtual IVBF_SGNodeGroup* getParent(unsigned int i)  { return _parents[i]; }
		virtual const IVBF_SGNodeGroup* getParent(unsigned int i) const  { return _parents[i]; }

        /**获取父节点的个数。*/
        virtual unsigned int getNumParents() const { return static_cast<unsigned int>(_parents.size()); }

        /** 获取父节点路径的列表（父节点路径可能有多个）。可选参数IVBF_SGNodeImpl* haltTraversalAtNode允许在指定的节点处停止遍历。*/
        virtual osg::NodePathList getParentalNodePaths(osg::IVBF_SGNode* haltTraversalAtNode=0) const;
 
		// 5.1、与矩阵变换路径有关的内容

        /** 获取把节点从局部坐标系变换到世界坐标系的矩阵列表。可选参数IVBF_SGNodeImpl* haltTraversalAtNode允许在指定的节点处停止遍历。*/
        osg::MatrixList getWorldMatrices(const osg::IVBF_SGNode* haltTraversalAtNode=0) const;
        


		// 6、与节点回调函数有关的内容

		// 6.1 更新回调

		/** 设置/获取Update回调函数，在遍历更新的时候回调。*/
		virtual void setUpdateCallback(NodeCallback* nc);
		virtual NodeCallback* getUpdateCallback() { return _updateCallback.get(); }
		virtual const NodeCallback* getUpdateCallback() const { return _updateCallback.get(); }

		/** 添加Update回调函数，节点的Update回调函数不存在时设置它，存在时把它嵌套到已经存在的Update回调函数。 */
        virtual void addUpdateCallback(NodeCallback* nc) 
		{
            if (nc == NULL) return;
			if (_updateCallback.valid()) _updateCallback->addNestedCallback(nc);
			else setUpdateCallback(nc);
        }

  		/** 移除节点的Update回调函数（即使该函数被嵌套了也适用），找不到该Update回调函数也不返回错误。 */
		virtual void removeUpdateCallback(NodeCallback* nc) 
		{
			if(nc == NULL) return ;
			if (!_updateCallback.valid()) return;
		
			if (_updateCallback == nc) setUpdateCallback(nc->getNestedCallback());        // replace the callback by the nested one
			else _updateCallback->removeNestedCallback(nc);			
		}

        /** 获取需要更新遍历的子节点的个数。这些子节点关联了Update Callback或其子节点关联了Update Callback。*/
        virtual unsigned int getNumChildrenRequiringUpdateTraversal() const { return _numChildrenRequiringUpdateTraversal; }


		// 6.2 事件回调

		/** 设置/获取event回调函数，在遍历event的时候回调。*/
		virtual void setEventCallback(NodeCallback* nc);
		virtual NodeCallback* getEventCallback() { return _eventCallback.get(); }
		virtual const NodeCallback* getEventCallback() const { return _eventCallback.get(); }

		/** 添加Event回调函数，节点的Event回调函数不存在时设置它，存在时把它嵌套到已经存在的Event回调函数。 */
 		virtual void addEventCallback(NodeCallback* nc) 
		{
			if (nc == NULL) return ;
			
			if (_eventCallback.valid()) _eventCallback->addNestedCallback(nc);
            else setEventCallback(nc);           
        }

  		/** 移除节点的Event回调函数（即使该函数被嵌套了也适用），找不到该Event回调函数也不返回错误。 */
		virtual void removeEventCallback(NodeCallback* nc) 
		{
			if (nc == NULL) return; 
			if (!_eventCallback.valid()) return;

			if (_eventCallback == nc) setEventCallback(nc->getNestedCallback());        // replace the callback by the nested one
			else _eventCallback->removeNestedCallback(nc);			
		}

		/** 获取需要Event遍历的子节点的个数。这些子节点关联了Event Callback或其子节点关联了Event Callback。*/
		virtual unsigned int getNumChildrenRequiringEventTraversal() const { return _numChildrenRequiringEventTraversal; }




		// 6.3 裁剪回调

        /** 设置/获取Cull回调函数，在遍历裁剪的时候回调。*/
		virtual void setCullCallback(NodeCallback* nc) { _cullCallback = nc; }
		virtual NodeCallback* getCullCallback() { return _cullCallback.get(); }
		virtual const NodeCallback* getCullCallback() const { return _cullCallback.get(); }

		/** 添加Cull回调函数，节点的Cull回调函数不存在时设置它，存在时把它嵌套到已经存在的Cull回调函数。 */
         virtual void addCullCallback(NodeCallback* nc) 
		 {
			 if (nc == NULL) return ;

			 if (_cullCallback.valid()) _cullCallback->addNestedCallback(nc);
			 else setCullCallback(nc);
		 }

 		/** 移除节点的Cull回调函数（即使该函数被嵌套了也适用），找不到该Cull回调函数也不返回错误。 */
        virtual void removeCullCallback(NodeCallback* nc)
		{
			if (nc == NULL) return ; 
            if (!_cullCallback.valid()) return;
			
            if (_cullCallback == nc) setCullCallback(nc->getNestedCallback());        // replace the callback by the nested one
            else _cullCallback->removeNestedCallback(nc);          
        }


        /** Set/get the view frustum/small feature culling of this node to be active or inactive.*/
        virtual void setCullingActive(bool active);
        virtual bool getCullingActive() const { return _cullingActive; }

        /** Get the number of Children of this node which have culling disabled.*/
        virtual unsigned int getNumChildrenWithCullingDisabled() const { return _numChildrenWithCullingDisabled; }

        /** Return true if this node can be culled by view frustum, occlusion or small feature culling during the cull traversal.
          * Note, returns true only if no children have culling disabled, and the local _cullingActive flag is true.*/
        virtual bool isCullingActive() const { return _numChildrenWithCullingDisabled==0 && _cullingActive && getBound().valid(); }

        /** 获取是或含有OccluderNode的子节点的个数。*/
        virtual unsigned int getNumChildrenWithOccluderNodes() const { return _numChildrenWithOccluderNodes; }

      
        /** 是否包含遮光板节点。如果该节点是OccluderNode或该节点的子图是OccluderNode返回true。*/
        virtual bool containsOccluderNodes() const;




		// 7、与节点Mask有关的内容

		/** 设置/获取节点Mask*/
		virtual void setNodeMask(IVBF_SGNode::NodeMask nm) { _nodeMask = nm; }
		virtual IVBF_SGNode::NodeMask getNodeMask() const { return _nodeMask; }



		// 8、与状态集合有关的内容


		/** 设置/获取节点的状态集合。*/
		virtual void setStateSet(osg::StateSet* stateset);
		virtual osg::StateSet* getOrCreateStateSet();
		virtual osg::StateSet* getStateSet() { return _stateset.get(); }
		virtual const osg::StateSet* getStateSet() const { return _stateset.get(); }



		// 9、与节点描述信息有关的内容


 

		/** 设置获取描述节点的字符串列表。*/
		void setDescriptions(const IVBF_SGNode::DescriptionList& descriptions);
		IVBF_SGNode::DescriptionList& getDescriptions();
		const IVBF_SGNode::DescriptionList& getDescriptions() const;


		/** 获取描述节点的第i个字符串列表。*/
		const std::string& getDescription(unsigned int i) const;
		std::string& getDescription(unsigned int i);

		/** 获取描述节点的字符串列表的个数。*/
		unsigned int getNumDescriptions() const;

		/** 添加一个描述节点的字符串列表。*/
		void addDescription(const std::string& desc);


		// 10、与节点包围球/盒有关的内容


		/** 设置/获取初始的包围体。*/
		virtual void setInitialBound(const osg::BoundingSphere& bsphere) { _initialBound = bsphere; dirtyBound(); }
		virtual const BoundingSphere& getInitialBound() const { return _initialBound; }

		/** 把节点的包围球标记为dirty，以便在下次调用getBound（）函数时强制计算包围球。*/
        virtual void dirtyBound();

        /** 获取节点的包围球，当包围球标记为dirty时，先计算包围球。*/
        virtual const BoundingSphere& getBound() const
        {
            if(!_boundingSphereComputed)
            {
                _boundingSphere = _initialBound;
                if (_computeBoundCallback.valid())  _boundingSphere.expandBy(_computeBoundCallback->computeBound(*this));
                else                                _boundingSphere.expandBy(computeBound());
                    
                _boundingSphereComputed = true;
            }
            return _boundingSphere;
        }


        /** 计算包围球（包含节点的geometry或children）。当通过dirtyBound()把包围球标记为dirty时，该方法被getBound()自动调用。*/
        virtual BoundingSphere computeBound() const;


		/** 设置/获取计算包围体的回调函数，该函数覆盖缺省的计算包围体的方法*/
		virtual void setComputeBoundingSphereCallback(IVBF_SGNode::ComputeBoundingSphereCallback* callback) { _computeBoundCallback = callback; }
		virtual IVBF_SGNode::ComputeBoundingSphereCallback* getComputeBoundingSphereCallback() { return _computeBoundCallback.get(); }
		virtual const IVBF_SGNode::ComputeBoundingSphereCallback* getComputeBoundingSphereCallback() const { return _computeBoundCallback.get(); }



		// 11、重载父类中的方法

        /** 设置是否使用mutex确保ref()和unref()的线程安全性。*/
        virtual void setThreadSafeRefUnref(bool threadSafe);

        /** 改变每个上下文GLObject buffers 为指定大小。 */
        virtual void resizeGLObjectBuffers(unsigned int /*maxSize*/);

        /** 释放OpenGL对象。*/
        virtual void releaseGLObjects(osg::State* = 0) const;


    protected:

        /** 保护类型的析构函数使得IVBF_SGNodeImpl不能被直接删除，而只能通过引用计数，防止IVBF_SGNodeImpl还在被引用时删除。
			同时还意味着IVBF_SGNodeImpl不能在stack上创建（无法编译），强制在heap上创建。如IVBF_SGNodeImpl* node = new IVBF_SGNodeImpl().*/
        virtual ~IVBF_SGNodeImpl();



		// 包围球
        BoundingSphere                          _initialBound;             // 初始包围球
        ref_ptr<IVBF_SGNode::ComputeBoundingSphereCallback>  _computeBoundCallback;     // 包围球计算回调函数
        mutable BoundingSphere                  _boundingSphere;           // 包围球
        mutable bool                            _boundingSphereComputed;   // 包围球计算标志


		// 父节点

        virtual void addParent(osg::IVBF_SGNodeGroup* node);
        virtual void removeParent(osg::IVBF_SGNodeGroup* node);

        osg::CVBF_NodeParentList _parents;                     // 父节点列表（支持多个父节点）


        friend class osg::IVBF_SGNodeGroup;
        friend class osg::Drawable;
        friend class osg::StateSet;





		// 各类回调
        ref_ptr<NodeCallback> _updateCallback;  // 更新回调函数
        unsigned int _numChildrenRequiringUpdateTraversal;
        virtual void setNumChildrenRequiringUpdateTraversal(unsigned int num);

        ref_ptr<NodeCallback> _eventCallback;  // 事件回调函数
        unsigned int _numChildrenRequiringEventTraversal;
        virtual void setNumChildrenRequiringEventTraversal(unsigned int num);

        ref_ptr<NodeCallback> _cullCallback;   // 裁剪回调函数

        bool _cullingActive;
        unsigned int _numChildrenWithCullingDisabled;        
        virtual void setNumChildrenWithCullingDisabled(unsigned int num);

		unsigned int _numChildrenWithOccluderNodes;        
        virtual void setNumChildrenWithOccluderNodes(unsigned int num);



        IVBF_SGNode::NodeMask _nodeMask;         //（32位无符号整形），用于限定节点是否能被指定的节点访问器访问。缺省值为0xffffffff。
                                    // 节点是否能被访问器访问取决于：TraversalMask & ( OverrideMask | NodeMask )

        ref_ptr<StateSet> _stateset;// 状态集合

};



}
#include "IVBF_SGNodeImpl.inl"

#endif
