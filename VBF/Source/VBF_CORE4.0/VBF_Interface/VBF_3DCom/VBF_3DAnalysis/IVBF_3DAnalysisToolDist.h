//*******************************************************************
// FileName：IVBF_3DAnalysisToolDist.h
// Function：三维分析工具：距离量算
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_DIST_H__
#define __IVBF_3DANALYSIS_TOOL_DIST_H__


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolDist : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolDist() {}

	// 是否需要将坐标量算结果输出到文本文件中，默认为不输出
	// 参数：bSerialized -- 是否需要输出
	//       szFileName  -- 输出的文件名 (完整路径+文件名.后缀)
	virtual void SetCoordSerialized(bool bSerialized, const char* szFileName)=0;

    // 距离信息必须可见
    virtual void SetTipDistVisible(bool bVisible) {}
};

#endif
