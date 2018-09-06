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



// CVBF_Map形成的场景图根节点，CVBF_Map是数据模型、CVBFO_SGNodeMap是数据的视图
class OSGEARTH_EXPORT CVBFO_SGNodeMap : public osg::CVBF_SGNodeGroup
{
public:
    // 通过参数列表从".earth"转载一个CVBFO_SGNodeMap
    static CVBFO_SGNodeMap* load( class ::ArgumentParser& arguments );

public:
    CVBFO_SGNodeMap();
    CVBFO_SGNodeMap( const CVBF_OptionsMapNode& options );
    CVBFO_SGNodeMap( CVBF_Map* pMap );//通过CVBF_Map创建一个空的CVBFO_SGNodeMap
    CVBFO_SGNodeMap( CVBF_Map* pMap, const CVBF_OptionsMapNode& options );
 public:

    virtual const char* libraryName() const { return "osgEarth"; }
    virtual const char* className() const { return "CVBFO_SGNodeMap"; }

    // 获取CVBFO_SGNodeMap对应（渲染）的CVBF_Map
    const CVBF_Map* GetMap() const;
          CVBF_Map* GetMap();
  
	// 获取空间Map的参考，便捷函数
    const CVBF_SpatialReference* GetMapSRS() const;

	// 获取内存中的地形场景
    const CVBF_Terrain* getTerrain() const;
		  CVBF_Terrain* getTerrain();

    // 从场景图中茶中最顶层的CVBFO_SGNodeMap，不存在则返回NULL
    static CVBFO_SGNodeMap* findMapNode( osg::IVBF_SGNode* graph, unsigned traversalMask =~0 );
    static CVBFO_SGNodeMap* get( osg::IVBF_SGNode* graph, unsigned travMask =~0 ) { return findMapNode(graph, travMask); }

 
	// 地形模型是否是geocentric？
    bool isGeocentric() const;

    // 获取模型节点（包含所有的CVBF_LayerModel对应的Node）
    osg::IVBF_SGNodeGroup* getModelLayerGroup() const;

    // 获取特定CVBF_LayerModel对应的Node
    osg::IVBF_SGNode* getModelLayerNode( CVBF_LayerModel* layer ) const;

	// 添加/移除地形的装饰器（decorates）
    void addTerrainDecorator( osg::IVBF_SGNodeGroup* decorator );
    void removeTerrainDecorator( osg::IVBF_SGNodeGroup* decorator );

    // 获取地图节点的覆盖装饰器，通常不需要直接访问，而是安装一个CVBFO_SGNodeOverlayDrapeable
    CVBFO_SGNodeDecoratorTerrainOverlay* getOverlayDecorator() { return m_pOverlayDecorator; }

    // 获取地图节点的配置项
    const CVBF_OptionsMapNode& GetMapNodeOptions() const;

	// 获取渲染地形表面的地形引擎
    CVBFO_SGNodeTerrainEngine* getTerrainEngine() const;

	// 在.earth文件中有<external>节点，该节点可被EARTH读取但不进行任何处理，可用于其他部分或应用层
	const CVBF_Config& externalConfig() const { return _externalConf; }
		  CVBF_Config& externalConfig() { return _externalConf; }

    // 在潜在的地形引擎上设置自定义的纹理合成技术（texture compositor technique），
    void setCompositorTechnique( class TextureCompositorTechnique* tech );

	// 获取海底纹理指针（杜莹添加：2018-02-08）
	CVBF_OceanFloorTexture* GetOceanFloorTexture() { return &m_OceanFloorTexture; }

public: // special purpose

    CVBFO_SGNodeMap( CVBF_Map* pMap, const CVBF_OptionsMapNode& options, bool initMap );

public: // 重载 osg::Node
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

	// 海底纹理（杜莹添加：2018-02-08）
	CVBF_OceanFloorTexture		m_OceanFloorTexture;
};

#endif // OSGEARTH_MAPNODE_H
