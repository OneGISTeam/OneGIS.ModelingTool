#ifndef __VBF_XML_EXPORT_H__
#define __VBF_XML_EXPORT_H__

#include <VBF_Config.h>


#if defined(_MSC_VER) && defined(OSG_DISABLE_MSVC_WARNINGS)
    #pragma warning( disable : 4251)   // 使警告失效
#endif


#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( VBF_XML_LIBRARY_STATIC )
    #    define VBF_XML_EXPORT
    #  elif defined( VBF_XML_LIBRARY )
    #    define VBF_XML_EXPORT   __declspec(dllexport)
    #  else
    #    define VBF_XML_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define VBF_XML_EXPORT
#endif



// set up define for whether member templates are supported by VisualStudio compilers.
#ifdef _MSC_VER
# if (_MSC_VER >= 1300)
#  define __STL_MEMBER_TEMPLATES
# endif
#endif


// 使用STL
#ifndef TIXML_USE_STL
	#define TIXML_USE_STL
#endif

#endif

