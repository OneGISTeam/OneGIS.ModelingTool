#ifndef IVBF_SG_NODE_GROUP_OCCLUDER_H
#define IVBF_SG_NODE_GROUP_OCCLUDER_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/ConvexPlanarOccluder>

namespace osg {

// 遮挡裁剪节点：可以设置遮挡板，裁剪掉被遮挡的物体。

class IVBF_SGNodeGroupOccluder : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupOccluder(){}
	IVBF_SGNodeGroupOccluder(const IVBF_SGNodeGroupOccluder& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	explicit IVBF_SGNodeGroupOccluder(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}

    // 设置/获取凸平面遮挡板          
    virtual void setOccluder(ConvexPlanarOccluder* occluder)  = 0;
    virtual ConvexPlanarOccluder* getOccluder()  = 0;
    virtual const ConvexPlanarOccluder* getOccluder() const  = 0;
};
}
#endif
