//*******************************************************************
// FileName：  VBF_DemTexDataType.h
// Function：  Dem和纹理使用的公共数据类型
// Author:     杜莹
// Date:       2004-10-20
// Note:       
//*******************************************************************

#ifndef __VBF_DEM_TEX_DATATYPE_H__
#define __VBF_DEM_TEX_DATATYPE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "float.h"
#include "Types/VBF_Vector.h"
#include <VBF_OS.h>

//#ifdef VBF_OS_LINUX
    //zj DTIS 中涉及文件的读取所以需要保持BOOL类型linux下与windows下内存大小一致
    //linux 下定义BOOL为unsigned char
    typedef unsigned int        BOOL;
//#endif


// 定义文件后缀
#define EXT_DEMFILE				"demx"     // Dem文件后缀
#define EXT_TEXFILE				"texx"     // 纹理文件后缀
#define EXT_NOTEFILE			"notx"     // 注记文件后缀

// 定义不完整块中缺失数据的临时填充值
#define NULLDATA_DEM			-99999.0                // Dem块中的临时填充值

// 全局函数，判断高程点是否有效
// 函数说明：无效点在地形块中的记录值为NULLDATA_DEM
static bool IsHeightValid(float fH) { return (fH > NULLDATA_DEM+1); } // 该算法比fabs()算法快 

// 定义地形块的编码长度
#define BLKKEY_LENGTH		16

// 定义无效的地形块编码值
#define ENCODE_BLKKEY(nLodNo, nBlkNoX, nBlkNoY)		( (UINT64)(((UINT64)nLodNo)<<59) + (UINT64)(((UINT64)nBlkNoX)<<30) + (UINT64)nBlkNoY )
#define INVALID_BLKKEY								( ENCODE_BLKKEY(0,1,1) )    // 即不可能存在 (nLod=0, nBlkNoX=1, nBlkNoY=1) 的地形块

//-----------------------------------------------------------
// 定义枚举：VBF_BLK_EDGE
// 枚举描述：列举块的4条边
//-----------------------------------------------------------
enum VBF_BLK_EDGE
{
	VBF_BLK_EDGE_TOP      = 0,
	VBF_BLK_EDGE_RIGHT    = 1,
	VBF_BLK_EDGE_BOTTOM   = 2,
	VBF_BLK_EDGE_LEFT     = 3
};

// 设置结构体对齐方式：4字节对齐
#include <pshpack4.h>

//-------------------------------------------------------------------
// 定义结构体：VBF_DEMTEXPERSISTHEADER
// 结构体描述：DemTex文件头
//-------------------------------------------------------------------
typedef struct _tagVBFDemTexPersistHeader
{
	unsigned int  dwVersionNo;      // 数据版本号
	int           nBlkNumX;			// X方向上的块数
	int           nBlkNumY;			// Y方向上的块数
	int           nReserved[2];		// 保留字节

	_tagVBFDemTexPersistHeader()
	{
		dwVersionNo   = 1;
		nBlkNumX      = 0;           // X方向上的块数
		nBlkNumY      = 0;           // Y方向上的块数

		for(int i=0; i<_countof(nReserved); i++) 
		{
			nReserved[i] = 0;
		}	
	}

	bool operator==(const _tagVBFDemTexPersistHeader& header)
	{
		return (dwVersionNo==header.dwVersionNo && nBlkNumX==header.nBlkNumX && 
			    nBlkNumY==header.nBlkNumY);
	}

}VBF_DEMTEXPERSISTHEADER;


//-------------------------------------------------------------------
// 定义结构体：VBF_DEMTEXPERSISTBLKINF
// 结构体描述：DemTex文件中每个block的信息
//-------------------------------------------------------------------
typedef struct _tagVBFDemTexPersistBlkInf
{
	unsigned int    nPos;          // 块在文件中的起始位置（杜莹修改为unsigned int，以便使文件字节数能大于2G）
	int				nLength;       // 块在文件中的长度(单位：字节)	
	int				nReserved[2];  // 保留字节

	_tagVBFDemTexPersistBlkInf()
	{
		nPos     = 0; 
		nLength  = 0; 	

		for(int i=0; i<_countof(nReserved); i++) 
		{
			nReserved[i] = 0;
		}
	}

	_tagVBFDemTexPersistBlkInf& operator=(const _tagVBFDemTexPersistBlkInf src)
	{
		this->nPos    = src.nPos;
		this->nLength = src.nLength;

		for(int i=0; i<_countof(nReserved); i++) 
		{
			this->nReserved[i] = src.nReserved[i];
		}

		return *this;
	}
}VBF_DEMTEXPERSISTBLKINF;


