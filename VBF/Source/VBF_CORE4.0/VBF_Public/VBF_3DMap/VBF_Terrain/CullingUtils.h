#ifndef OSGEARTH_CULLING_UTILS_H
#define OSGEARTH_CULLING_UTILS_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <Types/VBF_Optional.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/ClusterCullingCallback.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupCoordSys.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <Types/Vec3d>
#include <Types/Vec3>
#include <VBF_Engine/VBF_SGUtil/CullVisitor>

namespace osgEarth
{    
    // һ���Զ����ClusterCullingCallback����RTT���������ͶӰ���ʱ��������
    class SuperClusterCullingCallback : public osg::ClusterCullingCallback
    {
    public:
        bool cull(osg::NodeVisitor* nv, osg::Drawable* , osg::State*) const;
    };

    // �����۴زü��Ĺ��ߺ���
    class OSGEARTH_EXPORT ClusterCullingFactory
    {
    public:
        // !!!ǧ��Ҫ�� CCC(cluster culling callback)����һ��transform�£�����ֻ�ھ�������ռ���������

        // ����һ���۴زü��ص�
        static osg::NodeCallback* create( osg::IVBF_SGNode* node, const osg::Vec3d& ecefControlPoint );

        // ͬ�ϣ���ʹ����һ�ַ������������ֻ��ʹ��һ����������������ĸ��㷨���á�
        // Keeping this for now since it works with the feature setup..
        static osg::NodeCallback* create2( osg::IVBF_SGNode* node, const osg::Vec3d& ecefControlPoint );

        /**
         * Creates a cluster culling callback and installs it on the node. If the node is
         * a transform, it will create a group above the transform and install the callback
         * on that group instead.
         */
        static osg::IVBF_SGNode* createAndInstall( osg::IVBF_SGNode* node, const osg::Vec3d& ecefControlPoint );

        // ʹ�ñ�׼��������һ���۴زü��ص�
        static osg::NodeCallback* create(const osg::Vec3& controlPoint, const osg::Vec3& normal, float deviation, float radius);
    };


