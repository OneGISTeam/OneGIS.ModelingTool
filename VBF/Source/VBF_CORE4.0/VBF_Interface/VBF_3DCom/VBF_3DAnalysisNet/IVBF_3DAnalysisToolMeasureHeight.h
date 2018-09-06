//*******************************************************************
// FileName��IVBF_3DAnalysisToolMeasureHeight.h
// Function����ά�������ߣ����߷���
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_MEASUREHEIGHT_H__
#define __IVBF_3DANALYSIS_TOOL_MEASUREHEIGHT_H__


#include <VBF_3DCom/VBF_3DAnalysisNet/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolMeasureHeight : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolMeasureHeight() {}

    //��������:���̶������߽��
    //���������ptStart--��ʼ����Ļ���꣬ptEnd--��ֹ����Ļ����,textVisible--���ֱ�ע�Ƿ���ʾ(Ĭ����ʾ)
    //���������height--���㴹ֱ�߶Ȳ�(m)
    //����ֵ����
    virtual void GetP2PMeasureHeight(const osg::Vec2f ptStart,const osg::Vec2f ptEnd,
                                     double& height,bool textVisible=true)=0;

};

#endif
