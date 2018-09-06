//*******************************************************************
// FileName：IVBF_3DAnalysisToolBuffer.h
// Function：3D分析工具：缓冲区量算
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_BUFFER_H__
#define __IVBF_3DANALYSIS_TOOL_BUFFER_H__


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolBuffer : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolBuffer() {}

    // 设置/获取量算结果的多边形样式
    virtual void                      SetPolygonStyle(const VBF_POLYGON3DSTYLE& style)=0;
    virtual const VBF_POLYGON3DSTYLE& GetPolygonStyle()=0;
};

#endif
