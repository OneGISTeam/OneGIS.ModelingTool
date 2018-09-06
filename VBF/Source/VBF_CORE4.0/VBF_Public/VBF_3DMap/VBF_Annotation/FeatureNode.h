
#ifndef OSGEARTH_ANNO_FEATURE_NODE_H
#define OSGEARTH_ANNO_FEATURE_NODE_H 1

#include <VBF_3DMap/VBF_Annotation/AnnotationNode.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/GeometryCompiler.h>
#include <Types/VBF_Polytope.h>

namespace osgEarth { namespace Annotation
{
    using namespace osgEarth;
    using namespace osgEarth::Features;
    using namespace osgEarth::Symbology;

    /**
     * Renders a single feature. Since no feature profile is provided,
     * the feature must contain geometry that is in the same SRS as the map.
     * The feature must also include the Style you wish to use.
     */
    class OSGEARTHANNO_EXPORT FeatureNode : public AnnotationNode
    {
    public:
        META_AnnotationNode(VBF_Annotation, FeatureNode);

         FeatureNode(  CVBFO_SGNodeMap* mapNode, Feature* feature, bool draped   =false, 
            const GeometryCompilerOptions& options = GeometryCompilerOptions() );

        virtual ~FeatureNode() { }

        /**
         * The feature that this node will render.
         */
        void setFeature( Feature* feature );
        Feature* getFeature() { return _feature.get(); }
        const Feature* getFeature() const { return _feature.get(); }

        /** Whether the feature is draped on the terrain */
        bool isDraped() const { return _draped; }

        void init();

    public: // AnnotationNode

        virtual osg::IVBF_SGNodeGroup* getAttachPoint();

        virtual void setStyle(const Style& style);

    public: // MapNodeObserver

        virtual void setMapNode( CVBFO_SGNodeMap* mapNode );

    public:

        FeatureNode(CVBFO_SGNodeMap* mapNode, const CVBF_Config& conf, const osgDB::Options* options);
        virtual CVBF_Config getConfig() const;

    protected:
        ref_ptr<Feature>        _feature;
        GeometryCompilerOptions      _options;
        bool                         _draped;
        osg::IVBF_SGNodeGroup*       _attachPoint;
        osg::Polytope                _featurePolytope;

        FeatureNode() { }
        FeatureNode(const FeatureNode& rhs, const osg::CopyOp& op) { }
        
        virtual void reclamp( const CVBF_TileKey& key, osg::IVBF_SGNode* tile, const CVBF_Terrain* );
        
    private:
        void clampMesh( osg::IVBF_SGNode* terrainModel );
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTH_ANNO_FEATURE_NODE_H
