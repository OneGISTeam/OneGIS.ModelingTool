#ifndef __VBF_3DRASTERDB_EXPORT_H__
#define __VBF_3DRASTERDB_EXPORT_H__


// ����ĺ궨�壬��Ϊ�˵�����dll�����������
#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( VBF_3DRASTERDB_LIBRARY_STATIC )
    #    define VBF_3DRASTERDB_EXPORT
    #  elif defined( VBF_3DRASTERDB_LIBRARY )
    #    define VBF_3DRASTERDB_EXPORT   __declspec(dllexport)
    #  else
    #    define VBF_3DRASTERDB_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define VBF_3DRASTERDB_EXPORT
#endif


#endif