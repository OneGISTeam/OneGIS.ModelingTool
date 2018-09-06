//*******************************************************************
// FileName：  VBF_Macros.h
// Function：  公用的宏定义
// Author:     
// Date:       2004-11-14
//*******************************************************************

#ifndef __VBF_MACROS_H__
#define __VBF_MACROS_H__

#ifdef linux
    #include <cmath>
#else
    #include <math.h>
#endif

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

        //typedef unsigned long TYPE_PTR;   //注：(TYPE_PTR)pElemModel "TiXmlElement*"转"TYPE_PTR"精度丢失
typedef uintptr_t TYPE_PTR;

// WTypes.h
#ifndef _WINDEF_
        typedef unsigned char               BYTE;
        typedef unsigned short              WORD;

        # if __WORDSIZE == 64
            #ifndef DWORD
                typedef unsigned int                DWORD;
            # endif
        # else
            typedef unsigned long               DWORD;
        # endif

        typedef unsigned int                UINT;
        //typedef int                         BOOL;  // 不能全局定义 linux下与局部（VBF_Viewer）冲突

        # if __WORDSIZE == 64
            typedef long int		    int64_t;
        # else
            typedef long long int	    int64_t;
        # endif

        #if __WORDSIZE == 64
            typedef unsigned long int       uint64_t;
        #else
            typedef unsigned long long int  uint64_t;
        #endif

        typedef uint64_t                    UINT64;
        typedef unsigned long long          ULONGLONG;
//        typedef long long                   __int64;
        typedef unsigned long long          __uint64;

    #ifndef TRUE
        #define TRUE  1
    #endif

    #ifndef FALSE
        #define FALSE  0
    #endif
/*
#ifndef HINSTANCE
	typedef void *HINSTANCE;
#endif
#ifndef HDC
    typedef  void *HDC;
#endif
#ifndef HWND
    typedef  void *HWND;
#endif
*/
        
#endif  // _WINDEF_


#ifndef MAX_PATH
	#define MAX_PATH          260
#endif
#ifndef _MAX_PATH
    #define _MAX_PATH          260
#endif
#ifndef _MAX_DRIVE
    #define _MAX_DRIVE          260
#endif

#ifndef _MAX_DIR
    #define _MAX_DIR          260
#endif
// 释放指针
#ifndef SAFE_DELETE
	#define SAFE_DELETE(p)				{ if(p) { delete (p);     (p)=NULL; } }
	#define SAFE_DELETE_ARRAY(p)		{ if(p) { delete[] (p);   (p)=NULL; } }
#endif

// 释放接口
#ifndef SAFE_RELEASE
	#define SAFE_RELEASE(p)				{ if(p) { (p)->Release(); (p)=NULL; } }
#endif

// 计算数组中元素的个数
#ifndef _countof
	#define _countof(array)				(sizeof(array)/sizeof(array[0]))
#endif

#if defined(_MSC_VER)
// 定义最小取值函数
//#ifndef min
//    #define min(a, b)					(((a) < (b)) ? (a) : (b))
//#endif

//// 定义最大取值函数
//#ifndef max
//    #define max(a, b)					(((a) > (b)) ? (a) : (b))
//#endif

#endif



#ifndef FLT_MAX_PRECISION
	#define FLT_MAX_PRECISION     (pow(10, (float)-FLT_DIG))       // float型数的最大精度
#endif

#ifndef DBL_MAX_PRECISION
	#define DBL_MAX_PRECISION     (pow(10, (double)-DBL_DIG))       // double型数的最大精度
#endif

#ifndef DBL_ZERO
	#define DBL_ZERO              1.0e-12
#endif

#ifndef FLT_ZERO
	#define FLT_ZERO              1.0e-6
#endif

// 定义有效句柄
#ifndef VALID_HANDLE
	#define VALID_HANDLE(h)				(h!=NULL && h!=(HANDLE)0xdddddddd && h!=(HANDLE)0xcdcdcdcd )
#endif

// 定义4字节编码信息
#ifndef MAKEFOURCC
	#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
					((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |   \
					((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))

	typedef DWORD           FOURCC;         /* a four character code */
#endif

/* 定义 NULL 值 */
#ifndef NULL
    #ifdef  __cplusplus
        #define NULL    0
    #else
        #define NULL    ((void *)0)
    #endif
#endif


#define VBF_3D_FIXEDFPS 30

#endif