//-------------------------------------------------------------------
// 定义结构体：VBF_DEMTEXENGINECONFIGPAR
// 结构体描述：DEM和纹理引擎的配置参数
//-------------------------------------------------------------------
typedef struct _tagVBFDemTexEngineConfigPar
{
	// 从数据区的左上边界开始分块,左上边界块号为00

	// 数据区域总的坐标范围
	double   dGlobalX0;
	double   dGlobalX1;
	double   dGlobalY0;
	double   dGlobalY1;

	// 共存在多少个根节点
	int      nRootBlkNumX;
	int		 nRootBlkNumY;

	// LOD层次数
	int		 nLodCount;

	// 每一块DEM的大小（网格数）
	int		 nDemBlkSizeX;
	int		 nDemBlkSizeY;

	// 每一块纹理的大小（像素数）
	int		 nTexBlkSizeX;
	int		 nTexBlkSizeY;

	// 每个文件保存的块数, 实际可能比该值小
	int		 nPerFileBlkNumX;
	int		 nPerFileBlkNumY;

	// 注意：定义缺省的构造函数
	_tagVBFDemTexEngineConfigPar()
	{
		nLodCount        = 25;

		dGlobalX0		 = -180.0;
		dGlobalX1		 = +180.0;
		dGlobalY0		 = -90.0;
		dGlobalY1        = +90.0;

		nRootBlkNumX     = 2;
		nRootBlkNumY     = 1;

		nTexBlkSizeX     = 256;
		nTexBlkSizeY     = 256;

		nDemBlkSizeX     = 17;
		nDemBlkSizeY     = 17;

		nPerFileBlkNumX  = 100;
		nPerFileBlkNumY  = 100;
	}

	// 串行化：写 (配置文件格式, .ini)
	bool Write(const char* szFile)
	{
		/*char szSectionName[] = "ConfigPar";
		
		char  szKey[32]   = {'\0'};
		char  szValue[32] = {'\0'};
		
		for(int i=0; i<13; i++)
		{
			switch(i)
			{
				case 0:		{ strcpy(szKey, "nLodCount");			itoa(nLodCount, szValue, 10);			break; }
				case 1:		{ strcpy(szKey, "dGlobalX0");			_gcvt(dGlobalX0, 11, szValue);			break; }
				case 2:		{ strcpy(szKey, "dGlobalX1");			_gcvt(dGlobalX1, 11, szValue);			break; }
				case 3:		{ strcpy(szKey, "dGlobalY0");			_gcvt(dGlobalY0, 11, szValue);			break; }
				case 4:		{ strcpy(szKey, "dGlobalY1");			_gcvt(dGlobalY1, 11, szValue);			break; }
				case 5:		{ strcpy(szKey, "nRootBlkNumX");		itoa(nRootBlkNumX, szValue, 10);		break; }
				case 6:		{ strcpy(szKey, "nRootBlkNumY");		itoa(nRootBlkNumY, szValue, 10);		break; }
				case 7:		{ strcpy(szKey, "nTexBlkSizeX");		itoa(nTexBlkSizeX, szValue, 10);		break; }
				case 8:		{ strcpy(szKey, "nTexBlkSizeY");		itoa(nTexBlkSizeY, szValue, 10);		break; }
				case 9:		{ strcpy(szKey, "nDemBlkSizeX");		itoa(nDemBlkSizeX, szValue, 10);		break; }
				case 10:	{ strcpy(szKey, "nDemBlkSizeY");		itoa(nDemBlkSizeY, szValue, 10);		break; }
				case 11:	{ strcpy(szKey, "nPerFileBlkNumX");		itoa(nPerFileBlkNumX, szValue, 10);		break; }
				case 12:	{ strcpy(szKey, "nPerFileBlkNumY");		itoa(nPerFileBlkNumY, szValue, 10);		break; }
				default:    { break; }
			}

			bool bSuc = (::WritePrivateProfileString((LPCSTR)szSectionName, (LPCSTR)szKey, (LPCSTR)szValue, (LPCSTR)szFile)==1);
			if(!bSuc) return false;
		}*/
		
		return true;
	}

	// 串行化：读 (配置文件格式, .ini)
	bool Read(const char* szFile)
	{
		/*char szSectionName[] = "ConfigPar";

		char szBuffer[MAX_PATH];		

		nLodCount = ::GetPrivateProfileInt((LPCSTR)szSectionName, (LPCSTR)"nLodCount", 21, (LPCSTR)szFile);

		::GetPrivateProfileString((LPCSTR)szSectionName, (LPCSTR)"dGlobalX0", (LPCSTR)"-180.0", (LPSTR)szBuffer, sizeof(szBuffer), (LPCSTR)szFile);
		dGlobalX0 = atof(szBuffer);

		::GetPrivateProfileString((LPCSTR)szSectionName, (LPCSTR)"dGlobalX1", (LPCSTR)"+180.0", (LPSTR)szBuffer, sizeof(szBuffer), (LPCSTR)szFile);
		dGlobalX1 = atof(szBuffer);

		::GetPrivateProfileString((LPCSTR)szSectionName, (LPCSTR)"dGlobalY0", (LPCSTR)"-90.0", (LPSTR)szBuffer, sizeof(szBuffer), (LPCSTR)szFile);
		dGlobalY0 = atof(szBuffer);

		GetPrivateProfileString((LPCSTR)szSectionName, (LPCSTR)"dGlobalY1", (LPCSTR)"+90.0", (LPSTR)szBuffer, sizeof(szBuffer), (LPCSTR)szFile);
		dGlobalY1 = atof(szBuffer);

		nRootBlkNumX    = ::GetPrivateProfileInt((LPCSTR)szSectionName, (LPCSTR)"nRootBlkNumX",    2,   (LPCSTR)szFile);
		nRootBlkNumY    = ::GetPrivateProfileInt((LPCSTR)szSectionName, (LPCSTR)"nRootBlkNumY",    1,   (LPCSTR)szFile);
		nTexBlkSizeX    = ::GetPrivateProfileInt((LPCSTR)szSectionName, (LPCSTR)"nTexBlkSizeX",    256, (LPCSTR)szFile);
		nTexBlkSizeY    = ::GetPrivateProfileInt((LPCSTR)szSectionName, (LPCSTR)"nTexBlkSizeY",    256, (LPCSTR)szFile);
		nDemBlkSizeX    = ::GetPrivateProfileInt((LPCSTR)szSectionName, (LPCSTR)"nDemBlkSizeX",    17,  (LPCSTR)szFile);
		nDemBlkSizeY    = ::GetPrivateProfileInt((LPCSTR)szSectionName, (LPCSTR)"nDemBlkSizeY",    17,  (LPCSTR)szFile);
		nPerFileBlkNumX = ::GetPrivateProfileInt((LPCSTR)szSectionName, (LPCSTR)"nPerFileBlkNumX", 100, (LPCSTR)szFile);
		nPerFileBlkNumY = ::GetPrivateProfileInt((LPCSTR)szSectionName, (LPCSTR)"nPerFileBlkNumY", 100, (LPCSTR)szFile);
		*/
		return true;
	}

} VBF_DEMTEXENGINECONFIGPAR;


