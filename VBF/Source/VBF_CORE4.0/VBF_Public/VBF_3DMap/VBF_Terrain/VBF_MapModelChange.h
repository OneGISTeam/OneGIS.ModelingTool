#ifndef OSGEARTH_MAP_MODEL_CHANGE_H
#define OSGEARTH_MAP_MODEL_CHANGE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/Revisioning.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerTerrainImage.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerTerrainElevation.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerModel.h>
#include <VBF_3DMap/VBF_Terrain/VBF_LayerMask.h>

 
// 向地图（Map）数据模型传递自动变化动作
struct CVBF_MapModelChange /* no export, header-only */
{
    enum ActionType
    {
        BEGIN_BATCH_UPDATE,               // signals the start of multiple changes
        END_BATCH_UPDATE,                 // signals the end of multiple changes
        ADD_IMAGE_LAYER,
        REMOVE_IMAGE_LAYER,
        MOVE_IMAGE_LAYER,
        ADD_ELEVATION_LAYER,
        REMOVE_ELEVATION_LAYER,
        MOVE_ELEVATION_LAYER,
        ADD_MODEL_LAYER,
        REMOVE_MODEL_LAYER,
        MOVE_MODEL_LAYER,
        ADD_MASK_LAYER,
        REMOVE_MASK_LAYER,
        UNSPECIFIED
    };

    CVBF_MapModelChange( ActionType action, Revision mapModeRev, IVBF_MapLayer* layer =0L, int firstIndex =-1, int secondIndex =-1 )
        : _action(action), _layer(layer), _modelRevision(mapModeRev), _firstIndex(firstIndex), _secondIndex(secondIndex) 
	{ }

    const ActionType& getAction() const { return _action; }
    const Revision& getRevision() const { return _modelRevision; }
    int getFirstIndex() const { return _firstIndex; }
    int getSecondIndex() const { return _secondIndex; }
    IVBF_MapLayer* getLayer() const { return _layer.get(); }
    CVBF_LayerTerrainImage* getImageLayer() const { return dynamic_cast<CVBF_LayerTerrainImage*>(_layer.get()); }
    CVBF_LayerTerrainElevation* getElevationLayer() const { return dynamic_cast<CVBF_LayerTerrainElevation*>(_layer.get()); }
    CVBF_LayerModel* getModelLayer() const { return dynamic_cast<CVBF_LayerModel*>(_layer.get()); }
    CVBF_LayerMask* getMaskLayer() const { return dynamic_cast<CVBF_LayerMask*>(_layer.get()); }

private:
    ActionType					_action;
    ref_ptr<IVBF_MapLayer>	    _layer;
    Revision					_modelRevision;
    int							_firstIndex, _secondIndex;
};


#endif // OSGEARTH_MAP_MODEL_CHANGE_H
