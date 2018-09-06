#ifndef OSGMANIPULATOR_ROTATECYLINDERDRAGGER
#define OSGMANIPULATOR_ROTATECYLINDERDRAGGER 1

#include <VBF_Display/VBF_Dragger/Dragger.h>
#include <VBF_Display/VBF_Dragger/Projector.h>

namespace osgManipulator {

// 在圆柱面上旋转（绕轴旋转）
class OSGMANIPULATOR_EXPORT RotateCylinderDragger : public Dragger
{
    public:
        RotateCylinderDragger();

        META_OSGMANIPULATOR_Object(osgManipulator,RotateCylinderDragger)

		// 处理选择（pick）事件，并生成Rotate3DCommand命令
        virtual bool handle(const PointerInfo& pi, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

        // 设置默认的图形几何体
        void setupDefaultGeometry();

		// 获取上次的旋转值（杜莹添加：2013-09-12）
        inline const osg::Quat& GetPrevRotation() const	{ return _prevRotation; }

		// 获取世界坐标系与局部坐标系之间的变换矩阵（杜莹添加：2013-09-12）
		inline const osg::Matrix& GetLocalToWorld() const { return _startLocalToWorld; }
		inline const osg::Matrix& GetWorldToLocal() const { return _startWorldToLocal; }

        // 响应鼠标进入/离开该Dragger事件（杜莹添加：2014-12-29）
        virtual void OnEnter(const PointerInfo& pointer, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);
        virtual void OnLeave(const PointerInfo& pointer, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

    protected:

        virtual ~RotateCylinderDragger();

        ref_ptr<CylinderPlaneProjector> _projector;

        osg::Vec3d  _prevWorldProjPt;
        bool        _prevPtOnCylinder;

        osg::Matrix _startLocalToWorld, _startWorldToLocal;
        osg::Quat   _prevRotation;
};


}

#endif
