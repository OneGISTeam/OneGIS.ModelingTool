#ifndef OSGMANIPULATOR_SCALEAXISDRAGGER
#define OSGMANIPULATOR_SCALEAXISDRAGGER 1

#include <VBF_Display/VBF_Dragger/Scale1DDragger.h>

namespace osgManipulator {

/**
 * Dragger for performing scaling on all 3 axes.
 */
class OSGMANIPULATOR_EXPORT ScaleAxisDragger : public CompositeDragger
{
    public:
        ScaleAxisDragger();

        META_OSGMANIPULATOR_Object(osgManipulator,ScaleAxisDragger)
        void setupDefaultGeometry();


        // wuyuguo
        void SetHandleEvents(bool flag)
        {
            if(_xDragger.valid()) _xDragger->setHandleEvents(flag);
            if(_yDragger.valid()) _yDragger->setHandleEvents(flag);
            if(_zDragger.valid()) _zDragger->setHandleEvents(flag);
        }

    protected:

        virtual ~ScaleAxisDragger();

        ref_ptr< Scale1DDragger >        _xDragger;
        ref_ptr< Scale1DDragger >        _yDragger;
        ref_ptr< Scale1DDragger >        _zDragger;
};


}

#endif
