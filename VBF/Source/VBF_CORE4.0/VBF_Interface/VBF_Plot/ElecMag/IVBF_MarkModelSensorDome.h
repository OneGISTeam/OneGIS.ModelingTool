//*******************************************************************
// FileName：IVBF_MarkModelSensorDome.h
// Function：圆顶状传感器，适用于X波段
// Author：  杜莹
// Date：    2013-10-25
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_DOME_H__
#define __IVBF_MARK_MODEL_SENSOR_DOME_H__


#include "IVBF_MarkModelSensor.h"
#include <VBF_Plot/Shape/IVBF_MarkModelShapeDome.h>


class IVBF_MarkModelSensorDome : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorDome() {}

	// 获取传感器中的形状接口，以便设置与几何形状有关的参数
	virtual IVBF_MarkModelShapeDome* GetShape()=0;
};

#endif 
