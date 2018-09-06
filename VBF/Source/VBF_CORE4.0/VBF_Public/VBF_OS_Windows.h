//*******************************************************************
// FileName��  VBF_OS_Windows.h
// Function��  ��Windows����ϵͳ��ص�����
// Author:     ��Ө
// Date:       2012-11-01
//*******************************************************************

#ifndef __VBF_OS_WINDOWS_H__
#define __VBF_OS_WINDOWS_H__

#include "VBF_Macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VBF_LoadLibrary(szLibFileName)		LoadLibraryA(szLibFileName)	// װ�ض�̬��	
#define VBF_FreeLibrary						FreeLibrary							// ж�ض�̬��
#define VBF_SetCVBF_Timer					SetCVBF_Timer							// ������ʱ��
#define VBF_KillCVBF_Timer					KillCVBF_Timer							// �رռ�ʱ��
#define VBF_GetProcAddress					GetProcAddress						// ��ȡ������ַ


#if defined(_MSC_VER)
    #pragma warning (disable : 4996)
#endif

#ifdef _MSC_VER  // VS������
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
#else  // QT������
    #define VBF_strcpy          strcpy
    #define VBF_sprintf         sprintf
    #define VBF_fscanf          fscanf
    #define VBF_strcat          strcat
    #define VBF_itoa            itoa
    #define VBF_strncpy         strncpy
    #define VBF_stricmp         stricmp
#endif


//-------------------------------------------------------------------
// ������VBF_fopen()
// ���������ļ�
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
