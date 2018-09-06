//*******************************************************************
// FileName��IVBF_MarkModelSensorAC.h
// Function��Ŀָ�״�
// Author:   ��Ө
// Date:     2013-11-01
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_AC_H__
#define __IVBF_MARK_MODEL_SENSOR_AC_H__

#include "IVBF_MarkModelSensor.h"

class IVBF_MarkModelSensorAC : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorAC() {}

	virtual void AddTarget(IVBF_MarkModelPoint* pIMark)=0;
	virtual void RemoveTarget(IVBF_MarkModelPoint* pIMark)=0;
};

#endif 
