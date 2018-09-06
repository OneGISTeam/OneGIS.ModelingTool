//*******************************************************************
// FileName��IVBF_3DAnalysisToolLOSLinear.h
// Function����ά�������ߣ�����ͨ�ӷ���
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_LOS_LINEAR_H__
#define __IVBF_3DANALYSIS_TOOL_LOS_LINEAR_H__


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolLOSLinear : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolLOSLinear() {}

    // ����/��ȡ�Ƿ�ֻ�Ե��ν���ͨ�ӷ����������ǵ�����ڵ���Ĭ��ֵΪtrue��
    virtual void SetTerrainOnly(bool bTerrainOnly)=0;
    virtual bool IsTerrainOnly()=0;
};

#endif
