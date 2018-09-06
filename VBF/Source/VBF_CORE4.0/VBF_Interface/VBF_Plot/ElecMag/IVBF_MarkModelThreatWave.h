//*******************************************************************
// FileName��IVBF_MarkModelThreatWave.h
// Function������ʵ��ģ�ͣ���������������ɨ�貨��һ�鶯̬�����
// Author:   ��Ө
// Date:     2015-11-26
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_THREAT_WAVE_H__
#define __IVBF_MARK_MODEL_THREAT_WAVE_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>
#include <Types/VBF_3DStyles.h>


// ��������ɨ�跽ʽ
enum EVBF_THREATWAVE_SCAN_MODE
{
	VBF_THREATWAVE_SCAN_MOVE	= 0,	// ƽ��ʽ
	VBF_THREATWAVE_SCAN_BOUNCE	= 1		// ����ʽ��Ĭ�ϣ�
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelThreatWave
// �ӿ���������������һ�鶯̬����Σ��γ�һ�����ε�Բ׶��
//--------------------------------------------------------------------
class IVBF_MarkModelThreatWave : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelThreatWave() {}

public:

	// ����/��ȡԲ׶�Žǵ�һ�룬Ĭ��ֵΪ30�ȣ�Ĭ������£�ԭ��λ��׶�⣬����뾶Ϊ1��
	virtual void SetTess(float fHalfAngle)=0;
	virtual void GetTess(float& fHalfAngle)=0;

	/* ����/��ȡԲ׶��Բ�ָܷ�����Ĭ��ֵΪ36 */
	virtual void SetNumSplitCircle(int nNumSplit)=0;
	virtual int  GetNumSplitCircle()=0;

	// ����/��ȡԲ׶��ײ��뾶
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;

	// ����/��ȡԲ׶��߶�
	virtual void  SetHeight(float fHeight)=0;
	virtual float GetHeight()=0;

	// ����/��ȡ��̬ɨ����ٶȣ���λ����/�룬Ĭ��ֵΪ0.3��
	virtual void  SetScanSpeed(float fSpeed)=0;
	virtual float GetScanSpeed()=0;

	// ����/��ȡɨ������Բ���ĸ�����Ĭ��ֵΪ5��
	virtual void SetNumScanLines(int num)=0;
	virtual int  GetNumScanLines()=0;

	// ����/��ȡɨ���ߵ���ʽ
	virtual void                 SetScanLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetScanLineStyle()=0;

	// ����/��ȡɨ���ߵĽ���Alpha��ֵ���Ϊ[0, 1]����fAlpha0 <= fAlpha1
	virtual void SetScanLineAlpha(float fAlpha0, float fAlpha1)=0;
	virtual void GetScanLineAlpha(float& fAlpha0, float& fAlpha1)=0;

	// ����/��ȡɨ�跽ʽ
	virtual void                      SetScanMode(EVBF_THREATWAVE_SCAN_MODE nMode)=0;
	virtual EVBF_THREATWAVE_SCAN_MODE GetScanMode()=0;

	// ƽ�Ʒ�ʽ�£�����/��ȡɨ���߸߶�ռ������Բ׶�ĸ߶ȱ�����ֵ��Ϊ[0.0, 1.0]��Ĭ��ֵΪ0.2��
	virtual void  SetScanLineHeightRatio(float fRatio)=0;
	virtual float GetScanLineHeightRatio()=0;

	// ������ʽ�£�����/��ȡԲ׶��ⲿ�뾶��ײ��뾶�ı�ֵ��ֵ��Ϊ[0.0, 1.0]��Ĭ��ֵΪ0.3��
	virtual void  SetBounceScaleMin(float fScaleMin)=0;
	virtual float GetBounceScaleMin()=0;
};


#endif 
