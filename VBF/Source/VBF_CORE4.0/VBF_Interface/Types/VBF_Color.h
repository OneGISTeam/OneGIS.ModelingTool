//**********************************************************************************
// 文件名：  VBF_Color.h
// 描述：    定义基本数据类型：颜色
// 作者:     杜莹
// 日期:     2013-07-01
//**********************************************************************************

#ifndef __VBF_COLOR_H__
#define __VBF_COLOR_H__



#include <VBF_Common/VBF_Math/VBF_Export.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <Types/Vec4f>

#include <string>



struct VBF_MATH_EXPORT VBFCOLOR : public osg::Vec4f
{
public:
    enum Format 
	{
        RGBA,
        ABGR
    };
    
    VBFCOLOR() : osg::Vec4f(1,1,1,1) { }	/** Creates a new default color */
    VBFCOLOR(const VBFCOLOR& rhs) : osg::Vec4f(rhs) { }	/** Copy constructor */
    VBFCOLOR(const osg::Vec4f& rgba) : osg::Vec4f(rgba) { } /** Make from vec4 */
    VBFCOLOR(float r, float g, float b, float a = 1.0f): osg::Vec4f(r, g, b, a) { } /** Component constructor */

	 /** Copy constructor with modified alpha value */
    VBFCOLOR(const VBFCOLOR& rhs, float a);

    /** RGBA/ABGR constructor */
    VBFCOLOR(unsigned value, Format format=RGBA);

    /**
        * Construct a color from a hex string in one of the following formats, (with or
        * without the component order reversed):
        *   RRGGBB or RRGGBBAA
        *   #RRGGBB or #RRGGBBAA (HTML style - preceding hash)
        *   0xRRGGBB or 0xRRGGBBAA (C style - preceding "0x")
        */
    VBFCOLOR(const std::string& html, Format format=RGBA);

    virtual ~VBFCOLOR() { }

    /** Encode the color at an HTML color string (e.g., "#FF004F78") */
    std::string toHTML( Format format =RGBA ) const;

    /** Dump out the color as a 32-bit integer */
    unsigned as(Format format) const;

    /** Lighten/darken the color by factor */
    VBFCOLOR brightness(float factor) const;

    // built in colors
    // http://en.wikipedia.org/wiki/Web_colors#HTML_color_names

    static const VBFCOLOR White;
    static const VBFCOLOR Silver;
    static const VBFCOLOR Gray;
    static const VBFCOLOR Black;
    static const VBFCOLOR Red;
    static const VBFCOLOR Maroon;
    static const VBFCOLOR Yellow;
    static const VBFCOLOR Olive;
    static const VBFCOLOR Lime;
    static const VBFCOLOR Green;
    static const VBFCOLOR Aqua;
    static const VBFCOLOR Teal;
    static const VBFCOLOR Blue;
    static const VBFCOLOR Navy;
    static const VBFCOLOR Fuchsia;
    static const VBFCOLOR Purple;
    static const VBFCOLOR Orange;

    // others:
    static const VBFCOLOR Cyan;
    static const VBFCOLOR DarkGray;
    static const VBFCOLOR Magenta;
    static const VBFCOLOR Brown;
};

// CVBF_Config specializations for VBFCOLOR:

template <> inline
void CVBF_Config::addIfSet<VBFCOLOR>(const std::string& key, const CVBF_Optional<VBFCOLOR>& opt) 
{
    if ( opt.isSet() ) 
	{
        add( key, opt->toHTML() );
    }
}

template<> inline
void CVBF_Config::updateIfSet<VBFCOLOR>( const std::string& key, const CVBF_Optional<VBFCOLOR>& opt ) 
{
    if ( opt.isSet() ) 
	{
        remove( key );
        add( key, opt->toHTML() );
    }
}

template<> inline
bool CVBF_Config::getIfSet<VBFCOLOR>( const std::string& key, CVBF_Optional<VBFCOLOR>& output ) const 
{
    if ( hasValue( key ) ) 
	{
        output = VBFCOLOR( value(key) );
		return true; 
    }
    else
        return false;
}

// 全局函数：
VBF_MATH_EXPORT void VBF_RGB_TO_HSV(osg::Vec4f& c);
VBF_MATH_EXPORT void VBF_HSV_TO_RGB(osg::Vec4f& c);

#endif
