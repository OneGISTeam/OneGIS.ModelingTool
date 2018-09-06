//*******************************************************************
// FileName��IVBF_MarkModelChaff.h
// Function��ʵ��ģ�ͣ������ƣ��ɽ��������Ƴɣ����ԶԵз��״�ʵʩ��Դ���ţ�
// Author:   ��Ө
// Date:     2014-01-09
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_CHAFF_H__
#define __IVBF_MARK_MODEL_CHAFF_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Aviation/VBF_3DPlotDataTypes_Aviation.h>
#include <Types/VBF_3DStyles.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelChaff
// �ӿ�������������
//--------------------------------------------------------------------
class IVBF_MarkModelChaff : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelChaff() {}

	// ����/��ȡ�����Ƶİ뾶����λ���ף�
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;
};


#endif 
