#ifndef OSG_AUTOTRANSFORM
#define OSG_AUTOTRANSFORM 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformImpl.h>
#include <Types/VBF_Quat.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrViewport.h>

namespace osg {

// �Զ��任�ڵ㣺�Զ����ź���ת�������ӽڵ�ʼ������Ļ����һ��
class IVBF_SGNodeGroupTransformAuto : public IVBF_SGNodeGroupTransform
{
public:
	IVBF_SGNodeGroupTransformAuto(){}
	IVBF_SGNodeGroupTransformAuto(const IVBF_SGNodeGroupTransformAuto& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroupTransform(cs,copyop) {}
	inline explicit IVBF_SGNodeGroupTransformAuto(bool threadSafeRefUnref):IVBF_SGNodeGroupTransform(threadSafeRefUnref){}

	// ����/��ȡλ��
    virtual void setPosition(const Vec3d& pos)=0;
    virtual const Vec3d& getPosition() const =0;

	// ����/��ȡ��ת
    virtual void setRotation(const Quat& quat)=0;
    virtual const Quat& getRotation() const =0;

	// ����/��ȡ���ű�
    virtual void setScale(double scale)=0;
    virtual void setScale(const Vec3d& scale)=0;
    virtual const Vec3d& getScale() const =0;

	// ����/��ȡ��С���ű�
    virtual void setMinimumScale(double minimumScale)=0;
    virtual double getMinimumScale() const =0;

	// ����/��ȡ������ű�
    virtual void setMaximumScale(double maximumScale) =0;
    virtual double getMaximumScale() const =0;

	// ����/��ȡ��Ŧ��
    virtual void setPivotPoint(const Vec3d& pivot) =0;
    virtual const Vec3d& getPivotPoint() const =0;


    virtual void setAutoUpdateEyeMovementTolerance(float tolerance)=0;
    virtual float getAutoUpdateEyeMovementTolerance() const=0;


    enum AutoRotateMode
    {
        NO_ROTATION,		// ����ת
        ROTATE_TO_SCREEN,	// ������Ļ
        ROTATE_TO_CAMERA,	// �������
        ROTATE_TO_AXIS		// ������
    };
	// ����/��ȡ�Զ���תģʽ
    virtual void setAutoRotateMode(AutoRotateMode mode)=0;
    virtual AutoRotateMode getAutoRotateMode() const =0;

	// ��ȡ/�����ӽڵ����ת�ᣬ����_autoRotateMode==ROTATE_TO_AXISʱ��Ч
    virtual void setAxis(const Vec3& axis)=0;
    virtual const Vec3& getAxis() const =0;

	// ����/��ȡ���ߡ����߶������ӽڵ�δ��תʱ�����淽��
    virtual void setNormal(const Vec3& normal)=0;
    virtual const Vec3& getNormal() const =0;

	// ����/��ȡ�Ƿ������Ļ��С�����Žڵ㣬Ĭ��Ϊfalse��
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

		// ����/��ȡλ��
        inline void setPosition(const Vec3d& pos) { _position = pos; _matrixDirty=true; dirtyBound(); }
        inline const Vec3d& getPosition() const { return _position; }

		// ����/��ȡ��ת
        inline void setRotation(const Quat& quat) { _rotation = quat; _matrixDirty=true; dirtyBound(); }
        inline const Quat& getRotation() const { return _rotation; }

		// ����/��ȡ���ű�
        inline void setScale(double scale) { setScale(osg::Vec3(scale,scale,scale)); }
        void setScale(const Vec3d& scale);
        inline const Vec3d& getScale() const { return _scale; }

		// ����/��ȡ��С���ű�
        void setMinimumScale(double minimumScale) { _minimumScale = minimumScale; }
        double getMinimumScale() const { return _minimumScale; }

		// ����/��ȡ������ű�
        void setMaximumScale(double maximumScale) { _maximumScale = maximumScale; }
        double getMaximumScale() const { return _maximumScale; }

		// ����/��ȡ��Ŧ��
        inline void setPivotPoint(const Vec3d& pivot) { _pivotPoint = pivot; _matrixDirty=true; dirtyBound(); }
        inline const Vec3d& getPivotPoint() const { return _pivotPoint; }


        void setAutoUpdateEyeMovementTolerance(float tolerance) { _autoUpdateEyeMovementTolerance = tolerance; }
        float getAutoUpdateEyeMovementTolerance() const { return _autoUpdateEyeMovementTolerance; }


		// ����/��ȡ�Զ���תģʽ
        void setAutoRotateMode(AutoRotateMode mode);
        AutoRotateMode getAutoRotateMode() const { return _autoRotateMode; }

        // ��ȡ/�����ӽڵ����ת�ᣬ����_autoRotateMode==ROTATE_TO_AXISʱ��Ч
        void setAxis(const Vec3& axis);
        inline const Vec3& getAxis() const { return _axis; }

        // ����/��ȡ���ߡ����߶������ӽڵ�δ��תʱ�����淽��
        void setNormal(const Vec3& normal);
        inline const Vec3& getNormal() const { return _normal; }

		// ����/��ȡ�Ƿ������Ļ��С�����Žڵ㣬Ĭ��Ϊfalse��
        void setAutoScaleToScreen(bool autoScaleToScreen) { _autoScaleToScreen = autoScaleToScreen; _matrixDirty=true; }
        bool getAutoScaleToScreen() const { return _autoScaleToScreen; }

        void setAutoScaleTransitionWidthRatio(float ratio) { _autoScaleTransitionWidthRatio = ratio; }
        float getAutoScaleTransitionWidthRatio() const { return _autoScaleTransitionWidthRatio; }


        virtual bool computeLocalToWorldMatrix(Matrix& matrix,NodeVisitor* nv) const;

        virtual bool computeWorldToLocalMatrix(Matrix& matrix,NodeVisitor* nv) const;

        virtual BoundingSphere computeBound() const;


    protected :

        virtual ~AutoTransform() {}// IE���ܴ���

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
