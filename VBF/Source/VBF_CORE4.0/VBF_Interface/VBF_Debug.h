//*******************************************************************
// FileName：  VBF_Debug.h
// Function：  与调试有关的内容
// Author:     武玉国
// Date:       2013-09-10
//*******************************************************************

#ifndef __VBF_DEBUG_H__
#define __VBF_DEBUG_H__

#ifdef _DEBUG
/*
	#ifndef _WIN32_WINNT		// 允许使用特定于 Windows NT 4 或更高版本的功能。
	#define _WIN32_WINNT 0x0501	// 将此值更改为适当的值，以适用于 Windows 2000 或更高版本。
	#endif		

	#define _AFXDLL
	#include <afx.h>

	#define new DEBUG_NEW

	#define VBF_Max max
	#define VBF_Min min
*/
	#define VBF_Max std::max
	#define VBF_Min std::min
#else
#define VBF_Max std::max
#define VBF_Min std::min
#endif


#endif
