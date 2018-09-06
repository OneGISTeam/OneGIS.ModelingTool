//*******************************************************************
// FileName：  VBF_ImgCoderDataTypes.h
// Function：  图像压缩/解压缩使用的数据类型
// Author:     杜莹
// Date:       2006-5-11
//*******************************************************************

#ifndef __VBF_IMGCODER_DATATYPES_H__
#define __VBF_IMGCODER_DATATYPES_H__

#include <memory.h>
#include <VBF_Macros.h>

#define DDS_FOURCC		0x00000004  // DDPF_FOURCC
#define DDS_RGB			0x00000040  // DDPF_RGB
#define DDS_RGBA		0x00000041  // DDPF_RGB | DDPF_ALPHAPIXELS

#define FOURCC_DXT1		(MAKEFOURCC('D','X','T','1'))
#define FOURCC_DXT2		(MAKEFOURCC('D','X','T','2'))
#define FOURCC_DXT3		(MAKEFOURCC('D','X','T','3'))
#define FOURCC_DXT4		(MAKEFOURCC('D','X','T','4'))
#define FOURCC_DXT5		(MAKEFOURCC('D','X','T','5'))

#define VBF_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0  // GL_COMPRESSED_RGB_S3TC_DXT1_EXT
#define VBF_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1  // GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
#define VBF_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2  // GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
#define VBF_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3  // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT


// 枚举定义图像编码方式(也即压缩方式)
enum VBF_IMGCODETYPE
{
	VBF_IMGCODETYPE_UNKNOWN		= 0,
	VBF_IMGCODETYPE_RGB			= 1,
	VBF_IMGCODETYPE_DDS			= 2,
	VBF_IMGCODETYPE_ECW			= 3,
	VBF_IMGCODETYPE_JPG			= 4,
	VBF_IMGCODETYPE_PNG			= 5,
};

// 与上述编码方式对应的字符串名称(如用于列表框选项)
//static char* gs_szImgCodeTypes[] =
//{
//	"未知格式",
//	"RGB真彩色",
//	"DDS压缩",
//	"ECW压缩",
//	"JPG压缩",
//	"PNG压缩",
//};

//--------------------------------------------------------------------
// 定义结构体：CODEDIMAGE
// 结构体描述：编码后的图像信息(压缩/非压缩)
//--------------------------------------------------------------------
typedef struct _tagCodedImage
{
    int				nNumComponents; // 颜色分量数
    int				nNumMipmaps;    // 级别总数
    unsigned int    format;         // 图像格式
    int				nBitsBytes;     // 图像数据的字节数
    int*			pLevelWidth;    // 每级的宽度
    int*			pLevelHeight;   // 每级的高度
    int*			pLevelBytes;    // 每级的字节数
    BYTE*			pBits;          // 图像数据

    _tagCodedImage()
	{
		nNumComponents = 0; 
        nNumMipmaps    = 0;    
        format         = 0;        
        nBitsBytes     = 0;     
	    pLevelWidth    = NULL;
	    pLevelHeight   = NULL;
	    pLevelBytes    = NULL;
	    pBits          = NULL;
	}

    ~_tagCodedImage()
	{
		if(pLevelWidth)	 { delete pLevelWidth;  pLevelWidth  = NULL; }
		if(pLevelHeight) { delete pLevelHeight; pLevelHeight = NULL; }
		if(pLevelBytes)	 { delete pLevelBytes;  pLevelBytes  = NULL; }
		if(pBits)		 { delete pBits;        pBits        = NULL; }	 
	}

	_tagCodedImage& operator=(_tagCodedImage& img)
	{
		nNumComponents = img.nNumComponents; 
		nNumMipmaps    = img.nNumMipmaps;    
		format         = img.format;         
		nBitsBytes     = img.nBitsBytes;     

		pLevelWidth    = new int[nNumMipmaps];
		pLevelHeight   = new int[nNumMipmaps];
		pLevelBytes    = new int[nNumMipmaps];
		pBits          = new BYTE[nBitsBytes];
		
		memcpy(pLevelWidth,  img.pLevelWidth,  sizeof(int)*nNumMipmaps);
		memcpy(pLevelHeight, img.pLevelHeight, sizeof(int)*nNumMipmaps);
		memcpy(pLevelBytes,  img.pLevelBytes,  sizeof(int)*nNumMipmaps);
		memcpy(pBits, img.pBits, nBitsBytes);

		return *this;
	}

}CODEDIMAGE;


#endif 
