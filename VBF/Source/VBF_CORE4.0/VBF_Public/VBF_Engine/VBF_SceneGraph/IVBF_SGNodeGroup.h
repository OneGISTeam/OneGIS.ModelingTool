#ifndef IVBF_SG_NODE_GROUP_H
#define IVBF_SG_NODE_GROUP_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
namespace osg {

typedef std::vector< ref_ptr<IVBF_SGNode> > NodeList;

class IVBF_SGNodeGroup : public IVBF_SGNode
{
public:
	IVBF_SGNodeGroup(){}
	IVBF_SGNodeGroup(const IVBF_SGNodeGroup& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNode(cs,copyop) {}
	explicit IVBF_SGNodeGroup(bool threadSafeRefUnref):IVBF_SGNode(threadSafeRefUnref){}

	// 3、类型转化，!!!去掉，在使用时改为dynamic_cast<XXX*>(this)形式，降低性能（降低多少？）但代码结构清晰
    virtual IVBF_SGNodeGroup* asGroup() { return this; }
    virtual const IVBF_SGNodeGroup* asGroup() const { return this; }

		// 5、与父子关系有关的内容
	virtual bool addChild( IVBF_SGNode *child )=0;
	virtual bool insertChild( unsigned int index, IVBF_SGNode *child ) = 0;
	virtual bool removeChild( IVBF_SGNode *child )=0; //说明：不要重载该函数, 仅需要重载removeChildren(,)。

	virtual bool removeChild( unsigned int pos, unsigned int numChildrenToRemove=1 ) = 0;
	virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove) = 0;

	virtual bool replaceChild( IVBF_SGNode *origChild, IVBF_SGNode* newChild ) = 0;

	virtual unsigned int getNumChildren() const = 0;
	virtual bool setChild( unsigned  int i, IVBF_SGNode* node ) = 0;

	virtual IVBF_SGNode* getChild( unsigned  int i )  = 0;
	virtual const IVBF_SGNode* getChild( unsigned  int i ) const  = 0;


	/** 是否包含指定节点，包含则返回true。 */
	virtual bool containsNode( const IVBF_SGNode* node ) const = 0;
	

    /** 获取子节点的位置索引号，如果找到返回0到_children.size()-1之间的数值, 找不到返回_children.size()。*/
    virtual unsigned int getChildIndex( const IVBF_SGNode* node ) const = 0;
        

};

OSG_EXPORT IVBF_SGNodeGroup* VBF_CreateSGNodeGroup() ;
OSG_EXPORT IVBF_SGNodeGroup* VBF_CreateSGNodeGroup(const IVBF_SGNodeGroup& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;
OSG_EXPORT const std::type_info& VBF_GetTypeIDGroup();
}
#endif
