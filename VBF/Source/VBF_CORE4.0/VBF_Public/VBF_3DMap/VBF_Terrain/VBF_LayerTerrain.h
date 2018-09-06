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


// ����ͼ��ĳ�ʼ���������л���ѡ�����ͼ���ǽ������ġ������СLOD�������С�ֱ��ʡ�����Դ��
class OSGEARTH_EXPORT TerrainLayerOptions : public CVBF_Options
{
public:
    TerrainLayerOptions( const CVBF_Options& options =CVBF_Options() );
    TerrainLayerOptions( const std::string& name, const CVBF_OptionsDriverSourceTile& driverOptions );

    virtual ~TerrainLayerOptions();

    // ͼ������
    std::string& name() { return m_sName; }
    const std::string& name() const { return m_sName; }

	// ��ȡ��ȷ�Ĵ�ֱ��׼��ʶ��vertical datum identifier����������Ƭ��tile source��ָ���Ĵ�ֱ��׼
    CVBF_Optional<std::string>& verticalDatum() { return _vertDatum; }
    const CVBF_Optional<std::string>& verticalDatum() const { return _vertDatum; }

	// ��ȡ������������ѡ��
    CVBF_Optional<CVBF_OptionsDriverSourceTile>& driver() { return _driver; }
    const CVBF_Optional<CVBF_OptionsDriverSourceTile>& driver() const { return _driver; }

	// ��ȡ/���ñ����������ݵ���СLOD
    CVBF_Optional<unsigned>& minLevel() { return _minLevel; }
    const CVBF_Optional<unsigned>& minLevel() const { return _minLevel; }

	// ��ȡ/���ñ����������ݵ���С�ֱ��ʣ���λΪX/���أ�XΪͼ������Դ���ݵĻ�����λ
    CVBF_Optional<double>& minResolution() { return _minResolution; }
    const CVBF_Optional<double>& minResolution() const { return _minResolution; }

 	// ��ȡ/���ñ����������ݵ����LOD
    CVBF_Optional<unsigned>& maxLevel() { return _maxLevel; }
    const CVBF_Optional<unsigned>& maxLevel() const { return _maxLevel; }

 	// ��ȡ/���ñ����������ݵ����ֱ��ʣ���λΪX/���أ�XΪͼ������Դ���ݵĻ�����λ
    CVBF_Optional<double>& maxResolution() { return _maxResolution; }
    const CVBF_Optional<double>& maxResolution() const { return _maxResolution; }
        
    // �Ƿ�ʹ�ø�ͼ�㣬false��ζ�Ÿ�ͼ����Ȼ�����ڵ�ͼģ���У��������������棨terrain engine��ʹ�á�
    // ����������������ʱ����"enabled"״̬��
    CVBF_Optional<bool>& enabled() { return _enabled; }
    const CVBF_Optional<bool>& enabled() const { return _enabled; }

	// �Ƿ���Ⱦ��ͼ�㣨�Ƿ�ɼ���
    CVBF_Optional<bool>& visible() { return _visible; }
    const CVBF_Optional<bool>& visible() const { return _visible; }

	// �����Ҫ�ü�ʱ���Ƿ���þ�ȷ�ü�
    CVBF_Optional<bool>& exactCropping() { return _exactCropping; }
    const CVBF_Optional<bool>& exactCropping() const { return _exactCropping; }

	// �Ƿ�����ͶӰ��Ƭ�Ĵ�С
    CVBF_Optional<unsigned int>& reprojectedTileSize() { return _reprojectedTileSize; }
    const CVBF_Optional<unsigned int>& reprojectedTileSize() const { return _reprojectedTileSize; }

	// ��ȷ�Ļ���ID������Ψһ��ʶƥ��ͼ����ƬԴ�Ļ���
    CVBF_Optional<std::string>& cacheId() { return _cacheId; }
    const CVBF_Optional<std::string>& cacheId() const { return _cacheId; }

	// ��������ʱ���õĸ�ʽ��������һ��ģ�����ͣ�mime type����һ���ļ���չ��
    CVBF_Optional<std::string>& cacheFormat() { return _cacheFormat; }
    const CVBF_Optional<std::string>& cacheFormat() const { return _cacheFormat; }

	// ����Ĳ���
    CVBF_Optional<CachePolicy>& cachePolicy() { return _cachePolicy; }
    const CVBF_Optional<CachePolicy>& cachePolicy() const { return _cachePolicy; }
        
	// �������ݵ�Ȩ�أ����ڶ��̼߳��ز��ԣ�
    CVBF_Optional<float>& loadingWeight() { return _loadingWeight; }
    const CVBF_Optional<float>& loadingWeight() const { return _loadingWeight; }

	// ��Ƭ��Χ��չ�ı�����������Ƕ��Ƭ��ʱ�򣬸ù����������Ӳ�����Ƭ���������Ա�֤�����㹻�����ݣ���������Ƭ�ص���
    CVBF_Optional<double>& edgeBufferRatio() { return _edgeBufferRatio;}
    const CVBF_Optional<double>& edgeBufferRatio() const { return _edgeBufferRatio; }

	// �����������hostname/port������HTTPͨ�ţ�Default = no proxy��
    CVBF_Optional<CVBF_ProxySettings>& proxySettings() { return _proxySettings; }
    const CVBF_Optional<CVBF_ProxySettings>& proxySettings() const { return _proxySettings; }

public:
	// ��ȡ/�ϲ�ͼ������
    virtual CVBF_Config getConfig() const { return getConfig(false); }
    virtual CVBF_Config getConfig( bool isolate ) const;
    virtual void mergeConfig( const CVBF_Config& conf );

private:
    void fromConfig( const CVBF_Config& conf );
    void setDefaults();
       
