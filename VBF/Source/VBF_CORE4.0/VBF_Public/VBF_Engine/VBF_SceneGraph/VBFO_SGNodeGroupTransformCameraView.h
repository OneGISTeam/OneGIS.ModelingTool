#ifndef OSG_CAMERAVIEW
#define OSG_CAMERAVIEW 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformImpl.h>
#include <VBF_Engine/VBF_SceneGraph/AnimationPath.h>
#include <Types/Vec3d>
#include <Types/VBF_Quat.h>

namespace osg {

/** CameraView - is a Transform that is used to specify camera views from within the scene graph.
  * The application must attach a camera to a CameraView via the CVBF_SGNodePath from the top of the scene graph
  * to the CameraView node itself, and accumulate the view matrix from this CVBF_SGNodePath.
*/
class IVBF_SGNodeGroupTransformCameraView : public IVBF_SGNodeGroupTransform
{
public:
	IVBF_SGNodeGroupTransformCameraView(){}
	IVBF_SGNodeGroupTransformCameraView(const IVBF_SGNodeGroupTransformCameraView& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroupTransform(cs,copyop) {}
	inline explicit IVBF_SGNodeGroupTransformCameraView(bool threadSafeRefUnref):IVBF_SGNodeGroupTransform(threadSafeRefUnref){}

	virtual void setPosition(const Vec3d& pos) =0;
	virtual const Vec3d& getPosition() const =0;

	/** Set the attitude of the camera view.*/
	virtual void setAttitude(const Quat& quat) =0;
	virtual const Quat& getAttitude() const =0;

	virtual void setFieldOfView(double fieldOfView) =0;
	virtual double getFieldOfView() const =0;

    enum FieldOfViewMode
    {
        UNCONSTRAINED,
        HORIZONTAL,
        VERTICAL
    };

    /** Set the field of view mode - controlling how the field of view of the camera is constrained by the CameraView settings.*/
    virtual void setFieldOfViewMode(FieldOfViewMode mode)=0;
    virtual FieldOfViewMode getFieldOfViewMode() const=0;



    virtual void setFocalLength(double focalLength)=0;
    virtual double getFocalLength() const =0;


};
class OSG_EXPORT CameraView : public IVBF_SGNodeGroupTransformImpl<IVBF_SGNodeGroupTransformCameraView>
{
    public :
        CameraView();

        CameraView(const CameraView& pat,const CopyOp& copyop=CopyOp::SHALLOW_COPY);
            

        META_Node(osg, CameraView);

        /** Set the position of the camera view.*/
        inline void setPosition(const Vec3d& pos) { _position = pos; dirtyBound(); }
        inline const Vec3d& getPosition() const { return _position; }

        /** Set the attitude of the camera view.*/
        inline void setAttitude(const Quat& quat) { _attitude = quat; dirtyBound(); }
        inline const Quat& getAttitude() const { return _attitude; }

        /** Set the field of view.
          * The camera's field of view can be constrained to either the horizontal or vertical axis of the camera, or unconstrained
          * in which case the camera/application are left to choose an appropriate field of view.
          * The default value if 60 degrees. */
        inline void setFieldOfView(double fieldOfView) { _fieldOfView = fieldOfView; }
        inline double getFieldOfView() const { return _fieldOfView; }
        

        /** Set the field of view mode - controlling how the field of view of the camera is constrained by the CameraView settings.*/
        inline void setFieldOfViewMode(FieldOfViewMode mode) { _fieldOfViewMode = mode; }
        inline FieldOfViewMode getFieldOfViewMode() const { return _fieldOfViewMode; }

        /** Set the focal length of the camera.
          * A focal length of 0.0 indicates that the camera/application should determine the focal length.
          * The default value is 0.0. */
        inline void setFocalLength(double focalLength) { _focalLength = focalLength; }
        inline double getFocalLength() const { return _focalLength; }
        

        virtual bool computeLocalToWorldMatrix(Matrix& matrix,NodeVisitor* nv) const;
        virtual bool computeWorldToLocalMatrix(Matrix& matrix,NodeVisitor* nv) const;


    protected :
            
        virtual ~CameraView() {}// IE¿ÉÄÜ´íÎó

        Vec3d           _position;
        Quat            _attitude;
        double          _fieldOfView;
        FieldOfViewMode _fieldOfViewMode;
        double          _focalLength;
};

}

#endif
