#ifndef OSGGA_FLIGHT_MANIPULATOR
#define OSGGA_FLIGHT_MANIPULATOR 1

#include <VBF_Display/VBF_Manipulator/VBF_ManipulatorFirstPerson.h>


namespace osgGA {

// 飞行操作器，模拟飞行
// 默认情况下：鼠标左键加速，右键减速，中键（或左右同时）突然停止
class OSGGA_EXPORT FlightManipulator : public FirstPersonManipulator
{
        typedef FirstPersonManipulator inherited;

    public:


        FlightManipulator( int flags = UPDATE_MODEL_SIZE | COMPUTE_HOME_USING_BBOX );
        FlightManipulator( const FlightManipulator& fpm,
                           const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );

        META_Object( osgGA, FlightManipulator );



        // 设置翻滚操作模式
        enum YawControlMode
        {
            YAW_AUTOMATICALLY_WHEN_BANKED,
            NO_AUTOMATIC_YAW
        };
        virtual void setYawControlMode( YawControlMode ycm );
        inline YawControlMode getYawControlMode() const;

        // 设置/获取操作的灵敏度
        virtual void SetSensitivity(double dSensitivity) { m_dSensitivity = dSensitivity; }
        virtual double GetSensitivity() { return m_dSensitivity; }




        virtual void home( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual void init( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual void GetUsage( ::ApplicationUsage& usage ) const;

    protected:

        virtual bool handleFrame( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool handleMouseMove( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool handleMouseDrag( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool handleMousePush( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool handleMouseRelease( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool handleKeyDown( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
        virtual bool flightHandleEvent( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );

        virtual bool performMovement();
        virtual bool performMovementLeftMouseButton( double eventTimeDelta, double dx, double dy );
        virtual bool performMovementMiddleMouseButton( double eventTimeDelta, double dx, double dy );
        virtual bool performMovementRightMouseButton( double eventTimeDelta, double dx, double dy );

        YawControlMode _yawMode;

        double m_dSensitivity;// 灵敏度

};


/// Returns the Yaw control for the flight model.
inline FlightManipulator::YawControlMode FlightManipulator::getYawControlMode() const  { return _yawMode; }


}

#endif /* OSGGA_FLIGHT_MANIPULATOR */
