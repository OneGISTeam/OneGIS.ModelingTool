//***************************************************************************************
// FileName：VBF_3DPlotDataTypes_Common.h
// Function：3D标图模块（Common）使用的公用数据类型
// Author:   
// Date:     
//***************************************************************************************

#ifndef __VBF_3DPLOT_DATATYPES_COMMON_H__
#define __VBF_3DPLOT_DATATYPES_COMMON_H__

#include <VBF_Plot/VBF_3DPlotDataTypes.h>


// 实体模型的类型
const unsigned int VBF_MARK_RASTER				= VBF_PLOT_COMMON + 1;
// wuyuguo const unsigned int VBF_MARK_RASTER_SYMBOL		= VBF_PLOT_COMMON + 2;      // 栅格符号军标
const unsigned int VBF_MARK_RASTER_ANIM			= VBF_PLOT_COMMON + 3;      // 栅格动画
const unsigned int VBF_MARK_RASTER_SWITCH		= VBF_PLOT_COMMON + 4;      // 根据状态切换栅格图片
const unsigned int VBF_MARK_CROSSQUAD			= VBF_PLOT_COMMON + 5;
const unsigned int VBF_MARK_SINGLEQUAD			= VBF_PLOT_COMMON + 6;

const unsigned int VBF_MARK_MESH				= VBF_PLOT_COMMON + 11;
const unsigned int VBF_MARK_VOLUME_RAYTRACING	= VBF_PLOT_COMMON + 12;  // 体绘制（光线追踪法）
const unsigned int VBF_MARK_VOLUME_RAYCASTING	= VBF_PLOT_COMMON + 13;  // 体绘制（光线投射法）
// wuyuguo const unsigned int VBF_MARK_MESH2	= VBF_PLOT_COMMON + 12;
// wuyuguo const unsigned int VBF_MARK_ANIM		= VBF_PLOT_COMMON + 13;     // 骨骼动画
const unsigned int VBF_MARK_CAL3D				= VBF_PLOT_COMMON + 14;
const unsigned int VBF_MARK_FIELD				= VBF_PLOT_COMMON + 15;  // 场模型（如风场、洋流场等）

const unsigned int VBF_MARK_2DIMAGE   			= VBF_PLOT_COMMON + 21;     // 2D图像
const unsigned int VBF_MARK_2DCHART   			= VBF_PLOT_COMMON + 22;     // 2D图表


const unsigned int VBF_MARK_TEXT				= VBF_PLOT_COMMON + 41;     // 文本
const unsigned int VBF_MARK_TEXT_CHAINED		= VBF_PLOT_COMMON + 42;     // 散列式文本

const unsigned int VBF_MARK_VPLANE_LINE			= VBF_PLOT_COMMON + 61;
const unsigned int VBF_MARK_SCANZONE			= VBF_PLOT_COMMON + 62;
const unsigned int VBF_MARK_POLYLINE_NMT		= VBF_PLOT_COMMON + 63;     // 三维折线，不使用纹理，不贴地
const unsigned int VBF_MARK_POLYLINE_MT         = VBF_PLOT_COMMON + 64;     // 三维折线，不使用纹理，贴地
const unsigned int VBF_MARK_POLYLINE_TEX		= VBF_PLOT_COMMON + 65;     // 三维折线，沿线重复贴纹理
const unsigned int VBF_MARK_TINPOINT			= VBF_PLOT_COMMON + 66;     // 使用不规则三角网的模型，点状定位
const unsigned int VBF_MARK_TINPOLY             = VBF_PLOT_COMMON + 67;     // 使用不规则三角网的模型，面状定位
const unsigned int VBF_MARK_GEOMETRY			= VBF_PLOT_COMMON + 68;     // 不规则几何体（如三角面、三角条带、四边形等）
const unsigned int VBF_MARK_POINTSET			= VBF_PLOT_COMMON + 69;     // 点集（如一组海量卫星）
const unsigned int VBF_MARK_POLYGON_MT			= VBF_PLOT_COMMON + 70;     // 多边形（贴地）
const unsigned int VBF_MARK_POLYGON_NMT			= VBF_PLOT_COMMON + 71;     // 多边形（不贴地）
const unsigned int VBF_MARK_FAN_GEO				= VBF_PLOT_COMMON + 72;     // 使用地理坐标的扇形（贴地）
const unsigned int VBF_MARK_WALL				= VBF_PLOT_COMMON + 73;     // 直立的墙面
const unsigned int VBF_MARK_FUNCTION            = VBF_PLOT_COMMON + 75;     // 函数模型（由用户自定义函数曲面）
const unsigned int VBF_MARK_COORDSYS            = VBF_PLOT_COMMON + 76;     // 坐标系模型（用于显示点状模型的局部坐标系）

const unsigned int VBF_MARK_COMBINED			= VBF_PLOT_COMMON + 101;	// 组合模型
const unsigned int VBF_MARK_LOD                 = VBF_PLOT_COMMON + 106;	// 多分辨率模型
const unsigned int VBF_MARK_SWITCH              = VBF_PLOT_COMMON + 107;	// 可切换模型

const unsigned int VBF_MARK_PS_COMMON           = VBF_PLOT_COMMON + 200;	// 粒子系统-通用
const unsigned int VBF_MARK_PS_EXPLODE          = VBF_PLOT_COMMON + 201;	// 粒子系统-爆炸
const unsigned int VBF_MARK_PS_SMOKE_TRAIL      = VBF_PLOT_COMMON + 202;	// 粒子系统-尾烟

// 单个栅格模型
const unsigned int VBF_MARK_RASTER_BILLBOARD_H   = VBF_PLOT_COMMON + 301;    // 模型在水平方向使用布告牌
const unsigned int VBF_MARK_RASTER_BILLBOARD_V   = VBF_PLOT_COMMON + 302;    // 模型在垂直方向使用布告牌
const unsigned int VBF_MARK_RASTER_BILLBOARD_HV  = VBF_PLOT_COMMON + 303;    // 模型同时在水平和垂直方向使用布告牌
const unsigned int VBF_MARK_RASTER_HORIZON       = VBF_PLOT_COMMON + 304;    // 模型始终平行于地面，与视点无关

#endif
