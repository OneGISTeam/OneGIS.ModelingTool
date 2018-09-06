#ifndef OSGEARTHFEATURES_FEATURELIST_SOURCE_H
#define OSGEARTHFEATURES_FEATURELIST_SOURCE_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/FeatureCursor.h>
#include <VBF_3DMap/VBF_Features/VBF_SourceFeature.h>

#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>

namespace osgEarth { namespace Features
{   
	// 用于内存中的临时的数据源
    class OSGEARTHFEATURES_EXPORT FeatureListSource : public osgEarth::Features::FeatureSource
    {
    public:

		// 创建一个空的feature list源（source）
        FeatureListSource();

		// 使用默认的范围创建一个空的feature list源，该数据源可以利用默认的范围在列表为空时返回一个有效的feature profile
        FeatureListSource(const CVBF_GeoExtent& defaultExtent );
        virtual ~FeatureListSource() { }

        virtual FeatureCursor* createFeatureCursor( const Symbology::Query& query );

        virtual bool isWritable() const { return true; }
        virtual bool deleteFeature(FeatureID fid);
        virtual int getFeatureCount() const { return _features.size(); }
        virtual Feature* getFeature( FeatureID fid );
        virtual bool insertFeature(Feature* feature);
        virtual Geometry::Type getGeometryType() const { return Geometry::TYPE_UNKNOWN; }

        FeatureList& getFeatures() { return _features; }
    public: // Styling

        virtual bool hasEmbeddedStyles() const { return false; }

    public: 
        virtual const char* className() const { return "FeatureListSource"; }
        virtual const char* libraryName() const { return "VBF_Features"; }

    protected:
        virtual const FeatureProfile* createFeatureProfile();

        FeatureList      _features;
        CVBF_GeoExtent   _defaultExtent;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FEATURELIST_SOURCE_H

