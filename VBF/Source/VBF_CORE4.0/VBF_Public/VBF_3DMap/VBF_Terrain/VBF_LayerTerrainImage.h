#ifndef OSGEARTH_IMAGE_TERRAIN_LAYER_H
#define OSGEARTH_IMAGE_TERRAIN_LAYER_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/ColorFilter.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceTile.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerTerrain.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>


class CVBF_Profile;


// Imageͼ���ѡ�����͸���ȡ�����͸��ɫ�������С���䡢��ͬLOD֮���Ƿ��ϡ���ɫ���ˣ�
class OSGEARTH_EXPORT ImageLayerOptions : public TerrainLayerOptions
{
public:
    ImageLayerOptions( const CVBF_Options& options =CVBF_Options() );     
    ImageLayerOptions( const std::string& name, const CVBF_OptionsDriverSourceTile& driverOpt =CVBF_OptionsDriverSourceTile() );

    virtual ~ImageLayerOptions();
public:

	// ͼ��͸����
    CVBF_Optional<float>& opacity() { return _opacity; }
    const CVBF_Optional<float>& opacity() const { return _opacity; }

	// ͼ��ɼ�����С�����Χ��camera range��
    CVBF_Optional<float>& minVisibleRange() { return _minRange; }
    const CVBF_Optional<float>& minVisibleRange() const { return _minRange; }

    // ͼ��ɼ�����������Χ
    CVBF_Optional<float>& maxVisibleRange() { return _maxRange; }
    const CVBF_Optional<float>& maxVisibleRange() const { return _maxRange; }

	// ����/��ȡ������ʱ��Ӱ���ļ���
    CVBF_Optional<URI>& noDataImageFilename() { return _noDataImageFilename; }
    const CVBF_Optional<URI>& noDataImageFilename() const { return _noDataImageFilename; }

	// ͼ���͸��ɫ
    CVBF_Optional<osg::Vec4ub>& transparentColor() { return _transparentColor; }
    const CVBF_Optional<osg::Vec4ub>& transparentColor() const { return _transparentColor; }
        
	// �Ƿ�����LOD���
    CVBF_Optional<bool>& lodBlending() { return _lodBlending; }
    const CVBF_Optional<bool>& lodBlending() const { return _lodBlending; }

    // ͼ�����ɫ��
    ColorFilterChain& colorFilters() { return _colorFilters; }
    const ColorFilterChain& colorFilters() const { return _colorFilters; }

	//xahg h00017 
    CVBF_Optional<bool>& share() { return _share; }
    const CVBF_Optional<bool>& share() const { return _share; }

public:

    virtual CVBF_Config getConfig() const { return getConfig(false); }
    virtual CVBF_Config getConfig( bool isolate ) const;
    virtual void mergeConfig( const CVBF_Config& conf );
        
private:
    void fromConfig( const CVBF_Config& conf );
    void setDefaults();

    CVBF_Optional<float>       _opacity;
    CVBF_Optional<float>       _minRange;
    CVBF_Optional<float>       _maxRange;
    CVBF_Optional<osg::Vec4ub> _transparentColor;
    CVBF_Optional<URI>         _noDataImageFilename;
    CVBF_Optional<bool>        _lodBlending;
    ColorFilterChain           _colorFilters;
	//xahg h00017
	CVBF_Optional<bool>        _share;
};

//--------------------------------------------------------------------


// ����Ӱ��ͼ�����Ա仯��֪ͨ�Ļص��ӿ�
struct ImageLayerCallback : public TerrainLayerCallback
{
    virtual void onOpacityChanged( class CVBF_LayerTerrainImage* layer ) { }
    virtual void onVisibleRangeChanged( class CVBF_LayerTerrainImage* layer ) {}
    virtual void onColorFiltersChanged( class CVBF_LayerTerrainImage* layer ) { }
    virtual ~ImageLayerCallback() { }
};

typedef void (ImageLayerCallback::*ImageLayerCallbackMethodPtr)(CVBF_LayerTerrainImage* layer);

typedef std::list< ref_ptr<ImageLayerCallback> > ImageLayerCallbackList;

//--------------------------------------------------------------------

// �ڲ��Ĺ����࣬���ں���������CVBFO_SourceTile����Ƭ
class ImageLayerTileProcessor 
{
public:
    ImageLayerTileProcessor( const ImageLayerOptions& options =ImageLayerOptions() );
    virtual ~ImageLayerTileProcessor() { }

    void init( const ImageLayerOptions& options, const osgDB::Options* dbOptions, bool layerInTargetProfile );
    void process( ref_ptr<osg::Image>& image ) const;

private:
    ImageLayerOptions                  _options;
    osg::Vec4f                         _chromaKey;
    ref_ptr<osg::Image>           _noDataImage;
    bool                               _layerInTargetProfile;
};

