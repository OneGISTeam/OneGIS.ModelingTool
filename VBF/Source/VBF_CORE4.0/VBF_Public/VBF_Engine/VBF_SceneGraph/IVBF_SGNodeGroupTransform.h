#ifndef IVBF_SG_NODE_GROUP_TRANSFORM_H
#define IVBF_SG_NODE_GROUP_TRANSFORM_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>

namespace osg {

// 用于坐标系变换
// 世界坐标系是能够描述所有物体的坐标系（描述某物体不一定方便），也可以理解为绝对坐标系
// 物体坐标系是针对某一物体而建立的坐标系（描述该物体很方便），也可以理解为局部坐标系
// 相机坐标系是描述相机及视景体的坐标系，也可以理解为一个物体坐标系
// 采用左手坐标系（这点与OpenGL一致），X正方向向右，Y方向朝里，Z方向朝上。OpenGL是Y方向朝上，Z方向朝外


class IVBF_SGNodeGroupTransform : public IVBF_SGNodeGroup
{
public:

	enum ReferenceFrame
	{
		RELATIVE_RF,
		ABSOLUTE_RF,
		ABSOLUTE_RF_INHERIT_VIEWPOINT
	};

	IVBF_SGNodeGroupTransform(){}
	IVBF_SGNodeGroupTransform(const IVBF_SGNodeGroupTransform& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}

	explicit IVBF_SGNodeGroupTransform(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}

    virtual IVBF_SGNodeGroupTransformMatrix* asMatrixTransform() { return 0; }
    virtual const IVBF_SGNodeGroupTransformMatrix* asMatrixTransform() const { return 0; }
    virtual IVBF_SGNodeGroupTransformPositionAttitude* asPositionAttitudeTransform() { return 0; }
    virtual const IVBF_SGNodeGroupTransformPositionAttitude* asPositionAttitudeTransform() const { return 0; }


    virtual void setReferenceFrame(ReferenceFrame rf)=0;       
    virtual ReferenceFrame getReferenceFrame() const =0;

	// 局部坐标系（物体坐标系）到世界坐标系的变换矩阵
    virtual bool computeLocalToWorldMatrix(Matrix& matrix,NodeVisitor*) const =0;
  
	// 世界坐标系到局部坐标系的变换矩阵
    virtual bool computeWorldToLocalMatrix(Matrix& matrix,NodeVisitor*) const =0;

};


OSG_EXPORT IVBF_SGNodeGroupTransform* VBF_CreateSGNodeGroupTransform() ;
OSG_EXPORT IVBF_SGNodeGroupTransform* VBF_CreateSGNodeGroupTransform(const IVBF_SGNodeGroupTransform& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;
}
#endif
