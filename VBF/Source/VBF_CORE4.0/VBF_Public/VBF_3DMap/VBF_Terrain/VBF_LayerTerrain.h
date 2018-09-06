#ifndef OSGEARTH_TERRAIN_LAYER_H
#define OSGEARTH_TERRAIN_LAYER_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Cache.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CachePolicy.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Layer.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceTile.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_3DMap/VBF_Terrain/VBF_HTTPClient.h>


// 地形图层的初始化（和序列化）选项。地形图层是金字塔的。最大最小LOD、最大最小分辨率、数据源等
class OSGEARTH_EXPORT TerrainLayerOptions : public CVBF_Options
{
public:
    TerrainLayerOptions( const CVBF_Options& options =CVBF_Options() );
    TerrainLayerOptions( const std::string& name, const CVBF_OptionsDriverSourceTile& driverOptions );

    virtual ~TerrainLayerOptions();

    // 图层名称
    std::string& name() { return m_sName; }
    const std::string& name() const { return m_sName; }

	// 获取明确的垂直基准标识（vertical datum identifier），覆盖瓦片（tile source）指定的垂直基准
    CVBF_Optional<std::string>& verticalDatum() { return _vertDatum; }
    const CVBF_Optional<std::string>& verticalDatum() const { return _vertDatum; }

	// 获取数据驱动器的选项
    CVBF_Optional<CVBF_OptionsDriverSourceTile>& driver() { return _driver; }
    const CVBF_Optional<CVBF_OptionsDriverSourceTile>& driver() const { return _driver; }

	// 获取/设置本层生成数据的最小LOD
    CVBF_Optional<unsigned>& minLevel() { return _minLevel; }
    const CVBF_Optional<unsigned>& minLevel() const { return _minLevel; }

	// 获取/设置本层生成数据的最小分辨率，单位为X/像素，X为图层数据源数据的基本单位
    CVBF_Optional<double>& minResolution() { return _minResolution; }
    const CVBF_Optional<double>& minResolution() const { return _minResolution; }

 	// 获取/设置本层生成数据的最大LOD
    CVBF_Optional<unsigned>& maxLevel() { return _maxLevel; }
    const CVBF_Optional<unsigned>& maxLevel() const { return _maxLevel; }

 	// 获取/设置本层生成数据的最大分辨率，单位为X/像素，X为图层数据源数据的基本单位
    CVBF_Optional<double>& maxResolution() { return _maxResolution; }
    const CVBF_Optional<double>& maxResolution() const { return _maxResolution; }
        
    // 是否使用该图层，false意味着该图层依然保留在地图模型中，但不被地形引擎（terrain engine）使用。
    // ！！！不能在运行时更改"enabled"状态。
    CVBF_Optional<bool>& enabled() { return _enabled; }
    const CVBF_Optional<bool>& enabled() const { return _enabled; }

	// 是否渲染该图层（是否可见）
    CVBF_Optional<bool>& visible() { return _visible; }
    const CVBF_Optional<bool>& visible() const { return _visible; }

	// 如果需要裁剪时，是否采用精确裁剪
    CVBF_Optional<bool>& exactCropping() { return _exactCropping; }
    const CVBF_Optional<bool>& exactCropping() const { return _exactCropping; }

	// 是否重新投影瓦片的大小
    CVBF_Optional<unsigned int>& reprojectedTileSize() { return _reprojectedTileSize; }
    const CVBF_Optional<unsigned int>& reprojectedTileSize() const { return _reprojectedTileSize; }

	// 明确的缓存ID，用于唯一标识匹配图层瓦片源的缓存
    CVBF_Optional<std::string>& cacheId() { return _cacheId; }
    const CVBF_Optional<std::string>& cacheId() const { return _cacheId; }

	// 缓存数据时采用的格式，可以是一个模拟类型（mime type）和一个文件扩展名
    CVBF_Optional<std::string>& cacheFormat() { return _cacheFormat; }
    const CVBF_Optional<std::string>& cacheFormat() const { return _cacheFormat; }

	// 缓存的策略
    CVBF_Optional<CachePolicy>& cachePolicy() { return _cachePolicy; }
    const CVBF_Optional<CachePolicy>& cachePolicy() const { return _cachePolicy; }
        
	// 加载数据的权重（用于多线程加载策略）
    CVBF_Optional<float>& loadingWeight() { return _loadingWeight; }
    const CVBF_Optional<float>& loadingWeight() const { return _loadingWeight; }

