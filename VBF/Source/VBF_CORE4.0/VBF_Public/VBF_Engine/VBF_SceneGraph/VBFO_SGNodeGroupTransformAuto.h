#ifndef OSG_AUTOTRANSFORM
#define OSG_AUTOTRANSFORM 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformImpl.h>
#include <Types/VBF_Quat.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrViewport.h>

namespace osg {

// 自动变换节点：自动缩放和旋转，保持子节点始终与屏幕坐标一致
class IVBF_SGNodeGroupTransformAuto : public IVBF_SGNodeGroupTransform
{
public:
	IVBF_SGNodeGroupTransformAuto(){}
	IVBF_SGNodeGroupTransformAuto(const IVBF_SGNodeGroupTransformAuto& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroupTransform(cs,copyop) {}
	inline explicit IVBF_SGNodeGroupTransformAuto(bool threadSafeRefUnref):IVBF_SGNodeGroupTransform(threadSafeRefUnref){}

	// 设置/获取位置
    virtual void setPosition(const Vec3d& pos)=0;
    virtual const Vec3d& getPosition() const =0;

	// 设置/获取旋转
    virtual void setRotation(const Quat& quat)=0;
    virtual const Quat& getRotation() const =0;

	// 设置/获取缩放比
    virtual void setScale(double scale)=0;
    virtual void setScale(const Vec3d& scale)=0;
    virtual const Vec3d& getScale() const =0;

	// 设置/获取最小缩放比
    virtual void setMinimumScale(double minimumScale)=0;
    virtual double getMinimumScale() const =0;

	// 设置/获取最大缩放比
    virtual void setMaximumScale(double maximumScale) =0;
    virtual double getMaximumScale() const =0;

	// 设置/获取枢纽点
    virtual void setPivotPoint(const Vec3d& pivot) =0;
    virtual const Vec3d& getPivotPoint() const =0;


    virtual void setAutoUpdateEyeMovementTolerance(float tolerance)=0;
    virtual float getAutoUpdateEyeMovementTolerance() const=0;


    enum AutoRotateMode
    {
        NO_ROTATION,		// 无旋转
        ROTATE_TO_SCREEN,	// 朝向屏幕
        ROTATE_TO_CAMERA,	// 朝向相机
        ROTATE_TO_AXIS		// 朝向轴
    };
	// 设置/获取自动旋转模式
    virtual void setAutoRotateMode(AutoRotateMode mode)=0;
    virtual AutoRotateMode getAutoRotateMode() const =0;

	// 获取/设置子节点的旋转轴，仅当_autoRotateMode==ROTATE_TO_AXIS时有效
    virtual void setAxis(const Vec3& axis)=0;
    virtual const Vec3& getAxis() const =0;

	// 设置/获取法线。法线定义了子节点未旋转时的正面方向
    virtual void setNormal(const Vec3& normal)=0;
    virtual const Vec3& getNormal() const =0;

	// 设置/获取是否根据屏幕大小来缩放节点，默认为false。
    virtual void setAutoScaleToScreen(bool autoScaleToScreen) =0;
    virtual bool getAutoScaleToScreen() const =0;

	// 
    virtual void setAutoScaleTransitionWidthRatio(float ratio)=0;
    virtual float getAutoScaleTransitionWidthRatio() const =0;
};
class OSG_EXPORT AutoTransform : public IVBF_SGNodeGroupTransformImpl<IVBF_SGNodeGroupTransformAuto>
{
	typedef IVBF_SGNodeGroupTransformImpl<IVBF_SGNodeGroupTransformAuto> BaseClass;
    public :
        AutoTransform();

        AutoTransform(const AutoTransform& pat,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        virtual osg::CVBF_Object* cloneType() const { return new AutoTransform (); }
        virtual osg::CVBF_Object* clone(const osg::CopyOp& copyop) const { return new AutoTransform (*this,copyop); }
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const AutoTransform *>(obj)!=NULL; }
        virtual const char* className() const { return "AutoTransform"; }
        virtual const char* libraryName() const { return "osg"; }

        virtual void accept(NodeVisitor& nv);

        virtual AutoTransform* asAutoTransform() { return this; }
        virtual const AutoTransform* asAutoTransform() const { return this; }

