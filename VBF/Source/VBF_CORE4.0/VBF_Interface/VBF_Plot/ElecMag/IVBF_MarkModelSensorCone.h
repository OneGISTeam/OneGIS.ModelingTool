//*******************************************************************
// FileName：IVBF_MarkModelSensorCone.h
// Function：圆锥状传感器，适用于X波段
// Author：  杜莹
// Date：    2013-10-25
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_CONE_H__
#define __IVBF_MARK_MODEL_SENSOR_CONE_H__

#include "IVBF_MarkModelSensor.h"
#include <VBF_Plot/Shape/IVBF_MarkModelShapeCone.h>


class IVBF_MarkModelSensorCone : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorCone() {}

	// 获取传感器中的形状接口，以便设置与几何形状有关的参数
	virtual IVBF_MarkModelShapeCone* GetShape()=0;
};

#endif 
