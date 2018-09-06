#ifndef OSGEARTH_MAPNODE_H
#define OSGEARTH_MAPNODE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNodeOptions.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeTerrainEngine.h>
#include <VBF_3DMap/VBF_Terrain/VBF_OceanFloorTexture.h>

using namespace osgEarth;


class CVBF_MapNodeCullData;
class CVBF_Terrain;
class CVBFO_SGNodeDecoratorTerrainOverlay;



// CVBF_Map�γɵĳ���ͼ���ڵ㣬CVBF_Map������ģ�͡�CVBFO_SGNodeMap�����ݵ���ͼ
class OSGEARTH_EXPORT CVBFO_SGNodeMap : public osg::CVBF_SGNodeGroup
{
public:
    // ͨ�������б��".earth"ת��һ��CVBFO_SGNodeMap
    static CVBFO_SGNodeMap* load( class ::ArgumentParser& arguments );

public:
    CVBFO_SGNodeMap();
    CVBFO_SGNodeMap( const CVBF_OptionsMapNode& options );
    CVBFO_SGNodeMap( CVBF_Map* pMap );//ͨ��CVBF_Map����һ���յ�CVBFO_SGNodeMap
    CVBFO_SGNodeMap( CVBF_Map* pMap, const CVBF_OptionsMapNode& options );
 public:

    virtual const char* libraryName() const { return "osgEarth"; }
    virtual const char* className() const { return "CVBFO_SGNodeMap"; }

    // ��ȡCVBFO_SGNodeMap��Ӧ����Ⱦ����CVBF_Map
    const CVBF_Map* GetMap() const;
          CVBF_Map* GetMap();
  
	// ��ȡ�ռ�Map�Ĳο�����ݺ���
    const CVBF_SpatialReference* GetMapSRS() const;

	// ��ȡ�ڴ��еĵ��γ���
    const CVBF_Terrain* getTerrain() const;
		  CVBF_Terrain* getTerrain();

    // �ӳ���ͼ�в�������CVBFO_SGNodeMap���������򷵻�NULL
    static CVBFO_SGNodeMap* findMapNode( osg::IVBF_SGNode* graph, unsigned traversalMask =~0 );
    static CVBFO_SGNodeMap* get( osg::IVBF_SGNode* graph, unsigned travMask =~0 ) { return findMapNode(graph, travMask); }

 
	// ����ģ���Ƿ���geocentric��
    bool isGeocentric() const;

    // ��ȡģ�ͽڵ㣨�������е�CVBF_LayerModel��Ӧ��Node��
    osg::IVBF_SGNodeGroup* getModelLayerGroup() const;

    // ��ȡ�ض�CVBF_LayerModel��Ӧ��Node
    osg::IVBF_SGNode* getModelLayerNode( CVBF_LayerModel* layer ) const;

	// ���/�Ƴ����ε�װ������decorates��
    void addTerrainDecorator( osg::IVBF_SGNodeGroup* decorator );
    void removeTerrainDecorator( osg::IVBF_SGNodeGroup* decorator );

    // ��ȡ��ͼ�ڵ�ĸ���װ������ͨ������Ҫֱ�ӷ��ʣ����ǰ�װһ��CVBFO_SGNodeOverlayDrapeable
    CVBFO_SGNodeDecoratorTerrainOverlay* getOverlayDecorator() { return m_pOverlayDecorator; }

    // ��ȡ��ͼ�ڵ��������
    const CVBF_OptionsMapNode& GetMapNodeOptions() const;

	// ��ȡ��Ⱦ���α���ĵ�������
    CVBFO_SGNodeTerrainEngine* getTerrainEngine() const;

	// ��.earth�ļ�����<external>�ڵ㣬�ýڵ�ɱ�EARTH��ȡ���������κδ����������������ֻ�Ӧ�ò�
	const CVBF_Config& externalConfig() const { return _externalConf; }
		  CVBF_Config& externalConfig() { return _externalConf; }

    // ��Ǳ�ڵĵ��������������Զ��������ϳɼ�����texture compositor technique����
    void setCompositorTechnique( class TextureCompositorTechnique* tech );

	// ��ȡ��������ָ�루��Ө��ӣ�2018-02-08��
	CVBF_OceanFloorTexture* GetOceanFloorTexture() { return &m_OceanFloorTexture; }

public: // special purpose

    CVBFO_SGNodeMap( CVBF_Map* pMap, const CVBF_OptionsMapNode& options, bool initMap );

public: // ���� osg::Node
    virtual osg::BoundingSphere computeBound() const;
    virtual void traverse( class osg::NodeVisitor& nv );
protected:    
    virtual ~CVBFO_SGNodeMap();

private:

    ref_ptr<CVBF_Map>				m_ipMap;

    ref_ptr<osg::IVBF_SGNodeGroup>	m_ipNodeModels;
    ref_ptr<osg::IVBF_SGNodeGroup>	m_ipNodeOverlayModels;

    CVBFO_SGNodeDecoratorTerrainOverlay* m_pOverlayDecorator;
    CVBF_OptionsMapNode				_mapNodeOptions;
    CVBF_Config								_externalConf;

    // keep track of nodes created by model layers
    typedef std::map<CVBF_LayerModel*,osg::IVBF_SGNode*> ModelLayerNodeMap;
    ModelLayerNodeMap        _modelLayerNodes;
    osg::IVBF_SGNodeGroup*   _maskLayerNode;
    unsigned                 _lastNumBlacklistedFilenames;


    ref_ptr<CVBFO_SGNodeTerrainEngine> m_ipTerrainEngine;
    bool					m_bTerrainEngineInitialized;
    osg::IVBF_SGNodeGroup*	m_pTerrainEngineContainer;

public: // CVBF_MapCallback proxy

    void onModelLayerAdded( CVBF_LayerModel*, unsigned int );
    void onModelLayerRemoved( CVBF_LayerModel* );
	void onModelLayerMoved( CVBF_LayerModel* layer, unsigned int oldIndex, unsigned int newIndex );

public: // ModelLayerCallback
    void onModelLayerOverlayChanged( CVBF_LayerModel* layer );

public:
    struct TileRangeData : public ::CVBF_Referenced 
	{
        TileRangeData(double minRange, double maxRange) : _minRange( minRange ), _maxRange( maxRange ) { }
        double _minRange;
        double _maxRange;
    };

private:

    ref_ptr< ModelLayerCallback >	_modelLayerCallback;
    ref_ptr< CVBF_MapCallback >     _mapCallback;
    
    void init();

    CVBF_MapNodeCullData* getCullData(osg::IVBF_Camera* camera) const;
    typedef std::map<osg::IVBF_Camera*, ref_ptr<CVBF_MapNodeCullData> > CullDataMap;
    mutable CullDataMap _cullData;

    mutable CVBF_ReadWriteMutex _cullDataMutex;

	// ����������Ө��ӣ�2018-02-08��
	CVBF_OceanFloorTexture		m_OceanFloorTexture;
};

#endif // OSGEARTH_MAPNODE_H
