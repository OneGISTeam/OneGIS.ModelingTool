//*******************************************************************
// FileName：  VBF_OS_Windows.h
// Function：  与Windows操作系统相关的内容
// Author:     杜莹
// Date:       2012-11-01
//*******************************************************************

#ifndef __VBF_OS_WINDOWS_H__
#define __VBF_OS_WINDOWS_H__

#include "VBF_Macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VBF_LoadLibrary(szLibFileName)		LoadLibraryA(szLibFileName)	// 装载动态库	
#define VBF_FreeLibrary						FreeLibrary							// 卸载动态库
#define VBF_SetCVBF_Timer					SetCVBF_Timer							// 开启计时器
#define VBF_KillCVBF_Timer					KillCVBF_Timer							// 关闭计时器
#define VBF_GetProcAddress					GetProcAddress						// 获取函数地址


#if defined(_MSC_VER)
    #pragma warning (disable : 4996)
#endif

#ifdef _MSC_VER  // VS编译器
    #if _MSC_VER <= 1200		// VC6.0
            #define VBF_strcpy          strcpy
            #define VBF_sprintf         sprintf
            #define VBF_fscanf          fscanf
            #define VBF_strcat          strcat
            #define VBF_itoa            itoa
            #define VBF_strncpy         strncpy
            #define VBF_stricmp         stricmp
    #else
            #define VBF_strcpy          strcpy_s
            #define VBF_sprintf         sprintf_s
            #define VBF_fscanf          fscanf_s
            #define VBF_strcat          strcat_s
            #define VBF_itoa            _itoa_s
            #define VBF_strncpy         strncpy_s
            #define VBF_stricmp         _stricmp
    #endif
#else  // QT编译器
    #define VBF_strcpy          strcpy
    #define VBF_sprintf         sprintf
    #define VBF_fscanf          fscanf
    #define VBF_strcat          strcat
    #define VBF_itoa            itoa
    #define VBF_strncpy         strncpy
    #define VBF_stricmp         stricmp
#endif


//-------------------------------------------------------------------
// 函数：VBF_fopen()
// 描述：打开文件
//-------------------------------------------------------------------
inline bool VBF_fopen(const char* filename, const char* mode, FILE*& fp)
{
#if _MSC_VER <= 1200

	fp = fopen(filename, mode);
	return (fp!=NULL);

#else

	errno_t err = fopen_s(&fp, filename, mode);
	return (err==0);

#endif
}


#endif
