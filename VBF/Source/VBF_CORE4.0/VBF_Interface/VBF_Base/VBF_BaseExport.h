#ifndef __VBF_BASE_EXPORT_H__
#define __VBF_BASE_EXPORT_H__

#include <VBF_Config.h>




#if defined(_MSC_VER) && defined(OSG_DISABLE_MSVC_WARNINGS)
    #pragma warning( disable : 4244 )
    #pragma warning( disable : 4251 )
    #pragma warning( disable : 4275 )
    #pragma warning( disable : 4512 )
    #pragma warning( disable : 4267 )
    #pragma warning( disable : 4702 )
    #pragma warning( disable : 4511 )
#endif

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( VBF_BASE_LIBRARY_STATIC )
    #    define VBF_BASE_EXPORT
    #  elif defined( VBF_BASE_LIBRARY )
    #    define VBF_BASE_EXPORT   __declspec(dllexport)
    #  else
    #    define VBF_BASE_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define VBF_BASE_EXPORT
#endif

// set up define for whether member templates are supported by VisualStudio compilers.
#ifdef _MSC_VER
# if (_MSC_VER >= 1300)
#  define __STL_MEMBER_TEMPLATES
# endif
#endif


// ∂®“Â NULL ÷µ
#ifndef NULL
    #ifdef  __cplusplus
        #define NULL    0
    #else
        #define NULL    ((void *)0)
    #endif
#endif


#endif