    std::string                      m_sName;			// ͼ����
    CVBF_Optional<std::string>       _vertDatum;	// ��ֱ��׼

    CVBF_Optional<CVBF_OptionsDriverSourceTile> _driver;

    CVBF_Optional<unsigned>          _minLevel;		// ��СLOD
    CVBF_Optional<unsigned>          _maxLevel;		// ���LOD
    CVBF_Optional<double>            _minResolution;// ��С�ֱ�����
    CVBF_Optional<double>            _maxResolution;// ���ֱ���
    CVBF_Optional<float>             _loadingWeight;// ����Ȩ��
    CVBF_Optional<bool>              _exactCropping;// �Ƿ�ȷ�ü�
    CVBF_Optional<bool>              _enabled;		// �Ƿ�ʹ��
    CVBF_Optional<bool>              _visible;		// �Ƿ�ɼ�
    CVBF_Optional<unsigned>          _reprojectedTileSize;
    CVBF_Optional<double>            _edgeBufferRatio;        

    CVBF_Optional<std::string>       _cacheId;
    CVBF_Optional<std::string>       _cacheFormat;
    CVBF_Optional<CachePolicy>       _cachePolicy;
    CVBF_Optional<CVBF_ProxySettings>     _proxySettings;
};

// ����ͼ��Ļص����������ⲿ֪ͨ����ͼ������Ա仯
struct TerrainLayerCallback : public ::CVBF_Referenced
{
    virtual void onVisibleChanged( class CVBF_LayerTerrain* layer ) { }
    virtual ~TerrainLayerCallback() { }
};

typedef void (TerrainLayerCallback::*TerrainLayerCallbackMethodPtr)(CVBF_LayerTerrain* layer);


// �ر�ͼ��( image or elevation)
class OSGEARTH_EXPORT CVBF_LayerTerrain : public CVBF_Layer
{
protected:
    CVBF_LayerTerrain( const TerrainLayerOptions& initOptions, TerrainLayerOptions* runtimeOptions );       
    CVBF_LayerTerrain( const TerrainLayerOptions& initOptions, TerrainLayerOptions*runtimeOptions, CVBFO_SourceTile* tileSource );
    virtual ~CVBF_LayerTerrain();

public:
   
	// ��ȡͼ���ѡ���ʼ��ѡ�����ʱѡ�
    const TerrainLayerOptions& getInitialOptions() const { return _initOptions; }
    const TerrainLayerOptions& getTerrainLayerRuntimeOptions() const { return *_runtimeOptions; }

	// �Ƿ����ø�ͼ�㡣Note, a layer is enabled/disabled once and its status cannot be changed.
    bool getEnabled() const { return *_runtimeOptions->enabled(); }

	// �Ƿ���ƣ�����Ӧ�ã���ͼ��
    void setVisible( bool value );
    bool getVisible() const { return getEnabled() && *_runtimeOptions->visible(); }

	// ��ȡͼ����
    const std::string& getName() const { return getTerrainLayerRuntimeOptions().name(); }

	// ��ȡ��ͼ���profile
    const CVBF_Profile* getProfile() const;

 	// ��ȡ��ͼ�����õ�����Դ
    CVBFO_SourceTile* getTileSource() const;

	// ��ȡ��ͼ�����Ƭ��С
    unsigned int getTileSize() const;
        
	// ��ͼ���Ƿ���涯̬���ݣ�Ҳ����˵��Ƭ�����Ƿ��仯
    bool isDynamic() const;

	// ��������Ƭ��ֵ���ڸò��Ƿ���Ч
    virtual bool isKeyValid(const CVBF_TileKey& key) const;

	// ��������Ƭ��ֵ��Ӧ�������Ƿ��ڻ�����
    virtual bool isCached(const CVBF_TileKey& key) const;
        
	// ���ߵ���ͼ�㽫����ʲô���ĳ������������Ρ�ƽ���Σ������ǿ�ѡ����ں��и������ʹ�����ݵ���Ϣ����ͼ���Ż�����
    virtual void setTargetProfileHint( const CVBF_Profile* profile );

  	// The cache bin for storing data generated by this layer
    virtual CacheBin* getCacheBin( const CVBF_Profile* profile );
        
	// ��ȡ��ͼ�����õĻ���
    Cache* getCache() const { return _cache.get(); }

  	// �Ƿ���û����е�����
    bool isCacheOnly() const 
	{
        return 
            _runtimeOptions->cachePolicy().isSet() &&
            _runtimeOptions->cachePolicy()->usage() == CachePolicy::USAGE_CACHE_ONLY;
    }

public: // ����Layer�Ľӿ�

    virtual IVBF_SequenceControl* getSequenceControl();


public:
        
	// �洢�ڻ����еĵ���ͼ���Ԫ����
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

	// ��ȡ�������Ϣ
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

	// ����ͼ��Ļ���
	// ����¼: �κ�ʱ�����ö��ǺϷ��ģ�
    void setCache( Cache* cache );
};

typedef std::vector<ref_ptr<CVBF_LayerTerrain> > TerrainLayerVector;


#endif // OSGEARTH_TERRAIN_LAYER_H
