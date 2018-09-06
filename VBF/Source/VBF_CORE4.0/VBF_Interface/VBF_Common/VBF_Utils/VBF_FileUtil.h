//*******************************************************************
// FileName：  VBF_FileUtil.h
// Function：  封装工具库中常用的文件函数(.h文件)
// Author:     杜莹
// Date:       2004.10.23
// Note:       由于全部是工具型函数，所以全部使用静态函数，
//             且不需要构造函数和析构函数
//*******************************************************************


#ifndef __VBF_FILE_UTIL_H__
#define __VBF_FILE_UTIL_H__

#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>
#include "VBF_STL.h"
#include "VBF_Macros.h"
#include <stdio.h>

class VBF_UTILS_EXPORT CVBF_FileUtil  
{
public:

	static string   GetFileTitle(const string& strFullFn);
	static bool     IsFileExist(const string& strFullFn);
	static bool     IsPathExist(const string& strRelPathDir);
	static string   GetFilePath(const string& strFullFn);	
	static string   GetFileExt(const string& strFullFn);
	static long		GetFileLength(FILE* fp);
};

#endif 
