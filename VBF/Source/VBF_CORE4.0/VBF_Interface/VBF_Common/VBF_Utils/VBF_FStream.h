//**********************************************************************************
// 文件名：  VBF_FStream.h
// 描述：    与文件流有关的工具函数
// 作者:     杜莹
// 日期:     2013-06-24
//**********************************************************************************

#ifndef __VBF_FILE_STREAM_H__
#define __VBF_FILE_STREAM_H__


#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>
#include <fstream>


/**
* Replacements for std::fstream, std::ifstream, and std::ofstream to
* automatically handle UTF-8 to UTF-16 filename conversion. Always use one
* of these classes in any OpenSceneGraph code instead of the STL equivalent.
*/

class VBF_UTILS_EXPORT CVBF_FStream : public std::fstream
{
public:
    CVBF_FStream();
    explicit CVBF_FStream(const char* filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out);
    ~CVBF_FStream();

    void open(const char* filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out);
};

class VBF_UTILS_EXPORT CVBF_FStreamIn : public std::ifstream
{
public:
    CVBF_FStreamIn();
    explicit CVBF_FStreamIn(const char* filename, std::ios_base::openmode mode = std::ios_base::in);
    ~CVBF_FStreamIn();

    void open(const char* filename, std::ios_base::openmode mode = std::ios_base::in);
};

class VBF_UTILS_EXPORT CVBF_FStreamOut : public std::ofstream
{
public:
    CVBF_FStreamOut();
    explicit CVBF_FStreamOut(const char* filename, std::ios_base::openmode mode = std::ios_base::out);
    ~CVBF_FStreamOut();

    void open(const char* filename, std::ios_base::openmode mode = std::ios_base::out);
};


#endif
