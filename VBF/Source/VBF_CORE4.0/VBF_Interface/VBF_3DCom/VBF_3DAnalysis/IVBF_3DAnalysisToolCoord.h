//*******************************************************************
// FileName��IVBF_3DAnalysisToolCoord.h
// Function����ά�������ߣ�������������
// Date:     2015-04-22
//*******************************************************************


#ifndef __IVBF_3DANALYSIS_TOOL_COORD_H__
#define __IVBF_3DANALYSIS_TOOL_COORD_H__


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolCoord : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolCoord() {}

	// �Ƿ����ⲿ��ʾ���꣬�ڲ�����ϢVBF_MESSAGE_ANALYSIS_GEOCOOR����
	virtual void SetCoordDisplayOut(bool bDispalyOut)=0;

    // ������Ϣ����ɼ�
    virtual void SetTipCoordVisible(bool bVisible) {}
};

#endif
