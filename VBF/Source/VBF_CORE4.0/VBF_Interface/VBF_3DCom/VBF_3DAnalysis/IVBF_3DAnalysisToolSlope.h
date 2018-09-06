//*******************************************************************
// FileName：IVBF_3DAnalysisToolSlope.h
// Function：三维分析工具：坡度分析
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_SLOPE_H__
#define __IVBF_3DANALYSIS_TOOL_SLOPE_H__


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolSlope : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolSlope() {}

    // 设置/获取量算结果的多边形透明度（默认值为0.8）
    virtual void  SetPolygonAlpha(float fAlpha)=0;
    virtual float GetPolygonAlpha()=0;
};

#endif
