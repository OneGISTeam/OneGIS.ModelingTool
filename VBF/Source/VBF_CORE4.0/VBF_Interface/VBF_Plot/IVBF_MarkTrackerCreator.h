//*******************************************************************
// FileName��IVBF_MarkTrackerCreator.h
// Function����ά��ͼģ���Ϸ��������ӿ�
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_TRACKER_CREATOR_H__
#define __IVBF_MARK_TRACKER_CREATOR_H__


// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DPLOT_TRACKER_CREATOR[]	= "��ά��ͼģ���Ϸ��������ӿ�";

#include "IVBF_MarkTracker.h"
#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/IVBF_3DPlot.h>
//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkTrackerCreator
// �ӿ�������ʵ��ģ�����Դ����ӿ�
//--------------------------------------------------------------------
class IVBF_MarkTrackerCreator
{
public:
    virtual ~IVBF_MarkTrackerCreator() {}

public:
    virtual IVBF_MarkTracker* CreateMarkTracker(EVBF_PLOT_STATE nState,IVBF_MarkModel* pIMark)=0;
};


#endif 
