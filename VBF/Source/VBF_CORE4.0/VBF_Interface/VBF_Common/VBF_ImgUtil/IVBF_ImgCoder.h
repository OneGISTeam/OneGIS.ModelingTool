//*******************************************************************
// FileName：  IVBF_ImgCoder.h
// Function：  图像压缩/解压缩
// Author:     杜莹
// Date:       2006-3-28
//*******************************************************************

#ifndef __IVBF_IMGCODER_H__
#define __IVBF_IMGCODER_H__

#include "VBF_Macros.h"
#include "VBF_ImgCoderDataTypes.h"
#include "VBF_ImgUtilExport.h"


// 定义压缩后图像的采样方法
#define VBF_IMGFILTER_POINT			0x10000000L		// 点采样
#define VBF_IMGFILTER_LINEAR		0x20000000L		// 线性采样
#define VBF_IMGFILTER_BILINEAR		0x40000000L		// 点采样



//--------------------------------------------------------------------
// 定义接口：IVBF_ImgCoder
// 接口描述：图像编码器(压缩/解压缩)
//--------------------------------------------------------------------
class IVBF_ImgCoder
{
public:	
	virtual ~IVBF_ImgCoder() {}

	virtual VBF_IMGCODETYPE GetCodeType()=0;

	// 压缩/解压缩
	virtual bool Compress(int nImgSizeX, int nImgSizeY, BYTE* lpBuf, DWORD dwCompressedFormat, bool bMipmap, int& nCompressedSize, BYTE*& lpCompressedBuf)=0;
	virtual bool DeCompress(BYTE* lpCompressedBuf, int nCompressedSize, int& nImgSizeX, int& nImgSizeY, BYTE*& lpDecompressedBuf, int& nDecompressedSize)=0;

	// 获图图像信息
	virtual bool GetCompressedMipmapLevels(BYTE* lpCompressedBuf, int nCompressedSize, int& nMipmapLevels)=0;
};

// 全局函数: 创建/释放图像编码器
VBF_IMGUTIL_EXPORT IVBF_ImgCoder*  VBF_CreateImgCoder(VBF_IMGCODETYPE nCodeType);
VBF_IMGUTIL_EXPORT void            VBF_ReleaseImgCoder(IVBF_ImgCoder*& pICoder);

// 图像缩放
VBF_IMGUTIL_EXPORT bool VBF_BmpScale(BYTE* pBmpRGBSrc, int nBmpWidthSrc, int nBmpHeightSrc, int nBitCountSrc, BYTE* pBmpRGBDst, int nBmpWidthDst, int nBmpHeightDst);

// 全局函数: 图像是否支持Alpha通道
VBF_IMGUTIL_EXPORT bool VBF_IsAlphaSupported(VBF_IMGCODETYPE nCodeType);

#endif 