// 注意：取消字节对齐的设置
#include <poppack.h>    

// 与注记有关的最大值设置
#define MAX_NOTECHARS         32      // 每个注记中的最大字符个数
#define MAX_NOTERANK          10       // 注记的最大行政级别

// 设置结构体对齐方式：1字节对齐
#include <pshpack1.h>
//-------------------------------------------------------------------
// 定义结构体：VBF_NOTEDATA
// 结构体描述：注记数据结构
//-------------------------------------------------------------------
typedef struct _tagVBFNoteData
{
	char         szText[MAX_NOTECHARS];    // 注记字符串
	int          nRank;                    // 行政级别(值越大，级别越高)
	int          nStyleNo;                 // 注记样式码	
	int          nNumCoords;               // 注记坐标个数(即定位点个数，不能超过MAX_NOTECHARS)
	VBFVECTOR3D* pCoords;                 // 注记坐标串

	_tagVBFNoteData()  // 构造函数
	{
		memset(szText, '\0', sizeof(char)*MAX_NOTECHARS);
		nRank      = 0;		
		nStyleNo   = 0;
		nNumCoords = 0;
		pCoords    = NULL;
	}

	~_tagVBFNoteData()
	{
		SAFE_DELETE(pCoords);
	}	

	// 重载赋值操作符
	_tagVBFNoteData& operator=(const _tagVBFNoteData& NoteData)
	{
                VBF_strcpy(szText, NoteData.szText);
		nRank       = NoteData.nRank;
                nStyleNo    = NoteData.nStyleNo;
		nNumCoords  = NoteData.nNumCoords; 

		if(nNumCoords > 0)	// 要求至少有一个定位点
		{
			pCoords = new VBFVECTOR3D[nNumCoords];   
			memcpy(pCoords, NoteData.pCoords, sizeof(VBFVECTOR3D)*nNumCoords);
		}
		
		return *this;
	}

	// 重载==操作符
	bool operator==(const _tagVBFNoteData& NoteData)
	{
		if( strcmp(szText, NoteData.szText)!=0 )     return false;
		else if( nStyleNo!=NoteData.nStyleNo )       return false;
		else if( nRank!=NoteData.nRank )             return false;		
		else if( nNumCoords!=NoteData.nNumCoords )   return false;
		else
		{
			for(int i=0; i<nNumCoords; i++)
			{
				if( pCoords[i]!=NoteData.pCoords[i] ) return false;
			}
		}
		return true;
	}

	// 串行化操作：写文件
	template <class TYPE> 
	bool Write(TYPE* pPersist)
	{
		if(NULL==pPersist) return false;

		pPersist->Write( szText,       sizeof(char)*MAX_NOTECHARS ); 
		pPersist->Write( &nRank,       sizeof(int) );                
		pPersist->Write( &nStyleNo,    sizeof(int) );                
		pPersist->Write( &nNumCoords,  sizeof(int) );                    
		pPersist->Write( pCoords,      sizeof(VBFVECTOR3D)*nNumCoords );

		return true;
	}	

	// 串行化操作：读文件
	template <class TYPE> 
	bool Read(TYPE* pPersist)
	{
		if(NULL==pPersist) return false;

		pPersist->Read( szText,       sizeof(char)*MAX_NOTECHARS ); 
		pPersist->Read( &nRank,       sizeof(int) );                
		pPersist->Read( &nStyleNo,    sizeof(int) );               
		pPersist->Read( &nNumCoords,  sizeof(int) );                
		
		if(nNumCoords > 0)
		{
			pCoords = new VBFVECTOR3D[nNumCoords];
			pPersist->Read( pCoords,  sizeof(VBFVECTOR3D)*nNumCoords );   
		}

		return true;
	}

	// 串行化操作：写文件
	bool Write(FILE* fp)
	{
		if(NULL==fp) return false;

		fwrite( szText,		 sizeof(char)*MAX_NOTECHARS, 1, fp );
		fwrite( &nRank,       sizeof(int), 1, fp );              
		fwrite( &nStyleNo,    sizeof(int), 1, fp );               
		fwrite( &nNumCoords,  sizeof(int), 1, fp );                  
		fwrite( pCoords,      sizeof(VBFVECTOR3D)*nNumCoords, 1, fp );

		return true;
	}

	// 串行化操作：读文件
	bool Read(FILE* fp)
	{
		if(NULL==fp) return false;

		fread( szText,       sizeof(char)*MAX_NOTECHARS, 1, fp ); 
		fread( &nRank,       sizeof(int), 1, fp );                
		fread( &nStyleNo,    sizeof(int), 1, fp );               
		fread( &nNumCoords,  sizeof(int), 1, fp );                
		
		if(nNumCoords > 0)
		{
			pCoords = new VBFVECTOR3D[nNumCoords];
			fread( pCoords,  sizeof(VBFVECTOR3D)*nNumCoords, 1, fp );   
		}

		return true;
	}

}VBF_NOTEDATA;