		// 设置/获取位置
        inline void setPosition(const Vec3d& pos) { _position = pos; _matrixDirty=true; dirtyBound(); }
        inline const Vec3d& getPosition() const { return _position; }

		// 设置/获取旋转
        inline void setRotation(const Quat& quat) { _rotation = quat; _matrixDirty=true; dirtyBound(); }
        inline const Quat& getRotation() const { return _rotation; }

		// 设置/获取缩放比
        inline void setScale(double scale) { setScale(osg::Vec3(scale,scale,scale)); }
        void setScale(const Vec3d& scale);
        inline const Vec3d& getScale() const { return _scale; }

		// 设置/获取最小缩放比
        void setMinimumScale(double minimumScale) { _minimumScale = minimumScale; }
        double getMinimumScale() const { return _minimumScale; }

		// 设置/获取最大缩放比
        void setMaximumScale(double maximumScale) { _maximumScale = maximumScale; }
        double getMaximumScale() const { return _maximumScale; }

		// 设置/获取枢纽点
        inline void setPivotPoint(const Vec3d& pivot) { _pivotPoint = pivot; _matrixDirty=true; dirtyBound(); }
        inline const Vec3d& getPivotPoint() const { return _pivotPoint; }


        void setAutoUpdateEyeMovementTolerance(float tolerance) { _autoUpdateEyeMovementTolerance = tolerance; }
        float getAutoUpdateEyeMovementTolerance() const { return _autoUpdateEyeMovementTolerance; }


		// 设置/获取自动旋转模式
        void setAutoRotateMode(AutoRotateMode mode);
        AutoRotateMode getAutoRotateMode() const { return _autoRotateMode; }

        // 获取/设置子节点的旋转轴，仅当_autoRotateMode==ROTATE_TO_AXIS时有效
        void setAxis(const Vec3& axis);
        inline const Vec3& getAxis() const { return _axis; }

        // 设置/获取法线。法线定义了子节点未旋转时的正面方向
        void setNormal(const Vec3& normal);
        inline const Vec3& getNormal() const { return _normal; }

		// 设置/获取是否根据屏幕大小来缩放节点，默认为false。
        void setAutoScaleToScreen(bool autoScaleToScreen) { _autoScaleToScreen = autoScaleToScreen; _matrixDirty=true; }
        bool getAutoScaleToScreen() const { return _autoScaleToScreen; }

        void setAutoScaleTransitionWidthRatio(float ratio) { _autoScaleTransitionWidthRatio = ratio; }
        float getAutoScaleTransitionWidthRatio() const { return _autoScaleTransitionWidthRatio; }


        virtual bool computeLocalToWorldMatrix(Matrix& matrix,NodeVisitor* nv) const;

        virtual bool computeWorldToLocalMatrix(Matrix& matrix,NodeVisitor* nv) const;

        virtual BoundingSphere computeBound() const;


    protected :

        virtual ~AutoTransform() {}// IE可能错误

        Vec3d                           _position;
        Vec3d                           _pivotPoint;
        double                          _autoUpdateEyeMovementTolerance;

        AutoRotateMode                  _autoRotateMode;

        bool                            _autoScaleToScreen;

        mutable Quat                    _rotation;
        mutable Vec3d                   _scale;
        mutable bool                    _firstTimeToInitEyePoint;
        mutable osg::Vec3               _previousEyePoint;
        mutable osg::Vec3               _previousLocalUp;
        mutable Viewport::value_type    _previousWidth;
        mutable Viewport::value_type    _previousHeight;
        mutable osg::Matrixd            _previousProjection;
        mutable osg::Vec3d              _previousPosition;

        double                          _minimumScale;
        double                          _maximumScale;
        double                          _autoScaleTransitionWidthRatio;

        void computeMatrix() const;

        mutable bool                    _matrixDirty;
        mutable osg::Matrixd            _cachedMatrix;

        enum AxisAligned
        {
            AXIAL_ROT_X_AXIS=ROTATE_TO_AXIS+1,
            AXIAL_ROT_Y_AXIS,
            AXIAL_ROT_Z_AXIS,
            CACHE_DIRTY
        };

        Vec3                            _axis;
        Vec3                            _normal;

        // used internally as cache of which what _axis is aligned to help
        // decide which method of rotation to use.
        int                             _cachedMode;
        Vec3                            _side;
        void updateCache();

};

}

#endif
