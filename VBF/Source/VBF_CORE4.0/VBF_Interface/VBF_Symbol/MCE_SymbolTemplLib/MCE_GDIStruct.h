
#ifndef __MCE_GDISTRUCT_H__
#define __MCE_GDISTRUCT_H__

#pragma warning(disable: 4786)   // 使警告失效
#include <vector>
using namespace std;

#include <VBF_Symbol/MCE_SymbolTemplLib/VBF_WinGDI.h>

//------------------------------------------------------------
//  功能：基本笔结构
//		  基本笔是由操作系统的图形系统提供的，这里主要参照Windows
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
	bool		bAntialiasing; // 是否进行反走样
	
	UINT uCap;	// PS_ENDCAP_ROUND,PS_ENDCAP_SQUARE,PS_ENDCAP_FLAT
	UINT uJoin; // PS_JOIN_BEVEL, PS_JOIN_MITER,PS_JOIN_ROUND 
};

bool Read(FILE* fp, CMCE_PenBasic& a);

#define	BASIC_BRUSH_NULL		0  // 不填充  //GENERAL_BRUSH_NULL
#define BASIC_BRUSH_COLOR		1  // 纯色填充
#define BASIC_BRUSH_PATTERN		2  // 图案填充


//------------------------------------------------------------
//  功能：基本刷子结构
//		  基本刷子是由操作系统的图形系统提供的，这里主要参照Windows
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
	COLORREF	clrFG; // FG: Foreground 填充前景色

	UINT		uPatternIndex ; //图案索引
	int			nBkMode;      //背景模式
	COLORREF	clrPatternBG  ; //图案背景色
};


//--------------------------------------------------------
//  系统用户自定义系统笔样式数据
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
	CMCE_PenBasic		GenePen;	// 通用的系统笔(非用户定义)
	int					nH;			// 相对于x=0的垂直偏移
	std::vector<DWORD>	adwData;
};


bool Read(FILE* fp, CMCE_PenBasicEx& a);

#include "MCE_GDIStruct.inl"

#endif