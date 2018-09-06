//*******************************************************************
// FileName：  VBF_WinGDI.h
// Function：  与WindowsGDI有关的定义
// Author:     杜莹
// Date:       2014-06-03
//*******************************************************************

#ifndef __VBF_WIN_GDI_H__
#define __VBF_WIN_GDI_H__


#include <VBF_Macros.h>


#ifndef _WINGDI_
	typedef DWORD				COLORREF;
	#define RGB(r,g,b)			((DWORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
	#define GetRValue(rgb)      ((BYTE)(rgb))
	#define GetGValue(rgb)      ((BYTE)(((WORD)(rgb)) >> 8))
	#define GetBValue(rgb)      ((BYTE)((rgb)>>16))
#endif

/* Pen Styles */
#define PS_SOLID            0
#define PS_DASH             1       /* -------  */
#define PS_DOT              2       /* .......  */
#define PS_DASHDOT          3       /* _._._._  */
#define PS_DASHDOTDOT       4       /* _.._.._  */
#define PS_NULL             5
#define PS_INSIDEFRAME      6
#define PS_USERSTYLE        7
#define PS_ALTERNATE        8
#define PS_STYLE_MASK       0x0000000F

#define PS_ENDCAP_ROUND     0x00000000
#define PS_ENDCAP_SQUARE    0x00000100
#define PS_ENDCAP_FLAT      0x00000200
#define PS_ENDCAP_MASK      0x00000F00

#define PS_JOIN_ROUND       0x00000000
#define PS_JOIN_BEVEL       0x00001000
#define PS_JOIN_MITER       0x00002000
#define PS_JOIN_MASK        0x0000F000

#define PS_COSMETIC         0x00000000
#define PS_GEOMETRIC        0x00010000
#define PS_TYPE_MASK        0x000F0000

/* Background Modes */
#define TRANSPARENT         1
#define OPAQUE              2
#define BKMODE_LAST         2

#endif 
