#ifndef OSGGA_MULTITOUCH_TRACKBALL_MANIPULATOR
#define OSGGA_MULTITOUCH_TRACKBALL_MANIPULATOR 1

#include <VBF_Display/VBF_Manipulator/VBF_ManipulatorTrackball.h>


namespace osgGA {


class OSGGA_EXPORT MultiTouchTrackballManipulator : public TrackballManipulator
{
        typedef TrackballManipulator inherited;

    public:

        MultiTouchTrackballManipulator( int flags = DEFAULT_SETTINGS );
        MultiTouchTrackballManipulator( const MultiTouchTrackballManipulator& tm,
                              const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );

        META_Object( osgGA, MultiTouchTrackballManipulator );
        
        bool handle( const GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us );
    
    protected:
        
        void handleMultiTouchDrag(GUIEventAdapter::TouchData* now, GUIEventAdapter::TouchData* last, const double eventTimeDelta);
        
        ref_ptr<GUIEventAdapter::TouchData> _lastTouchData;
};


}

#endif /* OSGGA_MULTITOUCH_TRACKBALL_MANIPULATOR */
