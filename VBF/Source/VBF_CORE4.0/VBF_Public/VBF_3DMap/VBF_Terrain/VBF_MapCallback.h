#ifndef OSGEARTH_MAP_CALLBACK_H
#define OSGEARTH_MAP_CALLBACK_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Base/ref_ptr>
#include <list>

class CVBF_MapInfo;

class CVBF_LayerTerrainImage;
class CVBF_LayerTerrainElevation;
class CVBF_LayerModel;
class CVBF_LayerMask;
struct CVBF_MapModelChange;

// 地图对象向外通知地图数据模型的变化
struct OSGEARTH_EXPORT CVBF_MapCallback : public ::CVBF_Referenced
{
    virtual void onMapInfoEstablished( const CVBF_MapInfo& mapInfo ) { } 

    // 更新
    virtual void onBeginUpdate() { }
    virtual void onEndUpdate() { }

    virtual void onMapModelChanged( const CVBF_MapModelChange& change );

    virtual void onImageLayerAdded( CVBF_LayerTerrainImage* layer, unsigned int index ) { }
    virtual void onImageLayerRemoved( CVBF_LayerTerrainImage* layer, unsigned int index ) { }
    virtual void onImageLayerMoved( CVBF_LayerTerrainImage* layer, unsigned int oldIndex, unsigned int newIndex ) { }

    virtual void onElevationLayerAdded( CVBF_LayerTerrainElevation* layer, unsigned int index ) { }
    virtual void onElevationLayerRemoved( CVBF_LayerTerrainElevation* layer, unsigned int index ) { }
    virtual void onElevationLayerMoved( CVBF_LayerTerrainElevation* layer, unsigned int oldIndex, unsigned int newIndex ) { }

    virtual void onModelLayerAdded( CVBF_LayerModel* layer, unsigned int index ) { }
    virtual void onModelLayerRemoved( CVBF_LayerModel* layer ) { }
    virtual void onModelLayerMoved( CVBF_LayerModel* layer, unsigned int oldIndex, unsigned int newIndex ) { }

    virtual void onMaskLayerAdded( CVBF_LayerMask* mask ) { }
    virtual void onMaskLayerRemoved( CVBF_LayerMask* mask ) { }

    virtual ~CVBF_MapCallback() { }
};

typedef std::list< ref_ptr<CVBF_MapCallback> > MapCallbackList;


#endif // OSGEARTH_MAP_CALLBACK_H
