//*******************************************************************
// FileName��  VBF_ReadWrite.h
// Function��  ���д�йص���������
// Author:     ��Ө
// Date:       2014-06-03
//*******************************************************************

#ifndef __VBF_READ_WRITE_H__
#define __VBF_READ_WRITE_H__


#include <stdio.h>
#include <VBF_Macros.h>
#include <VBF_STL.h>
#include <VBF_Symbol/MCE_SymbolTemplLib/VBF_WinGDI.h>


// ���ļ��ж�ȡһ��CString�ַ������洢��std::string���͵ı�����
inline bool ReadString(FILE* fp, std::string& var)
{
	if(NULL==fp || feof(fp)) return false;

	return true;
}

// ���ļ��ж�ȡһ��BYTE�ͱ���
inline bool ReadBYTE(FILE* fp, BYTE& var)
{
	if(NULL==fp || feof(fp)) return false;

	fread(&var, sizeof(BYTE), 1, fp);

	return true;
}

// ���ļ��ж�ȡһ��int�ͱ���
inline bool ReadInt(FILE* fp, int& var)
{
	if(NULL==fp || feof(fp)) return false;

	fread(&var, sizeof(int), 1, fp);

	return true;
}

// ���ļ��ж�ȡһ��UINT�ͱ���
inline bool ReadUINT(FILE* fp, UINT& var)
{
	if(NULL==fp || feof(fp)) return false;

	fread(&var, sizeof(UINT), 1, fp);

	return true;
}

// ���ļ��ж�ȡһ��DWORD�ͱ���
inline bool ReadDWORD(FILE* fp, DWORD& var)
{
	if(NULL==fp || feof(fp)) return false;

	fread(&var, sizeof(DWORD), 1, fp);

	return true;
}

// ���ļ��ж�ȡһ��COLORREF�ͱ������洢��DWORD�ͱ���
inline bool ReadColor(FILE* fp, COLORREF& var)
{
	if(NULL==fp || feof(fp)) return false;
	
	fread(&var, sizeof(COLORREF), 1, fp);

	return true;
}

typedef int BOOL;

// ���ļ��ж�ȡһ��BOOL�ͱ������洢��bool�ͱ�����
inline bool ReadBool(FILE* fp, bool& var)
{
	if(NULL==fp || feof(fp)) return false;

	BOOL bValue = 0;
	fread(&bValue, sizeof(BOOL), 1, fp);

	var = (bValue==1);

	return true;
}

#endif 
