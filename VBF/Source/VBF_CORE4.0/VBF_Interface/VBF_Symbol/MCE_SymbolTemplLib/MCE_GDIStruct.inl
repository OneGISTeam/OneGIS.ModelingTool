#ifndef __MCE_GDISTRUCT_INL__
#define __MCE_GDISTRUCT_INL__

#include <VBF_Symbol/MCE_SymbolTemplLib/VBF_ReadWrite.h>


//------------------------------------------------------------
//  功能：实现一般笔的参数结构
//  时间：2002-03-10 09:30
//------------------------------------------------------------

inline CMCE_PenBasic::CMCE_PenBasic()
{
	nPenStyle		= PS_SOLID; 
	nWidth			= 20;
	cr				= RGB(0,0,0);
	bAntialiasing	= false;
	uCap			= PS_ENDCAP_FLAT; 
	uJoin			= PS_JOIN_MITER; 
}

inline CMCE_PenBasic::CMCE_PenBasic( const CMCE_PenBasic& pen )
{
	Set( pen );
}

inline CMCE_PenBasic::~CMCE_PenBasic()
{
}

inline void CMCE_PenBasic::Read(FILE* fp)
{
	ReadInt(fp, nPenStyle);
	ReadInt(fp, nWidth);
	ReadColor(fp, cr);
	ReadBool(fp, bAntialiasing);
	ReadUINT(fp, uCap);
	ReadUINT(fp, uJoin);
}

inline CMCE_PenBasic& CMCE_PenBasic::operator=( const CMCE_PenBasic& pen )
{
	Set( pen )  ;
	return *this;
}

inline bool CMCE_PenBasic::operator==( const CMCE_PenBasic& pen )
{
	return (  	nPenStyle==pen.nPenStyle &&
				nWidth   ==pen.nWidth    &&
				cr  ==pen.cr   &&
				bAntialiasing == pen.bAntialiasing &&
				uCap  == pen.uCap &&
				uJoin == pen.uJoin 
			);
}


inline bool CMCE_PenBasic::operator!=( const CMCE_PenBasic& pen )
{
	return !(*this==pen);
}

inline void CMCE_PenBasic::Set( const CMCE_PenBasic& pen )
{
	nPenStyle = pen.nPenStyle; 
	nWidth    = pen.nWidth ;
	cr   = pen.cr;
	bAntialiasing = pen.bAntialiasing; 
	uCap  = pen.uCap; 
	uJoin = pen.uJoin; 
}

//------------------------------------------------------------
//  功能：实现一般刷子的参数结构
//  时间：2002-03-10 09:30
//------------------------------------------------------------

inline CMCE_BrushBasic::CMCE_BrushBasic()
{
	nBkMode       = OPAQUE;
	btType        = BASIC_BRUSH_COLOR; 
	clrFG         = RGB(255,255,255)   ;
	uPatternIndex = 0;
	clrPatternBG  = RGB(255,255,0) ;
}

inline CMCE_BrushBasic::CMCE_BrushBasic( CMCE_BrushBasic& bh )
{
	Set( bh );
}

inline CMCE_BrushBasic::~CMCE_BrushBasic()
{
}

inline void CMCE_BrushBasic::Read(FILE* fp)
{
	ReadBYTE(fp, btType);

	if( btType==BASIC_BRUSH_COLOR )
	{
		ReadColor(fp, clrFG);
	}
	else if( btType==BASIC_BRUSH_PATTERN )
	{
		ReadColor(fp, clrFG);
		ReadUINT(fp, uPatternIndex);
		ReadColor(fp, clrPatternBG);
		ReadInt(fp, nBkMode);
	}
}

inline CMCE_BrushBasic& CMCE_BrushBasic::operator=( CMCE_BrushBasic& bh )
{
	Set( bh );
	return *this; 
}

inline bool CMCE_BrushBasic::operator==( CMCE_BrushBasic& bh )
{
	if( btType!=bh.btType ) return false;

	switch (btType)
	{
		case BASIC_BRUSH_COLOR:
			return ( clrFG==bh.clrFG );

		case BASIC_BRUSH_PATTERN:
			return (  clrFG        == bh.clrFG &&
					  uPatternIndex== bh.uPatternIndex &&
					  clrPatternBG == bh.clrPatternBG  &&
					  nBkMode      == bh.nBkMode );

		default: 
			break;
	}

	return true;
}

inline bool CMCE_BrushBasic::operator!=( CMCE_BrushBasic& bh )
{
	return !(*this==bh);
}

inline void CMCE_BrushBasic::Set( CMCE_BrushBasic& bh )
{
	btType = bh.btType;

	switch (btType)
	{
		case BASIC_BRUSH_COLOR:
			clrFG = bh.clrFG;
			break;

		case BASIC_BRUSH_PATTERN:
			{
				clrFG         = bh.clrFG;
				uPatternIndex = bh.uPatternIndex;
				clrPatternBG  = bh.clrPatternBG ;
				nBkMode       = bh.nBkMode;
			}
			break;

		default: 
			break;
	}
}

inline bool CMCE_BrushBasic::HasFill()
{
	return (btType!=BASIC_BRUSH_NULL);
}

//============================================================
// struct CMCE_PenBasicEx
// 应用: 作为线符号的一种数据，以便加快速度
// 时间: 2002-03-21  10:00
//============================================================

inline CMCE_PenBasicEx::CMCE_PenBasicEx()
{
	bKeepColor = true;
	nH = 0;
}

inline CMCE_PenBasicEx::CMCE_PenBasicEx( CMCE_PenBasicEx& usd )
{
	Set( usd );
}

inline CMCE_PenBasicEx& CMCE_PenBasicEx::operator=( CMCE_PenBasicEx& usd )
{
	Set( usd );
	return *this;
}

inline void CMCE_PenBasicEx::Set( CMCE_PenBasicEx& usd )
{
	nH         = usd.nH;
	bKeepColor = usd.bKeepColor;
	GenePen    = usd.GenePen;
	adwData    = usd.adwData; 
}

inline void CMCE_PenBasicEx::Read(FILE* fp)
{
	ReadInt(fp, nH);
	ReadBool(fp, bKeepColor);
	GenePen.Read(fp);

	int nSize = 0;
	ReadInt(fp, nSize);

	adwData.reserve(nSize);
	for(int i=0; i<nSize; i++)
	{
		ReadDWORD(fp, adwData[i]);
	}
}


#endif