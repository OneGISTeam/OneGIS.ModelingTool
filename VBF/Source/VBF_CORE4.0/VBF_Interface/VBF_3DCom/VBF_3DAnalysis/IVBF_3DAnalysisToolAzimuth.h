//*******************************************************************
// FileName��IVBF_3DAnalysisToolAzimuth.h
// Function��3D�������ߣ���λ������
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_AZIMUTH_H__
#define __IVBF_3DANALYSIS_TOOL_AZIMUTH_H__


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolAzimuth : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolAzimuth() {}

    // ��λ����Ϣ����ɼ�
    virtual void SetTipAzimuthVisible(bool bVisible) {}
};

#endif
