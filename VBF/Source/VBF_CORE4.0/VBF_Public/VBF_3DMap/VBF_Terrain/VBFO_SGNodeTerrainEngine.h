#ifndef OSGEARTH_TERRAIN_ENGINE_NODE_H
#define OSGEARTH_TERRAIN_ENGINE_NODE_H 1

#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapFrame.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Terrain.h>
#include <VBF_3DMap/VBF_Terrain/TextureCompositor.h>
#include <VBF_3DMap/VBF_Terrain/ShaderUtils.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupCoordSys.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>

using namespace osgEarth;



// 基类（接口类），位于CVBFO_SGNodeMap之下，负责生成表示地形的实际的 geometry。
class OSGEARTH_EXPORT CVBFO_SGNodeTerrainEngine : public osg::CVBF_SGNodeGroupCoordSys
{
public:
    // 获取该节点关联（渲染）的CVBF_Map
    const CVBF_Map* GetMap() const;

    // 获取用于和场景图进行交互的CVBF_Terrain（数据）
    const CVBF_Terrain* getTerrain() const;
          CVBF_Terrain* getTerrain() ;

	// 获取地形属性设置
    virtual const CVBF_OptionsTerrain& getTerrainOptions() const =0;

	// 获取纹理合成器（用于控制影像图层渲染）
    TextureCompositor* getTextureCompositor() const;

public: // Runtime properties

	// 设置/获取高度场的比例因子，默认是1.0
    void  setVerticalScale( float value );
    float getVerticalScale() const;

	// 设置/获取高度场的样本比，默认是1.0。地形引擎使用该值对高度场进行采样
    void  setElevationSamplingRatio( float value );
    float getElevationSamplingRatio() const ;

protected:
    CVBFO_SGNodeTerrainEngine();
    virtual ~CVBFO_SGNodeTerrainEngine();

public: // osg::Node overrides
    virtual osg::BoundingSphere computeBound() const;
    virtual void traverse( osg::NodeVisitor& );

protected: // implementation events
    virtual void onVerticalScaleChanged();
    virtual void onElevationSamplingRatioChanged();

protected:
    friend class CVBFO_SGNodeMap;
    friend class CVBF_TerrainEngineNodeFactory;

    virtual void validateTerrainOptions( CVBF_OptionsTerrain& options );

	// 把地图关联到地形引擎并初始化地形引擎
    virtual void preInitialize( const CVBF_Map* map, const CVBF_OptionsTerrain& options );
    virtual void postInitialize( const CVBF_Map* map, const CVBF_OptionsTerrain& options );

    virtual void dirty(); // 发出需要重画的信号

    ref_ptr<TextureCompositor> _texCompositor;		// 纹理合成器

	//xahg h00017
    unsigned int  _lastCollectTileFrameNumber;
	//xahg h00017

public: // utility

	// 创建一个表示瓦片几何数据的节点的工具函数。该节点是单独的，不能装载子节点或receive updates.
    virtual osg::IVBF_SGNode* createTile( const CVBF_TileKey& key ) =0;

private:
    friend struct CVBF_MapCallbackProxyTerrainEngineNode;

    void ctor();
    void onMapInfoEstablished( const CVBF_MapInfo& mapInfo ); // not virtual!
    void onMapModelChanged( const CVBF_MapModelChange& change );
    void updateImageUniforms();

    virtual void updateTextureCombining();

private:
    struct ImageLayerController : public ImageLayerCallback
    {
        ImageLayerController( const CVBF_Map* map, CVBFO_SGNodeTerrainEngine* engine );

        void onVisibleChanged( CVBF_LayerTerrain* layer );
        void onOpacityChanged( CVBF_LayerTerrainImage* layer );
        void onColorFiltersChanged( CVBF_LayerTerrainImage* layer );      
        void onVisibleRangeChanged( CVBF_LayerTerrainImage* layer );

        ArrayUniform					_layerOpacityUniform;
        ArrayUniform					_layerVisibleUniform;
        ArrayUniform					_layerRangeUniform;

    private:
        CVBF_MapFrame					_mapf;
        CVBFO_SGNodeTerrainEngine*		_engine;

        friend class CVBFO_SGNodeTerrainEngine;
    };

    ref_ptr<ImageLayerController>		_imageLayerController;
    ref_ptr<const CVBF_Map>            _map;
    ref_ptr<osg::Uniform>				_startFrameTimeUniform;
    ref_ptr<osg::Uniform>				_cameraElevationUniform;
    bool								_redrawRequired;
    float								_verticalScale;
    float								_elevationSamplingRatio;
    ref_ptr<CVBF_Terrain>              _terrainInterface;
    unsigned							_dirtyCount;
    UpdateLightingUniformsHelper		_updateLightingUniformsHelper;
        
    enum InitStage 
	{
        INIT_NONE,				// 没初始化
        INIT_PREINIT_COMPLETE,	// 完成了前初始化
        INIT_POSTINIT_COMPLETE	// 完成了后初始化
    };

    InitStage		_initStage;
};


// 创建地形引擎实例的类工厂 
class CVBF_TerrainEngineNodeFactory
{
public:
    static CVBFO_SGNodeTerrainEngine* create( CVBF_Map* map, const CVBF_OptionsTerrain& options );
};


// 地形引擎节点（在MapNode中）的装饰节点的基类
class CVBFO_SGNodeDecoratorTerrain : public osg::CVBF_SGNodeGroup
{
public:
    virtual void onInstall( CVBFO_SGNodeTerrainEngine* engine ) ;
    virtual void onUninstall( CVBFO_SGNodeTerrainEngine* engine );

protected:
    virtual ~CVBFO_SGNodeDecoratorTerrain();
};



#endif // OSGEARTH_TERRAIN_ENGINE_NODE_H
