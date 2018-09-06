#ifndef __IVBF_TOPO_JUDER_H__
#define __IVBF_TOPO_JUDER_H__

#include <VBF_Macros.h>
#include <VBF_OS.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>


// 宏定义：地形类型
#define VBF_TOPO_OCEAN		0	// 海洋
#define VBF_TOPO_LAND		1	// 陆地
#define VBF_TOPO_MIXED		2	// 海陆接边
#define VBF_TOPO_UNKNOWN	3	// 未知


// 根据某点的经纬度，获取其地形类型，返回值为VBF_TOPO_OCEAN、VBF_TOPO_LAND或VBF_TOPO_UNKNOWN
VBF_MAPAUX_EXPORT int VBF_GetPointTopoType(IVBF_3DMainCtrl* pI3DMainCtrl, double L, double B);


#endif

