//*******************************************************************
// FileName��IVBF_MarkModelSensorRect.h
// Function�����δ�������������P����
// Author:   ��Ө
// Date:    2013-10-28
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_RECT_H__
#define __IVBF_MARK_MODEL_SENSOR_RECT_H__


#include "IVBF_MarkModelSensor.h"
#include <VBF_Plot/Shape/IVBF_MarkModelShapeFrustum.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeCone.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensorDome.h>


class IVBF_MarkModelSensorRect : public IVBF_MarkModelSensor
{
public:
	virtual ~IVBF_MarkModelSensorRect() {}

	// ����/��ȡ�������Ƿ�Ϊ��ƽ״��Ĭ��Ϊtrue��
	// ��������Ϊ��ƽ״ʱ��  ��ƽ��ͷ��״��ԭ��λ��׶�⣬���ü���=0��Զ�ü���=1��
	// ����������Ϊ��ƽ״ʱ����Բ��״ƽ��ͷ��״
	virtual void SetFlat(bool bFlat)=0;
	virtual bool IsFlat()=0;

	// ��ȡ�������еĸ�����״�ӿڣ��Ա������뼸����״�йصĲ���
	virtual IVBF_MarkModelShapeFrustum* GetShape()=0;
};

#endif
