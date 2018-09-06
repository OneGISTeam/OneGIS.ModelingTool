#ifndef __SphericalManipulator_h__
#define __SphericalManipulator_h__

#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>
#include <VBF_Common/VBF_Math/VBF_Math.h>
#include <Types/VBF_Quat.h>

namespace osgGA
{

class OSGGA_EXPORT SphericalManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
{
    public:
        SphericalManipulator();

        virtual const char* className() const { return "Spherical Manipulator"; }

		// 1���̳���IVBF_CameraManipulator�ĺ���

        virtual void setByMatrix(const osg::Matrixd& matrix);
        virtual void setByInverseMatrix(const osg::Matrixd& matrix) { setByMatrix(osg::Matrixd::inverse(matrix)); }
        virtual osg::Matrixd getMatrix() const;
        virtual osg::Matrixd getInverseMatrix() const;

        virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const { return osgUtil::SceneView::USE_FUSION_DISTANCE_VALUE; }
        virtual float getFusionDistanceValue() const { return m_dDistance; }

        virtual void setNode(osg::IVBF_SGNode*);
        virtual const osg::IVBF_SGNode* getNode() const;
        virtual osg::IVBF_SGNode* getNode();

        virtual void home(const osgGA::GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);
        virtual void home(double);

        virtual void init(const osgGA::GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);

        virtual bool handle(const osgGA::GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);

        virtual void computeHomePosition();

        void computeViewPosition(const osg::BoundingSphere& bound,double& scale,double& distance,osg::Vec3d& center);



		// 2���̳���IVBF_CameraManipulatorSpherical�ĺ���

        void zoomOn(const osg::BoundingSphere& bound);

        void setCenter(const osg::Vec3d& center) {m_vCenter=center;}
        const osg::Vec3d& getCenter() const {return m_vCenter;}

        bool setDistance(double distance);
        double getDistance() const { return m_dDistance; }

        double getHomeDistance() const { return m_dHomeDistance; }

        void setHeading(double azimuth) { m_dHeading = azimuth; }
        double getHeading() const {return m_dHeading;}

        void setElevation(double elevation) { _elevation = elevation; }
        double getElevtion() const {return _elevation;}


		/** set the minimum distance (as ratio) the eye point can be zoomed in towards the
            center before the center is pushed forward.*/          
		double getMinimumZoomScale() const { return m_dMinZoomScale; }
        void setMinimumZoomScale(double minimumZoomScale) {m_dMinZoomScale=minimumZoomScale;}

		// ����/��ȡ�������ŵ�deltaֵ��-1.0 �� +1.0��
        void SetScroolWheelZoomDelta(double zoomDelta) { m_dWheelZoomDelta = zoomDelta; }
        double GetScroolWheelZoomDelta() const { return m_dWheelZoomDelta; }


        // ��ȡ�ò��������ͼ��̵��÷�
        virtual void GetUsage(::ApplicationUsage& usage) const;

		enum RotationMode
		{
			ELEVATION_HEADING=0,
			HEADING,
			ELEVATION,
			MAP
		};

		// ����/��ȡ��תģʽ
        RotationMode GetRotationMode() const {return m_eRotationMode;}
        void SetRotationMode(RotationMode mode);

		// ����/��ȡ����Ƿ�֧�ֱ��׳����׳�����ָ�û����¼��϶�ģ�Ͳ�ͻȻ�ɿ�����ʵ��ģ�͵ĳ�����ת���ƶ���
        bool GetAllowThrow() const { return m_bAllowThrow; }
        void SetAllowThrow(bool bAllowThrow) { m_bAllowThrow = bAllowThrow; }

    protected:

        virtual ~SphericalManipulator();

        void flushMouseEventStack();// �����������������¼�		
        void addMouseEvent(const GUIEventAdapter& ea);// ������������¼���ֻ����2����


		bool calcMovement(); // ���ݸ���������ƶ�����������ƶ����������ƶ��˲���Ҫ�ػ��򷵻�true

		bool isMouseMoving(); // �ж�����Ƿ����ƶ����ٶȴ�����ֵ����Ϊ�����ƶ���

        // �������������¼�
        ref_ptr<const osgGA::GUIEventAdapter> m_ipEventAdapter1;
        ref_ptr<const osgGA::GUIEventAdapter> m_ipEventAdapter0;

        observer_ptr<osg::IVBF_SGNode>  m_opNode;

        double m_dModelScale;
        double m_dMinZoomScale; // ��С���ű�

        bool m_bThrown;		// �Ƿ�����׳�
        bool m_bAllowThrow;	// �Ƿ���������׳�

        double m_dTimeOneFrame; // ����һ֡�Ĵ��ʱ�䣬���ڼ�������׳������� �ƶ�/��ת ������
        double m_dTimeLastFrame; // ���һ֡����ʼʱ�䣬���������Ϊtrueʱ��ƥ��ˢ�������ƶ�/��ת����

        RotationMode    m_eRotationMode;
        osg::Vec3d      m_vCenter;
        double          m_dDistance;
        double          m_dHeading;   // angle from x axis in xy plane
        double          _elevation;   // angle from xy plane, positive upwards towards the z axis
        double          m_dHomeDistance;
        double          m_dWheelZoomDelta;
};
}
#endif
