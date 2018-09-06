//*******************************************************************
// FileName��  VBF_DemTexDataType.h
// Function��  Dem������ʹ�õĹ�����������
// Author:     ��Ө
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
    //zj DTIS ���漰�ļ��Ķ�ȡ������Ҫ����BOOL����linux����windows���ڴ��Сһ��
    //linux �¶���BOOLΪunsigned char
    typedef unsigned int        BOOL;
//#endif


// �����ļ���׺
#define EXT_DEMFILE				"demx"     // Dem�ļ���׺
#define EXT_TEXFILE				"texx"     // �����ļ���׺
#define EXT_NOTEFILE			"notx"     // ע���ļ���׺

// ���岻��������ȱʧ���ݵ���ʱ���ֵ
#define NULLDATA_DEM			-99999.0                // Dem���е���ʱ���ֵ

// ȫ�ֺ������жϸ̵߳��Ƿ���Ч
// ����˵������Ч���ڵ��ο��еļ�¼ֵΪNULLDATA_DEM
static bool IsHeightValid(float fH) { return (fH > NULLDATA_DEM+1); } // ���㷨��fabs()�㷨�� 

// ������ο�ı��볤��
#define BLKKEY_LENGTH		16

// ������Ч�ĵ��ο����ֵ
#define ENCODE_BLKKEY(nLodNo, nBlkNoX, nBlkNoY)		( (UINT64)(((UINT64)nLodNo)<<59) + (UINT64)(((UINT64)nBlkNoX)<<30) + (UINT64)nBlkNoY )
#define INVALID_BLKKEY								( ENCODE_BLKKEY(0,1,1) )    // �������ܴ��� (nLod=0, nBlkNoX=1, nBlkNoY=1) �ĵ��ο�

//-----------------------------------------------------------
// ����ö�٣�VBF_BLK_EDGE
// ö���������оٿ��4����
//-----------------------------------------------------------
enum VBF_BLK_EDGE
{
	VBF_BLK_EDGE_TOP      = 0,
	VBF_BLK_EDGE_RIGHT    = 1,
	VBF_BLK_EDGE_BOTTOM   = 2,
	VBF_BLK_EDGE_LEFT     = 3
};

// ���ýṹ����뷽ʽ��4�ֽڶ���
#include <pshpack4.h>

