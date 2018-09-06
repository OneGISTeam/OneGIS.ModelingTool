#ifndef OSG_NODECALLBACK
#define OSG_NODECALLBACK 1

#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Base/ref_ptr>

namespace osg {

class IVBF_SGNode;
class NodeVisitor;

class OSG_EXPORT NodeCallback : public  virtual CVBF_Object 
{
    public :   
        NodeCallback();
        NodeCallback(const NodeCallback& nc,const CopyOp&);

        META_Object(osg,NodeCallback);          

        // �ص��������������ڵ�ʱ��NodeVisitor����
        virtual void operator()(IVBF_SGNode* node, NodeVisitor* nv)
        { 
			//!!! �ڴ˼��봦�����


			//  ע�⣺�ص���Ҫ���𳡾�ͼ�ı������������traverse(node,nv)��ȷ������ͼ��������������callbacks��������
            traverse(node,nv);
        }
        
 		// ����Ƕ�׵Ļص���Ȼ���������ͼ
        void traverse(IVBF_SGNode* node,NodeVisitor* nv);
        
		// ����Ƕ�׻ص�
        void setNestedCallback(NodeCallback* nc) { _nestedCallback = nc; }
        NodeCallback* getNestedCallback() { return _nestedCallback.get(); }
        const NodeCallback* getNestedCallback() const { return _nestedCallback.get(); }
        		
        inline void addNestedCallback(NodeCallback* nc);	// ���Ƕ�׻ص�       
        inline void removeNestedCallback(NodeCallback* nc);	// �Ƴ�Ƕ�׻ص� 
   
        
    public:

        ref_ptr<NodeCallback> _nestedCallback; // Ƕ�׻ص�
        
    protected:   
        virtual ~NodeCallback() {}// IE���ܴ���
};
inline void NodeCallback::addNestedCallback(NodeCallback* nc)
{
	if (nc==NULL) return;

	if (_nestedCallback.valid())
	{
		nc->addNestedCallback(_nestedCallback.get());
		_nestedCallback = nc;
	}
	else _nestedCallback = nc;       
}

inline void NodeCallback::removeNestedCallback(NodeCallback* nc)
{
	if (nc==NULL) return ;

	if (_nestedCallback==nc)
	{
		_nestedCallback = _nestedCallback->getNestedCallback();
	}
	else if (_nestedCallback.valid())
	{
		_nestedCallback->removeNestedCallback(nc);
	}           
}

} // namespace

#endif

