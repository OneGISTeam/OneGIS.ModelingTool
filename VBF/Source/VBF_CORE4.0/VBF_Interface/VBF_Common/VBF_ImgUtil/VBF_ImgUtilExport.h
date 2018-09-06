#ifndef __VBF_IMG_UTIL_EXPORT_H__
#define __VBF_IMG_UTIL_EXPORT_H__


// 下面的宏定义，是为了导出该dll中所定义的类
#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( VBF_IMGUTIL_LIBRARY_STATIC )
    #    define VBF_IMGUTIL_EXPORT
    #  elif defined( VBF_IMGUTIL_LIBRARY )
    #    define VBF_IMGUTIL_EXPORT   __declspec(dllexport)
    #  else
    #    define VBF_IMGUTIL_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define VBF_IMGUTIL_EXPORT
#endif


#endif