//*******************************************************************
// FileName��IVBF_3DAnalysisToolVisible.h
// Function����ά�������ߣ�ͨ�ӷ��������η�Χ�ڣ�
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_VISIBLE_H__
#define __IVBF_3DANALYSIS_TOOL_VISIBLE_H__


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolVisible : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolVisible() {}

    // ����/��ȡ�������Ķ����͸���ȣ�Ĭ��ֵΪ0.8��
    virtual void  SetPolygonAlpha(float fAlpha)=0;
    virtual float GetPolygonAlpha()=0;
};

#endif
