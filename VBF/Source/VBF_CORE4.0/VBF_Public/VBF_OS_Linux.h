//*******************************************************************
// FileName：  VBF_OS_Linux.h
// Function：  Linux操作系统相关的内容
// Author:     杜莹
// Date:       2012-11-01
//*******************************************************************

#ifndef __VBF_OS_LINUX_H__
#define __VBF_OS_LINUX_H__

#include "VBF_Macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>


#define VBF_LoadLibrary(szLibFileName)		LoadLibraryA(szLibFileName)	// ???
#define VBF_FreeLibrary						dlclose							// ж??
#define VBF_SetCVBF_Timer					SetCVBF_Timer							// ?
#define VBF_KillCVBF_Timer					KillCVBF_Timer							// ???
#define VBF_GetProcAddress				GetProcAddress						// ??


#if defined(_MSC_VER)
    #pragma warning (disable : 4996)
#endif


    #define VBF_strcpy          strcpy
    #define VBF_sprintf         sprintf
    #define VBF_fscanf          fscanf
    #define VBF_strcat          strcat
    #define VBF_strncpy         strncpy

#ifndef HINSTANCE
    typedef void *HINSTANCE;
#endif


//-------------------------------------------------------------------
// VBF_fopen()
//
//-------------------------------------------------------------------
inline bool VBF_fopen(const char* filename, const char* mode, FILE*& fp)
{
        fp = fopen(filename, mode);
        return (fp!=NULL);
}

inline void ZeroMemory(void* pTar, int nSize)
{
    memset(pTar,0,nSize);
}

inline char* itoa(unsigned int val, char* buf, unsigned int radix)
{
    if(radix==10)
    {
        sprintf(buf, "%d", val);
    }
    else if(radix==16)
    {
        sprintf(buf, "%x", val);
    }
    else if(radix==8)
    {
        sprintf(buf, "%o", val);
    }
    else if(radix==2)
    {
        char szBin[32];
        for(int i=0; i<32; i++) { szBin[i] = '0'; buf[i] = '0'; }

        unsigned int nValueT = val;
        int n=0;
        while(nValueT > 0 && n<=32)
        {
            sprintf(&szBin[n], "%d", (nValueT & 0x01));
            nValueT >>= 1;
            n++;
        }
        for(int i=n; i<32; i++) { szBin[i] = '0'; }

        // 逆序输出
        for(int k=0; k<32; k++) { buf[k] = szBin[31-k]; }
    }
    return buf;
}

inline void _ui64toa(unsigned long long val, char *buf, unsigned int radix)
{
    if(radix == 10)
    {
        sprintf(buf,"%llu",val);
    }
    else if(radix == 16)
    {
        //!!!32
        sprintf(buf,"%llx",val);
    }
}

inline int VBF_stricmp(const char* s1, const char* s2)
{
    return strcasecmp(s1, s2);
}


#endif
