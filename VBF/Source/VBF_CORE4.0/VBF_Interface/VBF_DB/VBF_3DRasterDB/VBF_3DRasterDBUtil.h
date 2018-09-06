//*******************************************************************
// FileName：  VBF_3DRasterDBUtil.h
// Function：  3D栅格数据库通用工具
// Author:     杜莹
// Date:       2011-07-11
//*******************************************************************

#ifndef __VBF_3DRASTERDB_UTIL_H__
#define __VBF_3DRASTERDB_UTIL_H__

#include "VBF_3DRasterDBExport.h"
#include "IVBF_Blk.h"


// 全局函数: 创建指定类型的数据块
VBF_3DRASTERDB_EXPORT IVBF_Blk* VBF_CreateBlk(VBF_BLK_TYPE nBlkType);

// 全局函数: 从低级Dem块获取数据(说明：目前暂用双线性内插法)
VBF_3DRASTERDB_EXPORT float VBF_DemBiLinearInsert(IVBF_BlkDem* pIBlk, double dU, double dV);

// 全局函数: 从低级块构建高级块
VBF_3DRASTERDB_EXPORT bool  VBF_BlkFromLower(IVBF_Blk* pIBlk, IVBF_Blk* pIBlkLower);

// 全局函数: 块合并
VBF_3DRASTERDB_EXPORT bool  VBF_BlkCombine(IVBF_Blk* pIBlkSrc1, IVBF_Blk* pIBlkSrc2, IVBF_Blk*& pIBlkDst);

// 全局函数: 从块中裁剪出部分数据，并生成同级新块
// 参数说明: dBlk01X0, dBlk01Y0, dBlk01X1, dBlk01Y1 -- 目标数据在原始块中的相对位置，值阈为[0,1]
VBF_3DRASTERDB_EXPORT IVBF_Blk* VBF_BlkClip(IVBF_Blk* pIBlkSrc, double dBlk01X0, double dBlk01Y0, double dBlk01X1, double dBlk01Y1);

// 全局函数: 紧缩文件
VBF_3DRASTERDB_EXPORT bool	VBF_PackBlkFile(const char* szBlkFn);

// 全局函数: 根据RGB数据和掩码图，生成对应的RGBA数据
VBF_3DRASTERDB_EXPORT bool	VBF_RGBMaskToRGBA(int nImgSizeX, int nImgSizeY, BYTE* pBufRGB, BYTE* pBufMask, BYTE*& pBufRGBA, int& nSizeRGBA);
VBF_3DRASTERDB_EXPORT bool	VBF_RGBAToRGBMask(int nImgSizeX, int nImgSizeY, BYTE* pBufRGBA, BYTE*& pBufRGB, int& nSizeRGB, bool bCreateMsk, BYTE*& pBufMask, int& nSizeMask);

#endif 
