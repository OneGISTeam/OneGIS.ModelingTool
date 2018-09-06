//**********************************************************************************
// 文件名：  VBF_StringUtils.h
// 描述：    与字符串有关的工具函数
// 作者:     杜莹
// 日期:     2013-06-24
//**********************************************************************************

#ifndef __VBF_STRING_UTILS_H__
#define __VBF_STRING_UTILS_H__


#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>
#include <Types/Vec3>
#include <Types/Vec3d>
#include <Types/Vec4>
#include <Types/Vec4d>
#include <Types/Vec4ub>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <locale>
#include <iomanip>
#include <map>
#include <ctype.h>
#include <assert.h>

extern VBF_UTILS_EXPORT std::wstring VBF_StringC2W(const char *pc);
extern VBF_UTILS_EXPORT std::string VBF_StringW2C(const wchar_t * pw);

extern VBF_UTILS_EXPORT const std::string VBF_EMPTY_STRING;

typedef std::vector<std::string> StringVector;

/** Replaces all the instances of "pattern" with "replacement" in "in_out" */
extern VBF_UTILS_EXPORT std::string& VBF_replaceIn(std::string& in_out, 
												   const std::string& pattern, 
												   const std::string& replacement );

/** Replaces all the instances of "pattern" with "replacement" in "in_out" (case-insensitive) */
extern VBF_UTILS_EXPORT std::string& VBF_ciReplaceIn(std::string&       in_out, 
												 const std::string& pattern, 
												 const std::string& replacement );

/**
* Trims whitespace from the ends of a string.
*/
extern VBF_UTILS_EXPORT std::string VBF_trim(const std::string& in);

/**
* True is "ref" starts with "pattern"
*/
extern VBF_UTILS_EXPORT bool VBF_startsWith(const std::string& ref, 
										const std::string& pattern, 
										bool               caseSensitive =true,
										const std::locale& locale        =std::locale());

/**
    * True is "ref" ends with "pattern"
    */
extern VBF_UTILS_EXPORT bool VBF_EndsWith(const std::string& ref, 
									  const std::string& pattern, 
									  bool               caseSensitive =true,
									  const std::locale& locale=std::locale());

/**
    * Case-insensitive compare
    */
extern VBF_UTILS_EXPORT bool VBF_ciEquals(const std::string& lhs,
									  const std::string& rhs,
									  const std::locale& local = std::locale() );


extern VBF_UTILS_EXPORT std::string VBF_joinStrings( const StringVector& input, char delim );

/** Returns a lower-case version of the input string. */
extern VBF_UTILS_EXPORT std::string VBF_toLower( const std::string& input );

// 字符串转换为OSG color "255 255 255 255" (r g b a [0..255])
extern VBF_UTILS_EXPORT osg::Vec4ub VBF_stringToColor(const std::string& str, osg::Vec4ub default_value);
extern VBF_UTILS_EXPORT std::string VBF_colorToString( const osg::Vec4ub& c );

// 字符串转换为vec2f "x y"
extern VBF_UTILS_EXPORT osg::Vec2f VBF_stringToVec2f( const std::string& str, const osg::Vec2f& default_value );
extern VBF_UTILS_EXPORT std::string VBF_vec2fToString( const osg::Vec2f& v );

// 字符串转换为vec3f "x y z"
extern VBF_UTILS_EXPORT osg::Vec3f VBF_stringToVec3f( const std::string& str, const osg::Vec3f& default_value );
extern VBF_UTILS_EXPORT std::string VBF_vec3fToString( const osg::Vec3f& v );

// 字符串转换为vec4f "x y z w"
extern VBF_UTILS_EXPORT osg::Vec4f VBF_stringToVec4f( const std::string& str, const osg::Vec4f& default_value );
extern VBF_UTILS_EXPORT std::string VBF_vec4fToString( const osg::Vec4f& v );

// 字符串转换为vec2d "x y"
extern VBF_UTILS_EXPORT osg::Vec2d VBF_stringToVec2d( const std::string& str, const osg::Vec2d& default_value );
extern VBF_UTILS_EXPORT std::string VBF_vec2dToString( const osg::Vec2d& v );

// 字符串转换为vec3d "x y z"
extern VBF_UTILS_EXPORT osg::Vec3d VBF_stringToVec3d( const std::string& str, const osg::Vec3d& default_value );
extern VBF_UTILS_EXPORT std::string VBF_vec3dToString( const osg::Vec3d& v );

// 字符串转换为vec4d "x y z w"
extern VBF_UTILS_EXPORT osg::Vec4d VBF_stringToVec4d( const std::string& str, const osg::Vec4d& default_value );
extern VBF_UTILS_EXPORT std::string VBF_vec4dToString( const osg::Vec4d& v );

/** Parses an HTML color ("#rrggbb" or "#rrggbbaa") into an OSG color. */
extern VBF_UTILS_EXPORT osg::Vec4f VBF_htmlColorToVec4f( const std::string& html );

/** Makes an HTML color ("#rrggbb" or "#rrggbbaa") from an OSG color. */
extern VBF_UTILS_EXPORT std::string VBF_vec4fToHtmlColor( const osg::Vec4f& c );

/** Makes a valid filename, hopefully, out of a string (without touching slashes) */
extern VBF_UTILS_EXPORT std::string VBF_toLegalFileName( const std::string& input );

/** Generates a hashed integer for a string (poor man's MD5) */
extern VBF_UTILS_EXPORT unsigned VBF_hashString( const std::string& input );

    
//------------------------------------------------------------------------
// conversion templates

