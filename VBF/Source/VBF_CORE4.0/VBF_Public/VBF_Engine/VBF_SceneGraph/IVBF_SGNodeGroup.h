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

	// 3������ת����!!!ȥ������ʹ��ʱ��Ϊdynamic_cast<XXX*>(this)��ʽ���������ܣ����Ͷ��٣���������ṹ����
    virtual IVBF_SGNodeGroup* asGroup() { return this; }
    virtual const IVBF_SGNodeGroup* asGroup() const { return this; }

		// 5���븸�ӹ�ϵ�йص�����
	virtual bool addChild( IVBF_SGNode *child )=0;
	virtual bool insertChild( unsigned int index, IVBF_SGNode *child ) = 0;
	virtual bool removeChild( IVBF_SGNode *child )=0; //˵������Ҫ���ظú���, ����Ҫ����removeChildren(,)��

	virtual bool removeChild( unsigned int pos, unsigned int numChildrenToRemove=1 ) = 0;
	virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove) = 0;

	virtual bool replaceChild( IVBF_SGNode *origChild, IVBF_SGNode* newChild ) = 0;

	virtual unsigned int getNumChildren() const = 0;
	virtual bool setChild( unsigned  int i, IVBF_SGNode* node ) = 0;

	virtual IVBF_SGNode* getChild( unsigned  int i )  = 0;
	virtual const IVBF_SGNode* getChild( unsigned  int i ) const  = 0;


	/** �Ƿ����ָ���ڵ㣬�����򷵻�true�� */
	virtual bool containsNode( const IVBF_SGNode* node ) const = 0;
	

    /** ��ȡ�ӽڵ��λ�������ţ�����ҵ�����0��_children.size()-1֮�����ֵ, �Ҳ�������_children.size()��*/
    virtual unsigned int getChildIndex( const IVBF_SGNode* node ) const = 0;
        

};

OSG_EXPORT IVBF_SGNodeGroup* VBF_CreateSGNodeGroup() ;
OSG_EXPORT IVBF_SGNodeGroup* VBF_CreateSGNodeGroup(const IVBF_SGNodeGroup& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;
OSG_EXPORT const std::type_info& VBF_GetTypeIDGroup();
}
#endif
