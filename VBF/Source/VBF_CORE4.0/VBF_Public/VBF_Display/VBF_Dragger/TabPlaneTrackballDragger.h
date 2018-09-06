#ifndef OSGMANIPULATOR_TABPLANETRACKBALLDRAGGER
#define OSGMANIPULATOR_TABPLANETRACKBALLDRAGGER 1

#include <VBF_Display/VBF_Dragger/TrackballDragger.h>
#include <VBF_Display/VBF_Dragger/TabPlaneDragger.h>

namespace osgManipulator {

/**
 * Dragger for performing rotation in all axes.
 */
class OSGMANIPULATOR_EXPORT TabPlaneTrackballDragger : public CompositeDragger
{
    public:

        TabPlaneTrackballDragger();

        META_OSGMANIPULATOR_Object(osgManipulator,TabPlaneTrackballDragger)

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

        void setPlaneColor(const osg::Vec4& color) { _tabPlaneDragger->setPlaneColor(color); }

    protected:

        virtual ~TabPlaneTrackballDragger();

        ref_ptr<TrackballDragger> _trackballDragger;
        ref_ptr<TabPlaneDragger>  _tabPlaneDragger;
};


}

#endif