// converts a string to primitive using serialization
template<typename T> 
inline T VBF_as( const std::string& str, const T& default_value )
{
    T temp = default_value;
    std::istringstream strin( str );
    if ( !strin.eof() ) strin >> temp;
    return temp;
}

// template specialization for a bool
template<> 
inline bool VBF_as<bool>( const std::string& str, const bool& default_value )
{
    std::string temp = str;
    std::transform( temp.begin(), temp.end(), temp.begin(), ::tolower );
    return
        temp == "true" || temp == "yes" || temp == "on" ? true :
        temp == "false" || temp == "no" || temp == "off" ? false :
        default_value;
}

// 将字符串转换为vec2f（杜莹添加：2017-07-16）
template<> 
inline osg::Vec2f VBF_as<osg::Vec2f>( const std::string& str, const osg::Vec2f& default_value )
{
    return VBF_stringToVec2f(str, default_value);
}

template<> 
inline osg::Vec3f VBF_as<osg::Vec3f>( const std::string& str, const osg::Vec3f& default_value )
{
    return VBF_stringToVec3f(str, default_value);
}

// 将字符串转换为Vec4f（杜莹添加：2017-07-16）
template<>
inline osg::Vec4f VBF_as<osg::Vec4f>( const std::string& str, const osg::Vec4f& default_value )
{
    return VBF_stringToVec4f(str, default_value);
}

template<>
inline osg::Vec2d VBF_as<osg::Vec2d>( const std::string& str, const osg::Vec2d& default_value )
{
    return VBF_stringToVec2d(str, default_value);
}

template<>
inline osg::Vec3d VBF_as<osg::Vec3d>( const std::string& str, const osg::Vec3d& default_value )
{
    return VBF_stringToVec3d(str, default_value);
}

template<>
inline osg::Vec4d VBF_as<osg::Vec4d>( const std::string& str, const osg::Vec4d& default_value )
{
    return VBF_stringToVec4d(str, default_value);
}

// template specialization for string
template<> 
inline std::string VBF_as<std::string>( const std::string& str, const std::string& default_value )
{
    return str;
}

// snips a substring and parses it.
template<typename T> 
inline bool VBF_as(const std::string& in, unsigned start, unsigned len, T default_value) 
{
    std::string buf;
    std::copy( in.begin()+start, in.begin()+start+len, std::back_inserter(buf) );
    return VBF_as<T>(buf, default_value);
}

// converts a primitive to a string
// TODO: precision??
template<typename T>
inline std::string VBF_toString(const T& value)
{
    std::stringstream out;
	out << std::setprecision(20) <<  value;
    std::string outStr;
    outStr = out.str();
    return outStr;
}

// template speciallization for a bool to print out "true" or "false"
template<> 
inline std::string VBF_toString<bool>(const bool& value)
{
    return value ? "true" : "false";
}

template<> 
inline std::string VBF_toString<osg::Vec3f>(const osg::Vec3f& value)
{
    return VBF_vec3fToString(value);
}
template<>
inline std::string VBF_toString<osg::Vec3d>(const osg::Vec3d& value)
{
    return VBF_vec3dToString(value);
}
/**
    * Assembles and returns an inline string using a stream-like << operator.
    * Example: 
    *     std::string str = CVBF_Stringify() << "Hello, world " << variable;
    */
struct CVBF_Stringify
{
    operator std::string () const
    {
        std::string result;
        result = m_buf.str();
        return result;
    }

    template<typename T>
    CVBF_Stringify& operator << (const T& val)				{ m_buf << val; return (*this); }

    CVBF_Stringify& operator << (const CVBF_Stringify& val)	{ m_buf << (std::string)val; return (*this); }

protected:
    std::stringstream	m_buf;
};

template<> inline CVBF_Stringify& CVBF_Stringify::operator << <bool>(const bool& val)					{ m_buf << (val ? "true" : "false"); return (*this); }
template<> inline CVBF_Stringify& CVBF_Stringify::operator << <osg::Vec3f>(const osg::Vec3f& val)		{ m_buf << val.x() << " " << val.y() << " " << val.z(); return (*this); }
template<> inline CVBF_Stringify& CVBF_Stringify::operator << <osg::Vec3d>(const osg::Vec3d& val )	{ m_buf << val.x() << " " << val.y() << " " << val.z(); return (*this); }
template<> inline CVBF_Stringify& CVBF_Stringify::operator << <osg::Vec4f>(const osg::Vec4f& val)		{ m_buf << val.r() << " " << val.g() << " " << val.b() << " " << val.a(); return (*this); }

/**
    * Splits a string up into a vector of strings based on a set of 
    * delimiters, quotes, and rules.
    */
class VBF_UTILS_EXPORT CVBF_StringTokenizer
{
public:
    CVBF_StringTokenizer( const std::string& delims =" \t\r\n", const std::string& quotes ="'\"" );

    CVBF_StringTokenizer(
        const std::string& input, StringVector& output,
        const std::string& delims =" \t\r\n", const std::string& quotes ="'\"",
        bool keepEmpties =true, bool trimTokens =true);

    void tokenize( const std::string& input, StringVector& output ) const;

    bool& keepEmpties() { return _allowEmpties; }
    bool& trimTokens() { return _trimTokens; }

    void addDelim( char delim, bool keepAsToken =false );
    void addDelims( const std::string& delims, bool keepAsTokens =false );
    void addQuote( char delim, bool keepInToken =false );
    void addQuotes( const std::string& delims, bool keepInTokens =false );
        
private:
    typedef std::map<char,bool> TokenMap;

    TokenMap		_delims;
    TokenMap		_quotes;
    bool			_allowEmpties;
    bool			_trimTokens;
};


#endif 

