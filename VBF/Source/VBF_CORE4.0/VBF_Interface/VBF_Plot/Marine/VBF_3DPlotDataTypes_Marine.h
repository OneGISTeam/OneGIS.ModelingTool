//***************************************************************************************
// FileName��VBF_3DPlotDataTypes_Marine.h
// Function��3D��ͼģ�飨������ʹ�õĹ�����������
// Author:   ��Ө
// Date:     2015-12-03
//***************************************************************************************

#ifndef __VBF_3DPLOT_DATATYPES_MARINE_H__
#define __VBF_3DPLOT_DATATYPES_MARINE_H__


#include <VBF_Plot/VBF_3DPlotDataTypes.h>


// ����ģ��
const unsigned int VBF_MARK_SHIPTRAILSET    = VBF_PLOT_MARINE + 101;    // ���������ļ��ϣ����Խ����������ͬʱ��ʾ������
const unsigned int VBF_MARK_SHIPTRAIL       = VBF_PLOT_MARINE + 102;    // ��������



// ����ö�٣������طŵĵ�ǰ״̬
enum VBF_REPLAY_STATE
{
    VBF_REPLAY_START        = 0,    // ��ʼ�ط�
    VBF_REPLAY_PAUSE        = 1,    // ��ͣ�ط�
    VBF_REPLAY_PLAY         = 2,    // ���ڻط�
    VBF_REPLAY_STOP         = 3     // ֹͣ�ط�
};

#endif
