#ifndef OSGEARTHFEATURES_FEATURE_SOURCE_INDEX_NODE_H
#define OSGEARTHFEATURES_FEATURE_SOURCE_INDEX_NODE_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/FeatureDrawSet.h>
#include <VBF_3DMap/VBF_Features/VBF_SourceFeature.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>

namespace osgEarth { namespace Features
{
   
	// 矢量数据源索引的选项
    class OSGEARTHFEATURES_EXPORT FeatureSourceIndexOptions
    {
    public:
        FeatureSourceIndexOptions(const CVBF_Config& conf =CVBF_Config());

        /** Wheter to embed the actual Feature objects in the index (instead of
         *  just the FeatureID). This is useful for feature sources that cannot
         *  be queried by ID (e.g., streaming data like TFS) */
        CVBF_Optional<bool>& embedFeatures() { return _embedFeatures; }
        const CVBF_Optional<bool>& embedFeatures() const { return _embedFeatures; }

    public:
        CVBF_Config getConfig() const;

    private:
        CVBF_Optional<bool> _embedFeatures;
    };


    // Feature索引的接口
    class FeatureSourceIndex
    {
    public: // tagging functions
        virtual void tagPrimitiveSets( osg::Drawable* drawable, Feature* feature ) const =0;
        virtual void tagNode( osg::IVBF_SGNode* node, Feature* feature ) const =0;

        virtual ~FeatureSourceIndex() { }
    };

    /**
     * Maintains an index that maps FeatureID's from a FeatureSource to PrimitiveSets within the subgraph's geometry.
     */
    class OSGEARTHFEATURES_EXPORT FeatureSourceIndexNode : public osg::CVBF_SGNodeGroup, public FeatureSourceIndex
    {
    public:
        FeatureSourceIndexNode( FeatureSource* featureSource, const FeatureSourceIndexOptions& options );
        virtual ~FeatureSourceIndexNode() { }


    public: // FeatureSourceIndex

        /**
         * Tags all the primitive sets in a Drawable with the specified FeatureID.
         */
        void tagPrimitiveSets( osg::Drawable* drawable, Feature* feature ) const;

        /**
         * Tags a node with the specified FeatureID.
         */
        void tagNode( osg::IVBF_SGNode* node, Feature* feature ) const;


    public:
        /**
         * The feature source tied to this node 
         */
        FeatureSource* getFeatureSource() { return _featureSource.get(); }

        /**
         * Traverses this node's subgraph and rebuilds the feature index based on
         * any tagged drawables found. (See tagPrimitiveSets for tagging drawables).
         */
        void reindex();

        /**
         * Given a primitive set, returns the feature ID corresponding to that set.
         *
         * @param pset Primitive set to query
         * @param output Holds the result of the query, if returning true
         * @return true if successful
         */
        bool getFID(osg::PrimitiveSet* pset, FeatureID& output) const;

        /**
         * Gets the Feature ID corresponding to a drawable and a prim index. This is
         * useful to call using the results of an intersection test.
         *
         * @param drawable       Drawable for which to lookup the feature ID
         * @param primitiveIndex Index of the primitive to look up
         * @param output         Holds the result of the query, if returning true
         * @return true if successful
         */
        bool getFID(osg::Drawable* drawable, int primitiveIndex, FeatureID& output) const;

        /**
         * Given a FeatureID, returns the collection of drawable/primitiveset combinations
         * corresponding to that feature.
         *
         * @param fid Feature ID to look up
         * @return Corresponding collection of primitive sets (empty if the query fails)
         */
        FeatureDrawSet& getDrawSet( const FeatureID& fid );

        /**
         * Given a FeatureID, returns the cached feature.
         *
         * @param fid     Feature ID to look up
         * @param output  cached feature 
         * @return true if successful 
         */
        bool getFeature(const FeatureID& fid, const Feature*& output) const;

        // 获取该节点下的所有要素（杜莹添加：2016-05-20）
        typedef std::map< FeatureID, ref_ptr<const Feature> > FeatureMap;
        FeatureMap& GetFeatureMap() { return _features; }

    private:
        ref_ptr<FeatureSource> _featureSource;

        typedef std::map<FeatureID, FeatureDrawSet> FeatureIDDrawSetMap;
        FeatureIDDrawSetMap _drawSets;

        struct Collect : public osg::NodeVisitor
        {
            Collect(FeatureIDDrawSetMap&);
            void apply(osg::IVBF_SGNode&);
            void apply(osg::IVBF_SGNodeGeometry&);
            FeatureIDDrawSetMap& _index;
            unsigned _psets;
        };
        
        FeatureSourceIndexOptions _options;
        mutable FeatureMap _features; // cache

    public:
        virtual const char* className() const { return "FeatureSourceIndexNode"; }
        virtual const char* libraryName() const { return "VBF_Features"; }
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FEATURE_SOURCE_INDEX_NODE_H
