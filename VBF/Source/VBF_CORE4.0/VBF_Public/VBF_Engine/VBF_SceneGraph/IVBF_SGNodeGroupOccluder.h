#ifndef IVBF_SG_NODE_GROUP_OCCLUDER_H
#define IVBF_SG_NODE_GROUP_OCCLUDER_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/ConvexPlanarOccluder>

namespace osg {

// �ڵ��ü��ڵ㣺���������ڵ��壬�ü������ڵ������塣

class IVBF_SGNodeGroupOccluder : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupOccluder(){}
	IVBF_SGNodeGroupOccluder(const IVBF_SGNodeGroupOccluder& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	explicit IVBF_SGNodeGroupOccluder(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}

    // ����/��ȡ͹ƽ���ڵ���          
    virtual void setOccluder(ConvexPlanarOccluder* occluder)  = 0;
    virtual ConvexPlanarOccluder* getOccluder()  = 0;
    virtual const ConvexPlanarOccluder* getOccluder() const  = 0;
};
}
#endif
