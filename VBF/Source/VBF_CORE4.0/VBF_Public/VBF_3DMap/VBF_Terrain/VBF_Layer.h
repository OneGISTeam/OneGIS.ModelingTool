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

// ����ͼ��Ļ��࣬ͼ������߳�ͼ�㡢Ӱ��ͼ�㡢ģ��ͼ�㡢����ͼ�㣬ÿ��ͼ���Ӧ����ͼ�ڵ�
class OSGEARTH_EXPORT CVBF_Layer : public IVBF_MapLayer
{
public:
    CVBF_Layer();
    virtual ~CVBF_Layer();

    // ͼ���Ψһ��ʶ
    UID getUID() const;

    // ��ȡ���л�������
    virtual IVBF_SequenceControl* getSequenceControl();
    virtual void Dirty();
    virtual void AddObserver(IVBF_LayerObserver* pLayerObserver);
    virtual void RemoveObserver(IVBF_LayerObserver* pLayerObserver);

private:
    UID  _uid; // ͼ���Ψһ��ʶ

    MapLayerObserverList m_ObserverList;

};



#endif