//----------------------------------------------------------------------------
// 内联函数：VBF_DeleteNoteData()
// 函数描述：释放注记数据指针
//----------------------------------------------------------------------------
inline void VBF_DeleteNoteData(int nNumNotes, VBF_NOTEDATA**& pNoteData)
{
	for(int i=0; i<nNumNotes; i++)
	{
		SAFE_DELETE(pNoteData[i]);
	}
	SAFE_DELETE(pNoteData);
}

// 下面的宏定义来自：WinGDI.h
#ifndef GB2312_CHARSET
	#define GB2312_CHARSET          134
#endif

//-------------------------------------------------------------------
// 定义结构体：VBF_NOTESTYLE
// 结构体描述：注记样式结构
//-------------------------------------------------------------------
typedef struct _tagVBFNoteStyle
{
	int      nNoteStyleNo;	
	DWORD    dwFontColor;
	DWORD    dwBackBorderColor;
	DWORD    dwBackFillColor;
	float    fPointSize;
	BYTE     nFontBold;
	BYTE     nFontItalic;
	BYTE     nFontUnderline;
	BYTE     nFontCharSet;
	char     szFontFaceName[32];  // 在VC++6.0中，LF_FACESIZE=32

	_tagVBFNoteStyle()
	{
		nFontCharSet = GB2312_CHARSET;
	}
	
	// 重载赋值操作符
	_tagVBFNoteStyle& operator=(const _tagVBFNoteStyle& NoteStyle)
	{
		nNoteStyleNo      = NoteStyle.nNoteStyleNo;	
		dwFontColor       = NoteStyle.dwFontColor;
		dwBackBorderColor = NoteStyle.dwBackBorderColor;
		dwBackFillColor   = NoteStyle.dwBackFillColor;
		fPointSize        = NoteStyle.fPointSize;	
		nFontBold         = NoteStyle.nFontBold;
		nFontItalic       = NoteStyle.nFontItalic;
		nFontUnderline    = NoteStyle.nFontUnderline;
		nFontCharSet      = NoteStyle.nFontCharSet;
                VBF_strcpy(szFontFaceName, NoteStyle.szFontFaceName);
		return *this;
	}

}VBF_NOTESTYLE;

