//*******************************************************************
// FileName��IVBF_MarkModelSensorRadarSkyEx.h
// Function��������ʵ��ģ�ͣ���ɨ�趯�����첨�״�
// Author:   ��Ө
// Date:     2013-10-17
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_RADAR_SKY_EX_H__
#define __IVBF_MARK_MODEL_SENSOR_RADAR_SKY_EX_H__


#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorRadarSky.h>

// �첨�״�ɨ�跽ʽ
enum EVBF_RADARSKY_SCAN_TYPE          
{
	VBF_RADARSKY_SCAN_TYPE_ORDINAL	= 0,	// ˳��ɨ�裨Ĭ��ֵ��
	VBF_RADARSKY_SCAN_TYPE_SKIP		= 1		// ��Ծɨ��
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelSensorRadarSkyEx
// �ӿ���������ɨ�趯�����첨�״�
//--------------------------------------------------------------------
class IVBF_MarkModelSensorRadarSkyEx : public IVBF_MarkModelSensorRadarSky
{
public:
	virtual ~IVBF_MarkModelSensorRadarSkyEx() {}

public:

	/* ����/��ȡ�״�����Σ�ͨ�������״����ǣ�
	   ������fAngleOpen -- �첨�״�����Ž�
	         fAngleH0, fAngleH1 -- �첨�״�ˮƽ�Ƿ�Χ
             fAngleV0, fAngleV1 -- �첨�״����Ƿ�Χ��ȡֵ��Χ��10-80��֮��
			 nNumRows, nNumCols -- ɨ�����������
	*/
	virtual void SetTess(float fAngleOpen, float fAngleH0, float fAngleH1, float fAngleV0, float fAngleV1, 
		                 int nNumRows, int nNumCols)=0;

	virtual void GetTess(float& fAngleOpen, float& fAngleH0, float& fAngleH1, float& fAngleV0, float& fAngleV1, 
		                 int& nNumRows, int& nNumCols)=0;

	/* ����/��ȡ�״�����Σ�ͨ�������״�̽����룩
	   ������fAngleOpen -- �첨�״�����Ž�
			 fAngleH0, fAngleH1 -- �첨�״�ˮƽ�Ƿ�Χ
			 fDistMin, fDistMax -- �첨�״���������Զ̽����루��λ���ף�
			 nNumRows, nNumCols -- ɨ�����������
	*/
	virtual void SetTessByDist(float fAngleOpen, float fAngleH0, float fAngleH1, float fDistMin, float fDistMax,
							   int nNumRows, int nNumCols)=0;

	virtual void GetTessByDist(float& fAngleOpen, float& fAngleH0, float& fAngleH1, float& fDistMin, float& fDistMax,
							   int& nNumRows, int& nNumCols)=0;

	// ����/��ȡɨ�跽ʽ��Ĭ��Ϊ˳��ɨ��
	virtual void SetScanType(EVBF_RADARSKY_SCAN_TYPE nType)=0;
	virtual EVBF_RADARSKY_SCAN_TYPE GetScanType()=0;

	// ����/��ȡ��ǰɨ��λ�ã�������ɨ������
	virtual void SetScanPos(int nRow, int nCol)=0;
	virtual void GetScanPos(int& nRow, int& nCol)=0;

	// ����/��ȡ˳��ɨ��ʱÿ������ͣ����ʱ�䣬��λ���루ֵԽ��ɨ���ٶ�Խ����Ĭ��ֵΪ2.0��
	virtual void  SetScanPausalTime(float fTime)=0;
	virtual float GetScanPausalTime()=0;

	// ����/��ȡɨ�������ɫ
	virtual void       SetScanBandColor(const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetScanBandColor()=0;

	// ע�⣺�첨�״ﲻ��������/ƽ��
	virtual void SetScale(float fScaleX, float fScaleY, float fScaleZ)	{}
	virtual void SetTrans(float fTransX, float fTransY, float fTransZ)	{}
	virtual void SetTess(float fAngleOpen, float fAngleH, float fAngleV){}
};


#endif 
