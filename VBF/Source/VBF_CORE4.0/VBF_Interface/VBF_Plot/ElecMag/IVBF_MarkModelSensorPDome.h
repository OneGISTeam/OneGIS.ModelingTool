//*******************************************************************
// FileName：IVBF_MarkModelSensorPDome.h
// Function：P波段传感器（探测区为圆顶形）
// Author:   杜莹
// Date:     2013-10-28
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_P_DOME_H__
#define __IVBF_MARK_MODEL_SENSOR_P_DOME_H__


#include "IVBF_MarkModelSensor.h"
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorRect.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorDome.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeCone.h>


class IVBF_MarkModelSensorPDome : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorPDome() {}

	// 获取传感器中的各类形状接口，以便设置与几何形状有关的参数
    virtual IVBF_MarkModelSensorRect*	GetSensorRect()=0;	// 传感器本身（平截头体）
    virtual IVBF_MarkModelSensorDome*	GetDetectZone()=0;	// 探测区（圆顶形）
    virtual IVBF_MarkModelShapeCone*    GetScanBeam()=0;	// 扫描波（圆锥形，跟随平截头体旋转）

	// 开启/关闭扫描
	virtual void EnableScan(bool bEnable)=0;
	virtual bool IsScanEnabled()=0;

	// 设置/获取扫描速度（单位：角度/秒）
	virtual void  SetScanSpeed(float fSpeed)=0;
	virtual float GetScanSpeed()=0;
};

#endif
