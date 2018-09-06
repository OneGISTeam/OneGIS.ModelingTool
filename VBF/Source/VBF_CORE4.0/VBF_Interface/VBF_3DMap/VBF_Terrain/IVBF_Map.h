//***************************************************************************************
// FileName：IVBF_Map.h
// Function：地图
// Author:
// Date:
//***************************************************************************************
#ifndef __IVBF_MAP_H__
#define __IVBF_MAP_H__

#include <VBF_3DMap/VBF_Terrain/IVBF_MapLayer.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>

class IVBF_Map : public ::CVBF_Referenced
{
public:
    IVBF_Map():CVBF_Referenced ( true ) { }
    virtual ~IVBF_Map() {}
public:
    virtual int getNumImageLayers() const=0;// 获取影像图层的数量

    virtual IVBF_MapLayer* getImageLayerByName( const std::string& name ) const=0;// 通过名字获取影像图层
    virtual IVBF_MapLayer* getImageLayerByUID( int layerUID ) const=0;// 通过ID获取影像图层
    virtual IVBF_MapLayer* getImageLayerAt( int index ) const=0;// 通过索引获取影像图层


    virtual int getNumModelLayers() const=0;// 通过索引获取模型图层
    virtual IVBF_MapLayer* getModelLayerByName( const std::string& name ) const=0;// 通过名字获取模型图层
    virtual IVBF_MapLayer* getModelLayerByUID( int layerUID ) const=0;// 通过ID获取模型图层
    virtual IVBF_MapLayer* getModelLayerAt( int index ) const=0;// 通过索引获取模型图层

    virtual int getNumElevationLayers() const=0;// 通过索引获取高程图层
    virtual IVBF_MapLayer* getElevationLayerByName( const std::string& name ) const=0;// 通过名字获取高程图层
    virtual IVBF_MapLayer* getElevationLayerByUID( int layerUID ) const=0;// 通过ID获取高程图层
    virtual IVBF_MapLayer* getElevationLayerAt( int index ) const=0;// 通过索引获取高程图层

    virtual bool AddModelLayer(const std::string& strFileName)=0;// 从配置文件添加模型图层（与earth一致）
    virtual void RemoveModelLayer(const std::string& name)=0;
    virtual void AddModelLayers(const CVBF_Config& conf)=0;// 从配置文件添加矢量图层（与earth一致）
    virtual void AddModelLayer(const CVBF_Config& conf)=0;// 从配置文件添加矢量图层（与earth一致）

    virtual bool AddImageLayer(const std::string& strFileName)=0;// 从配置文件添加图像图层（与earth一致）
    virtual void RemoveImageLayer(const std::string& name)=0;
    virtual void AddImageLayers(const CVBF_Config& conf)=0;// 从配置文件添加图像图层（与earth一致）
    virtual void AddImageLayer(const CVBF_Config& conf)=0;// 从配置文件添加图像图层（与earth一致）

    virtual bool AddElevationLayer(const std::string& strFileName)=0;// 从配置文件添加高程图层（与earth一致）
    virtual void RemoveElevationLayer(const std::string& name)=0;
    virtual void AddElevationLayers(const CVBF_Config& conf)=0;// 从配置文件添加高程图层（与earth一致）
    virtual void AddElevationLayer(const CVBF_Config& conf)=0;// 从配置文件添加高程图层（与earth一致）

};

#endif





















