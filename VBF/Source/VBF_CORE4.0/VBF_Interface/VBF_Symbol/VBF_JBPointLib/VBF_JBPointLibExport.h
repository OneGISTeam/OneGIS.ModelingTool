//***************************************************************************************
// FileName：VBF_JBPointLibExport.h
// Function：点状军标库的导出文件
// Author:   杜莹
// Date:     2014-05-14
//***************************************************************************************

#ifndef __VBF_JBPOINT_LIB_EXPORT_H__
#define __VBF_JBPOINT_LIB_EXPORT_H__

#include <VBF_Config.h>



#if defined(_MSC_VER) && defined(OSG_DISABLE_MSVC_WARNINGS)
    #pragma warning( disable : 4251)   // 使警告失效
#endif


#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( VBF_JBPOINTLIB_LIBRARY_STATIC )
    #    define VBF_JBPOINTLIB_EXPORT
    #  elif defined( VBF_JBPOINTLIB_LIBRARY )
    #    define VBF_JBPOINTLIB_EXPORT   __declspec(dllexport)
    #  else
    #    define VBF_JBPOINTLIB_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define VBF_JBPOINTLIB_EXPORT
#endif


// set up define for whether member templates are supported by VisualStudio compilers.
#ifdef _MSC_VER
	# if (_MSC_VER >= 1300)
	#  define __STL_MEMBER_TEMPLATES
	# endif
#endif

#endif