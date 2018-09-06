//*******************************************************************
// FileName：IVBF_MarkModelSensorInfrared.h
// Function：传感器实体模型：红外传感器
// Author:   杜莹
// Date:     2013-10-21
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_INFRARED_H__
#define __IVBF_MARK_MODEL_SENSOR_INFRARED_H__


#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeFrustum.h>
#include <Types/VBF_3DStyles.h>


// 定义常量：地球静止轨道的高度（与赤道上空的距离）
const double GEO_ORBIT_H = 3.5786e7; // 地球静止轨道：Geostationary Orbit，简称GEO


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelSensorInfrared
// 接口描述：红外传感器
//--------------------------------------------------------------------
class IVBF_MarkModelSensorInfrared : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorInfrared() {}

public:

	// 获取传感器中的形状接口，以便设置与几何形状有关的参数
	virtual IVBF_MarkModelShapeFrustumDome* GetShape()=0;

	// 设置/获取摆动扫描的纬度范围
	virtual void   SetSwingPosOnEarth(double dB)=0;
	virtual double GetSwingPosOnEarth()=0;

	// 设置/获取扫描周期，一个摆动来回的时间（单位：秒）
	virtual void  SetScanPeriod(float fPeriod)=0;
	virtual float GetScanPeriod()=0;
};


#endif 
