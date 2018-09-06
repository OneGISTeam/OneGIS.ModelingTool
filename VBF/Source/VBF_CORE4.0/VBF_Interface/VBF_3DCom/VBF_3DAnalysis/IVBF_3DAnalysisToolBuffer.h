//*******************************************************************
// FileName��IVBF_3DAnalysisToolBuffer.h
// Function��3D�������ߣ�����������
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_BUFFER_H__
#define __IVBF_3DANALYSIS_TOOL_BUFFER_H__


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolBuffer : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolBuffer() {}

    // ����/��ȡ�������Ķ������ʽ
    virtual void                      SetPolygonStyle(const VBF_POLYGON3DSTYLE& style)=0;
    virtual const VBF_POLYGON3DSTYLE& GetPolygonStyle()=0;
};

#endif