//-------------------------------------------------------------------
// ����ṹ�壺VBF_DEMTEXPERSISTHEADER
// �ṹ��������DemTex�ļ�ͷ
//-------------------------------------------------------------------
typedef struct _tagVBFDemTexPersistHeader
{
	unsigned int  dwVersionNo;      // ���ݰ汾��
	int           nBlkNumX;			// X�����ϵĿ���
	int           nBlkNumY;			// Y�����ϵĿ���
	int           nReserved[2];		// �����ֽ�

	_tagVBFDemTexPersistHeader()
	{
		dwVersionNo   = 1;
		nBlkNumX      = 0;           // X�����ϵĿ���
		nBlkNumY      = 0;           // Y�����ϵĿ���

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
// ����ṹ�壺VBF_DEMTEXPERSISTBLKINF
// �ṹ��������DemTex�ļ���ÿ��block����Ϣ
//-------------------------------------------------------------------
typedef struct _tagVBFDemTexPersistBlkInf
{
	unsigned int    nPos;          // �����ļ��е���ʼλ�ã���Ө�޸�Ϊunsigned int���Ա�ʹ�ļ��ֽ����ܴ���2G��
	int				nLength;       // �����ļ��еĳ���(��λ���ֽ�)	
	int				nReserved[2];  // �����ֽ�

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
// ����ṹ�壺VBF_DEMTEXENGINECONFIGPAR
// �ṹ��������DEM��������������ò���
//-------------------------------------------------------------------
typedef struct _tagVBFDemTexEngineConfigPar
{
	// �������������ϱ߽翪ʼ�ֿ�,���ϱ߽���Ϊ00

	// ���������ܵ����귶Χ
	double   dGlobalX0;
	double   dGlobalX1;
	double   dGlobalY0;
	double   dGlobalY1;

	// �����ڶ��ٸ����ڵ�
	int      nRootBlkNumX;
	int		 nRootBlkNumY;

	// LOD�����
	int		 nLodCount;

	// ÿһ��DEM�Ĵ�С����������
	int		 nDemBlkSizeX;
	int		 nDemBlkSizeY;

	// ÿһ������Ĵ�С����������
	int		 nTexBlkSizeX;
	int		 nTexBlkSizeY;

	// ÿ���ļ�����Ŀ���, ʵ�ʿ��ܱȸ�ֵС
	int		 nPerFileBlkNumX;
	int		 nPerFileBlkNumY;

	// ע�⣺����ȱʡ�Ĺ��캯��
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

	// ���л���д (�����ļ���ʽ, .ini)
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

	// ���л����� (�����ļ���ʽ, .ini)
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


// ע�⣺ȡ���ֽڶ��������
#include <poppack.h>    

// ��ע���йص����ֵ����
#define MAX_NOTECHARS         32      // ÿ��ע���е�����ַ�����
#define MAX_NOTERANK          10       // ע�ǵ������������

// ���ýṹ����뷽ʽ��1�ֽڶ���
#include <pshpack1.h>
//-------------------------------------------------------------------
// ����ṹ�壺VBF_NOTEDATA
// �ṹ��������ע�����ݽṹ
//-------------------------------------------------------------------
typedef struct _tagVBFNoteData
{
	char         szText[MAX_NOTECHARS];    // ע���ַ���
	int          nRank;                    // ��������(ֵԽ�󣬼���Խ��)
	int          nStyleNo;                 // ע����ʽ��	
	int          nNumCoords;               // ע���������(����λ����������ܳ���MAX_NOTECHARS)
	VBFVECTOR3D* pCoords;                 // ע�����괮

	_tagVBFNoteData()  // ���캯��
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

	// ���ظ�ֵ������
	_tagVBFNoteData& operator=(const _tagVBFNoteData& NoteData)
	{
                VBF_strcpy(szText, NoteData.szText);
		nRank       = NoteData.nRank;
                nStyleNo    = NoteData.nStyleNo;
		nNumCoords  = NoteData.nNumCoords; 

		if(nNumCoords > 0)	// Ҫ��������һ����λ��
		{
			pCoords = new VBFVECTOR3D[nNumCoords];   
			memcpy(pCoords, NoteData.pCoords, sizeof(VBFVECTOR3D)*nNumCoords);
		}
		
		return *this;
	}

	// ����==������
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

	// ���л�������д�ļ�
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

	// ���л����������ļ�
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

	// ���л�������д�ļ�
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

	// ���л����������ļ�
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
// ����������VBF_DeleteNoteData()
// �����������ͷ�ע������ָ��
//----------------------------------------------------------------------------
inline void VBF_DeleteNoteData(int nNumNotes, VBF_NOTEDATA**& pNoteData)
{
	for(int i=0; i<nNumNotes; i++)
	{
		SAFE_DELETE(pNoteData[i]);
	}
	SAFE_DELETE(pNoteData);
}

// ����ĺ궨�����ԣ�WinGDI.h
#ifndef GB2312_CHARSET
	#define GB2312_CHARSET          134
#endif

//-------------------------------------------------------------------
// ����ṹ�壺VBF_NOTESTYLE
// �ṹ��������ע����ʽ�ṹ
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
	char     szFontFaceName[32];  // ��VC++6.0�У�LF_FACESIZE=32

	_tagVBFNoteStyle()
	{
		nFontCharSet = GB2312_CHARSET;
	}
	
	// ���ظ�ֵ������
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
// ����ṹ�壺VBF_VRLABDEMHEADER
// �ṹ��˵����Dem��ʽ��ͷ�����ݣ�
//             �ø�ʽ��VRʵ�����ƶ����μ��ĵ���DEM�ļ��ṹ˵��.doc��
//---------------------------------------------------------------------------
typedef struct _tagVBFVRLabDemHeader
{
	double   dbLBX, dbLBY;      // ���½ǵ�����	
	double   dbRTX, dbRTY;      // ���Ͻǵ�����	
	long     nNumX;             // X�������
    long     nNumY;             // Y�������
	double   dbSpaceX;          // �᷽��������
	double   dbSpaceY;          // �ݷ���������
	double   dbScale;           // ����൱��ʵ�ؾ���
	float    fMinHeight;        // ��С�߳�ֵ
	float    fMaxHeight;        // ���߳�ֵ
}VBF_VRLABDEMHEADER;


//---------------------------------------------------------------------------
// ����ṹ�壺VBF_DTISHEADER
// �ṹ��˵����DTIS��ʽ���ļ�ͷ
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
// ����ṹ�壺VBF_SIMPDEMHEADER
// �ṹ��˵�������Dem��ʽ��ͷ�����ݣ�
//             �ø�ʽ��������ƶ����μ��ĵ���DEM�ļ��ṹ˵��.doc��
//---------------------------------------------------------------------------
typedef struct _tagVBFSimpDemHeader
{
	short     nNumX;             // X�������
    short     nNumY;             // Y�������
}VBF_SIMPDEMHEADER;

// ע�⣺ȡ���ֽڶ��������
#include <poppack.h>  


#endif
