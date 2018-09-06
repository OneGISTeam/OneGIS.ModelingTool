//*******************************************************************
// FileName：  VBF_3DTransBlkDataTypes.h
// Function：  3D交换数据模型使用的公共数据类型
// Author:     杜莹
// Date:       2011-07-23
//*******************************************************************

#ifndef __VBF_3DTRANS_BLK_DADA_TYPES_H__
#define __VBF_3DTRANS_BLK_DADA_TYPES_H__


//--------------------------------------------------------------------
// 定义枚举：VBF_BLK_TYPE
// 枚举描述：数据块的类型
//--------------------------------------------------------------------
enum VBF_BLK_TYPE
{
	VBF_BLK_UNKNOWN	= 0,	// 未知类型
	VBF_BLK_DEM		= 1,	// Dem数据块
	VBF_BLK_TEX		= 2,	// 纹理数据块
	VBF_BLK_NOTE	= 3,	// 注记数据块
	VBF_BLK_TYPE_COUNT		// 数据块类型总数
};


#endif