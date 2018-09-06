//*******************************************************************
// FileName��IVBF_MarkModelSensorRadarSky.h
// Function��������ʵ��ģ�ͣ��첨�״�
// Author:   ��Ө
// Date:     2013-10-16
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_RADAR_SKY_H__
#define __IVBF_MARK_MODEL_SENSOR_RADAR_SKY_H__


#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_SENSOR_RADARSKY_PART
// ö���������첨�״�ĸ�������
//--------------------------------------------------------------------
enum EVBF_SENSOR_RADARSKY_PART
{
	VBF_SENSOR_RADARSKY_PART_BODY		= 0,	// ����
	VBF_SENSOR_RADARSKY_PART_SCANWAVE	= 1,	// ɨ�貨
	VBF_SENSOR_RADARSKY_PART_IONOTOP	= 2,	// ����㶥��
	VBF_SENSOR_RADARSKY_PART_COUNT				// ����
};

// Ĭ��ֵ
const float	DEFAULT_IONO_HEIGHT			= 400000.0f;	// �����߶ȣ����첨�״ﷴ��߶Ⱦ���ر�ľ��루������ر�ľ��룩flk
const int   DEFAULT_CENTERLINE_SEGMENTS = 40;			// �����ߵķֶ�����ֵԽ��ɨ�貨������Խϸ��
const int	DEFAULT_SCANWAVE_LOOPS		= 5;			// ɨ�貨ÿ������Ȧ��
const int	DEFAULT_SCANWAVE_INTERVALS	= 4;			// ɨ�貨��֡���

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelSensorRadarSky
// �ӿ��������첨�״�
//--------------------------------------------------------------------
class IVBF_MarkModelSensorRadarSky : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorRadarSky() {}

public:

	/* �����״������
	   ������fAngleOpen -- �첨�״�����Ž�
	         fAngleH   -- �첨�״�ɨ���
			 fAngleV   -- �첨�״�����
	*/
	virtual void SetTess(float fAngleOpen, float fAngleH, float fAngleV)=0;
	virtual void GetTess(float& fAngleOpen, float& fAngleH, float& fAngleV)=0;

	// ����/��ȡ�����ĵ�ǰ�߶ȣ���λ���ף���Ĭ��ֵΪ�μ���������
	virtual void  SetIonosphereHeight(float fHeight)=0;
	virtual float GetIonosphereHeight()=0;

	// ����/��ȡ�����ߵķֶ�����ֵԽ��ɨ�貨������Խϸ����Ĭ��ֵΪ�μ���������
	virtual void SetNumCenterLineSegments(int num)=0;
	virtual int  GetNumCenterLineSegments()=0;

	// ����/��ȡɨ�貨ÿ������Ȧ����Ĭ��ֵΪ�μ���������
	virtual void SetNumScanWaveLoops(int num)=0;
	virtual int  GetNumScanWaveLoops()=0;

	// ����/��ȡɨ�貨��֡�����ֵԽ��ɨ�貨���ٶ�Խ������Ĭ��ֵΪ�μ���������
	virtual void SetNumScanWaveIntervals(int num)=0;
	virtual int  GetNumScanWaveIntervals()=0;

	// ע�⣺�첨�״ﲻ��������/ƽ��
	virtual void SetScale(float fScaleX, float fScaleY, float fScaleZ)	{}
	virtual void SetTrans(float fTransX, float fTransY, float fTransZ)	{}
};


#endif 
