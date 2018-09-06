//*******************************************************************
// FileName：IVBF_MarkModelSensorRect.h
// Function：矩形传感器，适用于P波段
// Author:   杜莹
// Date:    2013-10-28
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_RECT_H__
#define __IVBF_MARK_MODEL_SENSOR_RECT_H__


#include "IVBF_MarkModelSensor.h"
#include <VBF_Plot/Shape/IVBF_MarkModelShapeFrustum.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeCone.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorDome.h>


class IVBF_MarkModelSensorRect : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorRect() {}

	// 设置/获取传感器是否为扁平状（默认为true）
	// 当传感器为扁平状时，  呈平截头体状（原点位于锥尖，近裁剪面=0，远裁剪面=1）
	// 当传感器不为扁平状时，呈圆顶状平截头体状
	virtual void SetFlat(bool bFlat)=0;
	virtual bool IsFlat()=0;

	// 获取传感器中的各类形状接口，以便设置与几何形状有关的参数
	virtual IVBF_MarkModelShapeFrustum* GetShape()=0;
};

#endif
