//*******************************************************************
// FileName��IVBF_MarkModelBeam.h
// Function���״ﲨ��ʵ��ģ�ͽӿ�
// Author:   ��Ө
// Date:     2013-11-12
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_BEAM_H__
#define __IVBF_MARK_MODEL_BEAM_H__


#include <VBF_Plot/Common/IVBF_MarkModelGraphics.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeCone.h>
#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>


class IVBF_MarkModelBeam : public IVBF_MarkModelGraphics
{
public:
	virtual ~IVBF_MarkModelBeam() {}

	// ��ȡ�����е���״�ӿڣ��Ա������뼸����״�йصĲ���
	virtual IVBF_MarkModelShapeCone* GetShape()=0;
};

#endif 
