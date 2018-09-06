//********************************************************************************
// FileName：IVBF_S3CCity.h
// Function：三维城市管理接口，按照城市、区域、地块方式进行组织，单个模型格式为.osgb，
//           S3C: Smart 3D Capture
// Author:   杜莹
// Date:     2016-01-11
//********************************************************************************


#ifndef __IVBF_S3C_CITY__H__
#define __IVBF_S3C_CITY__H__


#include <VBF_Base/VBF_Referenced.h>
#include <string>
#include <Types/Vec3d>

// 定义该组件的ID号
const char VBF_COMPONENT_S3CCITY[]  = "Component: S3CCity";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_S3CCITY[]  = "S3C城市管理接口";

// 倾斜摄影功能接口 ID 号
const char VBF_INTERFACE_TILE_MODEL[]  = "倾斜摄影接口";


class IVBF_S3CCity : public CVBF_Referenced
{
public:	
    virtual ~IVBF_S3CCity() {}

    // 添加一个区域，如果该区域已经存在，返回false
    // 参数：strRegionID    -- 该区域的唯一ID号，不允许重复
    //      strDataPath    -- 该区域的模型数据路径
    //      ptGeo          -- 该区域模型的定位点
    //      L0, L1, B0, B1 -- 该区域的经纬度范围
    //      nNumTileRows   -- 该区域的分块行数
    //      nNumTileCols   -- 该城市的分块列数
    //      bModelToCache  -- 是否需要将读取的模型放入缓存
    virtual bool AddRegion(const std::string& strRegionID, const std::string& strDataPath, const osg::Vec3d& ptGeo,
                           double L0, double L1, double B0, double B1, int nNumTileRows, int nNumTileCols, bool bModelToCache=false)=0;

    // 移除一个区域，如果该区域不存在，返回false（该函数彻底卸载区域内的所有模型数据）
    virtual bool RemoveRegion(const std::string& strRegionID)=0;

    // 设置某个区域的可见性，如果该区域不存在，返回false（该函数并不卸载区域内的所有模型数据）
    virtual bool SetRegionVisible(const std::string& strRegionID, bool bVisible)=0;
};




class IVBF_TiltModel : public CVBF_Referenced
{
public:
	virtual ~IVBF_TiltModel(){}
	 
public:
	virtual bool AddTilt(const std::string& strTiltID, const std::string& strTiltFile) = 0;

	virtual bool RemoveTilt(const std::string& strTiltID) = 0;

	virtual bool ClearTilts() = 0;

	virtual bool SetTiltVisible(const std::string& strTiltID, bool bState) = 0;

	virtual bool GetTiltVisible(const std::string& strTiltID) = 0;

	virtual bool SetTiltPosition(const std::string& strTiltID, osg::Vec3d vecLBH) = 0;

	virtual osg::Vec3d GetTiltPosition(const std::string& strTiltID) = 0;

	virtual bool SetTiltScale(const std::string& strTiltID, osg::Vec3d vecScale) = 0;

	virtual osg::Vec3d GetTiltScale(const std::string& strTiltID) = 0;

	virtual bool SetTiltRotate(const std::string& strTiltID, osg::Vec3d vecRotate) = 0;

	virtual osg::Vec3d GetTiltRotate(const std::string& strTiltID) = 0;
};

#endif
