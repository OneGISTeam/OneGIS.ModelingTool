#ifndef OSGEARTH_ANNO_LOCALIZED_NODE_H
#define OSGEARTH_ANNO_LOCALIZED_NODE_H 1

#include <VBF_3DMap/VBF_Annotation/AnnotationNode.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeOverlay.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>

namespace osgEarth { namespace Annotation
{	
    using namespace osgEarth;

    /**
     * Base class for node that is localized at a specific geographic point.
     *
     * Don't use this class *directly*. If you are trying to add your own 
     * osg::Node as an Annotation, use the LocalizedGeometryNode instead.
     */
    class OSGEARTHANNO_EXPORT LocalizedNode : public PositionedAnnotationNode
    {
    public:
        META_AnnotationNodeAbstract(VBF_Annotation, LocalizedNode);

        LocalizedNode(CVBFO_SGNodeMap* mapNode,const GeoPoint& pos=GeoPoint::INVALID );
        LocalizedNode( CVBFO_SGNodeMap* mapNode, const CVBF_Config& conf );


    public: // PositionedAnnotationNode
        virtual bool setPosition( const GeoPoint& p );
        virtual GeoPoint getPosition() const;


    public: // MapNodeObserver

        virtual void setMapNode( CVBFO_SGNodeMap* mapNode );

    public:
        /**
         * Sets a "local offset" position - for an ECEF map, this is an offset in 
         * the local tangent plane of the node that is applied to the geometry.
         */
        void setLocalOffset( const osg::Vec3d& offset );

        /**
         * Gets the local tangent plane -space offset.
         */
        const osg::Vec3d& getLocalOffset() const;

        /**
         * Sets a local rotation - a rotation relative to the local tangent plane
         * of the geometry.
         */
        void setLocalRotation( const osg::Quat& rotation );

        /**
         * Gets the local tangent plane -space rotation.
         */
        const osg::Quat& getLocalRotation() const;

        /**
         * Local scale factor.
         */
        void setScale( const osg::Vec3f& scale );
        const osg::Vec3f& getScale() const { return _scale; }

        /**
         * Enables or disable automatic horizon culling
         */
        void setHorizonCulling( bool value );
        bool getHorizonCulling() const;


    public: // osg::Node

        virtual osg::BoundingSphere computeBound() const;


    protected:

        /**
         * The matrix transform that controls this node's position
         */
        virtual osg::IVBF_SGNodeGroupTransformMatrix* getTransform() =0;


    protected:
        bool                               _initComplete;
        bool                               _horizonCulling;
        GeoPoint                           _mapPosition;
        osg::Vec3f                         _scale;
        osg::Vec3d                         _localOffset;
        osg::Quat                          _localRotation;
        ref_ptr<osg::NodeCallback>    _cullByHorizonCB;

        friend class Decoration;
        
        // re-clamped the vert mesh based on a new terrain tile coming in
        virtual void reclamp( const CVBF_TileKey& key, osg::IVBF_SGNode* tile, const CVBF_Terrain* terrain );

        // refreshed the main transform with data from an asbolute point
        bool updateTransform(const GeoPoint& absPt, osg::IVBF_SGNode* patch =0L);

        // checks for overlay requirements, and if needed, installs a decorator node above
        // the passed-in node to facilitate the clamping/draping. The proper usage pattern
        // is:  node = applyAltitudePolicy(node, style)
        osg::IVBF_SGNode* applyAltitudePolicy( osg::IVBF_SGNode* node, const Style& style );

        // hidden copy constructor
        LocalizedNode() { }
        LocalizedNode(const LocalizedNode& rhs, const osg::CopyOp& op=osg::CopyOp::DEEP_COPY_ALL) { }
        virtual ~LocalizedNode() { }


    private:

        void init();
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTH_ANNO_LOCALIZED_NODE_H
