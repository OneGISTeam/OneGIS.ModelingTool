#ifndef OSGMANIPULATOR_ROTATESPHEREDRAGGER
#define OSGMANIPULATOR_ROTATESPHEREDRAGGER 1

#include <VBF_Display/VBF_Dragger/Dragger.h>
#include <VBF_Display/VBF_Dragger/Projector.h>

namespace osgManipulator {

/**
 * Dragger for performing 3D rotation on a sphere.
 */
class OSGMANIPULATOR_EXPORT RotateSphereDragger : public Dragger
{
    public:

        RotateSphereDragger();

        META_OSGMANIPULATOR_Object(osgManipulator,RotateSphereDragger)

        /**
         * Handle pick events on dragger and generate TranslateInLine commands.
         */
        virtual bool handle(const PointerInfo&, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

    protected:

        virtual ~RotateSphereDragger();

        ref_ptr<SpherePlaneProjector> _projector;

        osg::Vec3d  _prevWorldProjPt;
        bool        _prevPtOnSphere;
        osg::Matrix _startLocalToWorld, _startWorldToLocal;
        osg::Quat   _prevRotation;
};


}

#endif