    // �򵥵Ĳü�ƽ��ص� (a simpler version of ClusterCullingCallback)
    struct OSGEARTH_EXPORT CullNodeByNormal : public osg::NodeCallback 
	{
        osg::Vec3d _normal;
        CullNodeByNormal( const osg::Vec3d& normal );
        void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);
    };

    struct CullDrawableByNormal : public osg::Drawable::CullCallback 
	{
        osg::Vec3d _normal;
        CullDrawableByNormal( const osg::Vec3d& normal ) : _normal(normal) { }

        bool cull(osg::NodeVisitor* nv, osg::Drawable* drawable, osg::State* state) const 
		{
            return nv && nv->getEyePoint() * _normal <= 0;
        }
    };

    // ����������ü� //!!��
    struct OSGEARTH_EXPORT CullNodeByEllipsoid : public osg::NodeCallback 
	{
        double _minRadius;
        CullNodeByEllipsoid( const osg::EllipsoidModel* model );
        void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);
    };

	// ��ƽ�߲ü�
    struct OSGEARTH_EXPORT CullNodeByHorizon : public osg::NodeCallback 
	{
        observer_ptr<osg::IVBF_SGNodeGroupTransformMatrix> _xform;
        osg::Vec3d _world;
        double _r, _r2;
        CullNodeByHorizon( const osg::Vec3d& world, const osg::EllipsoidModel* model );
        CullNodeByHorizon( osg::IVBF_SGNodeGroupTransformMatrix* xform, const osg::EllipsoidModel* model );
        void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv );
    };

    struct OSGEARTH_EXPORT CullNodeByFrameNumber : public osg::NodeCallback
	{
        unsigned _frame;
        CullNodeByFrameNumber() : _frame(0) { }
        void operator()( osg::IVBF_SGNode* node, osg::NodeVisitor* nv ) 
		{
            if ( nv->getFrameStamp()->getFrameNumber() - _frame <= 1 )
                traverse(node, nv);
        }
    };

    struct DisableSubgraphCulling : public osg::NodeCallback
    {
        void operator()(osg::IVBF_SGNode* n, osg::NodeVisitor* v);
    };

    struct StaticBound : public osg::IVBF_SGNode::ComputeBoundingSphereCallback
    {
        osg::BoundingSphere _bs;
        StaticBound(const osg::BoundingSphere& bs) : _bs(bs) { }
        osg::BoundingSphere computeBound(const osg::IVBF_SGNode&) const { return _bs; }
    };

    /**
     * �򵥵��ڵ��ü��ص� that does a ray interseciton between the eyepoint
     * and a world point and doesn't draw if there are intersections with the node.
     */
    struct OSGEARTH_EXPORT OcclusionCullingCallback : public osg::NodeCallback
    {
        OcclusionCullingCallback( const osg::Vec3d& world, osg::IVBF_SGNode* node);

        const osg::Vec3d& getWorld() const;
        void setWorld( const osg::Vec3d& world);
        double getMaxRange() const;
        void setMaxRange( double maxRange);
        void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);

        ref_ptr<osg::IVBF_SGNode> _node;
        osg::Vec3d _world;
        osg::Vec3d _prevWorld;
        osg::Vec3d _prevEye;
        bool _visible;
        double _maxRange;
        double _maxRange2;
    };

    struct OSGEARTH_EXPORT Culling
    {
        static osgUtil::CullVisitor* asCullVisitor(osg::NodeVisitor* nv);
        static osgUtil::CullVisitor* asCullVisitor(osg::NodeVisitor& nv) { return asCullVisitor(&nv); }

        /** General user data to calculate once and pass down with a CullVisitor. */
        struct CullUserData : public ::CVBF_Referenced
        {
            CVBF_Optional<double> _cameraAltitude;
        };

        static CullUserData* getCullUserData(osgUtil::CullVisitor* cv) {
            return cv ? dynamic_cast<CullUserData*>(cv->getUserData()) : 0L; }
    };

    /**
     * Node Visitor that proxies the CullVisitor but uses a separate
     * frustum for bounds-culling.
     */
    class ProxyCullVisitor : public osg::NodeVisitor, public osg::CullStack
    {
    private:
        osgUtil::CullVisitor* _cv;
        osg::Polytope         _proxyFrustum;
        osg::Polytope         _proxyProjFrustum;
        osg::Matrix           _proxyModelViewMatrix;
        osg::Matrix           _proxyProjMatrix;

    public:
        ProxyCullVisitor( osgUtil::CullVisitor* cv, const osg::Matrix& proj, const osg::Matrix& view );

        // access to the underlying cull visitor.
        osgUtil::CullVisitor* getCullVisitor() { return _cv; }

    public: // proxy functions:
        osg::Vec3 getEyePoint() const;
        osg::Vec3 getViewPoint() const;
        float getDistanceToEyePoint(const osg::Vec3& pos, bool useLODScale) const;
        float getDistanceFromEyePoint(const osg::Vec3& pos, bool useLODScale) const;
        float getDistanceToViewPoint(const osg::Vec3& pos, bool useLODScale) const;

    protected: // custom culling functions:

        bool isCulledByProxyFrustum(osg::IVBF_SGNode& node);
        bool isCulledByProxyFrustum(const osg::BoundingBox& bbox);
        
        osgUtil::CullVisitor::value_type distance(const osg::Vec3& coord,const osg::Matrix& matrix);

        void handle_cull_callbacks_and_traverse(osg::IVBF_SGNode& node);

        void apply(osg::IVBF_SGNode& node);
        void apply(osg::IVBF_SGNodeGroupTransform& node);
        void apply(osg::IVBF_SGNodeGeometry& node);
    };
}

//-----------------------------------------------------------------------------------
// ȫ�ֺ������ж�ĳ��Ŀ����Ƿ�λ�ڵ����棨���Ƿ񱻲ü�����
//-----------------------------------------------------------------------------------
class IVBF_View;

OSGEARTH_EXPORT bool VBF_IsClipedByEarth(IVBF_View* pIView,double R, const osg::Vec3d& ptWorld);

#endif
