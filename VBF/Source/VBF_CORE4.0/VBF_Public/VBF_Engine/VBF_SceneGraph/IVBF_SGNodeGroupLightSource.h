#ifndef IVBF_SG_NODE_GROUP_LIGHT_SOURCE_H
#define IVBF_SG_NODE_GROUP_LIGHT_SOURCE_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLight.h>

namespace osg {

class IVBF_SGNodeGroupLightSource : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupLightSource(){}
	IVBF_SGNodeGroupLightSource(const IVBF_SGNodeGroupLightSource& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	explicit IVBF_SGNodeGroupLightSource(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}

	enum ReferenceFrame
	{
		RELATIVE_RF,
		ABSOLUTE_RF
	};

	virtual void setReferenceFrame(ReferenceFrame rf)=0;
	virtual ReferenceFrame getReferenceFrame() const =0;

    // 设置/获取灯光
    virtual void setLight(Light* light)=0;
	virtual Light* getLight()=0;
	virtual const Light* getLight() const=0;
};

OSG_EXPORT IVBF_SGNodeGroupLightSource* VBF_CreateSGNodeGroupLightSource() ;
OSG_EXPORT IVBF_SGNodeGroupLightSource* VBF_CreateSGNodeGroupLightSource(const IVBF_SGNodeGroupLightSource& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;

}
#endif
