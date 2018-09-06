//***************************************************************************************
// FileName：VBF_3DPlotDataTypes_ElecMag.h
// Function：3D电磁模块使用的公用数据类型
// Author:   杜莹
// Date:     2013-10-14
//***************************************************************************************

#ifndef __VBF_3DPLOT_DATATYPES_ELECMAG_H__
#define __VBF_3DPLOT_DATATYPES_ELECMAG_H__


#include <VBF_Plot/VBF_3DPlotDataTypes.h>


// 电磁类实体模型的类型
const unsigned int VBF_MARK_SENSOR				= VBF_PLOT_ELECMAG + 1000;		// 传感器（总类，不可创建该ID号的模型）
const unsigned int VBF_MARK_BEAM				= VBF_PLOT_ELECMAG + 2000;		// 雷达波束
const unsigned int VBF_MARK_LINK_2D		        = VBF_PLOT_ELECMAG + 2001;		// 连通线，二维纹理
const unsigned int VBF_MARK_LINK_LINE		    = VBF_PLOT_ELECMAG + 2002;		// 连通线，三维线
const unsigned int VBF_MARK_LINK_RING	   	    = VBF_PLOT_ELECMAG + 2003;		// 连通线，三维环状
const unsigned int VBF_MARK_LINK_METEOR	   	    = VBF_PLOT_ELECMAG + 2004;		// 连通线，流星线
const unsigned int VBF_MARK_LINK_2D_DUALWORK    = VBF_PLOT_ELECMAG + 2005;		// 连通线，二维纹理，双工

// 各种雷达方向图与波瓣组
const unsigned int VBF_MARK_RADARUNION          = VBF_PLOT_ELECMAG + 2010;      // 雷达包络干扰，求并显示
const unsigned int VBF_MARK_RADARENERGY_XYZ     = VBF_PLOT_ELECMAG + 2011;      // 雷达方向图（直角坐标系）
const unsigned int VBF_MARK_RADARENERGY_POLAR   = VBF_PLOT_ELECMAG + 2012;      // 雷达方向图（极坐标系）
const unsigned int VBF_MARK_RADARLOBE_CONE      = VBF_PLOT_ELECMAG + 2013;      // 雷达波瓣组（圆锥形）

// 各种传感器
const unsigned int VBF_MARK_SENSOR_CONE			= VBF_MARK_SENSOR + 1;		// 锥形传感器
const unsigned int VBF_MARK_SENSOR_DOME	        = VBF_MARK_SENSOR + 2;		// 圆顶形传感器
const unsigned int VBF_MARK_SENSOR_SECTOR       = VBF_MARK_SENSOR + 3;      // 扇形传感器
const unsigned int VBF_MARK_SENSOR_RECT			= VBF_MARK_SENSOR + 4;		// 矩形传感器
const unsigned int VBF_MARK_SENSOR_INFRARED		= VBF_MARK_SENSOR + 5;		// 红外传感器
const unsigned int VBF_MARK_SENSOR_RADAR_SKY	= VBF_MARK_SENSOR + 6;		// 天波雷达
const unsigned int VBF_MARK_SENSOR_RADAR_SKYEX	= VBF_MARK_SENSOR + 7;		// 带扫描动作的天波雷达
const unsigned int VBF_MARK_SENSOR_RADAR_AEW	= VBF_MARK_SENSOR + 8;		// 预警机雷达
const unsigned int VBF_MARK_SENSOR_RADAR_GROUND	= VBF_MARK_SENSOR + 9;		// 地面雷达
const unsigned int VBF_MARK_SENSOR_AC	        = VBF_MARK_SENSOR + 10;		// 目指雷达
const unsigned int VBF_MARK_SENSOR_FK_RECT	   	= VBF_MARK_SENSOR + 11;		// 防空雷达（传感器为矩形）
const unsigned int VBF_MARK_SENSOR_FK_DOME	   	= VBF_MARK_SENSOR + 12;		// 防空雷达（传感器为圆顶形）
const unsigned int VBF_MARK_SENSOR_VISIBLE	   	= VBF_MARK_SENSOR + 13;		// 目指雷达
const unsigned int VBF_MARK_SENSOR_P_DOME       = VBF_MARK_SENSOR + 14;		// P波段传感器（探测区为圆顶形）
const unsigned int VBF_MARK_SENSOR_P_SECTOR     = VBF_MARK_SENSOR + 15;		// P波段传感器（探测区为扇形）
const unsigned int VBF_MARK_SENSOR_MULTIBEAM    = VBF_MARK_SENSOR + 16;     // 多波束传感器
const unsigned int VBF_MARK_SENSOR_PA           = VBF_MARK_SENSOR + 17;     // 相控阵雷达
const unsigned int VBF_MARK_SENSOR_RADAR_JAMMED	= VBF_MARK_SENSOR + 18;		// 被干扰雷达

// 各种攻击效果
const unsigned int VBF_MARK_THREAT_WAVE         = VBF_PLOT_ELECMAG + 3001;   // 攻击波（类似于扫描波的一组动态多边形）

#endif
