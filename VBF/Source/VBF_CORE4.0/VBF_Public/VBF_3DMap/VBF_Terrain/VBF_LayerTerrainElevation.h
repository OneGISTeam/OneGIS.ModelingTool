#ifndef OSGEARTH_ELEVATION_TERRAIN_LAYER_H
#define OSGEARTH_ELEVATION_TERRAIN_LAYER_H 1

#include <VBF_3DMap/VBF_Terrain/VBF_LayerTerrain.h>
#include <Types/MixinVector>

// 高程图层的初始化和序列化选项
class OSGEARTH_EXPORT ElevationLayerOptions : public TerrainLayerOptions
{
public:
    ElevationLayerOptions( const CVBF_Options& options =CVBF_Options() );
	// 根据数据源驱动器配置选项构建
    ElevationLayerOptions( const std::string& name, const CVBF_OptionsDriverSourceTile& driverOptions );

    virtual ~ElevationLayerOptions();

public:
    virtual CVBF_Config getConfig() const { return getConfig(false); }
    virtual CVBF_Config getConfig( bool isolate ) const;
    virtual void mergeConfig( const CVBF_Config& conf );
        
private:
    void fromConfig( const CVBF_Config& conf );
    void setDefaults();
};



// 高程图层回调函数（预留扩展）
struct ElevationLayerCallback : public TerrainLayerCallback
{
    //TODO
};

typedef void (ElevationLayerCallback::*ElevationLayerCallbackMethodPtr)(class CVBF_LayerTerrainElevation* layer);

typedef std::list< ref_ptr<ElevationLayerCallback> > ElevationLayerCallbackList;



// 高程图层
class OSGEARTH_EXPORT CVBF_LayerTerrainElevation : public CVBF_LayerTerrain
{
public:

	// 根据指定的配置选项构建高程图层，该选项需包含必要的数据源驱动器配置选项
    CVBF_LayerTerrainElevation( const ElevationLayerOptions& options );

	// 根据名字和数据源驱动器配置选项构建高程图层
    CVBF_LayerTerrainElevation( const std::string& name, const CVBF_OptionsDriverSourceTile& driverOptions );

 	// 根据图层选项和用户提供的数据源创建高程图层
    CVBF_LayerTerrainElevation( const ElevationLayerOptions& options, CVBFO_SourceTile* tileSource );

    virtual ~CVBF_LayerTerrainElevation() { }

	// 获取创建该图层的初始选项
    const ElevationLayerOptions& getElevationLayerOptions() const { return _runtimeOptions; }
    virtual const TerrainLayerOptions& getTerrainLayerRuntimeOptions() const { return _runtimeOptions; }

	// 添加/移除一个图层属性更新回调
    void addCallback( ElevationLayerCallback* cb );
    void removeCallback( ElevationLayerCallback* cb );

public: // methods

	// 创建一个与给定TileKey的范围与LOD对应的高度图
    virtual GeoHeightField createHeightField( const CVBF_TileKey& key, ProgressCallback* progress =0L );

protected:
        
	// 从瓦片数据源（tile source）直接创建一个高度图
    osg::HeightField* createHeightFieldFromTileSource( const CVBF_TileKey& key, ProgressCallback* progress);

    // assembles tiles from a layer that is not in the same profile as the map, and
    // returns a single tile in the map's profile.
    osg::HeightField* assembleHeightFieldFromTileSource( const CVBF_TileKey& key, ProgressCallback*  progress );
        
    virtual std::string suggestCacheFormat() const;

    virtual void initTileSource();

private:
    ElevationLayerOptions _runtimeOptions;

    ElevationLayerCallbackList _callbacks;
    virtual void fireCallback( TerrainLayerCallbackMethodPtr method );
    virtual void fireCallback( ElevationLayerCallbackMethodPtr method );

    ref_ptr<CVBFO_SourceTile::HeightFieldOperation> _preCacheOp;

    void init();
};


// 高程图层列表
class OSGEARTH_EXPORT CVBF_LayerTerrainElevations : public osg::MixinVector< ref_ptr<CVBF_LayerTerrainElevation> >
{
public:

	// 通过采样高程图层创建高度场
    bool createHeightField( const CVBF_TileKey& key, bool fallback, const CVBF_Profile* haeProfile,
				ElevationInterpolation interpolation, ElevationSamplePolicy samplePolicy,
				ref_ptr<osg::HeightField>& out_result, bool* out_isFallback, ProgressCallback* progress ) const;

public:

    CVBF_LayerTerrainElevations();
    CVBF_LayerTerrainElevations(const CVBF_LayerTerrainElevations& rhs);

	// 设置createHeightField时瓦片的大小。默认时，返回数据源图层中瓦片最大的瓦片大小
    void setExpressTileSize( unsigned tileSize );

private:
    CVBF_Optional<unsigned> m_onTileSize;
};

#endif // OSGEARTH_ELEVATION_TERRAIN_LAYER_H
