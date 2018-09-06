//*******************************************************************
// FileName：IVBF_MarkModelSensorPA.h
// Function：相控阵雷达（PA: Phased Array）
// Author:   李海生
// Date:     2015-04-15
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_PA_H__
#define __IVBF_MARK_MODEL_SENSOR_PA_H__

#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorDome.h>


class IVBF_MarkModelSensorPA : public IVBF_MarkModelSensor
{
public:
    virtual ~IVBF_MarkModelSensorPA() {}

    // 设置/获取传感器的外观
    // 参数：nNumBeamGroups   -- 波束组数
    //      nNumRowsPerGroup -- 每组波束中的行数
    //      nNumColsPerGroup -- 每组波束中的列数
    virtual void SetTess(int nNumBeamGroups, int nNumRowsPerGroup, int nNumColsPerGroup)=0;
    virtual void GetTess(int& nNumBeamGroups, int& nNumRowsPerGroup, int& nNumColsPerGroup)=0;

    // 获取传感器中的各类形状接口，以便设置与几何形状有关的参数
    virtual IVBF_MarkModelSensorDome* GetDetectZone()=0;	// 探测区（圆顶形）

	// 开启/关闭扫描（默认为开启）
	virtual void EnableScan(bool bEnable)=0;
	virtual bool IsScanEnabled()=0;

	// 设置/获取扫描速度（单位：角度/秒，默认值为2.0）
	virtual void  SetScanSpeed(float fSpeed)=0;
	virtual float GetScanSpeed()=0;
};

#endif 