//--------------------------------------------------------------------

// Imageͼ��
class OSGEARTH_EXPORT CVBF_LayerTerrainImage : public CVBF_LayerTerrain
{
public:
    CVBF_LayerTerrainImage( const ImageLayerOptions& options );
    CVBF_LayerTerrainImage( const std::string& name, const CVBF_OptionsDriverSourceTile& driverOptions );
    CVBF_LayerTerrainImage( const ImageLayerOptions& options, CVBFO_SourceTile* tileSource );

    virtual ~CVBF_LayerTerrainImage();

public:
	// ��ȡͼ���ѡ���ʼ��ѡ�����ʱѡ�
    const ImageLayerOptions& getImageLayerOptions() const { return _runtimeOptions; }
    virtual const TerrainLayerOptions& getTerrainLayerRuntimeOptions() const { return _runtimeOptions; }

 	// ���/�Ƴ�һ���ص����������ڸ�ͼ������֪ͨ���Ա仯
    void addCallback( ImageLayerCallback* cb );
    void removeCallback( ImageLayerCallback* cb );

    /** Override: see CVBF_LayerTerrain */
    virtual void setTargetProfileHint( const CVBF_Profile* profile );

	// ���/�Ƴ�һ����ɫ������
    void addColorFilter( ColorFilter* filter );
    void removeColorFilter( ColorFilter* filter );

	// ��ȡ��ɫ����������
    const ColorFilterChain& getColorFilters() const;


public: // runtime properties

    // ����/��ȡͼ��ͼ���͸���ȣ�0..1] -> [͸��..��͸��]
    void setOpacity( float opacity );
    float getOpacity() const { return *_runtimeOptions.opacity(); }

    void disableLODBlending();
    bool isLODBlendingEnabled() const { return *_runtimeOptions.lodBlending(); }

    float getMinVisibleRange() const { return *_runtimeOptions.minVisibleRange();}
    void setMinVisibleRange( float minVisibleRange );

    float getMaxVisibleRange() const { return *_runtimeOptions.maxVisibleRange();}
    void setMaxVisibleRange( float maxVisibleRange );

    //xahg h00017
    CVBF_Optional<int>& shareImageUnit() { return _shareImageUnit; }
    const CVBF_Optional<int>& shareImageUnit() const { return _shareImageUnit; }
	//xahg h00017
	bool isShareEnabled() const { return *_runtimeOptions.share(); }


public:
    // ����һ����key��Ӧ��GeoImage����ͼ��ʹ��key��profile�����Զ�����ͶӰ��ƴ�ӡ��ü�
    virtual GeoImage createImage( const CVBF_TileKey& key, ProgressCallback* progress = 0, bool forceFallback =false);

    // ���Լ���profile����ͼ��
    GeoImage createImageInNativeProfile(const CVBF_TileKey& key, ProgressCallback* progress, bool forceFallback, bool& out_isFallback);

public: // CVBF_LayerTerrain override
    CacheBin* getCacheBin( const CVBF_Profile* profile );
	virtual int unref() const;
	virtual int ref() const;
protected:

    // Creates an image that's in the same profile as the provided key.
    GeoImage createImageInKeyProfile(const CVBF_TileKey& key, ProgressCallback* progress, bool forceFallback, bool& out_isFallback);

    // Fetches an image from the underlying CVBFO_SourceTile whose data matches that of the key extent.
    GeoImage createImageFromTileSource(const CVBF_TileKey& key, ProgressCallback* progress, bool forceFallback, bool& out_isFallback);

    // Fetches multiple images from the CVBFO_SourceTile; mosaics/reprojects/crops as necessary, and
    // returns a single tile. This is called by createImageFromTileSource() if the key profile
    // doesn't match the layer profile.
    GeoImage assembleImageFromTileSource(const CVBF_TileKey& key, ProgressCallback* progress, bool& out_isFallback);


    virtual void initTileSource();


protected:
    ImageLayerOptions                        _runtimeOptions;
    ref_ptr<CVBFO_SourceTile::ImageOperation> _preCacheOp;
    ref_ptr<osg::Image>                 _emptyImage;
    ImageLayerCallbackList                   _callbacks;

    //xahg h00017
    CVBF_Optional<int>                            _shareImageUnit;

    virtual void fireCallback( TerrainLayerCallbackMethodPtr method );
    virtual void fireCallback( ImageLayerCallbackMethodPtr method );

    void init();
    void initPreCacheOp();
};

typedef std::vector< ref_ptr<CVBF_LayerTerrainImage> > CVBF_LayersImage;



#endif // OSGEARTH_IMAGE_TERRAIN_LAYER_H
