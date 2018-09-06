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

        // 回调方法，当遍历节点时被NodeVisitor调用
        virtual void operator()(IVBF_SGNode* node, NodeVisitor* nv)
        { 
			//!!! 在此加入处理代码


			//  注意：回调类要负责场景图的遍历，必须调用traverse(node,nv)以确保场景图子树（及关联的callbacks）被遍历
            traverse(node,nv);
        }
        
 		// 调用嵌套的回调，然后遍历场景图
        void traverse(IVBF_SGNode* node,NodeVisitor* nv);
        
		// 设置嵌套回调
        void setNestedCallback(NodeCallback* nc) { _nestedCallback = nc; }
        NodeCallback* getNestedCallback() { return _nestedCallback.get(); }
        const NodeCallback* getNestedCallback() const { return _nestedCallback.get(); }
        		
        inline void addNestedCallback(NodeCallback* nc);	// 添加嵌套回调       
        inline void removeNestedCallback(NodeCallback* nc);	// 移除嵌套回调 
   
        
    public:

        ref_ptr<NodeCallback> _nestedCallback; // 嵌套回调
        
    protected:   
        virtual ~NodeCallback() {}// IE可能错误
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

