#ifndef OSG_CLUSTERCULLINGCALLBACK
#define OSG_CLUSTERCULLINGCALLBACK 1

#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>

namespace osg {

/** Implements cluster culling to cull back facing drawables. Derived from
  * Drawable::CullCallback.
*/


class OSG_EXPORT ClusterCullingCallback : public Drawable::CullCallback, public NodeCallback
{
    public:

        ClusterCullingCallback();
        ClusterCullingCallback(const ClusterCullingCallback& ccc,const CopyOp& copyop);
        ClusterCullingCallback(const osg::Vec3& controlPoint, const osg::Vec3& normal, float deviation);
        ClusterCullingCallback(const osg::Drawable* drawable);

        META_Object(osg,ClusterCullingCallback);


        /** Computes the control point, normal, and deviation from the
          * given drawable contents. */
        void computeFrom(const osg::Drawable* drawable);
        
        /** Transform the ClusterCullingCallback's positional members to a new coordinate frame.*/
        void transform(const osg::Matrixd& matrix);

        void set(const osg::Vec3& controlPoint, const osg::Vec3& normal, float deviation, float radius);

        void setControlPoint(const osg::Vec3& controlPoint) { _controlPoint = controlPoint; }
        const osg::Vec3& getControlPoint() const { return _controlPoint; }

        void setNormal(const osg::Vec3& normal) { _normal = normal; }
        const osg::Vec3& getNormal() const { return _normal; }

        void setRadius(float radius) { _radius = radius; }
        float getRadius() const { return _radius; }

        void setDeviation(float deviation) { _deviation = deviation; }
        float getDeviation() const { return _deviation; }

        virtual bool cull(osg::NodeVisitor*, osg::Drawable*, osg::State*) const;

        /** Callback method called by the NodeVisitor when visiting a node.*/
        virtual void operator()(IVBF_SGNode* node, NodeVisitor* nv);


    protected:

        virtual ~ClusterCullingCallback() {} // IE¿ÉÄÜ´íÎó

        osg::Vec3    _controlPoint;
        osg::Vec3    _normal;
        float        _radius;
        float        _deviation;
};


}

#endif
