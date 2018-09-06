#ifndef OSGMANIPULATOR_TRANSLATEAXISDRAGGER
#define OSGMANIPULATOR_TRANSLATEAXISDRAGGER 1

#include <VBF_Display/VBF_Dragger/Translate1DDragger.h>

namespace osgManipulator {

/**
 * Dragger for performing translation in all three axes.
 */
class OSGMANIPULATOR_EXPORT TranslateAxisDragger : public CompositeDragger
{
    public:

        TranslateAxisDragger();

        META_OSGMANIPULATOR_Object(osgManipulator,TranslateAxisDragger)

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

    protected:

        virtual ~TranslateAxisDragger();

        ref_ptr< Translate1DDragger >  _xDragger;
        ref_ptr< Translate1DDragger >  _yDragger;
        ref_ptr< Translate1DDragger >  _zDragger;
};


}

#endif
