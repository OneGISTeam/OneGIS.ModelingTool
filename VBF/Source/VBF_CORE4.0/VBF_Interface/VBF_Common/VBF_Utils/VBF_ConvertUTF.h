//**********************************************************************************
// 文件名：  VBF_ConvertUTF.h
// 描述：    与字符串编码转换有关的工具函数
// 作者:     杜莹
// 日期:     2013-06-24
//**********************************************************************************

#ifndef __VBF_CONVERT_UTF_H__
#define __VBF_CONVERT_UTF_H__

#include <VBF_Config.h>
#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>

#include <string>

#if defined(__CYGWIN__) || defined(ANDROID)
	namespace std
	{
		typedef basic_string<wchar_t> wstring;
	}
#endif


extern VBF_UTILS_EXPORT std::string  convertUTF16toUTF8(const wchar_t* source, unsigned sourceLength);
extern VBF_UTILS_EXPORT std::wstring convertUTF8toUTF16(const char* source, unsigned sourceLength);

extern VBF_UTILS_EXPORT std::string convertUTF16toUTF8(const std::wstring& s);
extern VBF_UTILS_EXPORT std::string convertUTF16toUTF8(const wchar_t* s);

extern VBF_UTILS_EXPORT std::wstring convertUTF8toUTF16(const std::string& s);
extern VBF_UTILS_EXPORT std::wstring convertUTF8toUTF16(const char* s);

extern VBF_UTILS_EXPORT std::string convertStringFromCurrentCodePageToUTF8(const char* source, unsigned sourceLength);
extern VBF_UTILS_EXPORT std::string convertStringFromUTF8toCurrentCodePage(const char* source, unsigned sourceLength);

extern VBF_UTILS_EXPORT std::string convertStringFromCurrentCodePageToUTF8(const std::string& s);
extern VBF_UTILS_EXPORT std::string convertStringFromCurrentCodePageToUTF8(const char* s);

extern VBF_UTILS_EXPORT std::string convertStringFromUTF8toCurrentCodePage(const std::string& s);
extern VBF_UTILS_EXPORT std::string convertStringFromUTF8toCurrentCodePage(const char* s);


#endif