//---------------------------------------------------------------------------
// 定义结构体：VBF_VRLABDEMHEADER
// 结构体说明：Dem格式的头部数据，
//             该格式由VR实验室制订，参见文档《DEM文件结构说明.doc》
//---------------------------------------------------------------------------
typedef struct _tagVBFVRLabDemHeader
{
	double   dbLBX, dbLBY;      // 左下角点坐标	
	double   dbRTX, dbRTY;      // 右上角点坐标	
	long     nNumX;             // X方向点数
    long     nNumY;             // Y方向点数
	double   dbSpaceX;          // 横方向网格间隔
	double   dbSpaceY;          // 纵方向网格间隔
	double   dbScale;           // 间隔相当于实地距离
	float    fMinHeight;        // 最小高程值
	float    fMaxHeight;        // 最大高程值
}VBF_VRLABDEMHEADER;


//---------------------------------------------------------------------------
// 定义结构体：VBF_DTISHEADER
// 结构体说明：DTIS格式的文件头
//---------------------------------------------------------------------------
typedef struct tagDTIS_DEMHEAD0
{
	long   m_lDemHeadSize;
	long   m_lReserved;
	float  m_fDemGeoL0, m_fDemGeoB0, m_fDemGeoL1,m_fDemGeoB1;
	short  m_numROWS,m_numCOLUMS;
	short  m_nMinHeight,m_nMaxHeight;
	double m_dGridSizeX,m_dGridSizeY;

	tagDTIS_DEMHEAD0()
	{
		m_lDemHeadSize  = sizeof(tagDTIS_DEMHEAD0);
		m_lReserved		= 0;
	}

}VBF_DTISHEADER;


//---------------------------------------------------------------------------
// 定义结构体：VBF_SIMPDEMHEADER
// 结构体说明：最简单Dem格式的头部数据，
//             该格式由武玉国制订，参见文档《DEM文件结构说明.doc》
//---------------------------------------------------------------------------
typedef struct _tagVBFSimpDemHeader
{
	short     nNumX;             // X方向点数
    short     nNumY;             // Y方向点数
}VBF_SIMPDEMHEADER;

// 注意：取消字节对齐的设置
#include <poppack.h>  


#endif
