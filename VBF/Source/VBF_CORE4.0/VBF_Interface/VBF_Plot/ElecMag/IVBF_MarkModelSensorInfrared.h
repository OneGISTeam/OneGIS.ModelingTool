//*******************************************************************
// FileName��IVBF_MarkModelSensorInfrared.h
// Function��������ʵ��ģ�ͣ����⴫����
// Author:   ��Ө
// Date:     2013-10-21
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_INFRARED_H__
#define __IVBF_MARK_MODEL_SENSOR_INFRARED_H__


#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeFrustum.h>
#include <Types/VBF_3DStyles.h>


// ���峣��������ֹ����ĸ߶ȣ������Ͽյľ��룩
const double GEO_ORBIT_H = 3.5786e7; // ����ֹ�����Geostationary Orbit�����GEO


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelSensorInfrared
// �ӿ����������⴫����
//--------------------------------------------------------------------
class IVBF_MarkModelSensorInfrared : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorInfrared() {}

public:

	// ��ȡ�������е���״�ӿڣ��Ա������뼸����״�йصĲ���
	virtual IVBF_MarkModelShapeFrustumDome* GetShape()=0;

	// ����/��ȡ�ڶ�ɨ���γ�ȷ�Χ
	virtual void   SetSwingPosOnEarth(double dB)=0;
	virtual double GetSwingPosOnEarth()=0;

	// ����/��ȡɨ�����ڣ�һ���ڶ����ص�ʱ�䣨��λ���룩
	virtual void  SetScanPeriod(float fPeriod)=0;
	virtual float GetScanPeriod()=0;
};


#endif 
