//***************************************************************************************
// FileName��VBF_3DPlotDataTypes_Common.h
// Function��3D��ͼģ�飨Common��ʹ�õĹ�����������
// Author:   
// Date:     
//***************************************************************************************

#ifndef __VBF_3DPLOT_DATATYPES_COMMON_H__
#define __VBF_3DPLOT_DATATYPES_COMMON_H__

#include <VBF_Plot/VBF_3DPlotDataTypes.h>


// ʵ��ģ�͵�����
const unsigned int VBF_MARK_RASTER				= VBF_PLOT_COMMON + 1;
// wuyuguo const unsigned int VBF_MARK_RASTER_SYMBOL		= VBF_PLOT_COMMON + 2;      // դ����ž���
const unsigned int VBF_MARK_RASTER_ANIM			= VBF_PLOT_COMMON + 3;      // դ�񶯻�
const unsigned int VBF_MARK_RASTER_SWITCH		= VBF_PLOT_COMMON + 4;      // ����״̬�л�դ��ͼƬ
const unsigned int VBF_MARK_CROSSQUAD			= VBF_PLOT_COMMON + 5;
const unsigned int VBF_MARK_SINGLEQUAD			= VBF_PLOT_COMMON + 6;

const unsigned int VBF_MARK_MESH				= VBF_PLOT_COMMON + 11;
const unsigned int VBF_MARK_VOLUME_RAYTRACING	= VBF_PLOT_COMMON + 12;  // ����ƣ�����׷�ٷ���
const unsigned int VBF_MARK_VOLUME_RAYCASTING	= VBF_PLOT_COMMON + 13;  // ����ƣ�����Ͷ�䷨��
// wuyuguo const unsigned int VBF_MARK_MESH2	= VBF_PLOT_COMMON + 12;
// wuyuguo const unsigned int VBF_MARK_ANIM		= VBF_PLOT_COMMON + 13;     // ��������
const unsigned int VBF_MARK_CAL3D				= VBF_PLOT_COMMON + 14;
const unsigned int VBF_MARK_FIELD				= VBF_PLOT_COMMON + 15;  // ��ģ�ͣ���糡���������ȣ�

const unsigned int VBF_MARK_2DIMAGE   			= VBF_PLOT_COMMON + 21;     // 2Dͼ��
const unsigned int VBF_MARK_2DCHART   			= VBF_PLOT_COMMON + 22;     // 2Dͼ��


const unsigned int VBF_MARK_TEXT				= VBF_PLOT_COMMON + 41;     // �ı�
const unsigned int VBF_MARK_TEXT_CHAINED		= VBF_PLOT_COMMON + 42;     // ɢ��ʽ�ı�

const unsigned int VBF_MARK_VPLANE_LINE			= VBF_PLOT_COMMON + 61;
const unsigned int VBF_MARK_SCANZONE			= VBF_PLOT_COMMON + 62;
const unsigned int VBF_MARK_POLYLINE_NMT		= VBF_PLOT_COMMON + 63;     // ��ά���ߣ���ʹ������������
const unsigned int VBF_MARK_POLYLINE_MT         = VBF_PLOT_COMMON + 64;     // ��ά���ߣ���ʹ����������
const unsigned int VBF_MARK_POLYLINE_TEX		= VBF_PLOT_COMMON + 65;     // ��ά���ߣ������ظ�������
const unsigned int VBF_MARK_TINPOINT			= VBF_PLOT_COMMON + 66;     // ʹ�ò�������������ģ�ͣ���״��λ
const unsigned int VBF_MARK_TINPOLY             = VBF_PLOT_COMMON + 67;     // ʹ�ò�������������ģ�ͣ���״��λ
const unsigned int VBF_MARK_GEOMETRY			= VBF_PLOT_COMMON + 68;     // �����򼸺��壨�������桢�����������ı��εȣ�
const unsigned int VBF_MARK_POINTSET			= VBF_PLOT_COMMON + 69;     // �㼯����һ�麣�����ǣ�
const unsigned int VBF_MARK_POLYGON_MT			= VBF_PLOT_COMMON + 70;     // ����Σ����أ�
const unsigned int VBF_MARK_POLYGON_NMT			= VBF_PLOT_COMMON + 71;     // ����Σ������أ�
const unsigned int VBF_MARK_FAN_GEO				= VBF_PLOT_COMMON + 72;     // ʹ�õ�����������Σ����أ�
const unsigned int VBF_MARK_WALL				= VBF_PLOT_COMMON + 73;     // ֱ����ǽ��
const unsigned int VBF_MARK_FUNCTION            = VBF_PLOT_COMMON + 75;     // ����ģ�ͣ����û��Զ��庯�����棩
const unsigned int VBF_MARK_COORDSYS            = VBF_PLOT_COMMON + 76;     // ����ϵģ�ͣ�������ʾ��״ģ�͵ľֲ�����ϵ��

const unsigned int VBF_MARK_COMBINED			= VBF_PLOT_COMMON + 101;	// ���ģ��
const unsigned int VBF_MARK_LOD                 = VBF_PLOT_COMMON + 106;	// ��ֱ���ģ��
const unsigned int VBF_MARK_SWITCH              = VBF_PLOT_COMMON + 107;	// ���л�ģ��

const unsigned int VBF_MARK_PS_COMMON           = VBF_PLOT_COMMON + 200;	// ����ϵͳ-ͨ��
const unsigned int VBF_MARK_PS_EXPLODE          = VBF_PLOT_COMMON + 201;	// ����ϵͳ-��ը
const unsigned int VBF_MARK_PS_SMOKE_TRAIL      = VBF_PLOT_COMMON + 202;	// ����ϵͳ-β��

// ����դ��ģ��
const unsigned int VBF_MARK_RASTER_BILLBOARD_H   = VBF_PLOT_COMMON + 301;    // ģ����ˮƽ����ʹ�ò�����
const unsigned int VBF_MARK_RASTER_BILLBOARD_V   = VBF_PLOT_COMMON + 302;    // ģ���ڴ�ֱ����ʹ�ò�����
const unsigned int VBF_MARK_RASTER_BILLBOARD_HV  = VBF_PLOT_COMMON + 303;    // ģ��ͬʱ��ˮƽ�ʹ�ֱ����ʹ�ò�����
const unsigned int VBF_MARK_RASTER_HORIZON       = VBF_PLOT_COMMON + 304;    // ģ��ʼ��ƽ���ڵ��棬���ӵ��޹�

#endif
