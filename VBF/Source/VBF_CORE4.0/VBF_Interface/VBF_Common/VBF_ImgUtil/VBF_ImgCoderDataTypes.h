//*******************************************************************
// FileName��  VBF_ImgCoderDataTypes.h
// Function��  ͼ��ѹ��/��ѹ��ʹ�õ���������
// Author:     ��Ө
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


// ö�ٶ���ͼ����뷽ʽ(Ҳ��ѹ����ʽ)
enum VBF_IMGCODETYPE
{
	VBF_IMGCODETYPE_UNKNOWN		= 0,
	VBF_IMGCODETYPE_RGB			= 1,
	VBF_IMGCODETYPE_DDS			= 2,
	VBF_IMGCODETYPE_ECW			= 3,
	VBF_IMGCODETYPE_JPG			= 4,
	VBF_IMGCODETYPE_PNG			= 5,
};

// ���������뷽ʽ��Ӧ���ַ�������(�������б��ѡ��)
//static char* gs_szImgCodeTypes[] =
//{
//	"δ֪��ʽ",
//	"RGB���ɫ",
//	"DDSѹ��",
//	"ECWѹ��",
//	"JPGѹ��",
//	"PNGѹ��",
//};

//--------------------------------------------------------------------
// ����ṹ�壺CODEDIMAGE
// �ṹ��������������ͼ����Ϣ(ѹ��/��ѹ��)
//--------------------------------------------------------------------
typedef struct _tagCodedImage
{
    int				nNumComponents; // ��ɫ������
    int				nNumMipmaps;    // ��������
    unsigned int    format;         // ͼ���ʽ
    int				nBitsBytes;     // ͼ�����ݵ��ֽ���
    int*			pLevelWidth;    // ÿ���Ŀ��
    int*			pLevelHeight;   // ÿ���ĸ߶�
    int*			pLevelBytes;    // ÿ�����ֽ���
    BYTE*			pBits;          // ͼ������

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
