//***************************************************************************************
// FileName：VBF_3DPlotDataTypes_Aviation.h
// Function：3D航空模块（Aviation）使用的公用数据类型
// Author:   
// Date:     
//***************************************************************************************

#ifndef __VBF_3DPLOT_DATATYPES_AVIATION_H__
#define __VBF_3DPLOT_DATATYPES_AVIATION_H__

#include <VBF_Plot/VBF_3DPlotDataTypes.h>


const unsigned int VBF_MARK_AIRLINE             = VBF_PLOT_AVIATION + 1;	// 航线
const unsigned int VBF_MARK_CHAFF               = VBF_PLOT_AVIATION + 2;	// 箔条云
const unsigned int VBF_MARK_AIRSPACE_ARC        = VBF_PLOT_AVIATION + 3;	// 空域（弧段形）
const unsigned int VBF_MARK_AIRSPACE_CIRCLE     = VBF_PLOT_AVIATION + 4;	// 空域（圆形）
const unsigned int VBF_MARK_AIRSPACE_POLYLINE	= VBF_PLOT_AVIATION + 5;	// 空域（折线形）
const unsigned int VBF_MARK_EQUATORPLANE        = VBF_PLOT_AVIATION + 6;	// 赤道面
const unsigned int VBF_MARK_SPHERELIGHT         = VBF_PLOT_AVIATION + 7;    // 球（地球光影）
const unsigned int VBF_MARK_GEOELLIP            = VBF_PLOT_AVIATION + 8;    // 地理椭球（即与地心一致的椭球体）



const unsigned int VBF_MARK_ATTR_PATROL   = VBF_PLOT_AVIATION + 1;	// 飞机巡逻




#endif
