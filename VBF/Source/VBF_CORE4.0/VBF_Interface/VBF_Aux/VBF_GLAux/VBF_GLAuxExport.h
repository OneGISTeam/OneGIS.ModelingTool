#ifndef __VBF_GLAUX_EXPORT_H__
#define __VBF_GLAUX_EXPORT_H__


#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( VBF_GLAUX_LIBRARY_STATIC )
    #    define VBF_GLAUX_EXPORT
    #  elif defined( VBF_GLAUX_LIBRARY )
    #    define VBF_GLAUX_EXPORT   __declspec(dllexport)
    #  else
    #    define VBF_GLAUX_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define VBF_GLAUX_EXPORT
#endif


#endif