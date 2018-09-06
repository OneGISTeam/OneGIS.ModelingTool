#ifndef OSGEARTH_LAYER_H
#define OSGEARTH_LAYER_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/IVBF_MapLayer.h>
#include <VBF_Base/ref_ptr>
#include <VBF_Base/observer_ptr>
#include <list>

class IVBF_SequenceControl;

using namespace osgEarth;



typedef std::list< observer_ptr<IVBF_LayerObserver> > MapLayerObserverList;

// 各种图层的基类，图层包括高程图层、影像图层、模型图层、掩码图层，每个图层对应场景图节点
class OSGEARTH_EXPORT CVBF_Layer : public IVBF_MapLayer
{
public:
    CVBF_Layer();
    virtual ~CVBF_Layer();

    // 图层的唯一标识
    UID getUID() const;

    // 获取序列化控制器
    virtual IVBF_SequenceControl* getSequenceControl();
    virtual void Dirty();
    virtual void AddObserver(IVBF_LayerObserver* pLayerObserver);
    virtual void RemoveObserver(IVBF_LayerObserver* pLayerObserver);

private:
    UID  _uid; // 图层的唯一标识

    MapLayerObserverList m_ObserverList;

};



#endif
