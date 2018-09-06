//*******************************************************************
// FileName：IVBF_MarkModelSensorFKDome.h
// Function：防空雷达（传感器为圆顶形）
// Author:   杜莹
// Date:     2015-08-16
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_FK_DOME_H__
#define __IVBF_MARK_MODEL_SENSOR_FK_DOME_H__


#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorDome.h>


class IVBF_MarkModelSensorFKDome : public IVBF_MarkModelSensor
{
public:
    virtual ~IVBF_MarkModelSensorFKDome() {}

    // 获取传感器中的各类形状接口，以便设置与几何形状有关的参数
    virtual IVBF_MarkModelShapeDome*  GetSensorDome()=0;    // 传感器本身（圆顶形）
    virtual IVBF_MarkModelSensorDome* GetDetectZone()=0;	// 探测区（圆顶形）

	// 开启/关闭扫描（默认为开启）
	virtual void EnableScan(bool bEnable)=0;
	virtual bool IsScanEnabled()=0;

	// 设置/获取扫描速度（单位：角度/秒，默认值为2.0）
	virtual void  SetScanSpeed(float fSpeed)=0;
	virtual float GetScanSpeed()=0;
};

#endif 
