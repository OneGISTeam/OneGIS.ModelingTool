//***************************************************************************************
// FileName：VBF_3DPlotDataTypes_Marine.h
// Function：3D标图模块（航海）使用的公用数据类型
// Author:   杜莹
// Date:     2015-12-03
//***************************************************************************************

#ifndef __VBF_3DPLOT_DATATYPES_MARINE_H__
#define __VBF_3DPLOT_DATATYPES_MARINE_H__


#include <VBF_Plot/VBF_3DPlotDataTypes.h>


// 各类模型
const unsigned int VBF_MARK_SHIPTRAILSET    = VBF_PLOT_MARINE + 101;    // 多条航迹的集合，用以解决海量航迹同时显示的问题
const unsigned int VBF_MARK_SHIPTRAIL       = VBF_PLOT_MARINE + 102;    // 单条航迹



// 定义枚举：航迹回放的当前状态
enum VBF_REPLAY_STATE
{
    VBF_REPLAY_START        = 0,    // 开始回放
    VBF_REPLAY_PAUSE        = 1,    // 暂停回放
    VBF_REPLAY_PLAY         = 2,    // 正在回放
    VBF_REPLAY_STOP         = 3     // 停止回放
};

#endif
