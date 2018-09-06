//**********************************************************************************
// 文件名：  VBF_FileUtils.h
// 描述：    与文件有关的工具函数
// 作者:     杜莹
// 日期:     2013-06-24
//**********************************************************************************

#ifndef __VBF_FILE_UTILS_H__
#define __VBF_FILE_UTILS_H__


#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>
#include <Types/VBF_PublicTypes.h>
#include <vector>
#include <deque>
#include <string>
#include <stdio.h>


/** Overload of the standard fopen function. If OSG_USE_UTF8_FILENAME is defined,
  * filename will be expanded from UTF8 to UTF16 and _wfopen will be called. */
extern VBF_UTILS_EXPORT FILE* VBF_fopen(const char* filename, const char* mode);

/** Make a new directory.  Returns true if directory exists or was created. */
extern VBF_UTILS_EXPORT bool VBF_makeDirectory( const std::string &directoryPath );

// 为给定的文件创建一个新的路径
extern VBF_UTILS_EXPORT bool VBF_makeDirectoryForFile( const std::string &filePath );
    
// 获取/设置当前工作路径
extern VBF_UTILS_EXPORT std::string VBF_getCurrentWorkingDirectory( void );
extern VBF_UTILS_EXPORT bool VBF_setCurrentWorkingDirectory( const std::string &newCurrentWorkingDirectory );


/** return true if a file exists. */
extern VBF_UTILS_EXPORT bool VBF_fileExists(const std::string& filename);

enum EVBF_FILETYPE
{
    VBF_FILETYPE_FILE_NOT_FOUND,
    VBF_FILETYPE_REGULAR_FILE,
    VBF_FILETYPE_DIRECTORY
};


/** list of directories to search through which searching for files. */
typedef std::deque<std::string> VBF_FilePathList;

/** return type of file. */
extern VBF_UTILS_EXPORT EVBF_FILETYPE VBF_fileType(const std::string& filename);

/** find specified file in specified file path.*/
extern VBF_UTILS_EXPORT std::string VBF_findFileInPath(const std::string& filename, const VBF_FilePathList& filePath, EVBF_CASESENSITIVITY caseSensitivity=VBF_CASE_SENSITIVE);

/** return the directory/filename of a file if its is contained within specified directory.
  * return "" if directory does not contain file.  If caseInsensitive is set to true then
  * a case insensitive comparison is used to compare fileName to directory contents.
  * This is useful when unix programs attempt read case insensitive windows filenames.
  */
extern VBF_UTILS_EXPORT std::string VBF_findFileInDirectory(const std::string& fileName,const std::string& dirName,EVBF_CASESENSITIVITY caseSensitivity=VBF_CASE_SENSITIVE);

/** simple list of names to represent a directory's contents. */
typedef std::vector<std::string> CVBF_DirectoryContents;

/** Return the contents of a directory.
  * Return value will contain filenames only, not absolute paths.
  * Returns an empty array on any error.*/
extern VBF_UTILS_EXPORT CVBF_DirectoryContents VBF_getDirectoryContents(const std::string& dirName);

/** Return the list of filenames that match the given filename with wildcards.
  * Will only expand '*', and will not expand wildcards in directory, only in 
  * filename part of the given filename. 
  * Return value will contain path+filename so that if ever the above 
  * limitation (expanding wildcards in directory) is fixed, client code will 
  * still work unchanged. */
extern VBF_UTILS_EXPORT CVBF_DirectoryContents VBF_expandWildcardsInFilename(const std::string& filename);


enum EVBF_FILEOP_RESULT
{
    VBF_FILEOP_RESULT_OK,                          /**< Operation done. */
    VBF_FILEOP_RESULT_SOURCE_EQUALS_DESTINATION,   /**< Operation is useless (source == destination). */
    VBF_FILEOP_RESULT_BAD_ARGUMENT,
    VBF_FILEOP_RESULT_SOURCE_MISSING,              /**< Source file doesn't exist. */
    VBF_FILEOP_RESULT_SOURCE_NOT_OPENED,           /**< Error opening source file. */
    VBF_FILEOP_RESULT_DESTINATION_NOT_OPENED,      /**< Error opening destination file. */
    VBF_FILEOP_RESULT_READ_ERROR,
    VBF_FILEOP_RESULT_WRITE_ERROR
};


/** Copy a file to another location, overwriting if necessary.
  * You must provide full path for both source and destination.
  * \return true on success, or if source and destination are the same.
  * \todo Replace the implementation with filesystem functions from TR2 when available.
*/
extern VBF_UTILS_EXPORT EVBF_FILEOP_RESULT VBF_copyFile(const std::string & source, const std::string & destination);

/** convert a string containing a list of paths delimited either with ';' (Windows) or ':' (All other platforms) into FilePath representation.*/
extern VBF_UTILS_EXPORT void VBF_convertStringPathIntoFilePathList(const std::string& paths,VBF_FilePathList& filepath);

extern VBF_UTILS_EXPORT void VBF_appendPlatformSpecificLibraryFilePaths(VBF_FilePathList& filepath);
extern VBF_UTILS_EXPORT void VBF_appendPlatformSpecificResourceFilePaths(VBF_FilePathList& filepath);

/**
    * Determines whether a given filename is a relative path
    */
extern VBF_UTILS_EXPORT bool VBF_isRelativePath(const std::string& fileName);

/**
    * Gets the full path of a file relative to a file
    * For example, getFullPath("c:\images\vacation.jpg", "..") would return "c:\images".
    * If relativePath is an absolute path, it is returned
    *
    * @param relativeTo
    *       The name of the file to make the path relative to
    * @param relativePath
    *       The path relative to relativeTo
    * @returns
    *       The full path
    */
extern VBF_UTILS_EXPORT std::string VBF_getFullPath(const std::string& relativeTo, const std::string& relativePath );


/**
    * Gets whether or not the given path contains a zip file within the path
    */
extern VBF_UTILS_EXPORT bool VBF_isZipPath(const std::string& path);

/**
    * Gets the path to the temp directory
    */
extern VBF_UTILS_EXPORT std::string VBF_getTempPath();

/**
    * Gets a temporary filename
    * @param prefix
    *        The prefix of the temporary filename
    * @param suffix
    *        The suffix of the temporary filename
    */
    extern VBF_UTILS_EXPORT std::string VBF_getTempName(const std::string& prefix="", const std::string& suffix="");

extern VBF_UTILS_EXPORT bool VBF_containsCurrentWorkingDirectoryReference(const VBF_FilePathList& paths);

// 获取执行程序所在路径
extern VBF_UTILS_EXPORT std::string VBF_GetExePath();
//extern VBF_UTILS_EXPORT std::string VBF_GetDllPath(LPCWSTR );
#endif
