#ifndef OSGMANIPULATOR_TRANSLATE2DDRAGGER
#define OSGMANIPULATOR_TRANSLATE2DDRAGGER 1

#include <VBF_Display/VBF_Dragger/Dragger.h>
#include <VBF_Display/VBF_Dragger/Projector.h>

#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrPolygonOffset.h>

namespace osgManipulator {

/**
 * Dragger for performing 2D translation.
 */
class OSGMANIPULATOR_EXPORT Translate2DDragger : public Dragger
{
    public:

        Translate2DDragger();

        Translate2DDragger(const osg::Plane& plane);

        META_OSGMANIPULATOR_Object(osgManipulator,Translate2DDragger)

        /** Handle pick events on dragger and generate TranslateInLine commands. */
        virtual bool handle(const PointerInfo& pi, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

        // 响应鼠标进入/离开该Dragger事件（杜莹添加：2014-12-29）
        virtual void OnEnter(const PointerInfo& pointer, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);
        virtual void OnLeave(const PointerInfo& pointer, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

    protected:

        virtual ~Translate2DDragger();

        ref_ptr< PlaneProjector >       _projector;
        osg::Vec3d                      _startProjectedPoint;
        ref_ptr<osg::PolygonOffset>     _polygonOffset;
};


}

#endif
