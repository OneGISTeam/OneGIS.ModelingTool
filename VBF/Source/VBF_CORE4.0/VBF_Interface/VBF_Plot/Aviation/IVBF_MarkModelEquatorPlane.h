//*******************************************************************
// FileName：IVBF_MarkModelEquatorPlane.h
// Function：实体模型接口：赤道面
// Author:   杜莹
// Date:     2015-03-26
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_EQUATOR_PLANE_H__
#define __IVBF_MARK_MODEL_EQUATOR_PLANE_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <vector>
#include <VBF_Plot/Aviation/VBF_3DPlotDataTypes_Aviation.h>


class IVBF_MarkModelEquatorPlane : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelEquatorPlane() {}

    // 设置/获取同心圆的线段样式
    virtual void                 SetCircleLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetCircleLineStyle()=0;

    // 设置/获取同心圆中射线的线段样式
    virtual void                 SetRayLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetRayLineStyle()=0;
};

#endif 
