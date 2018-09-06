//*******************************************************************
// FileName��IVBF_MarkModelSensorPA.h
// Function��������״PA: Phased Array��
// Author:   ���
// Date:     2015-04-15
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_PA_H__
#define __IVBF_MARK_MODEL_SENSOR_PA_H__

#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorDome.h>


class IVBF_MarkModelSensorPA : public IVBF_MarkModelSensor
{
public:
    virtual ~IVBF_MarkModelSensorPA() {}

    // ����/��ȡ�����������
    // ������nNumBeamGroups   -- ��������
    //      nNumRowsPerGroup -- ÿ�鲨���е�����
    //      nNumColsPerGroup -- ÿ�鲨���е�����
    virtual void SetTess(int nNumBeamGroups, int nNumRowsPerGroup, int nNumColsPerGroup)=0;
    virtual void GetTess(int& nNumBeamGroups, int& nNumRowsPerGroup, int& nNumColsPerGroup)=0;

    // ��ȡ�������еĸ�����״�ӿڣ��Ա������뼸����״�йصĲ���
    virtual IVBF_MarkModelSensorDome* GetDetectZone()=0;	// ̽������Բ���Σ�

	// ����/�ر�ɨ�裨Ĭ��Ϊ������
	virtual void EnableScan(bool bEnable)=0;
	virtual bool IsScanEnabled()=0;

	// ����/��ȡɨ���ٶȣ���λ���Ƕ�/�룬Ĭ��ֵΪ2.0��
	virtual void  SetScanSpeed(float fSpeed)=0;
	virtual float GetScanSpeed()=0;
};

#endif 
