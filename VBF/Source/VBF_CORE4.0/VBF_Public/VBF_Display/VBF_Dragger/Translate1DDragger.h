#ifndef OSGMANIPULATOR_TRANSLATE1DDRAGGER
#define OSGMANIPULATOR_TRANSLATE1DDRAGGER 1

#include <VBF_Display/VBF_Dragger/Dragger.h>
#include <VBF_Display/VBF_Dragger/Projector.h>

namespace osgManipulator {



// ��һά����������ƶ�
class OSGMANIPULATOR_EXPORT Translate1DDragger : public Dragger
{
    public:
        Translate1DDragger();

        META_OSGMANIPULATOR_Object(osgManipulator,Translate1DDragger)

        Translate1DDragger(const osg::Vec3d& s, const osg::Vec3d& e);

        // ����ѡ���¼�������TranslateInLine����
        virtual bool handle(const PointerInfo& pi, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);
        void setupDefaultGeometry();

        inline void setCheckForNodeInNodePath(bool onOff) { _checkForNodeInNodePath = onOff; }

        // ��Ӧ������/�뿪��Dragger�¼�����Ө��ӣ�2014-12-29��
        virtual void OnEnter(const PointerInfo& pointer, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);
        virtual void OnLeave(const PointerInfo& pointer, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

    protected:

        virtual ~Translate1DDragger();

        ref_ptr< LineProjector >   _projector;
        osg::Vec3d                 _startProjectedPoint;
        bool                       _checkForNodeInNodePath;
};


}

#endif
