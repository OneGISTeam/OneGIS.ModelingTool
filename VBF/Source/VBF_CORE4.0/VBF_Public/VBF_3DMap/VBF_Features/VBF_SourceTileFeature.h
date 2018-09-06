#ifndef OSGEARTHFEATURES_FEATURE_TILE_SOURCE_H
#define OSGEARTHFEATURES_FEATURE_TILE_SOURCE_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/VBF_SourceFeature.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceTile.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SGDB/ReaderWriter>
#include <list>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

    class OSGEARTHFEATURES_EXPORT FeatureTileSourceOptions : public CVBF_OptionsDriverSourceTile
    {
    public: // serializable properties

        CVBF_Optional<CVBF_OptionsDriverSourceFeature>& featureOptions() { return _featureOptions; }
        const CVBF_Optional<CVBF_OptionsDriverSourceFeature>& featureOptions() const { return _featureOptions; }

        ref_ptr<StyleSheet>& styles() { return _styles; }
        const ref_ptr<StyleSheet>& styles() const { return _styles; }

        //TODO: deprecate in favor of convert filter
        CVBF_Optional<Geometry::Type>& geometryTypeOverride() { return _geomTypeOverride; }
        const CVBF_Optional<Geometry::Type>& geometryTypeOverride() const { return _geomTypeOverride; }

    public:
        /** A live feature source instance to use. Note, this does not serialize. */
        ref_ptr<FeatureSource>& featureSource() { return _featureSource; }
        const ref_ptr<FeatureSource>& featureSource() const { return _featureSource; }

        FeatureTileSourceOptions( const CVBF_Options& rhs =CVBF_Options() );

        virtual ~FeatureTileSourceOptions() { }

    public:
        virtual CVBF_Config getConfig() const;

    protected:
        virtual void mergeConfig( const CVBF_Config& conf );

        CVBF_Optional<CVBF_OptionsDriverSourceFeature> _featureOptions;
        ref_ptr<StyleSheet>       _styles;
        CVBF_Optional<Geometry::Type>       _geomTypeOverride;
        ref_ptr<FeatureSource>    _featureSource;

    private:
        void fromConfig( const CVBF_Config& conf );
    };


	// ��Ƭ����Դ������ʸ������������Ƭ�� 
    class OSGEARTHFEATURES_EXPORT FeatureTileSource : public CVBFO_SourceTile
    {
    public:      
        FeatureTileSource( const CVBF_OptionsDriverSourceTile& options =CVBF_OptionsDriverSourceTile() );

	public:// ���غ���
        virtual Status initialize( const osgDB::Options* options );
        virtual osg::Image* createImage( const CVBF_TileKey& key, ProgressCallback* progress );

    public: // properties:

 		// ��ȡʸ������Դ
        FeatureSource* getFeatureSource() { return _features.get(); }

        // ����ʸ������Դ�������ȡʸ�����ݣ��� ��Map������ø����initialize����֮ǰ���ô˺������ǺϷ��ģ�֮����øú�����Ч
        void setFeatureSource( FeatureSource* source );

    protected:

        /** Creates an implementation-specific data object to be passed to buildNodeForStyle */
        virtual CVBF_Referenced* createBuildData() { return NULL; }     

		// ��style��Ⱦ�����ĵ����б�
        virtual bool renderFeaturesForStyle( const Style& style, const FeatureList& features,
            CVBF_Referenced* buildData, const CVBF_GeoExtent&  imageExtent, osg::Image* out_image ) 
		{ 
			return false; 
		}            
            
 		// �ڵ���renderFeaturesForStyle()֮ǰ��ͼ����д���
        virtual bool preProcess( osg::Image* image, CVBF_Referenced* buildData ) { return true; }
            
		// �ڵ���renderFeaturesForStyle()֮���ͼ����д���
        virtual bool postProcess( osg::Image* image, CVBF_Referenced* buildData ) { return true; }

    public:

        // META_Object specialization:
        virtual osg::CVBF_Object* cloneType() const { return 0; } // cloneType() not appropriate
        virtual osg::CVBF_Object* clone(const osg::CopyOp&) const { return 0; } // clone() not appropriate
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const FeatureTileSource*>(obj)!=NULL; }
        virtual const char* className() const { return "FeatureTileSource"; }
        virtual const char* libraryName() const { return "VBF_Features"; }

    protected:
        virtual ~FeatureTileSource() { }

        ref_ptr<FeatureSource> _features;
        const FeatureTileSourceOptions _options;
        ref_ptr<const CVBF_Map> _map;
        bool _initialized;
        
        bool queryAndRenderFeaturesForStyle( const Style& style, const Query& query,CVBF_Referenced* data, 
                                              const CVBF_GeoExtent& imageExtent, osg::Image* out_image );
    };

    } } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FEATURE_TILE_SOURCE_H




