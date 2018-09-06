//***************************************************************************************
// FileName��VBF_3DPlotDataTypes_Massive.h
// Function��3D��ͼģ�飨����ģ�ͣ�ʹ�õĹ�����������
// Author:   ��Ө
// Date:     2015-12-03
//***************************************************************************************

#ifndef __VBF_3DPLOT_DATATYPES_MASSIVE_H__
#define __VBF_3DPLOT_DATATYPES_MASSIVE_H__


#include <VBF_Plot/VBF_3DPlotDataTypes.h>


// դ��ģ�͵ļ��ϣ��ü���������ģ��������ͬ���ߴ���ͬ����ת����ͬ
const unsigned int VBF_MARK_RASTERSET_BILLBOARD_H   = VBF_PLOT_MASSIVE + 101;    // ������ÿ��ģ����ˮƽ����ʹ�ò�����
const unsigned int VBF_MARK_RASTERSET_BILLBOARD_V   = VBF_PLOT_MASSIVE + 102;    // ������ÿ��ģ���ڴ�ֱ����ʹ�ò�����
const unsigned int VBF_MARK_RASTERSET_BILLBOARD_HV  = VBF_PLOT_MASSIVE + 103;    // ������ÿ��ģ��ͬʱ��ˮƽ�ʹ�ֱ����ʹ�ò�����
const unsigned int VBF_MARK_RASTERSET_HORIZON       = VBF_PLOT_MASSIVE + 104;    // ������ÿ��ģ��ʼ��ƽ���ڵ��棬���ӵ��޹�

// ֧��Lod��դ��ģ�ͼ��ϣ�������ÿ��ģ�;�����3��Lod��Lod=0ʱʹ����ȫ�����ƣ�Lod=1��Lod=2ʱƽ���ڵ���
const unsigned int VBF_MARK_RASTERSET_LOD           = VBF_PLOT_MASSIVE + 201;

// �㾫�飨��ļ��ϣ����е�������ͬ���ߴ���ͬ����ʼ�ճ����ӵ㣩
const unsigned int VBF_MARK_POINTSPRITE             = VBF_PLOT_MASSIVE + 301;



#endif
