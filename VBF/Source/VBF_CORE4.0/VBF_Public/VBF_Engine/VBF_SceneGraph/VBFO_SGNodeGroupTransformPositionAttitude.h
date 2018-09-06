#ifndef OSG_POSITIONATTITUDETRANSFORM
#define OSG_POSITIONATTITUDETRANSFORM 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformImpl.h>
#include <VBF_Engine/VBF_SceneGraph/AnimationPath.h>
#include <Types/Vec3d>
#include <Types/VBF_Quat.h>

namespace osg {

// 位置变换节点
class IVBF_SGNodeGroupTransformPositionAttitude : public IVBF_SGNodeGroupTransform 
{
public:
	IVBF_SGNodeGroupTransformPositionAttitude(){}
	IVBF_SGNodeGroupTransformPositionAttitude(const IVBF_SGNodeGroupTransformPositionAttitude& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroupTransform(cs,copyop) {}
	inline explicit IVBF_SGNodeGroupTransformPositionAttitude(bool threadSafeRefUnref):IVBF_SGNodeGroupTransform(threadSafeRefUnref){}

	// 设置/获取位置
	virtual void setPosition(const Vec3d& pos) =0;
	virtual const Vec3d& getPosition() const =0;

	// 设置/获取姿态（参数为四元数）
	virtual void setAttitude(const Quat& quat) =0;
	virtual const Quat& getAttitude() const =0;

	// 设置/获取缩放
	virtual void setScale(const Vec3d& scale)=0;
	virtual const Vec3d& getScale() const=0;

	// 设置/获取枢纽点（一旦设置，所有变换基于该点而不是原点）
	virtual void setPivotPoint(const Vec3d& pivot)=0;
	virtual const Vec3d& getPivotPoint() const=0;

};

// 位置变换节点

class OSG_EXPORT PositionAttitudeTransform : public IVBF_SGNodeGroupTransformImpl<IVBF_SGNodeGroupTransformPositionAttitude>
{
	typedef IVBF_SGNodeGroupTransformImpl<IVBF_SGNodeGroupTransformPositionAttitude> BaseClass;
    public :
        PositionAttitudeTransform();
        PositionAttitudeTransform(const PositionAttitudeTransform& pat,const CopyOp& copyop=CopyOp::SHALLOW_COPY);
             
        META_Node(osg, PositionAttitudeTransform);

        virtual IVBF_SGNodeGroupTransformPositionAttitude* asPositionAttitudeTransform() { return this; }
        virtual const IVBF_SGNodeGroupTransformPositionAttitude* asPositionAttitudeTransform() const { return this; }

		// 设置/获取位置
        inline void setPosition(const Vec3d& pos) { _position = pos; dirtyBound(); }
        inline const Vec3d& getPosition() const { return _position; }

		// 设置/获取姿态（参数为四元数）
        inline void setAttitude(const Quat& quat) { _attitude = quat; dirtyBound(); }
        inline const Quat& getAttitude() const { return _attitude; }
        
		// 设置/获取缩放
        inline void setScale(const Vec3d& scale) { _scale = scale; dirtyBound(); }
        inline const Vec3d& getScale() const { return _scale; }

        // 设置/获取枢纽点（一旦设置，所有变换基于该点而不是原点）
        inline void setPivotPoint(const Vec3d& pivot) { _pivotPoint = pivot; dirtyBound(); }
        inline const Vec3d& getPivotPoint() const { return _pivotPoint; }
        

        virtual bool computeLocalToWorldMatrix(Matrix& matrix,NodeVisitor* nv) const;
        virtual bool computeWorldToLocalMatrix(Matrix& matrix,NodeVisitor* nv) const;


    protected :
            
        virtual ~PositionAttitudeTransform() {}// IE可能错误

        Vec3d _position;
        Quat _attitude;
        Vec3d _scale;
        Vec3d _pivotPoint;
};

}

#endif
