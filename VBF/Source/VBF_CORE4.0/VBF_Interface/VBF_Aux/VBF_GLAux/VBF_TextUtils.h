//***************************************************************************************
// FileName��VBF_TextUtils.h
// Function�����ı��йصĹ��ߺ���
// Author:   ��Ө
// Date:     2014-03-03
//***************************************************************************************

#ifndef __VBF_TEXT_UTILS_H__
#define __VBF_TEXT_UTILS_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Macros.h>
#include <VBF_Engine/VBF_Text/Text>
#include <Types/VBF_3DStyles.h>
#include <string>


// ע��һ�������ļ����ڵ�·�����ú�����ϵͳ���������һ�μ��ɣ�
VBF_GLAUX_EXPORT void VBF_RegisterFontFilePath(const std::string& strPath);


// ��char�͵��ַ���ת����wchar�ͣ��Ա�֧������
VBF_GLAUX_EXPORT bool VBF_StringCharToWChar(const char* szText, wchar_t*& wszText, int* pnNumWchars);


// ��������������simsun���������ļ�������msyh.ttf������ȡ���Ӧ������
VBF_GLAUX_EXPORT osgText::Font* VBF_GetFont(const std::string& strFont);


// �����ַ�����֧�����ģ�
VBF_GLAUX_EXPORT void VBF_SetText(osgText::Text* pText, const std::string& strText);


// �����ı���ʽ
VBF_GLAUX_EXPORT void VBF_SetTextStyle(osgText::Text* pText, const VBF_TEXTSTYLE& style);


#endif
