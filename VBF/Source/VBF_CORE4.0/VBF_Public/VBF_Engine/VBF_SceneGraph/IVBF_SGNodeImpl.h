#ifndef OSG_NODE
#define OSG_NODE 1

//#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>


//#include <string>
//#include <vector>


#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h>



namespace osg 
{

/** META_Node�궨���˱�׼��clone��isSameKindAs��className��accept�ȷ����� ����IVBF_SGNodeImpl������ʵ�ִ��麯����*/
#define META_Node(library,name) \
        virtual osg::CVBF_Object* cloneType() const { return new name (); } \
        virtual osg::CVBF_Object* clone(const osg::CopyOp& copyop) const { return new name (*this,copyop); } \
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
        virtual const char* className() const { return #name; } \
        virtual const char* libraryName() const { return #library; } \
        virtual void accept(osg::NodeVisitor& nv) { if (nv.validNodeMask(*this)) { nv.pushOntoNodePath(this); nv.apply(*this); nv.popFromNodePath(); } } \
        



/** ����ͼ�ڵ�Ļ��࣬�ṩ�˹��õĽڵ�����ӿڡ�*/
template<class T>
class IVBF_SGNodeImpl : public T
{
    public:
  		// 1���빹�캯���йص�����
      
		/** parent listΪ��, ����Ϊ""��bounding sphere dirty flagΪtrue.*/
        IVBF_SGNodeImpl();

        /** �������캯��, ͨ��CopyOp���ƶ�̬���ݵ�shallow vs deep������*/
        IVBF_SGNodeImpl(const IVBF_SGNodeImpl&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		// 2���������Ϣ�йص�����

        /** ����һ��ͬ���ͣ�IVBF_SGNodeImpl����ָ�룬�뱾������������û�й�ϵ*/
//        virtual CVBF_Object* cloneType() const { return new IVBF_SGNodeImpl<IVBF_SGNode>(); }

        /** ��¡һ�������� ������������ͬ����CopyOp��������*/
//        virtual CVBF_Object* clone(const CopyOp& copyop) const { return new IVBF_SGNodeImpl<IVBF_SGNode>(*this,copyop); }

        /** ���this��obj��ͬ����󷵻�true��*/
 //       virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const IVBF_SGNode*>(obj)!=NULL; }

        /** �������ڵĿ�����֡�*/
        virtual const char* libraryName() const { return "osg"; }

        /** ����������֡�*/
        virtual const char* className() const { return "Node"; }



		// 3������ת����!!!ȥ������ʹ��ʱ��Ϊdynamic_cast<XXX*>(this)��ʽ���������ܣ����Ͷ��٣���������ṹ����

 


		// 4�������������ص�����

         virtual void accept(NodeVisitor& nv);

        /** ���ϱ��� : ���ø��׵�accept���� with NodeVisitor.*/
        virtual void ascend(NodeVisitor& nv);

        /** ���±��� : ���ú��ӵ�accept���� with NodeVisitor.*/
        virtual void traverse(NodeVisitor& /*nv*/) {}       



		// 5���븸�ӹ�ϵ�йص�����


        /** ��ȡ�ڵ�ĸ��ڵ��б� */
        virtual const osg::CVBF_NodeParentList& getParents() const { return _parents; }

        /** ��ȡ���ڵ��б�Ŀ�����ʹ�ÿ������Է�ֹ���ڵ��б����ġ�*/
        virtual osg::CVBF_NodeParentList getParents() { return _parents; }

		/** ��ȡ��i�����ڵ㡣 */
		virtual IVBF_SGNodeGroup* getParent(unsigned int i)  { return _parents[i]; }
		virtual const IVBF_SGNodeGroup* getParent(unsigned int i) const  { return _parents[i]; }

        /**��ȡ���ڵ�ĸ�����*/
        virtual unsigned int getNumParents() const { return static_cast<unsigned int>(_parents.size()); }

        /** ��ȡ���ڵ�·�����б����ڵ�·�������ж��������ѡ����IVBF_SGNodeImpl* haltTraversalAtNode������ָ���Ľڵ㴦ֹͣ������*/
        virtual osg::NodePathList getParentalNodePaths(osg::IVBF_SGNode* haltTraversalAtNode=0) const;
 
		// 5.1�������任·���йص�����

        /** ��ȡ�ѽڵ�Ӿֲ�����ϵ�任����������ϵ�ľ����б���ѡ����IVBF_SGNodeImpl* haltTraversalAtNode������ָ���Ľڵ㴦ֹͣ������*/
        osg::MatrixList getWorldMatrices(const osg::IVBF_SGNode* haltTraversalAtNode=0) const;
        


		// 6����ڵ�ص������йص�����

		// 6.1 ���»ص�

		/** ����/��ȡUpdate�ص��������ڱ������µ�ʱ��ص���*/
		virtual void setUpdateCallback(NodeCallback* nc);
		virtual NodeCallback* getUpdateCallback() { return _updateCallback.get(); }
		virtual const NodeCallback* getUpdateCallback() const { return _updateCallback.get(); }

		/** ���Update�ص��������ڵ��Update�ص�����������ʱ������������ʱ����Ƕ�׵��Ѿ����ڵ�Update�ص������� */
        virtual void addUpdateCallback(NodeCallback* nc) 
		{
            if (nc == NULL) return;
			if (_updateCallback.valid()) _updateCallback->addNestedCallback(nc);
			else setUpdateCallback(nc);
        }

  		/** �Ƴ��ڵ��Update�ص���������ʹ�ú�����Ƕ����Ҳ���ã����Ҳ�����Update�ص�����Ҳ�����ش��� */
		virtual void removeUpdateCallback(NodeCallback* nc) 
		{
			if(nc == NULL) return ;
			if (!_updateCallback.valid()) return;
		
			if (_updateCallback == nc) setUpdateCallback(nc->getNestedCallback());        // replace the callback by the nested one
			else _updateCallback->removeNestedCallback(nc);			
		}

        /** ��ȡ��Ҫ���±������ӽڵ�ĸ�������Щ�ӽڵ������Update Callback�����ӽڵ������Update Callback��*/
        virtual unsigned int getNumChildrenRequiringUpdateTraversal() const { return _numChildrenRequiringUpdateTraversal; }


		// 6.2 �¼��ص�

		/** ����/��ȡevent�ص��������ڱ���event��ʱ��ص���*/
		virtual void setEventCallback(NodeCallback* nc);
		virtual NodeCallback* getEventCallback() { return _eventCallback.get(); }
		virtual const NodeCallback* getEventCallback() const { return _eventCallback.get(); }

		/** ���Event�ص��������ڵ��Event�ص�����������ʱ������������ʱ����Ƕ�׵��Ѿ����ڵ�Event�ص������� */
 		virtual void addEventCallback(NodeCallback* nc) 
		{
			if (nc == NULL) return ;
			
			if (_eventCallback.valid()) _eventCallback->addNestedCallback(nc);
            else setEventCallback(nc);           
        }

  		/** �Ƴ��ڵ��Event�ص���������ʹ�ú�����Ƕ����Ҳ���ã����Ҳ�����Event�ص�����Ҳ�����ش��� */
		virtual void removeEventCallback(NodeCallback* nc) 
		{
			if (nc == NULL) return; 
			if (!_eventCallback.valid()) return;

			if (_eventCallback == nc) setEventCallback(nc->getNestedCallback());        // replace the callback by the nested one
			else _eventCallback->removeNestedCallback(nc);			
		}

		/** ��ȡ��ҪEvent�������ӽڵ�ĸ�������Щ�ӽڵ������Event Callback�����ӽڵ������Event Callback��*/
		virtual unsigned int getNumChildrenRequiringEventTraversal() const { return _numChildrenRequiringEventTraversal; }




		// 6.3 �ü��ص�

        /** ����/��ȡCull�ص��������ڱ����ü���ʱ��ص���*/
		virtual void setCullCallback(NodeCallback* nc) { _cullCallback = nc; }
		virtual NodeCallback* getCullCallback() { return _cullCallback.get(); }
		virtual const NodeCallback* getCullCallback() const { return _cullCallback.get(); }

		/** ���Cull�ص��������ڵ��Cull�ص�����������ʱ������������ʱ����Ƕ�׵��Ѿ����ڵ�Cull�ص������� */
         virtual void addCullCallback(NodeCallback* nc) 
		 {
			 if (nc == NULL) return ;

			 if (_cullCallback.valid()) _cullCallback->addNestedCallback(nc);
			 else setCullCallback(nc);
		 }

 		/** �Ƴ��ڵ��Cull�ص���������ʹ�ú�����Ƕ����Ҳ���ã����Ҳ�����Cull�ص�����Ҳ�����ش��� */
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

        /** ��ȡ�ǻ���OccluderNode���ӽڵ�ĸ�����*/
        virtual unsigned int getNumChildrenWithOccluderNodes() const { return _numChildrenWithOccluderNodes; }

      
        /** �Ƿ�����ڹ��ڵ㡣����ýڵ���OccluderNode��ýڵ����ͼ��OccluderNode����true��*/
        virtual bool containsOccluderNodes() const;




		// 7����ڵ�Mask�йص�����

		/** ����/��ȡ�ڵ�Mask*/
		virtual void setNodeMask(IVBF_SGNode::NodeMask nm) { _nodeMask = nm; }
		virtual IVBF_SGNode::NodeMask getNodeMask() const { return _nodeMask; }



		// 8����״̬�����йص�����


		/** ����/��ȡ�ڵ��״̬���ϡ�*/
		virtual void setStateSet(osg::StateSet* stateset);
		virtual osg::StateSet* getOrCreateStateSet();
		virtual osg::StateSet* getStateSet() { return _stateset.get(); }
		virtual const osg::StateSet* getStateSet() const { return _stateset.get(); }



		// 9����ڵ�������Ϣ�йص�����


 

		/** ���û�ȡ�����ڵ���ַ����б�*/
		void setDescriptions(const IVBF_SGNode::DescriptionList& descriptions);
		IVBF_SGNode::DescriptionList& getDescriptions();
		const IVBF_SGNode::DescriptionList& getDescriptions() const;


		/** ��ȡ�����ڵ�ĵ�i���ַ����б�*/
		const std::string& getDescription(unsigned int i) const;
		std::string& getDescription(unsigned int i);

		/** ��ȡ�����ڵ���ַ����б�ĸ�����*/
		unsigned int getNumDescriptions() const;

		/** ���һ�������ڵ���ַ����б�*/
		void addDescription(const std::string& desc);


		// 10����ڵ��Χ��/���йص�����


		/** ����/��ȡ��ʼ�İ�Χ�塣*/
		virtual void setInitialBound(const osg::BoundingSphere& bsphere) { _initialBound = bsphere; dirtyBound(); }
		virtual const BoundingSphere& getInitialBound() const { return _initialBound; }

		/** �ѽڵ�İ�Χ����Ϊdirty���Ա����´ε���getBound��������ʱǿ�Ƽ����Χ��*/
        virtual void dirtyBound();

        /** ��ȡ�ڵ�İ�Χ�򣬵���Χ����Ϊdirtyʱ���ȼ����Χ��*/
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


        /** �����Χ�򣨰����ڵ��geometry��children������ͨ��dirtyBound()�Ѱ�Χ����Ϊdirtyʱ���÷�����getBound()�Զ����á�*/
        virtual BoundingSphere computeBound() const;


		/** ����/��ȡ�����Χ��Ļص��������ú�������ȱʡ�ļ����Χ��ķ���*/
		virtual void setComputeBoundingSphereCallback(IVBF_SGNode::ComputeBoundingSphereCallback* callback) { _computeBoundCallback = callback; }
		virtual IVBF_SGNode::ComputeBoundingSphereCallback* getComputeBoundingSphereCallback() { return _computeBoundCallback.get(); }
		virtual const IVBF_SGNode::ComputeBoundingSphereCallback* getComputeBoundingSphereCallback() const { return _computeBoundCallback.get(); }



		// 11�����ظ����еķ���

        /** �����Ƿ�ʹ��mutexȷ��ref()��unref()���̰߳�ȫ�ԡ�*/
        virtual void setThreadSafeRefUnref(bool threadSafe);

        /** �ı�ÿ��������GLObject buffers Ϊָ����С�� */
        virtual void resizeGLObjectBuffers(unsigned int /*maxSize*/);

        /** �ͷ�OpenGL����*/
        virtual void releaseGLObjects(osg::State* = 0) const;


    protected:

        /** �������͵���������ʹ��IVBF_SGNodeImpl���ܱ�ֱ��ɾ������ֻ��ͨ�����ü�������ֹIVBF_SGNodeImpl���ڱ�����ʱɾ����
			ͬʱ����ζ��IVBF_SGNodeImpl������stack�ϴ������޷����룩��ǿ����heap�ϴ�������IVBF_SGNodeImpl* node = new IVBF_SGNodeImpl().*/
        virtual ~IVBF_SGNodeImpl();



		// ��Χ��
        BoundingSphere                          _initialBound;             // ��ʼ��Χ��
        ref_ptr<IVBF_SGNode::ComputeBoundingSphereCallback>  _computeBoundCallback;     // ��Χ�����ص�����
        mutable BoundingSphere                  _boundingSphere;           // ��Χ��
        mutable bool                            _boundingSphereComputed;   // ��Χ������־


		// ���ڵ�

        virtual void addParent(osg::IVBF_SGNodeGroup* node);
        virtual void removeParent(osg::IVBF_SGNodeGroup* node);

        osg::CVBF_NodeParentList _parents;                     // ���ڵ��б�֧�ֶ�����ڵ㣩


        friend class osg::IVBF_SGNodeGroup;
        friend class osg::Drawable;
        friend class osg::StateSet;





		// ����ص�
        ref_ptr<NodeCallback> _updateCallback;  // ���»ص�����
        unsigned int _numChildrenRequiringUpdateTraversal;
        virtual void setNumChildrenRequiringUpdateTraversal(unsigned int num);

        ref_ptr<NodeCallback> _eventCallback;  // �¼��ص�����
        unsigned int _numChildrenRequiringEventTraversal;
        virtual void setNumChildrenRequiringEventTraversal(unsigned int num);

        ref_ptr<NodeCallback> _cullCallback;   // �ü��ص�����

        bool _cullingActive;
        unsigned int _numChildrenWithCullingDisabled;        
        virtual void setNumChildrenWithCullingDisabled(unsigned int num);

		unsigned int _numChildrenWithOccluderNodes;        
        virtual void setNumChildrenWithOccluderNodes(unsigned int num);



        IVBF_SGNode::NodeMask _nodeMask;         //��32λ�޷������Σ��������޶��ڵ��Ƿ��ܱ�ָ���Ľڵ���������ʡ�ȱʡֵΪ0xffffffff��
                                    // �ڵ��Ƿ��ܱ�����������ȡ���ڣ�TraversalMask & ( OverrideMask | NodeMask )

        ref_ptr<StateSet> _stateset;// ״̬����

};



}
#include "IVBF_SGNodeImpl.inl"

#endif
