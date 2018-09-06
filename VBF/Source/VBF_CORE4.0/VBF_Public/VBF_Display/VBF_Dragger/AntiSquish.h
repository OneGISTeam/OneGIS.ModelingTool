#ifndef _OSG_ANTISQUISH_
#define _OSG_ANTISQUISH_ 1

#include <VBF_Display/VBF_Dragger/Export.h>

#include <Types/VBF_Matrix.h>
#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <Types/VBF_Quat.h>
#include <Types/Vec3>

namespace osgManipulator {

/**
 * Class that performs the Anti Squish by making the scaling uniform along all axes.
 */
class OSGMANIPULATOR_EXPORT AntiSquish: public osg::MatrixTransform
{
    public :
        AntiSquish();
        AntiSquish(const osg::Vec3d& pivot);
        AntiSquish(const osg::Vec3d& pivot, const osg::Vec3d& position);
        AntiSquish(const AntiSquish& pat, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

        virtual osg::CVBF_Object* cloneType() const { return new AntiSquish(); }

        virtual osg::CVBF_Object* clone(const osg::CopyOp& copyop) const { return new AntiSquish (*this,copyop); }

        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const AntiSquish *>(obj)!=NULL; }

        void setPivot(const osg::Vec3d& pvt)
        {
            _pivot = pvt;
            _usePivot = true; 
            m_bDirty = true;
        }

        const osg::Vec3d& getPivot() const { return _pivot; }

        void setPosition(const osg::Vec3d& pos)
        {
            _position = pos;
            _usePosition = true; 
            m_bDirty = true;
        }

        const osg::Vec3d& getPosition() const { return _position; }
                    
        virtual ~AntiSquish();

        osg::Matrix computeUnSquishedMatrix(const osg::Matrix&, bool& flag);

    protected:

        osg::NodeCallback* _asqCallback;

        osg::Vec3d _pivot;
        bool _usePivot;

        osg::Vec3d _position;
        bool _usePosition;

        bool m_bDirty;
        osg::Matrix _cachedLocalToWorld;
}; 

}
#endif
