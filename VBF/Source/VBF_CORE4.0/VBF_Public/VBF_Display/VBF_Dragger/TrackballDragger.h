#ifndef OSGMANIPULATOR_TRACKBALLDRAGGER
#define OSGMANIPULATOR_TRACKBALLDRAGGER 1

#include <VBF_Display/VBF_Dragger/RotateCylinderDragger.h>
#include <VBF_Display/VBF_Dragger/RotateSphereDragger.h>

namespace osgManipulator {

/**
 * Dragger for performing rotation in all axes.
 */
class OSGMANIPULATOR_EXPORT TrackballDragger : public CompositeDragger
{
    public:

        TrackballDragger(bool useAutoTransform=false);

        META_OSGMANIPULATOR_Object(osgManipulator,TrackballDragger)

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

    protected:

        virtual ~TrackballDragger();

        ref_ptr<RotateCylinderDragger> _xDragger;
        ref_ptr<RotateCylinderDragger> _yDragger;
        ref_ptr<RotateCylinderDragger> _zDragger;
        ref_ptr<RotateSphereDragger>   _xyzDragger;
};


}

#endif
