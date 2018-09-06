//***************************************************************************************
// FileName：VBF_3DPlotDataTypes_JB.h
// Function：3D标图模块（军标）使用的公用数据类型
// Author:   
// Date:     
//***************************************************************************************

#ifndef __VBF_3DPLOT_DATATYPES_JB_H__
#define __VBF_3DPLOT_DATATYPES_JB_H__

#include <VBF_Plot/VBF_3DPlotDataTypes.h>

const unsigned int VBF_MARK_JB_POINT            = VBF_PLOT_JB_DKY + 1;	// 点状军标

const unsigned int VBF_MARK_JB_POINT_DTIS       = VBF_PLOT_JB_DTIS + 1;	// 点状军标
const unsigned int VBF_MARK_JB_LINE_DTIS        = VBF_PLOT_JB_DTIS + 2;	// 点状军标
const unsigned int VBF_MARK_JB_SINGLEARROW_DTIS	= VBF_PLOT_JB_DTIS + 3;	// 单箭头
const unsigned int VBF_MARK_JB_MULTIARROW_DTIS	= VBF_PLOT_JB_DTIS + 4;	// 多箭头
const unsigned int VBF_MARK_JB_KIDNEY           = VBF_PLOT_JB_DTIS + 5;	// 配置地域（猪腰子）
const unsigned int VBF_MARK_JB_CANNONGROUP      = VBF_PLOT_JB_DTIS + 6;	// 高炮阵地

#endif
