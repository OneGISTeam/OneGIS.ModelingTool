#ifndef __VBF_AUXTHEMATICMAP_EXPORT_H__
#define __VBF_AUXTHEMATICMAP_EXPORT_H__


#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( VBF_AUXTHEMATICMAP_LIBRARY_STATIC )
    #    define VBF_AUXTHEMATICMAP_EXPORT
    #  elif defined( VBF_AUXTHEMATICMAP_LIBRARY )
    #    define VBF_AUXTHEMATICMAP_EXPORT   __declspec(dllexport)
    #  else
    #    define VBF_AUXTHEMATICMAP_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define VBF_AUXTHEMATICMAP_EXPORT
#endif


#endif
