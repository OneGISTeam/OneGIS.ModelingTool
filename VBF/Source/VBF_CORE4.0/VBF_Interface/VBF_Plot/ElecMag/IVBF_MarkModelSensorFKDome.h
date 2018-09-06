//*******************************************************************
// FileName��IVBF_MarkModelSensorFKDome.h
// Function�������״������ΪԲ���Σ�
// Author:   ��Ө
// Date:     2015-08-16
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_FK_DOME_H__
#define __IVBF_MARK_MODEL_SENSOR_FK_DOME_H__


#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorDome.h>


class IVBF_MarkModelSensorFKDome : public IVBF_MarkModelSensor
{
public:
    virtual ~IVBF_MarkModelSensorFKDome() {}

    // ��ȡ�������еĸ�����״�ӿڣ��Ա������뼸����״�йصĲ���
    virtual IVBF_MarkModelShapeDome*  GetSensorDome()=0;    // ����������Բ���Σ�
    virtual IVBF_MarkModelSensorDome* GetDetectZone()=0;	// ̽������Բ���Σ�

	// ����/�ر�ɨ�裨Ĭ��Ϊ������
	virtual void EnableScan(bool bEnable)=0;
	virtual bool IsScanEnabled()=0;

	// ����/��ȡɨ���ٶȣ���λ���Ƕ�/�룬Ĭ��ֵΪ2.0��
	virtual void  SetScanSpeed(float fSpeed)=0;
	virtual float GetScanSpeed()=0;
};

#endif 
