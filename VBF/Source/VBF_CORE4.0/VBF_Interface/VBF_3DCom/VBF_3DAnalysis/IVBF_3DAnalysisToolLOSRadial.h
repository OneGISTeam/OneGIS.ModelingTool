//*******************************************************************
// FileName：IVBF_3DAnalysisToolLOSRadial.h
// Function：三维分析工具：环形区域内的通视分析
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_LOS_RADIAL_H__
#define __IVBF_3DANALYSIS_TOOL_LOS_RADIAL_H__


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolLOSRadial : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolLOSRadial() {}

    // 设置/获取是否只对地形进行通视分析，不考虑地物的遮挡（默认值为true）
    virtual void SetTerrainOnly(bool bTerrainOnly)=0;
    virtual bool IsTerrainOnly()=0;
};

#endif
