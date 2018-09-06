#ifndef OSGMANIPULATOR_TRANSLATEPLANEDRAGGER
#define OSGMANIPULATOR_TRANSLATEPLANEDRAGGER 1

#include <VBF_Display/VBF_Dragger/Translate2DDragger.h>
#include <VBF_Display/VBF_Dragger/Translate1DDragger.h>

namespace osgManipulator {

/**
 * Tab plane dragger consists of a plane with tabs on it's corners and edges
 * for scaling. And the plane is used as a 2D translate dragger.
 */
class OSGMANIPULATOR_EXPORT TranslatePlaneDragger : public CompositeDragger
{
    public:

        TranslatePlaneDragger();

        META_OSGMANIPULATOR_Object(osgManipulator,TranslatePlaneDragger)

        virtual bool handle(const PointerInfo& pi, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

        virtual void setColor(const osg::Vec4& color) { if (_translate2DDragger.valid()) _translate2DDragger->setColor(color); }

        Translate1DDragger* getTranslate1DDragger() { return _translate1DDragger.get(); }
        Translate2DDragger* getTranslate2DDragger() { return _translate2DDragger.get(); }

    protected:

        virtual ~TranslatePlaneDragger();

        ref_ptr< Translate2DDragger >      _translate2DDragger;
        ref_ptr< Translate1DDragger >      _translate1DDragger;
        bool                                    _usingTranslate1DDragger;
};


}

#endif
