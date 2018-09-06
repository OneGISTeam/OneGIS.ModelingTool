//*******************************************************************
// FileName��IVBF_3DAnalysisToolDist.h
// Function����ά�������ߣ���������
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_DIST_H__
#define __IVBF_3DANALYSIS_TOOL_DIST_H__


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolDist : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolDist() {}

	// �Ƿ���Ҫ������������������ı��ļ��У�Ĭ��Ϊ�����
	// ������bSerialized -- �Ƿ���Ҫ���
	//       szFileName  -- ������ļ��� (����·��+�ļ���.��׺)
	virtual void SetCoordSerialized(bool bSerialized, const char* szFileName)=0;

    // ������Ϣ����ɼ�
    virtual void SetTipDistVisible(bool bVisible) {}
};

#endif
