//*******************************************************************
// FileName��IVBF_MarkModelRadarLobeCone.h
// Function������ʵ��ģ�ͣ��״ﲨ���飨Բ׶�Σ�
// Author:   ��Ө
// Date:     2015-01-08
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RADARLOBE_CONE_H__
#define __IVBF_MARK_MODEL_RADARLOBE_CONE_H__


#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>
#include <VBF_Plot/Common/IVBF_MarkModelGraphics.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeCone.h>


class IVBF_MarkModelRadarLobeCone : public IVBF_MarkModelGraphics
{
public:
    virtual ~IVBF_MarkModelRadarLobeCone() {}

	// ��ȡ�����е���״�ӿڣ��Ա������뼸����״�йصĲ���
	virtual IVBF_MarkModelShapeCone* GetShape()=0;
};


#endif 
