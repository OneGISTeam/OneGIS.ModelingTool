//*******************************************************************
// FileName��IVBF_MarkModelSensorSector.h
// Function�����δ�������������P����
// Author��  ��Ө
// Date��    2015-08-17
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_SECTOR_H__
#define __IVBF_MARK_MODEL_SENSOR_SECTOR_H__


#include "IVBF_MarkModelSensor.h"
#include <VBF_Plot/Shape/IVBF_MarkModelShapeSector.h>


class IVBF_MarkModelSensorSector : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorSector() {}

	// ��ȡ�������е���״�ӿڣ��Ա������뼸����״�йصĲ���
	virtual IVBF_MarkModelShapeSector* GetShape()=0;
};

#endif 
