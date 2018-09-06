#ifndef OSGGA_TRACKBALL_MANIPULATOR
#define OSGGA_TRACKBALL_MANIPULATOR 1

#include <VBF_Display/VBF_Manipulator/VBF_ManipulatorOrbit.h>

namespace osgGA {

// ¸ú×ÙÇò²Ù×÷Æ÷

class OSGGA_EXPORT TrackballManipulator : public OrbitManipulator
{
        typedef OrbitManipulator inherited;

    public:

        TrackballManipulator( int flags = DEFAULT_SETTINGS );
        TrackballManipulator( const TrackballManipulator& tm,
                              const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );

        META_Object( osgGA, TrackballManipulator );

        virtual void setByMatrix( const osg::Matrixd& matrix );

};
}

#endif
