//*******************************************************************
// FileName��  VBF_3DRasterDBUtil.h
// Function��  3Dդ�����ݿ�ͨ�ù���
// Author:     ��Ө
// Date:       2011-07-11
//*******************************************************************

#ifndef __VBF_3DRASTERDB_UTIL_H__
#define __VBF_3DRASTERDB_UTIL_H__

#include "VBF_3DRasterDBExport.h"
#include "IVBF_Blk.h"


// ȫ�ֺ���: ����ָ�����͵����ݿ�
VBF_3DRASTERDB_EXPORT IVBF_Blk* VBF_CreateBlk(VBF_BLK_TYPE nBlkType);

// ȫ�ֺ���: �ӵͼ�Dem���ȡ����(˵����Ŀǰ����˫�����ڲ巨)
VBF_3DRASTERDB_EXPORT float VBF_DemBiLinearInsert(IVBF_BlkDem* pIBlk, double dU, double dV);

// ȫ�ֺ���: �ӵͼ��鹹���߼���
VBF_3DRASTERDB_EXPORT bool  VBF_BlkFromLower(IVBF_Blk* pIBlk, IVBF_Blk* pIBlkLower);

// ȫ�ֺ���: ��ϲ�
VBF_3DRASTERDB_EXPORT bool  VBF_BlkCombine(IVBF_Blk* pIBlkSrc1, IVBF_Blk* pIBlkSrc2, IVBF_Blk*& pIBlkDst);

// ȫ�ֺ���: �ӿ��вü����������ݣ�������ͬ���¿�
// ����˵��: dBlk01X0, dBlk01Y0, dBlk01X1, dBlk01Y1 -- Ŀ��������ԭʼ���е����λ�ã�ֵ��Ϊ[0,1]
VBF_3DRASTERDB_EXPORT IVBF_Blk* VBF_BlkClip(IVBF_Blk* pIBlkSrc, double dBlk01X0, double dBlk01Y0, double dBlk01X1, double dBlk01Y1);

// ȫ�ֺ���: �����ļ�
VBF_3DRASTERDB_EXPORT bool	VBF_PackBlkFile(const char* szBlkFn);

// ȫ�ֺ���: ����RGB���ݺ�����ͼ�����ɶ�Ӧ��RGBA����
VBF_3DRASTERDB_EXPORT bool	VBF_RGBMaskToRGBA(int nImgSizeX, int nImgSizeY, BYTE* pBufRGB, BYTE* pBufMask, BYTE*& pBufRGBA, int& nSizeRGBA);
VBF_3DRASTERDB_EXPORT bool	VBF_RGBAToRGBMask(int nImgSizeX, int nImgSizeY, BYTE* pBufRGBA, BYTE*& pBufRGB, int& nSizeRGB, bool bCreateMsk, BYTE*& pBufMask, int& nSizeMask);

#endif 
