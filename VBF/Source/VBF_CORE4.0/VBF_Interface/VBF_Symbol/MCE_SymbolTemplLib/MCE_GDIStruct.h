
#ifndef __MCE_GDISTRUCT_H__
#define __MCE_GDISTRUCT_H__

#pragma warning(disable: 4786)   // ʹ����ʧЧ
#include <vector>
using namespace std;

#include <VBF_Symbol/MCE_SymbolTemplLib/VBF_WinGDI.h>

//------------------------------------------------------------
//  ���ܣ������ʽṹ
//		  ���������ɲ���ϵͳ��ͼ��ϵͳ�ṩ�ģ�������Ҫ����Windows
//------------------------------------------------------------
class CMCE_PenBasic
{
public:
	CMCE_PenBasic();
	CMCE_PenBasic( const CMCE_PenBasic& bh );
	~CMCE_PenBasic();

	void Read(FILE* fp);
	CMCE_PenBasic& operator=( const CMCE_PenBasic& bh );

	bool operator==(const CMCE_PenBasic& bh);
	bool operator!=(const CMCE_PenBasic& bh);
	void Set(const CMCE_PenBasic& bh);

public:
	int			nPenStyle;
	int			nWidth;
	COLORREF	cr;
	bool		bAntialiasing; // �Ƿ���з�����
	
	UINT uCap;	// PS_ENDCAP_ROUND,PS_ENDCAP_SQUARE,PS_ENDCAP_FLAT
	UINT uJoin; // PS_JOIN_BEVEL, PS_JOIN_MITER,PS_JOIN_ROUND 
};

bool Read(FILE* fp, CMCE_PenBasic& a);

#define	BASIC_BRUSH_NULL		0  // �����  //GENERAL_BRUSH_NULL
#define BASIC_BRUSH_COLOR		1  // ��ɫ���
#define BASIC_BRUSH_PATTERN		2  // ͼ�����


//------------------------------------------------------------
//  ���ܣ�����ˢ�ӽṹ
//		  ����ˢ�����ɲ���ϵͳ��ͼ��ϵͳ�ṩ�ģ�������Ҫ����Windows
//------------------------------------------------------------
class CMCE_BrushBasic
{
public:
	CMCE_BrushBasic() ;
	CMCE_BrushBasic( CMCE_BrushBasic& bh );
	~CMCE_BrushBasic();

	void Read(FILE* fp);

	CMCE_BrushBasic& operator=( CMCE_BrushBasic& bh );
	bool operator==( CMCE_BrushBasic& bh );
	bool operator!=( CMCE_BrushBasic& bh );
	void Set( CMCE_BrushBasic& bh );
	bool HasFill() ;

public:
	BYTE		btType; 
	COLORREF	clrFG; // FG: Foreground ���ǰ��ɫ

	UINT		uPatternIndex ; //ͼ������
	int			nBkMode;      //����ģʽ
	COLORREF	clrPatternBG  ; //ͼ������ɫ
};


//--------------------------------------------------------
//  ϵͳ�û��Զ���ϵͳ����ʽ����
//---------------------------------------------------------
class CMCE_PenBasicEx
{
public:
	CMCE_PenBasicEx() ;
	CMCE_PenBasicEx( CMCE_PenBasicEx& usd ) ;
	CMCE_PenBasicEx& operator=(CMCE_PenBasicEx& usd);

	void Set( CMCE_PenBasicEx& usd ) ;
	void Read(FILE* fp) ;

	bool				bKeepColor;
	CMCE_PenBasic		GenePen;	// ͨ�õ�ϵͳ��(���û�����)
	int					nH;			// �����x=0�Ĵ�ֱƫ��
	std::vector<DWORD>	adwData;
};


bool Read(FILE* fp, CMCE_PenBasicEx& a);

#include "MCE_GDIStruct.inl"

#endif