//*******************************************************************
// FileName��IVBF_MarkModelSensorMultiBeam.h
// Function���ನ��������
// Author��  ��Ө
// Date��    2015-04-03
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_MULTIBEAM_H__
#define __IVBF_MARK_MODEL_SENSOR_MULTIBEAM_H__


#include "IVBF_MarkModelSensor.h"
#include <VBF_Plot/Shape/IVBF_MarkModelShapeDome.h>


class IVBF_MarkModelSensorMultiBeam : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorMultiBeam() {}

	// ��ȡ�������е���״�ӿڣ��Ա������뼸����״�йصĲ���
	virtual IVBF_MarkModelShapeDome* GetShape()=0;
};

#endif 
