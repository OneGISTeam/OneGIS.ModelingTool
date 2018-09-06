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

		// 1、继承自IVBF_CameraManipulator的函数

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



		// 2、继承自IVBF_CameraManipulatorSpherical的函数

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

		// 设置/获取滚轮缩放的delta值（-1.0 到 +1.0）
        void SetScroolWheelZoomDelta(double zoomDelta) { m_dWheelZoomDelta = zoomDelta; }
        double GetScroolWheelZoomDelta() const { return m_dWheelZoomDelta; }


        // 获取该操作器鼠标和键盘的用法
        virtual void GetUsage(::ApplicationUsage& usage) const;

		enum RotationMode
		{
			ELEVATION_HEADING=0,
			HEADING,
			ELEVATION,
			MAP
		};

		// 设置/获取旋转模式
        RotationMode GetRotationMode() const {return m_eRotationMode;}
        void SetRotationMode(RotationMode mode);

		// 设置/获取相机是否支持被抛出（抛出，是指用户按下键拖动模型并突然松开，以实现模型的持续旋转或移动）
        bool GetAllowThrow() const { return m_bAllowThrow; }
        void SetAllowThrow(bool bAllowThrow) { m_bAllowThrow = bAllowThrow; }

    protected:

        virtual ~SphericalManipulator();

        void flushMouseEventStack();// 重设最近的两次鼠标事件		
        void addMouseEvent(const GUIEventAdapter& ea);// 添加最近的鼠标事件（只保留2个）


		bool calcMovement(); // 根据给定的鼠标移动计算相机的移动，如果相机移动了并需要重绘则返回true

		bool isMouseMoving(); // 判断鼠标是否在移动（速度大于阈值才认为是在移动）

        // 最近的两次鼠标事件
        ref_ptr<const osgGA::GUIEventAdapter> m_ipEventAdapter1;
        ref_ptr<const osgGA::GUIEventAdapter> m_ipEventAdapter0;

        observer_ptr<osg::IVBF_SGNode>  m_opNode;

        double m_dModelScale;
        double m_dMinZoomScale; // 最小缩放比

        bool m_bThrown;		// 是否相机抛出
        bool m_bAllowThrow;	// 是否允许相机抛出

        double m_dTimeOneFrame; // 绘制一帧的大概时间，用于计算相机抛出过程中 移动/旋转 的增量
        double m_dTimeLastFrame; // 最后一帧的起始时间，用于桢相关为true时，匹配刷新率与移动/旋转速率

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
