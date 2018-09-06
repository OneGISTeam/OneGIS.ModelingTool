#ifndef OSGMANIPULATOR_TABBOXTRACKBALLDRAGGER
#define OSGMANIPULATOR_TABBOXTRACKBALLDRAGGER 1

#include <VBF_Display/VBF_Dragger/TrackballDragger.h>
#include <VBF_Display/VBF_Dragger/TabBoxDragger.h>

namespace osgManipulator {

/**
 * Dragger for performing rotation in all axes.
 */
class OSGMANIPULATOR_EXPORT TabBoxTrackballDragger : public CompositeDragger
{
    public:

        TabBoxTrackballDragger();

        META_OSGMANIPULATOR_Object(osgManipulator,TabBoxTrackballDragger)

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

    protected:

        virtual ~TabBoxTrackballDragger();

        ref_ptr<TrackballDragger>  _trackballDragger;
        ref_ptr<TabBoxDragger>     _tabBoxDragger;
};


}

#endif
