#ifndef __IVBF_TOPO_JUDER_H__
#define __IVBF_TOPO_JUDER_H__

#include <VBF_Macros.h>
#include <VBF_OS.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>


// �궨�壺��������
#define VBF_TOPO_OCEAN		0	// ����
#define VBF_TOPO_LAND		1	// ½��
#define VBF_TOPO_MIXED		2	// ��½�ӱ�
#define VBF_TOPO_UNKNOWN	3	// δ֪


// ����ĳ��ľ�γ�ȣ���ȡ��������ͣ�����ֵΪVBF_TOPO_OCEAN��VBF_TOPO_LAND��VBF_TOPO_UNKNOWN
VBF_MAPAUX_EXPORT int VBF_GetPointTopoType(IVBF_3DMainCtrl* pI3DMainCtrl, double L, double B);


#endif

