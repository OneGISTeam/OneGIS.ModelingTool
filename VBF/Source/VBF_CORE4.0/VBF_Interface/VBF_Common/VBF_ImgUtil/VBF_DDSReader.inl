//************************************************************************
//  �ļ����� VBF_DDSReader.inl
//  ������   ��ȡDDS��ʵ���ļ�
//  ���ߣ�   ��Ө 
//  ʱ�䣺   2005-1-1
//************************************************************************

#ifndef __VBF_DDS_READER_INL__
#define __VBF_DDS_READER_INL__


#include "VBF_Common/VBF_Utils/VBF_MemFile.h"
#include "VBF_OS.h"


#define max(a, b)  (((a) > (b)) ? (a) : (b))


//---------------------------------------------------------------------------------
// ������ReadDDSFileInfo()
// ��������ȡDDS�ļ�����Ϣ
// ���أ�nLevelBytes0 -- ��0�����ݵ��ֽ���
//      nBitsOffset  -- ��0�����ݵ�ƫ�ƣ������pDDSBuf��
//---------------------------------------------------------------------------------
inline bool ReadDDSFileInfo(int nSizeDDS, BYTE* pDDSBuf, int& nDDSFormat, DDSHEADER& ddsHeader,
                            int& nLevelBytes0, int& nBitsOffset0)
{
	// �����ڴ��ļ�
	CVBF_MemFile* pMemFile = new CVBF_MemFile(pDDSBuf, nSizeDDS);

	// ȷ���ļ���ʽ
    unsigned int dwMagic;
    pMemFile->Read( &dwMagic, sizeof(unsigned int), 1 );

	if( dwMagic!=MAKEFOURCC('D','D','S',' ') )	
	{
		pMemFile->Close();
		SAFE_DELETE(pMemFile);
        return false;
	}
   
    // ��ȡ�ļ�ͷ��Ϣ (������������Ϣ)	
	pMemFile->Read( &ddsHeader, sizeof(DDSHEADER), 1 );
	
	// �ж��Ƿ�ѹ����ʽ
    bool bCompressed = false;
	if( ddsHeader.ddpfPixelFormat.dwFlags & DDS_RGB ) // ��ѹ����ʽ(RGB/RGBA)
	{
		bCompressed = false;
		switch(ddsHeader.ddpfPixelFormat.dwRGBBitCount)
		{
			case 24: { nDDSFormat = DDS_RGB;  break; }   // RGB
			case 32: { nDDSFormat = DDS_RGBA; break; }   // RGBA
			default: { return false; }
		}
	} 
	else if(ddsHeader.ddpfPixelFormat.dwFlags & DDS_FOURCC)  // ѹ����ʽ
	{
		bCompressed = true;
		switch(ddsHeader.ddpfPixelFormat.dwFourCC)
		{
			case FOURCC_DXT1: {	nDDSFormat = VBF_COMPRESSED_RGB_S3TC_DXT1_EXT;	break; }
			case FOURCC_DXT3: { nDDSFormat = VBF_COMPRESSED_RGBA_S3TC_DXT3_EXT;	break; }
			case FOURCC_DXT5: { nDDSFormat = VBF_COMPRESSED_RGBA_S3TC_DXT5_EXT;	break; }
			default: 	      { return false; }
		}
	}	

    // ����DDS��С
    // ÿ������Ĵ�С���㹫ʽΪ��(�μ�D3D9������DDS File Layout for Textures)
    // nSizeDDSLevel = max(1, width �� 4) x max(1, height �� 4) x 8(DXT1) or 16(DXT2-5)

    int nLevelWidth  = ddsHeader.dwWidth;
    int nLevelHeight = ddsHeader.dwHeight;
    int nSizeBlk     = (ddsHeader.ddpfPixelFormat.dwFourCC==FOURCC_DXT1) ? 8 : 16;

    if(bCompressed)
        nLevelBytes0 = max(1, nLevelWidth/4) * max(1, nLevelHeight/4) * nSizeBlk;
    else
        nLevelBytes0 = nLevelWidth * nLevelHeight * ddsHeader.ddpfPixelFormat.dwRGBBitCount/8;

    nBitsOffset0 = pMemFile->Tell();

	pMemFile->Close();
	SAFE_DELETE(pMemFile);

	return true;
}


