//*******************************************************************
// FileName��IVBF_MarkModelSensorCone.h
// Function��Բ׶״��������������X����
// Author��  ��Ө
// Date��    2013-10-25
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_CONE_H__
#define __IVBF_MARK_MODEL_SENSOR_CONE_H__

#include "IVBF_MarkModelSensor.h"
#include <VBF_Plot/Shape/IVBF_MarkModelShapeCone.h>


class IVBF_MarkModelSensorCone : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorCone() {}

	// ��ȡ�������е���״�ӿڣ��Ա������뼸����״�йصĲ���
	virtual IVBF_MarkModelShapeCone* GetShape()=0;
};

#endif 
