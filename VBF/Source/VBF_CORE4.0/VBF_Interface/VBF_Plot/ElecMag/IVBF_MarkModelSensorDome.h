//*******************************************************************
// FileName��IVBF_MarkModelSensorDome.h
// Function��Բ��״��������������X����
// Author��  ��Ө
// Date��    2013-10-25
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_DOME_H__
#define __IVBF_MARK_MODEL_SENSOR_DOME_H__


#include "IVBF_MarkModelSensor.h"
#include <VBF_Plot/Shape/IVBF_MarkModelShapeDome.h>


class IVBF_MarkModelSensorDome : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorDome() {}

	// ��ȡ�������е���״�ӿڣ��Ա������뼸����״�йصĲ���
	virtual IVBF_MarkModelShapeDome* GetShape()=0;
};

#endif 
