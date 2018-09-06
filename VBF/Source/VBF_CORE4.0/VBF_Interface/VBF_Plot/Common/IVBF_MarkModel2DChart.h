//*******************************************************************
// FileName��IVBF_MarkModel2DChart.h
// Function��ʵ��ģ�ͽӿڣ�2Dͼ��ʹ����Ļ����
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_2D_CHART_H__
#define __IVBF_MARK_MODEL_2D_CHART_H__


#include <VBF_Plot/Common/IVBF_MarkModel2D.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <string>
#include <VBF_Engine/VBF_SceneGraph/Image>

class CVBF_Chart;

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModel2DChart
// �ӿ�������2Dͼ��ʹ����Ļ����
//--------------------------------------------------------------------
class IVBF_MarkModel2DChart : public IVBF_MarkModel2D
{
public:
    virtual ~IVBF_MarkModel2DChart() {}
    virtual void Init(CVBF_Chart* pChart)=0;
};


#endif 
