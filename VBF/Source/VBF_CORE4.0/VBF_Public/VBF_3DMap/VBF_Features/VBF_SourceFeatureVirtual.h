#ifndef OSGEARTH_FEATURES_VIRTUAL_FEATURE_SOURCE
#define OSGEARTH_FEATURES_VIRTUAL_FEATURE_SOURCE

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Features/VBF_SourceFeature.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Layer.h>
#include <vector>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;
    using namespace osgEarth::Features;
    using namespace osgEarth::Symbology;

    // 判定：告诉多工器（multiplexer）对于给定的渲染器是否接受（或拒绝）一个feature
    struct OSGEARTHFEATURES_EXPORT FeaturePredicate : public ::CVBF_Referenced
    {
        virtual bool acceptFeature( Feature* f ) const =0;

        virtual ~FeaturePredicate() { }
    };

    // internal class
    struct FeatureSourceMapping
    {
        FeatureSourceMapping(FeatureSource* fs, FeaturePredicate* fp) : _source(fs), _predicate(fp) { }
        ref_ptr<FeatureSource>      _source;
        ref_ptr<FeaturePredicate>   _predicate;
    };
    typedef std::vector<FeatureSourceMapping> FeatureSourceMappingVector;


    class OSGEARTHFEATURES_EXPORT VirtualFeatureSource : public FeatureSource
    {
    public:
        VirtualFeatureSource() { }

        virtual ~VirtualFeatureSource() { }

        /**
         * Adds a feature source/predicate mapping. This FeatureSource will draw
         * from "source" and filter based on the predicate.
         */
        void add( FeatureSource* source, FeaturePredicate* predicate );

    public: // FeatureSource
        virtual FeatureCursor* createFeatureCursor( const Query& query );
        virtual void initialize( const osgDB::Options* options );
        virtual const FeatureProfile* createFeatureProfile();
        virtual const FeatureSchema& getSchema() const;
        virtual Feature* getFeature( FeatureID id ) { return 0L; }

    protected:
        FeatureSourceMappingVector _sources;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTH_FEATURES_VIRTUAL_FEATURE_SOURCE
