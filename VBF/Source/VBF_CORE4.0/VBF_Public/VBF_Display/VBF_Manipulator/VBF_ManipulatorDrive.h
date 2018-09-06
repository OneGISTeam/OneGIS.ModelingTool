#ifndef OSGGA_DRIVEMANIPULATOR
#define OSGGA_DRIVEMANIPULATOR 1

#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>
#include <Types/VBF_Quat.h>

namespace osgGA{

// ��ʻ��������Ĭ�ϲ����ǣ�������٣��Ҽ����٣��м���������ͬʱ��ֹͣ
class OSGGA_EXPORT DriveManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
{
    public:
        DriveManipulator();

        virtual const char* className() const { return "Drive"; }

		// 1���̳���IVBF_CameraManipulator�ĺ���

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

        virtual void GetUsage(::ApplicationUsage& usage) const;


		// 2���̳���IVBF_CameraManipulatorDrive�ĺ���
        void setModelScale( double in_ms ) { m_dModelScale = in_ms; }
        double getModelScale() const { return m_dModelScale; }

        void setVelocity( double in_vel ) { m_dVelocity = in_vel; }
        double getVelocity() const { return m_dVelocity; }

        void setHeight( double in_h ) { m_dHeight = in_h; }
        double getHeight() const { return m_dHeight; }

    protected:

        virtual ~DriveManipulator();

        bool intersect(const osg::Vec3d& start, const osg::Vec3d& end, osg::Vec3d& intersection, osg::Vec3d& normal) const;


		
        void flushMouseEventStack();// �����������������¼�		
        void addMouseEvent(const GUIEventAdapter& ea);// ������������¼���ֻ����2����

        void computePosition(const osg::Vec3d& eye,const osg::Vec3d& lv,const osg::Vec3d& up);

         bool calcMovement(); // ���ݸ���������ƶ�����������ƶ����������ƶ��˲���Ҫ�ػ��򷵻�true

        // �������������¼�
        ref_ptr<const GUIEventAdapter> m_ipEventAdapter1;
        ref_ptr<const GUIEventAdapter> m_ipEventAdapter0;

        observer_ptr<osg::IVBF_SGNode>    m_opNode;

        double m_dModelScale;
        double m_dVelocity;
        double m_dHeight;
        double m_dBuffer;

        enum SpeedControlMode 
		{
                USE_MOUSE_Y_FOR_SPEED,
                USE_MOUSE_BUTTONS_FOR_SPEED
        };

        SpeedControlMode _speedMode;

        osg::Vec3d   _eye;
        osg::Quat    _rotation;
        double       _pitch;
        double       m_dDistance;

        bool        _pitchUpKeyPressed;
        bool        _pitchDownKeyPressed;
};

}

#endif
