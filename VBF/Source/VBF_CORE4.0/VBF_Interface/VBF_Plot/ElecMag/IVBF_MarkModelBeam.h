//*******************************************************************
// FileName：IVBF_MarkModelBeam.h
// Function：雷达波束实体模型接口
// Author:   杜莹
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

	// 获取波束中的形状接口，以便设置与几何形状有关的参数
	virtual IVBF_MarkModelShapeCone* GetShape()=0;
};

#endif 
