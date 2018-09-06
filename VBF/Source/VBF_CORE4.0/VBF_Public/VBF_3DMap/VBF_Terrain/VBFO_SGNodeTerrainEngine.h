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



// ���ࣨ�ӿ��ࣩ��λ��CVBFO_SGNodeMap֮�£��������ɱ�ʾ���ε�ʵ�ʵ� geometry��
class OSGEARTH_EXPORT CVBFO_SGNodeTerrainEngine : public osg::CVBF_SGNodeGroupCoordSys
{
public:
    // ��ȡ�ýڵ��������Ⱦ����CVBF_Map
    const CVBF_Map* GetMap() const;

    // ��ȡ���ںͳ���ͼ���н�����CVBF_Terrain�����ݣ�
    const CVBF_Terrain* getTerrain() const;
          CVBF_Terrain* getTerrain() ;

	// ��ȡ������������
    virtual const CVBF_OptionsTerrain& getTerrainOptions() const =0;

	// ��ȡ����ϳ��������ڿ���Ӱ��ͼ����Ⱦ��
    TextureCompositor* getTextureCompositor() const;

public: // Runtime properties

	// ����/��ȡ�߶ȳ��ı������ӣ�Ĭ����1.0
    void  setVerticalScale( float value );
    float getVerticalScale() const;

	// ����/��ȡ�߶ȳ��������ȣ�Ĭ����1.0����������ʹ�ø�ֵ�Ը߶ȳ����в���
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

	// �ѵ�ͼ�������������沢��ʼ����������
    virtual void preInitialize( const CVBF_Map* map, const CVBF_OptionsTerrain& options );
    virtual void postInitialize( const CVBF_Map* map, const CVBF_OptionsTerrain& options );

    virtual void dirty(); // ������Ҫ�ػ����ź�

    ref_ptr<TextureCompositor> _texCompositor;		// ����ϳ���

	//xahg h00017
    unsigned int  _lastCollectTileFrameNumber;
	//xahg h00017

public: // utility

	// ����һ����ʾ��Ƭ�������ݵĽڵ�Ĺ��ߺ������ýڵ��ǵ����ģ�����װ���ӽڵ��receive updates.
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
        INIT_NONE,				// û��ʼ��
        INIT_PREINIT_COMPLETE,	// �����ǰ��ʼ��
        INIT_POSTINIT_COMPLETE	// ����˺��ʼ��
    };

    InitStage		_initStage;
};


// ������������ʵ�����๤�� 
class CVBF_TerrainEngineNodeFactory
{
public:
    static CVBFO_SGNodeTerrainEngine* create( CVBF_Map* map, const CVBF_OptionsTerrain& options );
};


// ��������ڵ㣨��MapNode�У���װ�νڵ�Ļ���
class CVBFO_SGNodeDecoratorTerrain : public osg::CVBF_SGNodeGroup
{
public:
    virtual void onInstall( CVBFO_SGNodeTerrainEngine* engine ) ;
    virtual void onUninstall( CVBFO_SGNodeTerrainEngine* engine );

protected:
    virtual ~CVBFO_SGNodeDecoratorTerrain();
};



#endif // OSGEARTH_TERRAIN_ENGINE_NODE_H
