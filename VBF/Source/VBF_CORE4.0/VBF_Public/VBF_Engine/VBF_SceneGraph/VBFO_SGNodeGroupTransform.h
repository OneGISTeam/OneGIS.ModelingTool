#ifndef VBF_SG_NODE_GROUP_TRANSFORM_H
#define VBF_SG_NODE_GROUP_TRANSFORM_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransform.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformImpl.h>

namespace osg {


class Transform : public IVBF_SGNodeGroupTransformImpl<IVBF_SGNodeGroupTransform>
{
public:
    Transform()
	{
	}
    Transform(const Transform& geode,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroupTransformImpl<IVBF_SGNodeGroupTransform>(geode,copyop)
	{
	}
	virtual CVBF_Object* cloneType() const { return new Transform(); }
    virtual CVBF_Object* clone(const CopyOp& copyop) const { return new Transform(*this,copyop); }
    virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const IVBF_SGNodeGroupTransform*>(obj)!=NULL; }
    virtual const char* className() const { return "Transform"; }
};


}
#endif
