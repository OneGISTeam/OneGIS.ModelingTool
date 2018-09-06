//*******************************************************************
// FileName：IVBF_MarkModelSensorSector.h
// Function：扇形传感器，适用于P波段
// Author：  杜莹
// Date：    2015-08-17
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_SECTOR_H__
#define __IVBF_MARK_MODEL_SENSOR_SECTOR_H__


#include "IVBF_MarkModelSensor.h"
#include <VBF_Plot/Shape/IVBF_MarkModelShapeSector.h>


class IVBF_MarkModelSensorSector : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorSector() {}

	// 获取传感器中的形状接口，以便设置与几何形状有关的参数
	virtual IVBF_MarkModelShapeSector* GetShape()=0;
};

#endif 
