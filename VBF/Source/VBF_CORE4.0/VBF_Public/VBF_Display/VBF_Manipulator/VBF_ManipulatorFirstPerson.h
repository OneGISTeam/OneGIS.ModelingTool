#ifndef OSGGA_FIRST_PERSON_MANIPULATOR
#define OSGGA_FIRST_PERSON_MANIPULATOR 1

#include <VBF_Display/VBF_Manipulator/VBF_ManipulatorStandard.h>


namespace osgGA {

// 第一人称操作，控制相机的参数为：相机位置和朝向，如走路、驾驶、飞行
class OSGGA_EXPORT FirstPersonManipulator : public StandardManipulator
{
        typedef StandardManipulator inherited;

    public:

        FirstPersonManipulator( int flags = DEFAULT_SETTINGS );
        FirstPersonManipulator( const FirstPersonManipulator& fpm,
                                const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );

        META_Object( osgGA, FirstPersonManipulator );

        virtual void setByMatrix( const osg::Matrixd& matrix );
        virtual void setByInverseMatrix( const osg::Matrixd& matrix );
        virtual osg::Matrixd getMatrix() const;
        virtual osg::Matrixd getInverseMatrix() const;

        virtual void setTransformation( const osg::Vec3d& eye, const osg::Quat& rotation );
        virtual void setTransformation( const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up );
        virtual void getTransformation( osg::Vec3d& eye, osg::Quat& rotation ) const;
        virtual void getTransformation( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up ) const;

        virtual void setVelocity( double velocity );
        virtual double getVelocity() const { return m_dVelocity; }
        virtual void setAcceleration( double acceleration, bool relativeToModelSize = false );
        double getAcceleration( bool *relativeToModelSize = NULL ) const;
        virtual void setMaxVelocity( double maxVelocity, bool relativeToModelSize = false );
        double getMaxVelocity( bool *relativeToModelSize = NULL ) const;

        virtual void setWheelMovement( double wheelMovement, bool relativeToModelSize = false );
        double getWheelMovement( bool *relativeToModelSize = NULL ) const;

        virtual void home( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual void home( double );

        virtual void init( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );

        virtual bool IsFixedNearFar(){ return true;}

    protected:

        virtual bool handleMouseWheel( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );

        virtual bool performMovementLeftMouseButton( double eventTimeDelta, double dx, double dy );
        virtual bool performMouseDeltaMovement( float dx, float dy );
        virtual void applyAnimationStep( double currentProgress, double prevProgress );
        virtual bool startAnimationByMousePointerIntersection( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );

        void moveForward( double distance );
        void moveForward( const osg::Quat& rotation, double distance );
        void moveRight( double distance );
        void moveUp( double distance );

        osg::Vec3d _eye;
        osg::Quat  _rotation;
        double m_dVelocity;

        double m_dAcceleration;
		bool m_bAccelerationRelativeModel; // 加速度是否是相对于模型大小

        double m_dMaxVelocity;
		bool m_bMaxVelocityRelativeModel; // 最大速度是否是相对于模型大小

        double m_dWheelMovement;
		bool m_bWheelMovementRelativeModel; // 滚轮移动是否是相对于模型大小


        class FirstPersonAnimationData : public AnimationData 
		{
        public:
            osg::Quat _startRot;
            osg::Quat _targetRot;
            void start( const osg::Quat& startRotation, const osg::Quat& targetRotation, const double startTime );
        };

        virtual void allocAnimationData() { m_ipAnimationData = new FirstPersonAnimationData(); }
};


}

#endif /* OSGGA_FIRST_PERSON_MANIPULATOR */
