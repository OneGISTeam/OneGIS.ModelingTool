//*******************************************************************
// FileName：IVBF_3DAnalysisToolLOSLinear.h
// Function：三维分析工具：两点通视分析
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_LOS_LINEAR_H__
#define __IVBF_3DANALYSIS_TOOL_LOS_LINEAR_H__


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolLOSLinear : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolLOSLinear() {}

    // 设置/获取是否只对地形进行通视分析，不考虑地物的遮挡（默认值为true）
    virtual void SetTerrainOnly(bool bTerrainOnly)=0;
    virtual bool IsTerrainOnly()=0;
};

#endif
