//***************************************************************************************
// FileName：VBF_3DPlotDataTypes_Massive.h
// Function：3D标图模块（海量模型）使用的公用数据类型
// Author:   杜莹
// Date:     2015-12-03
//***************************************************************************************

#ifndef __VBF_3DPLOT_DATATYPES_MASSIVE_H__
#define __VBF_3DPLOT_DATATYPES_MASSIVE_H__


#include <VBF_Plot/VBF_3DPlotDataTypes.h>


// 栅格模型的集合，该集合中所有模型纹理相同，尺寸相同，旋转角相同
const unsigned int VBF_MARK_RASTERSET_BILLBOARD_H   = VBF_PLOT_MASSIVE + 101;    // 集合中每个模型在水平方向使用布告牌
const unsigned int VBF_MARK_RASTERSET_BILLBOARD_V   = VBF_PLOT_MASSIVE + 102;    // 集合中每个模型在垂直方向使用布告牌
const unsigned int VBF_MARK_RASTERSET_BILLBOARD_HV  = VBF_PLOT_MASSIVE + 103;    // 集合中每个模型同时在水平和垂直方向使用布告牌
const unsigned int VBF_MARK_RASTERSET_HORIZON       = VBF_PLOT_MASSIVE + 104;    // 集合中每个模型始终平行于地面，与视点无关

// 支持Lod的栅格模型集合，集合中每个模型均建有3级Lod，Lod=0时使用完全布告牌，Lod=1和Lod=2时平行于地面
const unsigned int VBF_MARK_RASTERSET_LOD           = VBF_PLOT_MASSIVE + 201;

// 点精灵（点的集合，所有点纹理相同，尺寸相同，且始终朝向视点）
const unsigned int VBF_MARK_POINTSPRITE             = VBF_PLOT_MASSIVE + 301;



#endif
