#ifndef IVBF_SG_NODE_GROUP_TRANSFORM_H
#define IVBF_SG_NODE_GROUP_TRANSFORM_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>

namespace osg {

// ��������ϵ�任
// ��������ϵ���ܹ������������������ϵ������ĳ���岻һ�����㣩��Ҳ�������Ϊ��������ϵ
// ��������ϵ�����ĳһ���������������ϵ������������ܷ��㣩��Ҳ�������Ϊ�ֲ�����ϵ
// �������ϵ������������Ӿ��������ϵ��Ҳ�������Ϊһ����������ϵ
// ������������ϵ�������OpenGLһ�£���X���������ң�Y�����Z�����ϡ�OpenGL��Y�����ϣ�Z������


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

	// �ֲ�����ϵ����������ϵ������������ϵ�ı任����
    virtual bool computeLocalToWorldMatrix(Matrix& matrix,NodeVisitor*) const =0;
  
	// ��������ϵ���ֲ�����ϵ�ı任����
    virtual bool computeWorldToLocalMatrix(Matrix& matrix,NodeVisitor*) const =0;

};


OSG_EXPORT IVBF_SGNodeGroupTransform* VBF_CreateSGNodeGroupTransform() ;
OSG_EXPORT IVBF_SGNodeGroupTransform* VBF_CreateSGNodeGroupTransform(const IVBF_SGNodeGroupTransform& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;
}
#endif
