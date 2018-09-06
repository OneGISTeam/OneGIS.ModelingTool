//*******************************************************************
// FileName��  IVBF_ImgCoder.h
// Function��  ͼ��ѹ��/��ѹ��
// Author:     ��Ө
// Date:       2006-3-28
//*******************************************************************

#ifndef __IVBF_IMGCODER_H__
#define __IVBF_IMGCODER_H__

#include "VBF_Macros.h"
#include "VBF_ImgCoderDataTypes.h"
#include "VBF_ImgUtilExport.h"


// ����ѹ����ͼ��Ĳ�������
#define VBF_IMGFILTER_POINT			0x10000000L		// �����
#define VBF_IMGFILTER_LINEAR		0x20000000L		// ���Բ���
#define VBF_IMGFILTER_BILINEAR		0x40000000L		// �����



//--------------------------------------------------------------------
// ����ӿڣ�IVBF_ImgCoder
// �ӿ�������ͼ�������(ѹ��/��ѹ��)
//--------------------------------------------------------------------
class IVBF_ImgCoder
{
public:	
	virtual ~IVBF_ImgCoder() {}

	virtual VBF_IMGCODETYPE GetCodeType()=0;

	// ѹ��/��ѹ��
	virtual bool Compress(int nImgSizeX, int nImgSizeY, BYTE* lpBuf, DWORD dwCompressedFormat, bool bMipmap, int& nCompressedSize, BYTE*& lpCompressedBuf)=0;
	virtual bool DeCompress(BYTE* lpCompressedBuf, int nCompressedSize, int& nImgSizeX, int& nImgSizeY, BYTE*& lpDecompressedBuf, int& nDecompressedSize)=0;

	// ��ͼͼ����Ϣ
	virtual bool GetCompressedMipmapLevels(BYTE* lpCompressedBuf, int nCompressedSize, int& nMipmapLevels)=0;
};

// ȫ�ֺ���: ����/�ͷ�ͼ�������
VBF_IMGUTIL_EXPORT IVBF_ImgCoder*  VBF_CreateImgCoder(VBF_IMGCODETYPE nCodeType);
VBF_IMGUTIL_EXPORT void            VBF_ReleaseImgCoder(IVBF_ImgCoder*& pICoder);

// ͼ������
VBF_IMGUTIL_EXPORT bool VBF_BmpScale(BYTE* pBmpRGBSrc, int nBmpWidthSrc, int nBmpHeightSrc, int nBitCountSrc, BYTE* pBmpRGBDst, int nBmpWidthDst, int nBmpHeightDst);

// ȫ�ֺ���: ͼ���Ƿ�֧��Alphaͨ��
VBF_IMGUTIL_EXPORT bool VBF_IsAlphaSupported(VBF_IMGCODETYPE nCodeType);

#endif 
