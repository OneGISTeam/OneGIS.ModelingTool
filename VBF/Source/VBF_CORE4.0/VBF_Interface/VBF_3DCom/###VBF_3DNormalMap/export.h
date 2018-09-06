#ifndef HGBUMP_EXPORT_H
#define HGBUMP_EXPORT_H 1

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__) || defined( __MWERKS__)
#  if defined( VBF_3DNormalMap_LIBRARY_STATIC )
#    define VBF_3DNormalMap_EXPORT
#  elif defined( VBF_3DNormalMap_LIBRARY )
#    define VBF_3DNormalMap_EXPORT   __declspec(dllexport)
#  else
#    define VBF_3DNormalMap_EXPORT   __declspec(dllimport)
#endif
#else
#define VBF_3DNormalMap_EXPORT
#endif

#endif 
