//*******************************************************************
// FileName：IVBF_MarkTrackerCreator.h
// Function：三维标图模型拖放器创建接口
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_TRACKER_CREATOR_H__
#define __IVBF_MARK_TRACKER_CREATOR_H__


// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DPLOT_TRACKER_CREATOR[]	= "三维标图模型拖放器创建接口";

#include "IVBF_MarkTracker.h"
#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/IVBF_3DPlot.h>
//--------------------------------------------------------------------
// 定义接口：IVBF_MarkTrackerCreator
// 接口描述：实体模型属性创建接口
//--------------------------------------------------------------------
class IVBF_MarkTrackerCreator
{
public:
    virtual ~IVBF_MarkTrackerCreator() {}

public:
    virtual IVBF_MarkTracker* CreateMarkTracker(EVBF_PLOT_STATE nState,IVBF_MarkModel* pIMark)=0;
};


#endif 
