//*******************************************************************
// FileName��  VBF_FileUtil.h
// Function��  ��װ���߿��г��õ��ļ�����(.h�ļ�)
// Author:     ��Ө
// Date:       2004.10.23
// Note:       ����ȫ���ǹ����ͺ���������ȫ��ʹ�þ�̬������
//             �Ҳ���Ҫ���캯������������
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
