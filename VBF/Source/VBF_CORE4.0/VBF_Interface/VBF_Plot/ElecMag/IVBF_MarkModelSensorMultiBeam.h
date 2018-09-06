//*******************************************************************
// FileName：IVBF_MarkModelSensorMultiBeam.h
// Function：多波束传感器
// Author：  杜莹
// Date：    2015-04-03
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_MULTIBEAM_H__
#define __IVBF_MARK_MODEL_SENSOR_MULTIBEAM_H__


#include "IVBF_MarkModelSensor.h"
#include <VBF_Plot/Shape/IVBF_MarkModelShapeDome.h>


class IVBF_MarkModelSensorMultiBeam : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorMultiBeam() {}

	// 获取传感器中的形状接口，以便设置与几何形状有关的参数
	virtual IVBF_MarkModelShapeDome* GetShape()=0;
};

#endif 
