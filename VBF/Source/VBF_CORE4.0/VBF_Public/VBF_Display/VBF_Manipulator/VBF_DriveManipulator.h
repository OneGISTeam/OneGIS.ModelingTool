
#ifndef __VBF_DRIVE_MANIPULATOR_H__
#define __VBF_DRIVE_MANIPULATOR_H__

#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>
#include <Types/VBF_Quat.h>

using namespace osgGA;

class OSGGA_EXPORT VBF_DriveManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
{
public:
    VBF_DriveManipulator();

    virtual const char* className() const { return "Drive"; }

    virtual void setByMatrix(const osg::Matrixd& matrix);
    virtual void setByInverseMatrix(const osg::Matrixd& matrix) { setByMatrix(osg::Matrixd::inverse(matrix)); }
    virtual osg::Matrixd getMatrix() const;
    virtual osg::Matrixd getInverseMatrix() const;

    virtual void setNode(osg::IVBF_SGNode*);
    virtual const osg::IVBF_SGNode* getNode() const;
    virtual osg::IVBF_SGNode* getNode();

    virtual void computeHomePosition();

    virtual void home(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);
    virtual void init(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);
    virtual bool handle(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);

    // 获取该操作器鼠标和键盘的用法
    virtual void GetUsage(ApplicationUsage& usage) const;

    void setModelScale( double in_ms ) { _modelScale = in_ms; }
    double getModelScale() const { return _modelScale; }

    // 设置/获取速度
    void setVelocity( double in_vel ) { _velocity = in_vel; }
    double getVelocity() const { return _velocity; }

    // 设置/获取高度
    void setHeight( double in_h ) { _height = in_h; }
    double getHeight() const { return _height; }

    //以下函数为GGR添加
    void GetHPRFromQuat(const osg::Quat& q, double &h, double &p, double &r);

    // 设置/获取方位和俯仰
    osg::Quat getRotation() { return _rotation; }		//旋转参数
    double GetHeading();								//旋转角度，单位为Degree
    double GetPitch();									//俯仰角度，单位为Degree
    void   SetPitch(double in_p);

protected:

    virtual ~VBF_DriveManipulator();

    bool intersect(const osg::Vec3d& start, const osg::Vec3d& end, osg::Vec3d& intersection, osg::Vec3d& normal) const;

    void flushMouseEventStack(); // Reset the internal GUIEvent stack

    /** Add the current mouse GUIEvent to internal stack.*/
    void addMouseEvent(const GUIEventAdapter& ea);

    void computePosition(const osg::Vec3d& eye,const osg::Vec3d& lv,const osg::Vec3d& up);

    /** For the given mouse movement calculate the movement of the camera.
      * Return true if camera has moved and a redraw is required.
      */
    bool calcMovement();

    // Internal event stack comprising last two mouse events.
    ref_ptr<const GUIEventAdapter> m_ipEventAdapter1;
    ref_ptr<const GUIEventAdapter> m_ipEventAdapter0;

    observer_ptr<osg::IVBF_SGNode>    _node;

    double _modelScale;
    double _velocity;
    double _height;
    double _buffer;

    enum SpeedControlMode
    {
        USE_MOUSE_Y_FOR_SPEED,
        USE_MOUSE_BUTTONS_FOR_SPEED
    };

    SpeedControlMode _speedMode;

    osg::Vec3d   _eye;
    osg::Quat    _rotation;
    double       _pitch;
    double       _distance;

    bool        _pitchUpKeyPressed;
    bool        _pitchDownKeyPressed;
    bool        m_bMoveLeftKeyPressed;
    bool        m_bMoveRightKeyPressed;
};


#endif
