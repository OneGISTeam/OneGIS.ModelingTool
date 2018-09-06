//**********************************************************************************
// 文件名：  VBF_FileNameUtils.h
// 描述：    与文件名有关的工具函数
// 作者:     杜莹
// 日期:     2013-06-24
//**********************************************************************************

#ifndef __VBF_FILE_NAME_UTILS_H__
#define __VBF_FILE_NAME_UTILS_H__


#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>
#include <string>
#include <vector>


/** Gets the parent path from full name (Ex: /a/b/c.Ext => /a/b). */
extern VBF_UTILS_EXPORT std::string VBF_getFilePath(const std::string& filename);

/** Gets the extension without dot (Ex: /a/b/c.Ext => Ext). */
extern VBF_UTILS_EXPORT std::string VBF_getFileExtension(const std::string& filename);

/** Gets the extension including dot (Ex: /a/b/c.Ext => .Ext). */
extern VBF_UTILS_EXPORT std::string VBF_getFileExtensionIncludingDot(const std::string& filename);

/** Gets the lowercase extension without dot (Ex: /a/b/c.Ext => ext). */
extern VBF_UTILS_EXPORT std::string VBF_getLowerCaseFileExtension(const std::string& filename);

/** Gets file name with extension (Ex: /a/b/c.Ext => c.Ext). */
extern VBF_UTILS_EXPORT std::string VBF_getSimpleFileName(const std::string& fileName);

/** Gets file path without last extension (Ex: /a/b/c.Ext => /a/b/c ; file.ext1.ext2 => file.ext1). */
extern VBF_UTILS_EXPORT std::string VBF_getNameLessExtension(const std::string& fileName);

/** Gets file path without \b all extensions (Ex: /a/b/c.Ext => /a/b/c ; file.ext1.ext2 => file). */
extern VBF_UTILS_EXPORT std::string VBF_getNameLessAllExtensions(const std::string& fileName);

/** Gets file name without last extension (Ex: /a/b/c.Ext => c ; file.ext1.ext2 => file.ext1). */
extern VBF_UTILS_EXPORT std::string VBF_getStrippedName(const std::string& fileName);

/** If 'to' is in a subdirectory of 'from' then this function returns the subpath, otherwise it just returns the file name.
  * The function does \b not automagically resolve paths as the system does, so be careful to give canonical paths.
  * However, the function interprets slashes ('/') ans backslashes ('\') as they were equal.
  */
extern VBF_UTILS_EXPORT std::string VBF_getPathRelative(const std::string& from, const std::string& to);

/** Gets root part of a path ("/" or "C:"), or an empty string if none found. */
extern VBF_UTILS_EXPORT std::string VBF_getPathRoot(const std::string& path);

/** Tests if path is absolute, as !VBF_getPathRoot(path).empty(). */
extern VBF_UTILS_EXPORT bool VBF_isAbsolutePath(const std::string& path);


/** Converts forward slashes (/) to back slashes (\). */
extern VBF_UTILS_EXPORT std::string VBF_convertFileNameToWindowsStyle(const std::string& fileName);

/** Converts back slashes (\) to forward slashes (/). */
extern VBF_UTILS_EXPORT std::string VBF_convertFileNameToUnixStyle(const std::string& fileName);
extern VBF_UTILS_EXPORT std::string VBF_convertToLowerCase(const std::string& fileName);

const char UNIX_PATH_SEPARATOR    = '/';
const char WINDOWS_PATH_SEPARATOR = '\\';

/** Get the path separator for the current platform. */
extern VBF_UTILS_EXPORT char VBF_getNativePathSeparator();

/** Check if the path contains only the current platform's path separators. */
extern VBF_UTILS_EXPORT bool VBF_isFileNameNativeStyle(const std::string& fileName);

/** Convert the path to contain only the current platform's path separators. */
extern VBF_UTILS_EXPORT std::string VBF_convertFileNameToNativeStyle(const std::string& fileName);

extern VBF_UTILS_EXPORT bool VBF_equalCaseInsensitive(const std::string& lhs,const std::string& rhs);
extern VBF_UTILS_EXPORT bool VBF_equalCaseInsensitive(const std::string& lhs,const char* rhs);

// 判断一个路径字符串中是否包含局域网地址
extern VBF_UTILS_EXPORT bool VBF_containsLANAddress(const std::string& filename);

extern VBF_UTILS_EXPORT bool VBF_containsServerAddress(const std::string& filename);
extern VBF_UTILS_EXPORT std::string VBF_getServerProtocol(const std::string& filename);
extern VBF_UTILS_EXPORT std::string VBF_getServerAddress(const std::string& filename);
extern VBF_UTILS_EXPORT std::string VBF_getServerFileName(const std::string& filename);

/** Concatenates two paths */
extern VBF_UTILS_EXPORT std::string VBF_concatPaths(const std::string& left, const std::string& right);

/** Removes .. and . dirs in a path */
extern VBF_UTILS_EXPORT std::string VBF_getRealPath(const std::string& path);

/** Splits a path into elements between separators (including Windows' root, if any). */
extern VBF_UTILS_EXPORT void VBF_getPathElements(const std::string& path, std::vector<std::string> & out_elements);


#endif
