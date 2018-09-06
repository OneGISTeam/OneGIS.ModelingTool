//*******************************************************************
// FileName��IVBF_MarkModelSensorPSector.h
// Function��P���δ�������̽����Ϊ���Σ�
// Author:   ��Ө
// Date:     2015-08-17
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_P_SECTOR_H__
#define __IVBF_MARK_MODEL_SENSOR_P_SECTOR_H__


#include "IVBF_MarkModelSensor.h"
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorRect.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorSector.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeCone.h>


class IVBF_MarkModelSensorPSector : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorPSector() {}

	// ��ȡ�������еĸ�����״�ӿڣ��Ա������뼸����״�йصĲ���
    virtual IVBF_MarkModelSensorRect*	GetSensorRect()=0;	// ����������ƽ��ͷ�壩
    virtual IVBF_MarkModelSensorSector*	GetDetectZone()=0;	// ̽���������Σ�
    virtual IVBF_MarkModelShapeCone*    GetScanBeam()=0;	// ɨ�貨��Բ׶�Σ�����ƽ��ͷ����ת��

	// ����/�ر�ɨ��
	virtual void EnableScan(bool bEnable)=0;
	virtual bool IsScanEnabled()=0;

	// ����/��ȡɨ���ٶȣ���λ���Ƕ�/�룩
	virtual void  SetScanSpeed(float fSpeed)=0;
	virtual float GetScanSpeed()=0;
};

#endif
