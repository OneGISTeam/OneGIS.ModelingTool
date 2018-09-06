#ifndef OSGMANIPULATOR_TABPLANEDRAGGER
#define OSGMANIPULATOR_TABPLANEDRAGGER 1

#include <VBF_Display/VBF_Dragger/TranslatePlaneDragger.h>
#include <VBF_Display/VBF_Dragger/Scale2DDragger.h>
#include <VBF_Display/VBF_Dragger/Scale1DDragger.h>

namespace osgManipulator {

/**
 * Tab plane dragger consists of a plane with tabs on it's corners and edges
 * for scaling. And the plane is used as a 2D translate dragger.
 */
class OSGMANIPULATOR_EXPORT TabPlaneDragger : public CompositeDragger
{
    public:

        TabPlaneDragger();

        META_OSGMANIPULATOR_Object(osgManipulator,TabPlaneDragger)

        virtual bool handle(const PointerInfo& pi, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry(bool twoSidedHandle = true);

        void setPlaneColor(const osg::Vec4& color) { _translateDragger->setColor(color); }

    protected:

        virtual ~TabPlaneDragger();

        ref_ptr< TranslatePlaneDragger >   _translateDragger;
        ref_ptr< Scale2DDragger >          _cornerScaleDragger;
        ref_ptr< Scale1DDragger >          _horzEdgeScaleDragger;
        ref_ptr< Scale1DDragger >          _vertEdgeScaleDragger;

        float                                   _handleScaleFactor;
};


}

#endif
