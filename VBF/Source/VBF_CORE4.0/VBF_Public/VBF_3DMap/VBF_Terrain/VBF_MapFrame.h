#ifndef OSGEARTH_MAP_FRAME_H
#define OSGEARTH_MAP_FRAME_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapInfo.h>

// CVBF_Map�޶����ļ�ʱ���ա� �ø����ȡCVBF_Map�İ�ȫ������safe "copy"�������õ���ʹ��ʱCVBF_Map�������̸߳ı�
class OSGEARTH_EXPORT CVBF_MapFrame
{
public:
    CVBF_MapFrame( const CVBF_Map* map, CVBF_Map::ModelParts parts =CVBF_Map::TERRAIN_LAYERS, const std::string& name ="" );	
    CVBF_MapFrame( const CVBF_MapFrame& frame, const std::string& name ="" );// ���µ����ֿ������죨����Ҫͬ����no sync happens��
    virtual ~CVBF_MapFrame() { }

    bool sync(); // �Ѹ�frame��Դ��ͼ����ͬ����������Ҫ��ʱ�򣩣������������ͬ���˷���true�����򷵻�false
    bool needsSync() const; // �Ƿ����µ�������Ҫͬ��

    const CVBF_MapInfo& GetMapInfo() const { return m_MapInfo; }// ��ȡԴ��ͼ��profile/rendering��Ϣ
    const CVBF_Profile* getProfile() const { return m_MapInfo.getProfile(); } // ����ķ�����ȡ��ͼ��profile
        

	// ͼ��ͼ��Ŀ���
    const CVBF_LayersImage& imageLayers() const { return m_ImageLayers; }
    CVBF_LayerTerrainImage* getImageLayerAt( int index ) const { return m_ImageLayers[index].get(); }
    CVBF_LayerTerrainImage* getImageLayerByUID( UID uid ) const;
    CVBF_LayerTerrainImage* getImageLayerByName( const std::string& name ) const;

    // �߳�ͼ��Ŀ���
    const CVBF_LayerTerrainElevations& elevationLayers() const { return m_ElevationLayers; }
    CVBF_LayerTerrainElevation* getElevationLayerAt( int index ) const { return m_ElevationLayers[index].get(); }
    CVBF_LayerTerrainElevation* getElevationLayerByUID( UID uid ) const;
    CVBF_LayerTerrainElevation* getElevationLayerByName( const std::string& name ) const;

    // ģ��ͼ��Ŀ���
    const CVBF_LayersModel& modelLayers() const { return m_ModelLayers; }
    CVBF_LayerModel* getModelLayerAt(int index) const { return m_ModelLayers[index].get(); }

    // Maskͼ��Ŀ���
    const CVBF_LayersMask& terrainMaskLayers() const { return m_MaskLayers; }

    // ��ȡͼ����ͼ������е�����
	// ��ȡͼ�������
    int indexOf( CVBF_LayerTerrainImage* layer ) const;
    int indexOf( CVBF_LayerTerrainElevation* layer ) const;
    int indexOf( CVBF_LayerModel* layer ) const;

    // ��ȡ�ÿ���ͬ���� ��ͼ����ģ�͵��޶������汾�ţ�
    Revision getRevision() const { return _mapDataModelRevision; }

    // ���ָ����ֵ��key�����������ݣ��̺߳�Ӱ���Ƿ񱻻���
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

    // ͼ�����
    CVBF_LayersImage     m_ImageLayers;
    CVBF_LayerTerrainElevations m_ElevationLayers;
    CVBF_LayersModel     m_ModelLayers;
    CVBF_LayersMask      m_MaskLayers;

    friend class CVBF_Map;
};



#endif // OSGEARTH_MAP_FRAME_H