	// 瓦片范围扩展的比例，用于镶嵌瓦片的时候，该功能用于增加捕获瓦片的数量，以保证捕获足够的数据（与输入瓦片重叠）
    CVBF_Optional<double>& edgeBufferRatio() { return _edgeBufferRatio;}
    const CVBF_Optional<double>& edgeBufferRatio() const { return _edgeBufferRatio; }

	// 代理服务器的hostname/port，用于HTTP通信（Default = no proxy）
    CVBF_Optional<CVBF_ProxySettings>& proxySettings() { return _proxySettings; }
    const CVBF_Optional<CVBF_ProxySettings>& proxySettings() const { return _proxySettings; }

public:
	// 获取/合并图层配置
    virtual CVBF_Config getConfig() const { return getConfig(false); }
    virtual CVBF_Config getConfig( bool isolate ) const;
    virtual void mergeConfig( const CVBF_Config& conf );

private:
    void fromConfig( const CVBF_Config& conf );
    void setDefaults();
       
    std::string                      m_sName;			// 图层名
    CVBF_Optional<std::string>       _vertDatum;	// 垂直基准

    CVBF_Optional<CVBF_OptionsDriverSourceTile> _driver;

    CVBF_Optional<unsigned>          _minLevel;		// 最小LOD
    CVBF_Optional<unsigned>          _maxLevel;		// 最大LOD
    CVBF_Optional<double>            _minResolution;// 最小分辨率率
    CVBF_Optional<double>            _maxResolution;// 最大分辨率
    CVBF_Optional<float>             _loadingWeight;// 加载权重
    CVBF_Optional<bool>              _exactCropping;// 是否精确裁剪
    CVBF_Optional<bool>              _enabled;		// 是否使用
    CVBF_Optional<bool>              _visible;		// 是否可见
    CVBF_Optional<unsigned>          _reprojectedTileSize;
    CVBF_Optional<double>            _edgeBufferRatio;        

    CVBF_Optional<std::string>       _cacheId;
    CVBF_Optional<std::string>       _cacheFormat;
    CVBF_Optional<CachePolicy>       _cachePolicy;
    CVBF_Optional<CVBF_ProxySettings>     _proxySettings;
};

// 地形图层的回调函数：向外部通知地形图层的属性变化
struct TerrainLayerCallback : public ::CVBF_Referenced
{
    virtual void onVisibleChanged( class CVBF_LayerTerrain* layer ) { }
    virtual ~TerrainLayerCallback() { }
};

typedef void (TerrainLayerCallback::*TerrainLayerCallbackMethodPtr)(CVBF_LayerTerrain* layer);


// 地表图层( image or elevation)
class OSGEARTH_EXPORT CVBF_LayerTerrain : public CVBF_Layer
{
protected:
    CVBF_LayerTerrain( const TerrainLayerOptions& initOptions, TerrainLayerOptions* runtimeOptions );       
    CVBF_LayerTerrain( const TerrainLayerOptions& initOptions, TerrainLayerOptions*runtimeOptions, CVBFO_SourceTile* tileSource );
    virtual ~CVBF_LayerTerrain();

public:
   
	// 获取图层的选项（初始化选项、运行时选项）
    const TerrainLayerOptions& getInitialOptions() const { return _initOptions; }
    const TerrainLayerOptions& getTerrainLayerRuntimeOptions() const { return *_runtimeOptions; }

	// 是否启用该图层。Note, a layer is enabled/disabled once and its status cannot be changed.
    bool getEnabled() const { return *_runtimeOptions->enabled(); }

	// 是否绘制（或别的应用）该图层
    void setVisible( bool value );
    bool getVisible() const { return getEnabled() && *_runtimeOptions->visible(); }

	// 获取图层名
    const std::string& getName() const { return getTerrainLayerRuntimeOptions().name(); }

	// 获取该图层的profile
    const CVBF_Profile* getProfile() const;

 	// 获取该图层所用的数据源
    CVBFO_SourceTile* getTileSource() const;

	// 获取该图层的瓦片大小
    unsigned int getTileSize() const;
        
	// 该图层是否描绘动态数据，也就是说瓦片数据是否会变化
    bool isDynamic() const;

	// 给定的瓦片键值对于该层是否有效
    virtual bool isKeyValid(const CVBF_TileKey& key) const;

	// 给定的瓦片键值对应的数据是否在缓存中
    virtual bool isCached(const CVBF_TileKey& key) const;
        
	// 告诉地形图层将用于什么样的场景轮廓（球形、平面形），这是可选项，由于含有更多如何使用数据的信息，对图层优化有用
    virtual void setTargetProfileHint( const CVBF_Profile* profile );

