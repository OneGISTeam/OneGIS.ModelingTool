#ifndef OSGMANIPULATOR_ROTATECYLINDERDRAGGER
#define OSGMANIPULATOR_ROTATECYLINDERDRAGGER 1

#include <VBF_Display/VBF_Dragger/Dragger.h>
#include <VBF_Display/VBF_Dragger/Projector.h>

namespace osgManipulator {

// ��Բ��������ת��������ת��
class OSGMANIPULATOR_EXPORT RotateCylinderDragger : public Dragger
{
    public:
        RotateCylinderDragger();

        META_OSGMANIPULATOR_Object(osgManipulator,RotateCylinderDragger)

		// ����ѡ��pick���¼���������Rotate3DCommand����
        virtual bool handle(const PointerInfo& pi, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

        // ����Ĭ�ϵ�ͼ�μ�����
        void setupDefaultGeometry();

		// ��ȡ�ϴε���תֵ����Ө��ӣ�2013-09-12��
        inline const osg::Quat& GetPrevRotation() const	{ return _prevRotation; }

		// ��ȡ��������ϵ��ֲ�����ϵ֮��ı任���󣨶�Ө��ӣ�2013-09-12��
		inline const osg::Matrix& GetLocalToWorld() const { return _startLocalToWorld; }
		inline const osg::Matrix& GetWorldToLocal() const { return _startWorldToLocal; }

        // ��Ӧ������/�뿪��Dragger�¼�����Ө��ӣ�2014-12-29��
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
