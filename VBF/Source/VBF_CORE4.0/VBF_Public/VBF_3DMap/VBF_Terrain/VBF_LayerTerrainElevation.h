#ifndef OSGEARTH_ELEVATION_TERRAIN_LAYER_H
#define OSGEARTH_ELEVATION_TERRAIN_LAYER_H 1

#include <VBF_3DMap/VBF_Terrain/VBF_LayerTerrain.h>
#include <Types/MixinVector>

// �߳�ͼ��ĳ�ʼ�������л�ѡ��
class OSGEARTH_EXPORT ElevationLayerOptions : public TerrainLayerOptions
{
public:
    ElevationLayerOptions( const CVBF_Options& options =CVBF_Options() );
	// ��������Դ����������ѡ���
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



// �߳�ͼ��ص�������Ԥ����չ��
struct ElevationLayerCallback : public TerrainLayerCallback
{
    //TODO
};

typedef void (ElevationLayerCallback::*ElevationLayerCallbackMethodPtr)(class CVBF_LayerTerrainElevation* layer);

typedef std::list< ref_ptr<ElevationLayerCallback> > ElevationLayerCallbackList;



// �߳�ͼ��
class OSGEARTH_EXPORT CVBF_LayerTerrainElevation : public CVBF_LayerTerrain
{
public:

	// ����ָ��������ѡ����߳�ͼ�㣬��ѡ���������Ҫ������Դ����������ѡ��
    CVBF_LayerTerrainElevation( const ElevationLayerOptions& options );

	// �������ֺ�����Դ����������ѡ����߳�ͼ��
    CVBF_LayerTerrainElevation( const std::string& name, const CVBF_OptionsDriverSourceTile& driverOptions );

 	// ����ͼ��ѡ����û��ṩ������Դ�����߳�ͼ��
    CVBF_LayerTerrainElevation( const ElevationLayerOptions& options, CVBFO_SourceTile* tileSource );

    virtual ~CVBF_LayerTerrainElevation() { }

	// ��ȡ������ͼ��ĳ�ʼѡ��
    const ElevationLayerOptions& getElevationLayerOptions() const { return _runtimeOptions; }
    virtual const TerrainLayerOptions& getTerrainLayerRuntimeOptions() const { return _runtimeOptions; }

	// ���/�Ƴ�һ��ͼ�����Ը��»ص�
    void addCallback( ElevationLayerCallback* cb );
    void removeCallback( ElevationLayerCallback* cb );

public: // methods

	// ����һ�������TileKey�ķ�Χ��LOD��Ӧ�ĸ߶�ͼ
    virtual GeoHeightField createHeightField( const CVBF_TileKey& key, ProgressCallback* progress =0L );

protected:
        
	// ����Ƭ����Դ��tile source��ֱ�Ӵ���һ���߶�ͼ
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


// �߳�ͼ���б�
class OSGEARTH_EXPORT CVBF_LayerTerrainElevations : public osg::MixinVector< ref_ptr<CVBF_LayerTerrainElevation> >
{
public:

	// ͨ�������߳�ͼ�㴴���߶ȳ�
    bool createHeightField( const CVBF_TileKey& key, bool fallback, const CVBF_Profile* haeProfile,
				ElevationInterpolation interpolation, ElevationSamplePolicy samplePolicy,
				ref_ptr<osg::HeightField>& out_result, bool* out_isFallback, ProgressCallback* progress ) const;

public:

    CVBF_LayerTerrainElevations();
    CVBF_LayerTerrainElevations(const CVBF_LayerTerrainElevations& rhs);

	// ����createHeightFieldʱ��Ƭ�Ĵ�С��Ĭ��ʱ����������Դͼ������Ƭ������Ƭ��С
    void setExpressTileSize( unsigned tileSize );

private:
    CVBF_Optional<unsigned> m_onTileSize;
};

#endif // OSGEARTH_ELEVATION_TERRAIN_LAYER_H
