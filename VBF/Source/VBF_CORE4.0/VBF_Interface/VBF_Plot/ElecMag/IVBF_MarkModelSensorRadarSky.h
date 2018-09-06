//*******************************************************************
// FileName：IVBF_MarkModelSensorRadarSky.h
// Function：传感器实体模型：天波雷达
// Author:   杜莹
// Date:     2013-10-16
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_RADAR_SKY_H__
#define __IVBF_MARK_MODEL_SENSOR_RADAR_SKY_H__


#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_SENSOR_RADARSKY_PART
// 枚举描述：天波雷达的各个部分
//--------------------------------------------------------------------
enum EVBF_SENSOR_RADARSKY_PART
{
	VBF_SENSOR_RADARSKY_PART_BODY		= 0,	// 主体
	VBF_SENSOR_RADARSKY_PART_SCANWAVE	= 1,	// 扫描波
	VBF_SENSOR_RADARSKY_PART_IONOTOP	= 2,	// 电离层顶面
	VBF_SENSOR_RADARSKY_PART_COUNT				// 总数
};

// 默认值
const float	DEFAULT_IONO_HEIGHT			= 400000.0f;	// 电离层高度，即天波雷达反射高度距离地表的距离（电离层距地表的距离）flk
const int   DEFAULT_CENTERLINE_SEGMENTS = 40;			// 中心线的分段数（值越大，扫描波的条带越细）
const int	DEFAULT_SCANWAVE_LOOPS		= 5;			// 扫描波每个带的圈数
const int	DEFAULT_SCANWAVE_INTERVALS	= 4;			// 扫描波的帧间隔

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelSensorRadarSky
// 接口描述：天波雷达
//--------------------------------------------------------------------
class IVBF_MarkModelSensorRadarSky : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorRadarSky() {}

public:

	/* 设置雷达的外形
	   参数：fAngleOpen -- 天波雷达近似张角
	         fAngleH   -- 天波雷达扫描角
			 fAngleV   -- 天波雷达仰角
	*/
	virtual void SetTess(float fAngleOpen, float fAngleH, float fAngleV)=0;
	virtual void GetTess(float& fAngleOpen, float& fAngleH, float& fAngleV)=0;

	// 设置/获取电离层的当前高度（单位：米），默认值为参见上述定义
	virtual void  SetIonosphereHeight(float fHeight)=0;
	virtual float GetIonosphereHeight()=0;

	// 设置/获取中心线的分段数（值越大，扫描波的条带越细），默认值为参见上述定义
	virtual void SetNumCenterLineSegments(int num)=0;
	virtual int  GetNumCenterLineSegments()=0;

	// 设置/获取扫描波每个带的圈数，默认值为参见上述定义
	virtual void SetNumScanWaveLoops(int num)=0;
	virtual int  GetNumScanWaveLoops()=0;

	// 设置/获取扫描波的帧间隔（值越大，扫描波的速度越慢），默认值为参见上述定义
	virtual void SetNumScanWaveIntervals(int num)=0;
	virtual int  GetNumScanWaveIntervals()=0;

	// 注意：天波雷达不允许缩放/平移
	virtual void SetScale(float fScaleX, float fScaleY, float fScaleZ)	{}
	virtual void SetTrans(float fTransX, float fTransY, float fTransZ)	{}
};


#endif 
