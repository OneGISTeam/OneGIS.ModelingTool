#ifndef OSGEARTH_MAP_FRAME_H
#define OSGEARTH_MAP_FRAME_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapInfo.h>

// CVBF_Map修订本的即时快照。 用该类获取CVBF_Map的安全拷贝（safe "copy"），不用担心使用时CVBF_Map被其他线程改变
class OSGEARTH_EXPORT CVBF_MapFrame
{
public:
    CVBF_MapFrame( const CVBF_Map* map, CVBF_Map::ModelParts parts =CVBF_Map::TERRAIN_LAYERS, const std::string& name ="" );	
    CVBF_MapFrame( const CVBF_MapFrame& frame, const std::string& name ="" );// 用新的名字拷贝构造（不需要同步，no sync happens）
    virtual ~CVBF_MapFrame() { }

    bool sync(); // 把该frame与源地图进行同步（仅在需要的时候），如果有新数据同步了返回true，否则返回false
    bool needsSync() const; // 是否有新的数据需要同步

    const CVBF_MapInfo& GetMapInfo() const { return m_MapInfo; }// 获取源地图的profile/rendering信息
    const CVBF_Profile* getProfile() const { return m_MapInfo.getProfile(); } // 方便的方法获取地图的profile
        

	// 图像图层的快照
    const CVBF_LayersImage& imageLayers() const { return m_ImageLayers; }
    CVBF_LayerTerrainImage* getImageLayerAt( int index ) const { return m_ImageLayers[index].get(); }
    CVBF_LayerTerrainImage* getImageLayerByUID( UID uid ) const;
    CVBF_LayerTerrainImage* getImageLayerByName( const std::string& name ) const;

    // 高程图层的快照
    const CVBF_LayerTerrainElevations& elevationLayers() const { return m_ElevationLayers; }
    CVBF_LayerTerrainElevation* getElevationLayerAt( int index ) const { return m_ElevationLayers[index].get(); }
    CVBF_LayerTerrainElevation* getElevationLayerByUID( UID uid ) const;
    CVBF_LayerTerrainElevation* getElevationLayerByName( const std::string& name ) const;

    // 模型图层的快照
    const CVBF_LayersModel& modelLayers() const { return m_ModelLayers; }
    CVBF_LayerModel* getModelLayerAt(int index) const { return m_ModelLayers[index].get(); }

    // Mask图层的快照
    const CVBF_LayersMask& terrainMaskLayers() const { return m_MaskLayers; }

    // 获取图层在图层快照中的索引
	// 获取图层的索引
    int indexOf( CVBF_LayerTerrainImage* layer ) const;
    int indexOf( CVBF_LayerTerrainElevation* layer ) const;
    int indexOf( CVBF_LayerModel* layer ) const;

    // 获取该快照同步的 地图数据模型的修订本（版本号）
    Revision getRevision() const { return _mapDataModelRevision; }

    // 检测指定键值（key）的所有数据（高程和影像）是否被缓存
    bool isCached( const CVBF_TileKey& key ) const;


    bool getHeightField( const CVBF_TileKey& key, bool fallback, ref_ptr<osg::HeightField>& out_hf,
                        bool* out_isFallback =0L, bool bToHAE = true,
                        ElevationSamplePolicy samplePolicy = SAMPLE_FIRST_VALID, ProgressCallback*  progress =0L ) const;

private:
    bool _initialized;

    observer_ptr<const CVBF_Map> m_opMap;

    std::string          m_sName;
    CVBF_MapInfo         m_MapInfo;
    CVBF_Map::ModelParts m_parts;
    Revision             _mapDataModelRevision;

    // 图层快照
    CVBF_LayersImage     m_ImageLayers;
    CVBF_LayerTerrainElevations m_ElevationLayers;
    CVBF_LayersModel     m_ModelLayers;
    CVBF_LayersMask      m_MaskLayers;

    friend class CVBF_Map;
};



#endif // OSGEARTH_MAP_FRAME_H
