#ifndef OSGGA_UFO_MANIPULATOR_DEF
#define OSGGA_UFO_MANIPULATOR_DEF 1

#include <iostream>

#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <Types/VBF_Matrix.h>

/**
  The UFOManipulator is better suited for applications that employ 
  architectural walk-throughs, or situations where the eyepoint motion
  model must move slowly, deliberately and well controlled.  

   Key combinations:
    \param UpArrow          Acceleration forward.
    \param DownArrow        Acceleration backward (or deceleration forward).
    \param LeftArrow        Rotate view and direction of travel to the left.
    \param RightArrow       Rotate view and direction of travel to the right.
    \param SpaceBar         Brake.  Gradually decelerates linear and rotational movement.
    \param Shift/UpArrow    Accelerate up.
    \param Shift/DownArrow  Accelerate down.
    \param Shift/LeftArrow  Accelerate (linearly) left.
    \param Shift/RightArrow Accelerate (linearly) right.
    \param Shift/SpaceBar   Instant brake.  Immediately stop all linear and rotational movement.

When the Shift key is released, up, down, linear left and/or linear right movement is decelerated.

    \param Ctrl/UpArrow     Rotate view (but not direction of travel) up.
    \param Ctrl/DownArrow   Rotate view (but not direction of travel) down.
    \param Ctrl/LeftArrow   Rotate view (but not direction of travel) left.
    \param Ctrl/RightArrow  Rotate view (but not direction of travel) right.
    \param Ctrl/Return      Straightens out the view offset.

*/

namespace osgGA {


// UFO操作器

	class OSGGA_EXPORT UFOManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
	{
	public:
		UFOManipulator();

		virtual const char* className() const;

		// 1、继承自IVBF_CameraManipulator的函数
		virtual void setByMatrix( const osg::Matrixd &matrix ) ;
		virtual void setByInverseMatrix( const osg::Matrixd &invmat);
		virtual osg::Matrixd getMatrix() const;
		virtual osg::Matrixd getInverseMatrix() const ;


		virtual void setNode(osg::IVBF_SGNode* node);
		virtual const osg::IVBF_SGNode* getNode() const;
		virtual osg::IVBF_SGNode* getNode();


        virtual void computeHomePosition();
        virtual void home(const osgGA::GUIEventAdapter&, ::IVBF_GUIActionAdapter&) ;
        void home(double);

        virtual void init(const GUIEventAdapter& ,::IVBF_GUIActionAdapter&);

        bool handle(const osgGA::GUIEventAdapter& ea,::IVBF_GUIActionAdapter &aa);

        void GetUsage(::ApplicationUsage& usage) const;

        void getCurrentPositionAsLookAt( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up );


		// 2、继承自IVBF_CameraManipulatorUFO的函数
        void setMinHeight( double in_min_height ) { _minHeightAboveGround = in_min_height; }
        double getMinHeight() const { return _minHeightAboveGround; }

        void setMinDistance( double in_min_dist ) { _minDistanceInFront = in_min_dist; }
        double getMinDistance() const { return _minDistanceInFront; }

        void setForwardSpeed( double in_fs ) { _forwardSpeed = in_fs; }
        double getForwardSpeed() const { return _forwardSpeed; }

        void setSideSpeed( double in_ss ) { _sideSpeed = in_ss; }
        double getSideSpeed() const { return _sideSpeed; }

        void setRotationSpeed( double in_rot_speed ) { _directionRotationRate = in_rot_speed; }
        double getRotationSpeed() const { return _directionRotationRate; }


    protected:

        virtual ~UFOManipulator();

        bool intersect(const osg::Vec3d& start, const osg::Vec3d& end, osg::Vec3d& intersection) const;

        observer_ptr<osg::IVBF_SGNode> m_opNode;
        float       _viewAngle;
        osg::Matrixd _matrix;
        osg::Matrixd _inverseMatrix;
        osg::Matrixd _offset;

        double    _minHeightAboveGround;
        double    _minDistanceInFront;

        double    _speedEpsilon;
        double    _forwardSpeed;
        double    _sideSpeed;
        double    _upSpeed;
        double    _speedAccelerationFactor;
        double    _speedDecelerationFactor;

        bool      _decelerateUpSideRate;

        double    _directionRotationEpsilon;
        double    _directionRotationRate;
        double    _directionRotationAcceleration;
        double    _directionRotationDeceleration;

        double    _viewOffsetDelta;
        double    _pitchOffsetRate;
        double    _pitchOffset;
        double    _yawOffsetRate;
        double    _yawOffset;

        double    _t0;
        double    _dt;
        osg::Vec3d _direction;
        osg::Vec3d _position;


        bool _shift;
        bool _ctrl;
        bool _decelerateOffsetRate;

        bool _straightenOffset;

        void _stop();
        void _keyDown( const osgGA::GUIEventAdapter &ea, ::IVBF_GUIActionAdapter &);
        void _keyUp( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter &);
        void _frame(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter &);

        void _adjustPosition();
};

}

#endif
