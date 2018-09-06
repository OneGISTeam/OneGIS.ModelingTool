//*******************************************************************
// FileName：IVBF_MarkModelSensorRadarSkyEx.h
// Function：传感器实体模型：带扫描动作的天波雷达
// Author:   杜莹
// Date:     2013-10-17
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_RADAR_SKY_EX_H__
#define __IVBF_MARK_MODEL_SENSOR_RADAR_SKY_EX_H__


#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorRadarSky.h>

// 天波雷达扫描方式
enum EVBF_RADARSKY_SCAN_TYPE          
{
	VBF_RADARSKY_SCAN_TYPE_ORDINAL	= 0,	// 顺序扫描（默认值）
	VBF_RADARSKY_SCAN_TYPE_SKIP		= 1		// 跳跃扫描
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelSensorRadarSkyEx
// 接口描述：带扫描动作的天波雷达
//--------------------------------------------------------------------
class IVBF_MarkModelSensorRadarSkyEx : public IVBF_MarkModelSensorRadarSky
{
public:
	virtual ~IVBF_MarkModelSensorRadarSkyEx() {}

public:

	/* 设置/获取雷达的外形（通过设置雷达仰角）
	   参数：fAngleOpen -- 天波雷达近似张角
	         fAngleH0, fAngleH1 -- 天波雷达水平角范围
             fAngleV0, fAngleV1 -- 天波雷达仰角范围，取值范围在10-80度之间
			 nNumRows, nNumCols -- 扫描带的行列数
	*/
	virtual void SetTess(float fAngleOpen, float fAngleH0, float fAngleH1, float fAngleV0, float fAngleV1, 
		                 int nNumRows, int nNumCols)=0;

	virtual void GetTess(float& fAngleOpen, float& fAngleH0, float& fAngleH1, float& fAngleV0, float& fAngleV1, 
		                 int& nNumRows, int& nNumCols)=0;

	/* 设置/获取雷达的外形（通过设置雷达探测距离）
	   参数：fAngleOpen -- 天波雷达近似张角
			 fAngleH0, fAngleH1 -- 天波雷达水平角范围
			 fDistMin, fDistMax -- 天波雷达的最近和最远探测距离（单位：米）
			 nNumRows, nNumCols -- 扫描带的行列数
	*/
	virtual void SetTessByDist(float fAngleOpen, float fAngleH0, float fAngleH1, float fDistMin, float fDistMax,
							   int nNumRows, int nNumCols)=0;

	virtual void GetTessByDist(float& fAngleOpen, float& fAngleH0, float& fAngleH1, float& fDistMin, float& fDistMax,
							   int& nNumRows, int& nNumCols)=0;

	// 设置/获取扫描方式，默认为顺序扫描
	virtual void SetScanType(EVBF_RADARSKY_SCAN_TYPE nType)=0;
	virtual EVBF_RADARSKY_SCAN_TYPE GetScanType()=0;

	// 设置/获取当前扫描位置，仅对跳扫起作用
	virtual void SetScanPos(int nRow, int nCol)=0;
	virtual void GetScanPos(int& nRow, int& nCol)=0;

	// 设置/获取顺序扫描时每个网格停留的时间，单位：秒（值越大，扫描速度越慢，默认值为2.0）
	virtual void  SetScanPausalTime(float fTime)=0;
	virtual float GetScanPausalTime()=0;

	// 设置/获取扫描带的颜色
	virtual void       SetScanBandColor(const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetScanBandColor()=0;

	// 注意：天波雷达不允许缩放/平移
	virtual void SetScale(float fScaleX, float fScaleY, float fScaleZ)	{}
	virtual void SetTrans(float fTransX, float fTransY, float fTransZ)	{}
	virtual void SetTess(float fAngleOpen, float fAngleH, float fAngleV){}
};


#endif 
