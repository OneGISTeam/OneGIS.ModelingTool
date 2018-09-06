//***************************************************************************************
// FileName：IVBF_MapLayer.h
// Function：图层
// Author:
// Date:
//***************************************************************************************
#ifndef __IVBF_MAP_LAYER_H__
#define __IVBF_MAP_LAYER_H__

#include <VBF_Base/VBF_Referenced.h>
#include <string>

// 图层向外通知数据变化
class IVBF_LayerObserver : public CVBF_Referenced
{
public:
    explicit IVBF_LayerObserver(bool threadSafeRefUnref): CVBF_Referenced(threadSafeRefUnref) { }
    virtual ~IVBF_LayerObserver() { }

    virtual void Dirty( )=0;
};

class IVBF_MapLayer : public ::CVBF_Referenced
{
public: 	
    virtual ~IVBF_MapLayer() {}

public:
    // 图层的唯一标识
    virtual int getUID() const = 0;

    // 获取图层名
    virtual const std::string& getName() const  = 0;

    virtual bool getEnabled() const = 0;

    // 是否绘制（或别的应用）该图层
    virtual void setVisible( bool value ) = 0;
    virtual bool getVisible() const = 0;

    virtual void Dirty() = 0;

    virtual void AddObserver(IVBF_LayerObserver* pLayerObserver)=0;
    virtual void RemoveObserver(IVBF_LayerObserver* pLayerObserver)=0;

};

#endif





















