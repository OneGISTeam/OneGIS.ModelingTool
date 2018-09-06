//*******************************************************************
// FileName：IVBF_MarkModelSensorRadarAEW.h
// Function：传感器实体模型：预警机雷达（预警机：AEW, Air Early Warning）
// Author:   杜莹
// Date:     2013-11-04
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_RADAR_AEW_H__
#define __IVBF_MARK_MODEL_SENSOR_RADAR_AEW_H__


#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeRevoSurface.h>


class IVBF_MarkModelSensorRadarAEW : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorRadarAEW() {}

	// 获取传感器中的形状接口，以便设置与几何形状有关的参数
	virtual IVBF_MarkModelShapeRevoSurface* GetShape()=0;

	// 设置/获取雷达功率
	virtual void  SetPower(float fPower)=0;
	virtual float GetPower()=0;
};


#endif
