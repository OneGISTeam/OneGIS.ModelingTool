//*******************************************************************
// FileName：  VBF_OS.h
// Function：  与操作系统或平台相关的内容
// Author:     杜莹
// Date:       2012-11-01
//*******************************************************************

#ifndef __VBF_OS_H__
#define __VBF_OS_H__

// 定义操作系统/平台（只能任选其一）
//#define VBF_OS_WINDOWS
//#define VBF_OS_LINUX
//#define VBF_OS_VXWORKS

// Windows操作系统下使用的定义与函数
#ifdef VBF_OS_WINDOWS
	#include "VBF_OS_Windows.h"
#endif


// 以下为Linux操作系统下使用的定义与函数
#ifdef VBF_OS_LINUX
	#include "VBF_OS_Linux.h"
#endif


#ifdef VBF_OS_LINUX
    #define VBF_DLL_LOCAL   __attribute__((visibility("hidden")))
#else
     #define VBF_DLL_LOCAL
#endif


// 以下为QT编译环境下使用的定义与函数
#ifdef VBF_QT
	#include "VBF_OS_QT.h"
#endif

#endif
