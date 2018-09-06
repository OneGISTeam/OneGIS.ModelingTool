//*******************************************************************
// FileName：  VBF_ReadWrite.h
// Function：  与读写有关的内联函数
// Author:     杜莹
// Date:       2014-06-03
//*******************************************************************

#ifndef __VBF_READ_WRITE_H__
#define __VBF_READ_WRITE_H__


#include <stdio.h>
#include <VBF_Macros.h>
#include <VBF_STL.h>
#include <VBF_Symbol/MCE_SymbolTemplLib/VBF_WinGDI.h>


// 从文件中读取一个CString字符串，存储到std::string类型的变量中
inline bool ReadString(FILE* fp, std::string& var)
{
	if(NULL==fp || feof(fp)) return false;

	return true;
}

// 从文件中读取一个BYTE型变量
inline bool ReadBYTE(FILE* fp, BYTE& var)
{
	if(NULL==fp || feof(fp)) return false;

	fread(&var, sizeof(BYTE), 1, fp);

	return true;
}

// 从文件中读取一个int型变量
inline bool ReadInt(FILE* fp, int& var)
{
	if(NULL==fp || feof(fp)) return false;

	fread(&var, sizeof(int), 1, fp);

	return true;
}

// 从文件中读取一个UINT型变量
inline bool ReadUINT(FILE* fp, UINT& var)
{
	if(NULL==fp || feof(fp)) return false;

	fread(&var, sizeof(UINT), 1, fp);

	return true;
}

// 从文件中读取一个DWORD型变量
inline bool ReadDWORD(FILE* fp, DWORD& var)
{
	if(NULL==fp || feof(fp)) return false;

	fread(&var, sizeof(DWORD), 1, fp);

	return true;
}

// 从文件中读取一个COLORREF型变量，存储到DWORD型变量
inline bool ReadColor(FILE* fp, COLORREF& var)
{
	if(NULL==fp || feof(fp)) return false;
	
	fread(&var, sizeof(COLORREF), 1, fp);

	return true;
}

typedef int BOOL;

// 从文件中读取一个BOOL型变量，存储到bool型变量中
inline bool ReadBool(FILE* fp, bool& var)
{
	if(NULL==fp || feof(fp)) return false;

	BOOL bValue = 0;
	fread(&bValue, sizeof(BOOL), 1, fp);

	var = (bValue==1);

	return true;
}

#endif 