  	// The cache bin for storing data generated by this layer
    virtual CacheBin* getCacheBin( const CVBF_Profile* profile );
        
	// 获取该图层所用的缓存
    Cache* getCache() const { return _cache.get(); }

  	// 是否仅用缓存中的数据
    bool isCacheOnly() const 
	{
        return 
            _runtimeOptions->cachePolicy().isSet() &&
            _runtimeOptions->cachePolicy()->usage() == CachePolicy::USAGE_CACHE_ONLY;
    }

public: // 重载Layer的接口

    virtual IVBF_SequenceControl* getSequenceControl();


public:
        
	// 存储在缓存中的地形图层的元数据
    struct CacheBinMetadata
    {
        CacheBinMetadata() { }

        CacheBinMetadata( const CacheBinMetadata& rhs ) :
            _empty        ( rhs._empty ),
            _cacheBinId   ( rhs._cacheBinId ),
            _sourceName   ( rhs._sourceName ),
            _sourceDriver ( rhs._sourceDriver ),                
            _sourceProfile( rhs._sourceProfile ),
            _cacheProfile ( rhs._cacheProfile ) { }

        CacheBinMetadata( const CVBF_Config& conf )
        {
            _empty = conf.isEmpty();
            conf.getIfSet   ( "cachebin_id",    _cacheBinId );
            conf.getIfSet   ( "source_name",    _sourceName );
            conf.getIfSet   ( "source_driver",  _sourceDriver );                
            conf.getObjIfSet( "source_profile", _sourceProfile );
            conf.getObjIfSet( "cache_profile",  _cacheProfile );
        }

        CVBF_Config getConfig() const
        {
            CVBF_Config conf( "osgearth_terrainlayer_cachebin" );
            conf.addIfSet   ( "cachebin_id",    _cacheBinId );
            conf.addIfSet   ( "source_name",    _sourceName );
            conf.addIfSet   ( "source_driver",  _sourceDriver );                
            conf.addObjIfSet( "source_profile", _sourceProfile );
            conf.addObjIfSet( "cache_profile",  _cacheProfile );
            return conf;
        }

        bool						  _empty;
        CVBF_Optional<std::string>    _cacheBinId;
        CVBF_Optional<std::string>    _sourceName;
        CVBF_Optional<std::string>    _sourceDriver;            
        CVBF_Optional<CVBF_OptionsProfile> _sourceProfile;
        CVBF_Optional<CVBF_OptionsProfile> _cacheProfile;
    };

	// 获取缓存的信息
    bool getCacheBinMetadata( const CVBF_Profile* profile, CacheBinMetadata& output );

protected:

    virtual void initTileSource();

    CacheBin* getCacheBin( const CVBF_Profile* profile, const std::string& binId );

protected:

    ref_ptr<CVBFO_SourceTile>       _tileSource;
    ref_ptr<const CVBF_Profile>    _profile;
    ref_ptr<const CVBF_Profile>    _targetProfileHint;
    bool                           _tileSourceInitAttempted;
    bool                           _tileSourceInitFailed;
    unsigned                       _tileSize;  
    ref_ptr<osgDB::Options>			_dbOptions;

    void setCachePolicy( const CachePolicy& cp );
    const CachePolicy& getCachePolicy() const;

private:
    std::string                    m_sName;
    std::string                    _referenceURI;
    OpenThreads::Mutex             _initTileSourceMutex;
    TerrainLayerOptions            _initOptions;
    TerrainLayerOptions*           _runtimeOptions;

    ref_ptr<Cache>            _cache;

    // maps profile signature to cache bin pointer.
    struct CacheBinInfo
    {
        ref_ptr<CacheBin>     _bin;
        CVBF_Optional<CacheBinMetadata> _metadata;
    };
    typedef std::map< std::string, CacheBinInfo > CacheBinInfoMap; // indexed by profile signature

    CacheBinInfoMap          _cacheBins;
    CVBF_ReadWriteMutex      _cacheBinsMutex;

    void init();
    virtual void fireCallback( TerrainLayerCallbackMethodPtr method ) =0;

    friend class CVBF_Map;

    void setDBOptions( const osgDB::Options* dbOptions );
    void initializeCachePolicy( const osgDB::Options* );
    void storeProxySettings( osgDB::Options* );

	// 设置图层的缓存
	// 备忘录: 任何时候设置都是合法的？
    void setCache( Cache* cache );
};

typedef std::vector<ref_ptr<CVBF_LayerTerrain> > TerrainLayerVector;


#endif // OSGEARTH_TERRAIN_LAYER_H
