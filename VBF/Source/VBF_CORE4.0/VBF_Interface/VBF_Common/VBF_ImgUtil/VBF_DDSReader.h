//************************************************************************
//  文件名： VBF_DDSReader.h
//  描述：   读取DDS文件
//  作者：   杜莹 
//  时间：   2004-12-28

// This header defines constants and structures that are useful when parsing 
// DDS files.  DDS files were originally designed to use several structures
// and constants that are native to DirectDraw and are defined in ddraw.h,
// such as DDSURFACEDESC2 and DDSCAPS2.  This file defines similar 
// (compatible) constants and structures so that one can use DDS files 
// without needing to include <ddraw.h>.
//************************************************************************

#ifndef __VBF_DDS_READER_H__
#define __VBF_DDS_READER_H__

#include "VBF_Common/VBF_ImgUtil/VBF_ImgCoderDataTypes.h"
#include "VBF_STL.h"

//-------------------------------------------------------------
// 定义结构体：DDSPIXELFORMAT
// 结构体描述：DDS像素格式
//-------------------------------------------------------------
typedef struct _tagDDSPixelFormat
{
    unsigned int   dwSize;
    unsigned int   dwFlags;
    unsigned int   dwFourCC;
    unsigned int   dwRGBBitCount;
    unsigned int   dwRBitMask;
    unsigned int   dwGBitMask;
    unsigned int   dwBBitMask;
    unsigned int   dwABitMask;
}DDSPIXELFORMAT;

const DDSPIXELFORMAT DDSPF_DXT1 =
    { sizeof(DDSPIXELFORMAT), DDS_FOURCC, MAKEFOURCC('D','X','T','1'), 0, 0, 0, 0, 0 };

const DDSPIXELFORMAT DDSPF_DXT2 =
    { sizeof(DDSPIXELFORMAT), DDS_FOURCC, MAKEFOURCC('D','X','T','2'), 0, 0, 0, 0, 0 };

const DDSPIXELFORMAT DDSPF_DXT3 =
    { sizeof(DDSPIXELFORMAT), DDS_FOURCC, MAKEFOURCC('D','X','T','3'), 0, 0, 0, 0, 0 };

const DDSPIXELFORMAT DDSPF_DXT4 =
    { sizeof(DDSPIXELFORMAT), DDS_FOURCC, MAKEFOURCC('D','X','T','4'), 0, 0, 0, 0, 0 };

const DDSPIXELFORMAT DDSPF_DXT5 =
    { sizeof(DDSPIXELFORMAT), DDS_FOURCC, MAKEFOURCC('D','X','T','5'), 0, 0, 0, 0, 0 };

const DDSPIXELFORMAT DDSPF_A8R8G8B8 =
    { sizeof(DDSPIXELFORMAT), DDS_RGBA, 0, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000 };

const DDSPIXELFORMAT DDSPF_A1R5G5B5 =
    { sizeof(DDSPIXELFORMAT), DDS_RGBA, 0, 16, 0x00007c00, 0x000003e0, 0x0000001f, 0x00008000 };

const DDSPIXELFORMAT DDSPF_A4R4G4B4 =
    { sizeof(DDSPIXELFORMAT), DDS_RGBA, 0, 16, 0x00000f00, 0x000000f0, 0x0000000f, 0x0000f000 };

const DDSPIXELFORMAT DDSPF_R8G8B8 =
    { sizeof(DDSPIXELFORMAT), DDS_RGB, 0, 24, 0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000 };

const DDSPIXELFORMAT DDSPF_R5G6B5 =
    { sizeof(DDSPIXELFORMAT), DDS_RGB, 0, 16, 0x0000f800, 0x000007e0, 0x0000001f, 0x00000000 };

#define DDS_HEADER_FLAGS_TEXTURE    0x00001007  // DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT 
#define DDS_HEADER_FLAGS_MIPMAP     0x00020000  // DDSD_MIPMAPCOUNT
#define DDS_HEADER_FLAGS_VOLUME     0x00800000  // DDSD_DEPTH
#define DDS_HEADER_FLAGS_PITCH      0x00000008  // DDSD_PITCH
#define DDS_HEADER_FLAGS_LINEARSIZE 0x00080000  // DDSD_LINEARSIZE

#define DDS_SURFACE_FLAGS_TEXTURE   0x00001000 // DDSCAPS_TEXTURE
#define DDS_SURFACE_FLAGS_MIPMAP    0x00400008 // DDSCAPS_COMPLEX | DDSCAPS_MIPMAP
#define DDS_SURFACE_FLAGS_CUBEMAP   0x00000008 // DDSCAPS_COMPLEX

#define DDS_CUBEMAP_POSITIVEX 0x00000600 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEX
#define DDS_CUBEMAP_NEGATIVEX 0x00000a00 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEX
#define DDS_CUBEMAP_POSITIVEY 0x00001200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEY
#define DDS_CUBEMAP_NEGATIVEY 0x00002200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEY
#define DDS_CUBEMAP_POSITIVEZ 0x00004200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEZ
#define DDS_CUBEMAP_NEGATIVEZ 0x00008200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEZ

#define DDS_CUBEMAP_ALLFACES ( DDS_CUBEMAP_POSITIVEX | DDS_CUBEMAP_NEGATIVEX |\
                               DDS_CUBEMAP_POSITIVEY | DDS_CUBEMAP_NEGATIVEY |\
                               DDS_CUBEMAP_POSITIVEZ | DDS_CUBEMAP_NEGATIVEZ )

#define DDS_FLAGS_VOLUME 0x00200000 // DDSCAPS2_VOLUME

//-------------------------------------------------------------
// 定义结构体：DDSHEADER
// 结构体描述：DDS头信息
//-------------------------------------------------------------
typedef struct _tagDDSHeader 
{
    unsigned int             dwSize;
    unsigned int             dwFlags;
    unsigned int             dwHeight;
    unsigned int             dwWidth;
    unsigned int             dwPitchOrLinearSize;
    unsigned int             dwDepth;   // only if DDS_HEADER_FLAGS_VOLUME is set in dwHeaderFlags
    unsigned int             dwMipMapCount;
    unsigned int             dwReserved1[11];
	DDSPIXELFORMAT    ddpfPixelFormat;	
    unsigned int             dwSurfaceFlags;
    unsigned int             dwCubemapFlags;
    unsigned int             dwReserved2[3];
}DDSHEADER;


// 全局函数：
bool	ReadDDSFileInMemory(BYTE* pDDSBuf, int nSizeDDS, CODEDIMAGE* pImage);
bool	LoadDDSBuf(int nSizeDDS, BYTE* pDDSBuf, CODEDIMAGE* pImage);
bool	ReadDDSFileInfo(int nSizeDDS, BYTE* pDDSBuf, int& nDDSFormat, DDSHEADER& ddsHeader, int& nLevelBytes0, int& nBitsOffset0);

#include "VBF_DDSReader.inl"

#endif
