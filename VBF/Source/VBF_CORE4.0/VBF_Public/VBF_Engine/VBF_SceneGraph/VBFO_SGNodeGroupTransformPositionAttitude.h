#ifndef OSG_POSITIONATTITUDETRANSFORM
#define OSG_POSITIONATTITUDETRANSFORM 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformImpl.h>
#include <VBF_Engine/VBF_SceneGraph/AnimationPath.h>
#include <Types/Vec3d>
#include <Types/VBF_Quat.h>

namespace osg {

// λ�ñ任�ڵ�
class IVBF_SGNodeGroupTransformPositionAttitude : public IVBF_SGNodeGroupTransform 
{
public:
	IVBF_SGNodeGroupTransformPositionAttitude(){}
	IVBF_SGNodeGroupTransformPositionAttitude(const IVBF_SGNodeGroupTransformPositionAttitude& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroupTransform(cs,copyop) {}
	inline explicit IVBF_SGNodeGroupTransformPositionAttitude(bool threadSafeRefUnref):IVBF_SGNodeGroupTransform(threadSafeRefUnref){}

	// ����/��ȡλ��
	virtual void setPosition(const Vec3d& pos) =0;
	virtual const Vec3d& getPosition() const =0;

	// ����/��ȡ��̬������Ϊ��Ԫ����
	virtual void setAttitude(const Quat& quat) =0;
	virtual const Quat& getAttitude() const =0;

	// ����/��ȡ����
	virtual void setScale(const Vec3d& scale)=0;
	virtual const Vec3d& getScale() const=0;

	// ����/��ȡ��Ŧ�㣨һ�����ã����б任���ڸõ������ԭ�㣩
	virtual void setPivotPoint(const Vec3d& pivot)=0;
	virtual const Vec3d& getPivotPoint() const=0;

};

// λ�ñ任�ڵ�

class OSG_EXPORT PositionAttitudeTransform : public IVBF_SGNodeGroupTransformImpl<IVBF_SGNodeGroupTransformPositionAttitude>
{
	typedef IVBF_SGNodeGroupTransformImpl<IVBF_SGNodeGroupTransformPositionAttitude> BaseClass;
    public :
        PositionAttitudeTransform();
        PositionAttitudeTransform(const PositionAttitudeTransform& pat,const CopyOp& copyop=CopyOp::SHALLOW_COPY);
             
        META_Node(osg, PositionAttitudeTransform);

        virtual IVBF_SGNodeGroupTransformPositionAttitude* asPositionAttitudeTransform() { return this; }
        virtual const IVBF_SGNodeGroupTransformPositionAttitude* asPositionAttitudeTransform() const { return this; }

		// ����/��ȡλ��
        inline void setPosition(const Vec3d& pos) { _position = pos; dirtyBound(); }
        inline const Vec3d& getPosition() const { return _position; }

		// ����/��ȡ��̬������Ϊ��Ԫ����
        inline void setAttitude(const Quat& quat) { _attitude = quat; dirtyBound(); }
        inline const Quat& getAttitude() const { return _attitude; }
        
		// ����/��ȡ����
        inline void setScale(const Vec3d& scale) { _scale = scale; dirtyBound(); }
        inline const Vec3d& getScale() const { return _scale; }

        // ����/��ȡ��Ŧ�㣨һ�����ã����б任���ڸõ������ԭ�㣩
        inline void setPivotPoint(const Vec3d& pivot) { _pivotPoint = pivot; dirtyBound(); }
        inline const Vec3d& getPivotPoint() const { return _pivotPoint; }
        

        virtual bool computeLocalToWorldMatrix(Matrix& matrix,NodeVisitor* nv) const;
        virtual bool computeWorldToLocalMatrix(Matrix& matrix,NodeVisitor* nv) const;


    protected :
            
        virtual ~PositionAttitudeTransform() {}// IE���ܴ���

        Vec3d _position;
        Quat _attitude;
        Vec3d _scale;
        Vec3d _pivotPoint;
};

}

#endif
