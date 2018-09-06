//***************************************************************************************
// FileName��VBF_3DPlotDataTypes_ElecMag.h
// Function��3D���ģ��ʹ�õĹ�����������
// Author:   ��Ө
// Date:     2013-10-14
//***************************************************************************************

#ifndef __VBF_3DPLOT_DATATYPES_ELECMAG_H__
#define __VBF_3DPLOT_DATATYPES_ELECMAG_H__


#include <VBF_Plot/VBF_3DPlotDataTypes.h>


// �����ʵ��ģ�͵�����
const unsigned int VBF_MARK_SENSOR				= VBF_PLOT_ELECMAG + 1000;		// �����������࣬���ɴ�����ID�ŵ�ģ�ͣ�
const unsigned int VBF_MARK_BEAM				= VBF_PLOT_ELECMAG + 2000;		// �״ﲨ��
const unsigned int VBF_MARK_LINK_2D		        = VBF_PLOT_ELECMAG + 2001;		// ��ͨ�ߣ���ά����
const unsigned int VBF_MARK_LINK_LINE		    = VBF_PLOT_ELECMAG + 2002;		// ��ͨ�ߣ���ά��
const unsigned int VBF_MARK_LINK_RING	   	    = VBF_PLOT_ELECMAG + 2003;		// ��ͨ�ߣ���ά��״
const unsigned int VBF_MARK_LINK_METEOR	   	    = VBF_PLOT_ELECMAG + 2004;		// ��ͨ�ߣ�������
const unsigned int VBF_MARK_LINK_2D_DUALWORK    = VBF_PLOT_ELECMAG + 2005;		// ��ͨ�ߣ���ά����˫��

// �����״﷽��ͼ�벨����
const unsigned int VBF_MARK_RADARUNION          = VBF_PLOT_ELECMAG + 2010;      // �״������ţ�����ʾ
const unsigned int VBF_MARK_RADARENERGY_XYZ     = VBF_PLOT_ELECMAG + 2011;      // �״﷽��ͼ��ֱ������ϵ��
const unsigned int VBF_MARK_RADARENERGY_POLAR   = VBF_PLOT_ELECMAG + 2012;      // �״﷽��ͼ��������ϵ��
const unsigned int VBF_MARK_RADARLOBE_CONE      = VBF_PLOT_ELECMAG + 2013;      // �״ﲨ���飨Բ׶�Σ�

// ���ִ�����
const unsigned int VBF_MARK_SENSOR_CONE			= VBF_MARK_SENSOR + 1;		// ׶�δ�����
const unsigned int VBF_MARK_SENSOR_DOME	        = VBF_MARK_SENSOR + 2;		// Բ���δ�����
const unsigned int VBF_MARK_SENSOR_SECTOR       = VBF_MARK_SENSOR + 3;      // ���δ�����
const unsigned int VBF_MARK_SENSOR_RECT			= VBF_MARK_SENSOR + 4;		// ���δ�����
const unsigned int VBF_MARK_SENSOR_INFRARED		= VBF_MARK_SENSOR + 5;		// ���⴫����
const unsigned int VBF_MARK_SENSOR_RADAR_SKY	= VBF_MARK_SENSOR + 6;		// �첨�״�
const unsigned int VBF_MARK_SENSOR_RADAR_SKYEX	= VBF_MARK_SENSOR + 7;		// ��ɨ�趯�����첨�״�
const unsigned int VBF_MARK_SENSOR_RADAR_AEW	= VBF_MARK_SENSOR + 8;		// Ԥ�����״�
const unsigned int VBF_MARK_SENSOR_RADAR_GROUND	= VBF_MARK_SENSOR + 9;		// �����״�
const unsigned int VBF_MARK_SENSOR_AC	        = VBF_MARK_SENSOR + 10;		// Ŀָ�״�
const unsigned int VBF_MARK_SENSOR_FK_RECT	   	= VBF_MARK_SENSOR + 11;		// �����״������Ϊ���Σ�
const unsigned int VBF_MARK_SENSOR_FK_DOME	   	= VBF_MARK_SENSOR + 12;		// �����״������ΪԲ���Σ�
const unsigned int VBF_MARK_SENSOR_VISIBLE	   	= VBF_MARK_SENSOR + 13;		// Ŀָ�״�
const unsigned int VBF_MARK_SENSOR_P_DOME       = VBF_MARK_SENSOR + 14;		// P���δ�������̽����ΪԲ���Σ�
const unsigned int VBF_MARK_SENSOR_P_SECTOR     = VBF_MARK_SENSOR + 15;		// P���δ�������̽����Ϊ���Σ�
const unsigned int VBF_MARK_SENSOR_MULTIBEAM    = VBF_MARK_SENSOR + 16;     // �ನ��������
const unsigned int VBF_MARK_SENSOR_PA           = VBF_MARK_SENSOR + 17;     // ������״�
const unsigned int VBF_MARK_SENSOR_RADAR_JAMMED	= VBF_MARK_SENSOR + 18;		// �������״�

// ���ֹ���Ч��
const unsigned int VBF_MARK_THREAT_WAVE         = VBF_PLOT_ELECMAG + 3001;   // ��������������ɨ�貨��һ�鶯̬����Σ�

#endif
