//*******************************************************************
// FileName��IVBF_3DAnalysisToolLOSRadial.h
// Function����ά�������ߣ����������ڵ�ͨ�ӷ���
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_LOS_RADIAL_H__
#define __IVBF_3DANALYSIS_TOOL_LOS_RADIAL_H__


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolLOSRadial : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolLOSRadial() {}

    // ����/��ȡ�Ƿ�ֻ�Ե��ν���ͨ�ӷ����������ǵ�����ڵ���Ĭ��ֵΪtrue��
    virtual void SetTerrainOnly(bool bTerrainOnly)=0;
    virtual bool IsTerrainOnly()=0;
};

#endif