//---------------------------------------------------------------------------------
// ������LoadDDSBuf()
// ���������ڴ�DDS�����л�ȡ��Ϣ
// ˵����DDS�ļ�������ѹ����ʽ�ģ����ѹ����ʽ��
//---------------------------------------------------------------------------------
inline bool LoadDDSBuf(int nSizeDDS, BYTE* pDDSBuf, CODEDIMAGE* pImage)
{
    memset(pImage, 0, sizeof(CODEDIMAGE));

	// �����ڴ��ļ�
	CVBF_MemFile* pMemFile = new CVBF_MemFile(pDDSBuf, nSizeDDS);

	// ȷ���ļ���ʽ
        unsigned int dwMagic;
        pMemFile->Read( &dwMagic, sizeof(unsigned int), 1 );
	if( dwMagic!=MAKEFOURCC('D','D','S',' ') )	
	{
		pMemFile->Close();
		SAFE_DELETE(pMemFile);
        return false;
	}
   
    // ��ȡ�ļ�ͷ��Ϣ (������������Ϣ)	
	DDSHEADER ddsHeader; 
	pMemFile->Read( &ddsHeader, sizeof(DDSHEADER), 1 );
	
	// �ж��Ƿ�ѹ����ʽ
    bool bCompressed = false;
	if( ddsHeader.ddpfPixelFormat.dwFlags & DDS_RGB ) // ��ѹ����ʽ(RGB/RGBA)
	{
		bCompressed = false;
		switch(ddsHeader.ddpfPixelFormat.dwRGBBitCount)
		{
			case 24: { pImage->format = DDS_RGB;  break; }   // RGB
			case 32: { pImage->format = DDS_RGBA; break; }   // RGBA
			default: { return false; }
		}
	} 
	else if(ddsHeader.ddpfPixelFormat.dwFlags & DDS_FOURCC)  // ѹ����ʽ
	{
		bCompressed = true;
		switch(ddsHeader.ddpfPixelFormat.dwFourCC)
		{
			case FOURCC_DXT1: {	pImage->format = VBF_COMPRESSED_RGB_S3TC_DXT1_EXT; break; }
			case FOURCC_DXT3: { pImage->format = VBF_COMPRESSED_RGBA_S3TC_DXT3_EXT;	break; }
			case FOURCC_DXT5: { pImage->format = VBF_COMPRESSED_RGBA_S3TC_DXT5_EXT;	break; }
			default: 	      { return false; }
		}
	}		
    
	// ��Ө�޸ģ�2004-12-29
	// ����DDS��С
	// ÿ������Ĵ�С���㹫ʽΪ��(�μ�D3D9������DDS File Layout for Textures)
	// nSizeDDSLevel = max(1, width �� 4) x max(1, height �� 4) x 8(DXT1) or 16(DXT2-5)
	
	int nSizeBlk = (ddsHeader.ddpfPixelFormat.dwFourCC==FOURCC_DXT1) ? 8 : 16;
	int nLevelWidth  = ddsHeader.dwWidth;
	int nLevelHeight = ddsHeader.dwHeight;

    pImage->nNumComponents = (ddsHeader.ddpfPixelFormat.dwFourCC==FOURCC_DXT1)? 3 : 4;
	pImage->nNumMipmaps    = ddsHeader.dwMipMapCount;
	if(pImage->nNumMipmaps==0) 
	{	
		pImage->nNumMipmaps = 1;
	}
	pImage->pLevelWidth    = new int[pImage->nNumMipmaps];
	pImage->pLevelHeight   = new int[pImage->nNumMipmaps];
	pImage->pLevelBytes    = new int[pImage->nNumMipmaps];

	pImage->nBitsBytes = 0;

        for(unsigned int i=0; i<(unsigned int)pImage->nNumMipmaps; i++)
	{
	    if(bCompressed)
			pImage->pLevelBytes[i] = max(1,nLevelWidth/4) * max(1,nLevelHeight/4) * nSizeBlk;
		else 
			pImage->pLevelBytes[i] = nLevelWidth * nLevelHeight * ddsHeader.ddpfPixelFormat.dwRGBBitCount/8;  
		
		pImage->nBitsBytes += pImage->pLevelBytes[i];
		pImage->pLevelWidth[i]  = nLevelWidth;
		pImage->pLevelHeight[i] = nLevelHeight;	
		
		nLevelWidth  >>= 1;
		nLevelHeight >>= 1;		
	}	

	pImage->pBits = new BYTE[pImage->nBitsBytes];
	pMemFile->Read( pImage->pBits, pImage->nBitsBytes, 1 );       

	pMemFile->Close();
	SAFE_DELETE(pMemFile);

	return true;
}


//---------------------------------------------------------------------------------
// ������ReadDDSFileInMemory()
// ��������ȡDDS�ļ�
//---------------------------------------------------------------------------------
inline bool ReadDDSFileInMemory(BYTE* pDDSBuf, int nSizeDDS, CODEDIMAGE* pImage)
{
	return ::LoadDDSBuf(nSizeDDS, pDDSBuf, pImage);
}

#endif
