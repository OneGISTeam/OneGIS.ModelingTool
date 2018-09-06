#ifndef OSG_GROUP
#define OSG_GROUP 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
//#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>

namespace osg {



/** 场景图组节点，拥有子节点。*/

template<class T>
class IVBF_SGNodeGroupImpl : public IVBF_SGNodeImpl<T>
{
private:
    typedef osg::IVBF_SGNodeImpl<T> _Base;

    public :

  		// 1、与构造函数有关的内容

        IVBF_SGNodeGroupImpl();
        
        /** 拷贝构造函数, 通过CopyOp控制动态数据的shallow vs deep拷贝。 */
        IVBF_SGNodeGroupImpl(const IVBF_SGNodeGroupImpl&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);


		// 2、与基本信息有关的内容

//		META_Node(osg, IVBF_SGNodeGroupImpl<T>);
//        virtual CVBF_Object* cloneType() const { return new IVBF_SGNodeGroupImpl<T>(); }
//        virtual CVBF_Object* clone(const CopyOp& copyop) const { return new IVBF_SGNodeGroupImpl<T>(*this,copyop); }
        virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const T*>(obj)!=NULL; }
        virtual const char* className() const { return "IVBF_SGNodeGroupImpl"; }





		// 4、与遍历操作相关的内容

        virtual void traverse(NodeVisitor& nv);


		// 5、与父子关系有关的内容


        /** 添加子节点。如果子节点非空并未被该组节点包含则增加该子节点的引用计数、把它加入到子节点
		  * 列表、设置包围球dirty标志并返回true，否则返回false。不能加入Scene node
		  */
        virtual bool addChild( IVBF_SGNode *child );

        /** 在指定位置插入子节点。新子节点插入到指定位置节点的前面。该操作不移除节点。 */
        virtual bool insertChild( unsigned int index, IVBF_SGNode *child );

        /** 移除节点。如果节点被该组节点包含，则从子节点列表中移除、减少引用计数、设置包围球dirty标志并返回true。
          * 如果节点找不到返回false，不改变节点的引用计数。
          * 说明：不要重载该函数, 仅需要重载removeChildren(,)。
        */
        virtual bool removeChild( IVBF_SGNode *child )
        {
            unsigned int pos = getChildIndex(child);
            if (pos<_children.size()) return removeChildren(pos,1);
            else return false;
        }

        /** 移除指定位置的节点。*/
        virtual bool removeChild( unsigned int pos, unsigned int numChildrenToRemove=1 )
        {
            if (pos<_children.size()) return removeChildren(pos,numChildrenToRemove);
            else return false;
        }

        /** 移除指定位置的节点。
          * 说明：必须被Group的子类重载 which add per child attributes.*/
        virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove);

        /** Replace specified IVBF_SGNode with another IVBF_SGNode.
          * Equivalent to setChild(getChildIndex(orignChild),node)
          * See docs for setChild for further details on implementation.
          */
        virtual bool replaceChild( IVBF_SGNode *origChild, IVBF_SGNode* newChild );

        /** Return the number of children nodes. */
        virtual unsigned int getNumChildren() const { return static_cast<unsigned int>(_children.size()); }

        /** 在指定位置设置子节点。设置正确返回true，失败返回false(node==NULL或i超界)。
          * 设置正确时: 减少原来节点的引用计数、增加新节点的引用计数、设置包围球dirty标志。
          * 如果原来节点找不到则返回false，并不加入新节点。如果新节点为NULL返回false 并不移除原来的节点
          * 如果新节点是Scene node也返回false。
        */
        virtual bool setChild( unsigned  int i, IVBF_SGNode* node );

		/** 获取指定位置出的子节点（i必须是有效值） */
		virtual IVBF_SGNode* getChild( unsigned  int i ) { return _children[i].get(); }
		virtual const IVBF_SGNode* getChild( unsigned  int i ) const { return _children[i].get(); }

		/** 是否包含指定节点，包含则返回true。 */
		virtual bool containsNode( const IVBF_SGNode* node ) const
		{         
			for (NodeList::const_iterator itr=_children.begin(); itr!=_children.end();  ++itr)
			{
				if (itr->get()==node) return true;
			}
			return false;
		}

        /** 获取子节点的位置索引号，如果找到返回0到_children.size()-1之间的数值, 找不到返回_children.size()。*/
        virtual unsigned int getChildIndex( const IVBF_SGNode* node ) const
        {
            for (unsigned int childNum=0;childNum<_children.size();++childNum)
            {
                if (_children[childNum]==node) return childNum;
            }
            return static_cast<unsigned int>(_children.size()); // node not found.
        }



		// 6、重载父类中的方法


        /** 设置是否使用mutex确保ref()和unref()的线程安全性。*/
        virtual void setThreadSafeRefUnref(bool threadSafe);

        /** 改变每个上下文GLObject buffers 为指定大小。 */
        virtual void resizeGLObjectBuffers(unsigned int maxSize);

        /** 释放OpenGL对象。 */
        virtual void releaseGLObjects(osg::State* = 0) const;

		/** 计算包围球 */
        virtual BoundingSphere computeBound() const;
        
    protected:

        virtual ~IVBF_SGNodeGroupImpl();

        virtual void childRemoved(unsigned int /*pos*/, unsigned int /*numChildrenToRemove*/) {}
        virtual void childInserted(unsigned int /*pos*/) {}

        NodeList _children;


};


}
#include "IVBF_SGNodeGroupImpl.inl"
#endif
