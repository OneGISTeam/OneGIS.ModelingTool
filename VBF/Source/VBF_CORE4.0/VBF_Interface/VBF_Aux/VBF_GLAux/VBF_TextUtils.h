//***************************************************************************************
// FileName：VBF_TextUtils.h
// Function：与文本有关的工具函数
// Author:   杜莹
// Date:     2014-03-03
//***************************************************************************************

#ifndef __VBF_TEXT_UTILS_H__
#define __VBF_TEXT_UTILS_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Macros.h>
#include <VBF_Engine/VBF_Text/Text>
#include <Types/VBF_3DStyles.h>
#include <string>


// 注册一个字体文件所在的路径（该函数在系统启动后调用一次即可）
VBF_GLAUX_EXPORT void VBF_RegisterFontFilePath(const std::string& strPath);


// 把char型的字符串转换成wchar型，以便支持中文
VBF_GLAUX_EXPORT bool VBF_StringCharToWChar(const char* szText, wchar_t*& wszText, int* pnNumWchars);


// 根据字体名（如simsun）或字体文件名（如msyh.ttf），获取其对应的字体
VBF_GLAUX_EXPORT osgText::Font* VBF_GetFont(const std::string& strFont);


// 设置字符串（支持中文）
VBF_GLAUX_EXPORT void VBF_SetText(osgText::Text* pText, const std::string& strText);


// 设置文本样式
VBF_GLAUX_EXPORT void VBF_SetTextStyle(osgText::Text* pText, const VBF_TEXTSTYLE& style);


#endif
