#ifndef OSG_GROUP
#define OSG_GROUP 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
//#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>

namespace osg {



/** ����ͼ��ڵ㣬ӵ���ӽڵ㡣*/

template<class T>
class IVBF_SGNodeGroupImpl : public IVBF_SGNodeImpl<T>
{
private:
    typedef osg::IVBF_SGNodeImpl<T> _Base;

    public :

  		// 1���빹�캯���йص�����

        IVBF_SGNodeGroupImpl();
        
        /** �������캯��, ͨ��CopyOp���ƶ�̬���ݵ�shallow vs deep������ */
        IVBF_SGNodeGroupImpl(const IVBF_SGNodeGroupImpl&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);


		// 2���������Ϣ�йص�����

//		META_Node(osg, IVBF_SGNodeGroupImpl<T>);
//        virtual CVBF_Object* cloneType() const { return new IVBF_SGNodeGroupImpl<T>(); }
//        virtual CVBF_Object* clone(const CopyOp& copyop) const { return new IVBF_SGNodeGroupImpl<T>(*this,copyop); }
        virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const T*>(obj)!=NULL; }
        virtual const char* className() const { return "IVBF_SGNodeGroupImpl"; }





		// 4�������������ص�����

        virtual void traverse(NodeVisitor& nv);


		// 5���븸�ӹ�ϵ�йص�����


        /** ����ӽڵ㡣����ӽڵ�ǿղ�δ������ڵ���������Ӹ��ӽڵ�����ü������������뵽�ӽڵ�
		  * �б����ð�Χ��dirty��־������true�����򷵻�false�����ܼ���Scene node
		  */
        virtual bool addChild( IVBF_SGNode *child );

        /** ��ָ��λ�ò����ӽڵ㡣���ӽڵ���뵽ָ��λ�ýڵ��ǰ�档�ò������Ƴ��ڵ㡣 */
        virtual bool insertChild( unsigned int index, IVBF_SGNode *child );

        /** �Ƴ��ڵ㡣����ڵ㱻����ڵ����������ӽڵ��б����Ƴ����������ü��������ð�Χ��dirty��־������true��
          * ����ڵ��Ҳ�������false�����ı�ڵ�����ü�����
          * ˵������Ҫ���ظú���, ����Ҫ����removeChildren(,)��
        */
        virtual bool removeChild( IVBF_SGNode *child )
        {
            unsigned int pos = getChildIndex(child);
            if (pos<_children.size()) return removeChildren(pos,1);
            else return false;
        }

        /** �Ƴ�ָ��λ�õĽڵ㡣*/
        virtual bool removeChild( unsigned int pos, unsigned int numChildrenToRemove=1 )
        {
            if (pos<_children.size()) return removeChildren(pos,numChildrenToRemove);
            else return false;
        }

        /** �Ƴ�ָ��λ�õĽڵ㡣
          * ˵�������뱻Group���������� which add per child attributes.*/
        virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove);

        /** Replace specified IVBF_SGNode with another IVBF_SGNode.
          * Equivalent to setChild(getChildIndex(orignChild),node)
          * See docs for setChild for further details on implementation.
          */
        virtual bool replaceChild( IVBF_SGNode *origChild, IVBF_SGNode* newChild );

        /** Return the number of children nodes. */
        virtual unsigned int getNumChildren() const { return static_cast<unsigned int>(_children.size()); }

        /** ��ָ��λ�������ӽڵ㡣������ȷ����true��ʧ�ܷ���false(node==NULL��i����)��
          * ������ȷʱ: ����ԭ���ڵ�����ü����������½ڵ�����ü��������ð�Χ��dirty��־��
          * ���ԭ���ڵ��Ҳ����򷵻�false�����������½ڵ㡣����½ڵ�ΪNULL����false �����Ƴ�ԭ���Ľڵ�
          * ����½ڵ���Scene nodeҲ����false��
        */
        virtual bool setChild( unsigned  int i, IVBF_SGNode* node );

		/** ��ȡָ��λ�ó����ӽڵ㣨i��������Чֵ�� */
		virtual IVBF_SGNode* getChild( unsigned  int i ) { return _children[i].get(); }
		virtual const IVBF_SGNode* getChild( unsigned  int i ) const { return _children[i].get(); }

		/** �Ƿ����ָ���ڵ㣬�����򷵻�true�� */
		virtual bool containsNode( const IVBF_SGNode* node ) const
		{         
			for (NodeList::const_iterator itr=_children.begin(); itr!=_children.end();  ++itr)
			{
				if (itr->get()==node) return true;
			}
			return false;
		}

        /** ��ȡ�ӽڵ��λ�������ţ�����ҵ�����0��_children.size()-1֮�����ֵ, �Ҳ�������_children.size()��*/
        virtual unsigned int getChildIndex( const IVBF_SGNode* node ) const
        {
            for (unsigned int childNum=0;childNum<_children.size();++childNum)
            {
                if (_children[childNum]==node) return childNum;
            }
            return static_cast<unsigned int>(_children.size()); // node not found.
        }



		// 6�����ظ����еķ���


        /** �����Ƿ�ʹ��mutexȷ��ref()��unref()���̰߳�ȫ�ԡ�*/
        virtual void setThreadSafeRefUnref(bool threadSafe);

        /** �ı�ÿ��������GLObject buffers Ϊָ����С�� */
        virtual void resizeGLObjectBuffers(unsigned int maxSize);

        /** �ͷ�OpenGL���� */
        virtual void releaseGLObjects(osg::State* = 0) const;

		/** �����Χ�� */
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
