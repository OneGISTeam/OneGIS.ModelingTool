//*******************************************************************
// FileName：IVBF_MarkModelSatellite.h
// Function：实体模型：卫星（包括卫星模型、轨道、星下点轨迹）
// Author:   杜莹
// Date:     2013-12-24
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SATELLITE_H__
#define __IVBF_MARK_MODEL_SATELLITE_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <string>
#include <VBF_Plot/Satellite/VBF_3DPlotDataTypes_Satellite.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>
#include <VBF_Plot/Shape/IVBF_MarkAttrSphereAttitude.h>

#include <VBF_Plot/Satellite/VBF_OrbitElements.h>

//----------------------------------------------------------------
// 定义枚举：EVBF_ORBIT_TYPE
// 接口描述：轨道类型
//----------------------------------------------------------------
enum EVBF_ORBIT_TYPE
{
    VBF_ORBIT_TWOBODY,
    VBF_ORBIT_J2,
    VBF_ORBIT_J4
};

// 
//----------------------------------------------------------------
// 定义枚举：EVBF_SATEDRIVING_MODE
// 接口描述：卫星驱动方式
//----------------------------------------------------------------
enum EVBF_SATEDRIVING_MODE	
{
    VBF_SATEDRIVING_ORBITELEMENTS,	// 六根数（默认值）
    VBF_SATEDRIVING_ORBITDATA,      // 已经计算好的轨道数据
    VBF_SATEDRIVING_POS     		// 位置驱动
};

// 轨道点数据
struct VBF_ORBITDATA
{
    double	   dTime;   // 时间，JD
    osg::Vec3d vPos;	// 地惯系下的位置矢量
    osg::Vec3d vVel;	// 地惯系下的速度矢量
};
enum EVBF_ORBIT_DATA_FORMAT
{
    VBF_ORBIT_DATA_FORMAT_CSV, // TLE_ 1000_HPOP_20171213205227To20171221190921.csv :: 010002017121320522706,-7613857.708765,5100227.962408,4230.836080,-3113.494083,-4637.566773,3509.290572
    VBF_ORBIT_DATA_FORMAT_LLA // STK，经纬高，LLA Position :: 头 + 1 Jun 2004 12:00:00.00  19.600  110.950 -0.000000  -0.000000  -0.000000 0.000000
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelSatellite
// 接口描述：卫星（包括卫星模型、轨道、星下点轨迹）
//--------------------------------------------------------------------
class IVBF_MarkModelSatellite : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelSatellite() {}

    /* 设置/获取轨道参数（注意：该函数必须最先调用）
            参数：orbit		 -- 卫星轨道根数
            参数：dBeginTime -- 卫星开始仿真时间（儒略日，单位：天）
            参数：dEndTime	 -- 卫星结束仿真时间（儒略日，单位：天）
            参数：dTimeStep   -- 卫星仿真步长（单位：秒）
			参数：nNumSatellites -- 该轨道面上的卫星个数（默认值为1）
    */
    virtual void SetOrbitParams(const VBF_ORBIT_ELEMENTS& orbit, double dBeginTime, double dEndTime, double dTimeStep, int nNumSatellites=1)=0;
    virtual void GetOrbitParams(VBF_ORBIT_ELEMENTS& orbit, double& dBeginTime, double& dEndTime, double& dTimeStep, int& nNumSatellites)=0;
    virtual void SetOrbitData(const std::string& strFileName,EVBF_ORBIT_DATA_FORMAT eFormat,double dPeriod=0.5)=0;// 设置轨道数据，dPeriod为显示轨道的时间，如果为-1，则全部显示

	// 获取该轨道上的卫星个数
	virtual int GetNumSatellites()=0;

    // 设置/获取卫星模型的完整文件名（含路径）
    // 如果文件类型为模型文件（如.3ds, .flt, .dae等），则卫星模型类型为VBF_MARK_MESH
    // 如果文件类型为图像文件（如.tga, .png, .bmp等），则卫星模型类型为VBF_MARK_RASTER
    virtual void               SetModelFileName(const std::string& strFileName)=0;
    virtual const std::string& GetModelFileName()=0;

    // 设置/获取卫星模型在配置文件MarkStyle.xml中的编码（该函数与上面的SetModelFileName()函数只能取后调用者）
    virtual void               SetModelCode(const std::string& strCode)=0;
    virtual const std::string& GetModelCode()=0;

    // 设置/获取卫星模型是否允许设置固定大小
    virtual void EnableModelFixedSizeInPixels(bool bEnable)=0;
    virtual bool IsModelFixedSizeInPixelsEnabled()=0;

