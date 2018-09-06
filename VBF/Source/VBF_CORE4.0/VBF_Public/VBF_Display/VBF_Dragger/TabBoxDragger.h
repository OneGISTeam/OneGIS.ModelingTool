#ifndef OSGMANIPULATOR_TABBOXDRAGGER
#define OSGMANIPULATOR_TABBOXDRAGGER 1

#include <VBF_Display/VBF_Dragger/TabPlaneDragger.h>

namespace osgManipulator {

/**
 * TabBoxDragger consists of 6 TabPlaneDraggers to form a box dragger that
 * performs translation and scaling.
 */
class OSGMANIPULATOR_EXPORT TabBoxDragger : public CompositeDragger
{
    public:

        TabBoxDragger();

        META_OSGMANIPULATOR_Object(osgManipulator,TabBoxDragger)

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

        void setPlaneColor(const osg::Vec4& color);

    protected:

        virtual ~TabBoxDragger();

        std::vector< ref_ptr< TabPlaneDragger > > _planeDraggers;
};


}

#endif
