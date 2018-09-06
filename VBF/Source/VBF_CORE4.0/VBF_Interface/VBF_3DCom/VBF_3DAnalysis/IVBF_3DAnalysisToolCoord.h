//*******************************************************************
// FileName：IVBF_3DAnalysisToolCoord.h
// Function：三维分析工具：地理坐标量算
// Date:     2015-04-22
//*******************************************************************


#ifndef __IVBF_3DANALYSIS_TOOL_COORD_H__
#define __IVBF_3DANALYSIS_TOOL_COORD_H__


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolCoord : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolCoord() {}

	// 是否在外部显示坐标，内部把消息VBF_MESSAGE_ANALYSIS_GEOCOOR发出
	virtual void SetCoordDisplayOut(bool bDispalyOut)=0;

    // 坐标信息必须可见
    virtual void SetTipCoordVisible(bool bVisible) {}
};

#endif