    // 设置/获取卫星模型的固定大小 (单位：像素)
    virtual void  SetModelFixedSizeInPixels(float fFixedSize)=0;
    virtual float GetModelFixedSizeInPixels()=0;

    // 设置/获取卫星模型的缩放比
    virtual void SetModelScale(float fScaleX, float fScaleY, float fScaleZ)=0;
    virtual void GetModelScale(float& fScaleX, float& fScaleY, float& fScaleZ)=0;

    // 设置/获取轨道是否可见（包括轨道线和轨道垂线，默认值为true）
    virtual void SetOrbitVisible(bool bVisible)=0;
    virtual bool IsOrbitVisible()=0;

    // 设置/获取轨道线的样式
    virtual void                 SetOrbitLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetOrbitLineStyle()=0;

	// 设置/获取轨道上各特殊点及其信息是否可见（如近地点、远地点等，默认值为false）
	virtual void SetOrbitSpecialPointsVisible(bool bVisible)=0;
	virtual bool IsOrbitSpecialPointsVisible()=0;

	// 设置/获取当前被激活卫星的索引号（默认被激活卫星的索引号为0） 
	// 注意：只有卫星被激活后，才能显示其垂线和星下点轨迹
	virtual void SetActiveSatellite(int nSatelliteIndex)=0;
	virtual int  GetActiveSatellite()=0;

    // 设置/获取当前被激活卫星的垂线是否可见（该垂线指向星下点轨迹，默认值为true）
    virtual void SetVertLineVisible(bool bVisible)=0;
    virtual bool IsVertLineVisible()=0;

    // 设置/获取当前被激活卫星垂线的样式
    virtual void				 SetVertLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetVertLineStyle()=0;

    // 设置/获取当前被激活卫星的星下点轨迹是否可见（默认值为false）
    virtual void SetGroundTrackVisible(bool bVisible)=0;
    virtual bool IsGroundTrackVisible()=0;

    // 设置/获取当前被激活卫星的星下点轨迹的样式
    virtual void                 SetGroundTrackLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetGroundTrackLineStyle()=0;

    // 设置/获取是否显示卫星信息（默认值为false）
    virtual void SetInfoVisible(bool bVisible)=0;
    virtual bool IsInfoVisible()=0;

    // 设置/获取卫星信息的文本样式
    virtual void                 SetInfoTextStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetInfoTextStyle()=0;

    // 设置/获取卫星信息的背景框样式
    virtual void                      SetInfoFrameStyle(const VBF_POLYGON2DSTYLE& style)=0;
    virtual const VBF_POLYGON2DSTYLE& GetInfoFrameStyle()=0;

    // 设置/获取卫星姿态球是否可见（只有Mesh模型有姿态球，默认值为false）
    virtual void SetSphereAttitudeVisible(bool bVisible)=0;
	virtual bool IsSphereAttitudeVisible()=0;

    // 获取卫星姿态球（只有Mesh模型有姿态球）
    virtual IVBF_MarkAttrSphereAttitude* GetSphereAttitude(int nSatelliteIndex)=0;

    // 获取卫星模型
    virtual IVBF_MarkModelPoint* GetSatelliteModel()=0;

    // 控制卫星探测器显隐
    virtual void SetSensorVisible(bool bVisible)=0;

    // 给第n个卫星添加一个传感器，参数nSatelliteIndex表示卫星的索引号
    virtual void AddSensor(int nSatelliteIndex, IVBF_MarkModelSensor* pISensor)=0;

	// 移除第n个卫星的所有传感器，参数nSatelliteIndex表示卫星的索引号
    virtual void RemoveSensors(int nSatelliteIndex)=0;

    // 开启/关闭探测器与地面相交, 注意：多波束和目指雷达目前没有此功能
    virtual void EnableSensorCal(bool bEnable)=0;

	// 设置/获取卫星驱动方式（默认值为VBF_SATEDRIVING_ORBITSIMUTIME）
	virtual void SetDrivingMode(EVBF_SATEDRIVING_MODE nMode)=0;
	virtual EVBF_SATEDRIVING_MODE GetDrivingMode()=0;

    // 设置/获取某个卫星的位置（注意：前提是卫星为位置驱动方式）
    virtual void SetGeoPos(int nSatelliteIndex, const osg::Vec3d& vGeoPos)=0;
    virtual void StepGeoPos(int nSatelliteIndex, const osg::Vec3d& vGeoPos, float fRotateX, float fRotateY, float fRotateZ, const std::string& strInfo="")=0;
	virtual const osg::Vec3d& GetGeoPos(int nSatelliteIndex)=0;
};


#endif
