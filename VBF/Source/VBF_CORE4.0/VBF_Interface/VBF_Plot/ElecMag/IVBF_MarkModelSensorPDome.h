//*******************************************************************
// FileName��IVBF_MarkModelSensorPDome.h
// Function��P���δ�������̽����ΪԲ���Σ�
// Author:   ��Ө
// Date:     2013-10-28
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_P_DOME_H__
#define __IVBF_MARK_MODEL_SENSOR_P_DOME_H__


#include "IVBF_MarkModelSensor.h"
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorRect.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorDome.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeCone.h>


class IVBF_MarkModelSensorPDome : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorPDome() {}

	// ��ȡ�������еĸ�����״�ӿڣ��Ա������뼸����״�йصĲ���
    virtual IVBF_MarkModelSensorRect*	GetSensorRect()=0;	// ����������ƽ��ͷ�壩
    virtual IVBF_MarkModelSensorDome*	GetDetectZone()=0;	// ̽������Բ���Σ�
    virtual IVBF_MarkModelShapeCone*    GetScanBeam()=0;	// ɨ�貨��Բ׶�Σ�����ƽ��ͷ����ת��

	// ����/�ر�ɨ��
	virtual void EnableScan(bool bEnable)=0;
	virtual bool IsScanEnabled()=0;

	// ����/��ȡɨ���ٶȣ���λ���Ƕ�/�룩
	virtual void  SetScanSpeed(float fSpeed)=0;
	virtual float GetScanSpeed()=0;
};

#endif
