//*******************************************************************
// FileName��IVBF_MarkModelSensorRadarAEW.h
// Function��������ʵ��ģ�ͣ�Ԥ�����״Ԥ������AEW, Air Early Warning��
// Author:   ��Ө
// Date:     2013-11-04
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_RADAR_AEW_H__
#define __IVBF_MARK_MODEL_SENSOR_RADAR_AEW_H__


#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeRevoSurface.h>


class IVBF_MarkModelSensorRadarAEW : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorRadarAEW() {}

	// ��ȡ�������е���״�ӿڣ��Ա������뼸����״�йصĲ���
	virtual IVBF_MarkModelShapeRevoSurface* GetShape()=0;

	// ����/��ȡ�״﹦��
	virtual void  SetPower(float fPower)=0;
	virtual float GetPower()=0;
};


#endif
