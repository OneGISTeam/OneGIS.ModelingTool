//*******************************************************************
// FileName：IVBF_MarkModelRadarLobeCone.h
// Function：军标实体模型：雷达波瓣组（圆锥形）
// Author:   杜莹
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

	// 获取波束中的形状接口，以便设置与几何形状有关的参数
	virtual IVBF_MarkModelShapeCone* GetShape()=0;
};


#endif 
