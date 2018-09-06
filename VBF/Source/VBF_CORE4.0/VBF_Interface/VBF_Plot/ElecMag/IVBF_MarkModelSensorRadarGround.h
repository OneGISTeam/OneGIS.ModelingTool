//*******************************************************************
// FileName��IVBF_MarkModelSensorRadarGround.h
// Function��������ʵ��ģ�ͣ������״�
// Author:   ��Ө
// Date:     2013-11-08
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_RADAR_GROUND_H__
#define __IVBF_MARK_MODEL_SENSOR_RADAR_GROUND_H__


#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeRevoSurface.h>


class IVBF_MarkModelSensorRadarGround : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorRadarGround() {}

	// ��ȡ�������е���״�ӿڣ��Ա������뼸����״�йصĲ���
	virtual IVBF_MarkModelShapeRevoSurface* GetShape()=0;

	// ����/��ȡ�״﹦��
	virtual void  SetPower(float fPower)=0;
	virtual float GetPower()=0;
};


#endif
