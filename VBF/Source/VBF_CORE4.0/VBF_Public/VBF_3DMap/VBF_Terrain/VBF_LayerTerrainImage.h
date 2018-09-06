#ifndef OSGEARTH_IMAGE_TERRAIN_LAYER_H
#define OSGEARTH_IMAGE_TERRAIN_LAYER_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/ColorFilter.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceTile.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerTerrain.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>


class CVBF_Profile;


// Image图层的选项（包括透明度、叠加透明色、最大最小区间、不同LOD之间是否混合、颜色过滤）
class OSGEARTH_EXPORT ImageLayerOptions : public TerrainLayerOptions
{
public:
    ImageLayerOptions( const CVBF_Options& options =CVBF_Options() );     
    ImageLayerOptions( const std::string& name, const CVBF_OptionsDriverSourceTile& driverOpt =CVBF_OptionsDriverSourceTile() );

    virtual ~ImageLayerOptions();
public:

	// 图层透明度
    CVBF_Optional<float>& opacity() { return _opacity; }
    const CVBF_Optional<float>& opacity() const { return _opacity; }

	// 图层可见的最小相机范围（camera range）
    CVBF_Optional<float>& minVisibleRange() { return _minRange; }
    const CVBF_Optional<float>& minVisibleRange() const { return _minRange; }

    // 图层可见的最大相机范围
    CVBF_Optional<float>& maxVisibleRange() { return _maxRange; }
    const CVBF_Optional<float>& maxVisibleRange() const { return _maxRange; }

	// 设置/获取无数据时的影像文件名
    CVBF_Optional<URI>& noDataImageFilename() { return _noDataImageFilename; }
    const CVBF_Optional<URI>& noDataImageFilename() const { return _noDataImageFilename; }

	// 图像的透明色
    CVBF_Optional<osg::Vec4ub>& transparentColor() { return _transparentColor; }
    const CVBF_Optional<osg::Vec4ub>& transparentColor() const { return _transparentColor; }
        
	// 是否启用LOD混合
    CVBF_Optional<bool>& lodBlending() { return _lodBlending; }
    const CVBF_Optional<bool>& lodBlending() const { return _lodBlending; }

    // 图层的滤色器
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


// 接收影像图层属性变化的通知的回调接口
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

// 内部的工具类，用于后处理来自于CVBFO_SourceTile的瓦片
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

// Image图层
class OSGEARTH_EXPORT CVBF_LayerTerrainImage : public CVBF_LayerTerrain
{
public:
    CVBF_LayerTerrainImage( const ImageLayerOptions& options );
    CVBF_LayerTerrainImage( const std::string& name, const CVBF_OptionsDriverSourceTile& driverOptions );
    CVBF_LayerTerrainImage( const ImageLayerOptions& options, CVBFO_SourceTile* tileSource );

    virtual ~CVBF_LayerTerrainImage();

public:
	// 获取图层的选项（初始化选项、运行时选项）
    const ImageLayerOptions& getImageLayerOptions() const { return _runtimeOptions; }
    virtual const TerrainLayerOptions& getTerrainLayerRuntimeOptions() const { return _runtimeOptions; }

 	// 添加/移除一个回调函数，用于该图层向外通知属性变化
    void addCallback( ImageLayerCallback* cb );
    void removeCallback( ImageLayerCallback* cb );

    /** Override: see CVBF_LayerTerrain */
    virtual void setTargetProfileHint( const CVBF_Profile* profile );

	// 添加/移除一个颜色过滤器
    void addColorFilter( ColorFilter* filter );
    void removeColorFilter( ColorFilter* filter );

	// 获取颜色过滤器数组
    const ColorFilterChain& getColorFilters() const;


public: // runtime properties

    // 设置/获取图像图层的透明度，0..1] -> [透明..不透明]
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
    // 创建一个与key对应的GeoImage，该图像使用key的profile，并自动被重投影、拼接、裁剪
    virtual GeoImage createImage( const CVBF_TileKey& key, ProgressCallback* progress = 0, bool forceFallback =false);

    // 用自己的profile创建图像
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
