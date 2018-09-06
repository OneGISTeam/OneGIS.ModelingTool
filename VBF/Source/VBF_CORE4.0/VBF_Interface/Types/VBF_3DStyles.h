//**********************************************************************************
// 文件名：  VBF_3DStyles.h
// 描述：    各种样式的定义
// 作者:     杜莹
// 日期:     2013-06-25
//**********************************************************************************

#ifndef __VBF_3DSTYLES_H__
#define __VBF_3DSTYLES_H__


#include <Types/Vec4f>
#include <string>
#include <VBF_Common/VBF_Math/VBF_Math.h>
#include <Types/VBF_Optional.h>
#include <VBF_Base/ref_ptr>
#include <VBF_Engine/VBF_SceneGraph/Image>


//-------------------------------------------------------------------
// 定义结构体：VBF_POINTSTYLE
// 结构体描述：点样式
//-------------------------------------------------------------------
typedef struct _tagVBFPointStyle
{
    float			fSize;		// 点的大小
    osg::Vec4f		color;		// 点的颜色

    // 构造函数
    _tagVBFPointStyle()
    {
        fSize	= 1.0f;
        color	= osg::Vec4f(1.0f, 0.0f, 0.0f, 1.0f);
    }

    _tagVBFPointStyle& operator=(const _tagVBFPointStyle& src)
    {
        if(this==&src) return *this;

        fSize	= src.fSize;
        color	= src.color;

        return *this;
    }

    bool operator==(const _tagVBFPointStyle& src)
    {
        if(this==&src) return true;

        if(!osg::equivalent(fSize, src.fSize)) return false;
        if(color!=src.color) return false;

        return true;
    }

} VBF_POINTSTYLE;


//-------------------------------------------------------------------
// 定义结构体：VBF_LINESTYLE
// 结构体描述：线样式
//-------------------------------------------------------------------
typedef struct _tagVBFLineStyle
{
	osg::Vec4f			color;				// 线的颜色
	float				fWidth;				// 线的宽度
	int					nStippleFactor;		// 点划线的因子（即glLineStipple()函数的第一个参数，值域为[1, 256]）
	unsigned short		nStipplePattern;	// 点划线的模式（即glLineStipple()函数的第二个参数）

	// 构造函数
	_tagVBFLineStyle()
	{
		color			= osg::Vec4f(1.0f, 0.0f, 0.0f, 1.0f);
		fWidth			= 2.0f;
		nStippleFactor	= 1;
		nStipplePattern	= 0xFFFF;
	}

	_tagVBFLineStyle& operator=(const _tagVBFLineStyle& src)
	{
		if(this==&src) return *this;

		color			= src.color;
		fWidth			= src.fWidth;
		nStippleFactor	= src.nStippleFactor;
		nStipplePattern	= src.nStipplePattern;
		return *this;
	}

	bool operator==(const _tagVBFLineStyle& src)
	{
		if(this==&src) return true;

		if(color!=src.color) return false;
		if(!osg::equivalent(fWidth, src.fWidth)) return false; 
		if(nStipplePattern!=src.nStipplePattern) return false;
		if(nStippleFactor!=src.nStippleFactor) return false;

		return true;
	}

} VBF_LINESTYLE;


//-------------------------------------------------------------------
// 定义结构体：VBF_POLYGON2DSTYLE
// 结构体描述：二维多边形样式
//-------------------------------------------------------------------
typedef struct _tagPolygon2DStyle
{
	bool			bShadowed;			// 是否显示阴影效果
	bool			bOutlined;			// 是否显示轮廓线
	osg::Vec4f		colorFill;			// 填充颜色
	osg::Vec4f		colorOutline;		// 轮廓线颜色（仅当bOutlined=true时有效）
	osg::Vec4f		colorShadow;		// 阴影颜色（仅当bShadowed=true时有效）
	int				nShadowOffset;		// 阴影偏移量（仅当bShadowed=true时有效）

	// 构造函数
	_tagPolygon2DStyle()
	{
		bShadowed		= false;
		bOutlined		= true;
		colorFill		= osg::Vec4f(1.0f, 1.0f, 0.0f, 0.4f);
		colorOutline	= osg::Vec4f(1.0f, 1.0f, 0.0f, 1.0f);
		colorShadow		= osg::Vec4f(0.1f, 0.1f, 0.1f, 0.8f);
		nShadowOffset	= 8;
	}

	_tagPolygon2DStyle& operator=(const _tagPolygon2DStyle& src)
	{
		if(this==&src) return *this;

		bShadowed		= src.bShadowed;
		bOutlined		= src.bOutlined;
		colorFill		= src.colorFill;
		colorOutline	= src.colorOutline;
		colorShadow		= src.colorShadow;
		nShadowOffset	= src.nShadowOffset;

		return *this;
	}

	bool operator==(const _tagPolygon2DStyle& src)
	{
		if(this==&src) return true;

		if(bShadowed!=src.bShadowed) return false;
		if(colorFill!=src.colorFill) return false;
        if(bOutlined!=src.bOutlined) return false;

		if(bOutlined)
		{
			if(colorOutline!=src.colorOutline) return false;
		}

		if(bShadowed)
		{
			if(colorShadow!=src.colorShadow)     return false;
			if(nShadowOffset!=src.nShadowOffset) return false;
		}

		return true;
	}

}VBF_POLYGON2DSTYLE;


//-------------------------------------------------------------------
// 定义结构体：VBF_POLYGON3DSTYLE
// 结构体描述：三维多边形样式
//-------------------------------------------------------------------
typedef struct _tagPolygon3DStyle
{
	osg::Vec4f		colorFill;		// 填充颜色

	// 构造函数
	_tagPolygon3DStyle()
	{
		colorFill	= osg::Vec4f(1.0f, 1.0f, 0.0f, 0.4f);
	}

	_tagPolygon3DStyle& operator=(const _tagPolygon3DStyle& src)
	{
		if(this==&src) return *this;
		
		colorFill	= src.colorFill;
		return *this;
	}

	bool operator==(const _tagPolygon3DStyle& src)
	{
		if(this==&src) return true;
		
		if(colorFill!=src.colorFill) return false;
		return true;
	}

}VBF_POLYGON3DSTYLE;


//-------------------------------------------------------------------
// 定义结构体：VBF_TEXTSTYLE
// 结构体描述：文本样式
//-------------------------------------------------------------------
typedef struct _tagVBFTextStyle
{
	// 字体样式
	std::string		strFontName;	// 字体名（如：simhei，系统会依次查找C:/Windows/Fonts/simhei.ttf和simhei.ttc文件）
	float			fFontSize;		// 字体大小
	unsigned int	nFontResX;		// 字体横向分辨率（注意：分辨率过大会增加渲染负担）
	unsigned int	nFontResY;		// 字体纵向分辨率

	// 文本样式
	osg::Vec4f		colorText;		// 文本颜色
	float			fLineSpacing;	// 行间距（相对于字体高度的倍率）

	// 衬线样式
	bool			bSerif;			// 是否衬线
	osg::Vec4f		colorSerif;		// 衬线颜色
	float			fSerifOffset;	// 衬线偏移量（建议值范围为：[0.03, 0.1]）
	float			fRationHW;// 文字高度与宽度比

	// 构造函数
	_tagVBFTextStyle()
	{
		strFontName		= "simhei";
		fFontSize		= 24.0f;
        nFontResX		= 32;
        nFontResY		= 32;
		fLineSpacing	= 0.4f;
        colorText		= osg::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
		bSerif			= true;
        colorSerif		= osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
		fSerifOffset	= 0.04f;
		fRationHW       = 2.0;
	}

	_tagVBFTextStyle& operator=(const _tagVBFTextStyle& src)
	{
		if(this==&src) return *this;

		strFontName		= src.strFontName;
		fFontSize		= src.fFontSize;
		nFontResX		= src.nFontResX;
		nFontResY		= src.nFontResY;
		fLineSpacing	= src.fLineSpacing;
		colorText		= src.colorText;
		bSerif			= src.bSerif;
		colorSerif		= src.colorSerif;
		fSerifOffset	= src.fSerifOffset;
		fRationHW       = src.fRationHW;
	
		return *this;
	}

	bool operator==(const _tagVBFTextStyle& src)
	{
		if(this==&src) return true;

		if(strFontName!=src.strFontName) return false;
		if(!osg::equivalent(fFontSize, src.fFontSize)) return false;
		if(nFontResX!=src.nFontResX) return false;
		if(nFontResY!=src.nFontResY) return false;
		if(!osg::equivalent(fLineSpacing, src.fLineSpacing)) return false;
		if(colorText!=src.colorText) return false;
        if(bSerif!=src.bSerif) return false;
		if(colorSerif!=src.colorSerif) return false;
		if(!osg::equivalent(fSerifOffset, src.fSerifOffset)) return false;
		if(!osg::equivalent(fRationHW, src.fRationHW)) return false;

		return true;
	}

} VBF_TEXTSTYLE;


//---------------------------------------------------------
// 定义枚举：VBF_CUBEFACE
// 枚举描述：立方体的六个面
//---------------------------------------------------------
enum EVBF_CUBEFACE
{
    VBF_CUBEFACE_POSITIVEX  = 0,    // +x, right
    VBF_CUBEFACE_NEGATIVEX  = 1,    // -x, left
    VBF_CUBEFACE_POSITIVEY  = 2,    // +y, back
    VBF_CUBEFACE_NEGATIVEY  = 3,    // -y, front
    VBF_CUBEFACE_POSITIVEZ  = 4,    // +z, top
    VBF_CUBEFACE_NEGATIVEZ  = 5     // -z, bottom
};


//---------------------------------------------------------
// 定义结构体：VBF_BOUNDINGBOXSTYLE
// 结构体描述：包围盒样式
//---------------------------------------------------------
typedef struct _tagVBFBoundingBoxStyle
{
	// 外观
	osg::Vec4f	color;				// 包围盒颜色
	float		fLineWidth;			// 外围线粗度
    float		fExpand;			// 包围盒外扩倍数（相对于包围盒尺寸，值域为[0.0, 1.0]）

	// 闪烁
	int			nFlickerTimes;		// 闪烁的总次数
	int			nFlickerInterval;	// 两次闪烁之间的间隔 (单位：帧)
	bool		bFlickerAlways;		// 是否一直闪烁

    // 包围盒的六个面的可见性（默认为可见，每个面的枚举值参见EVBF_CUBEFACE）
    bool        bFaceVisible[6];

	_tagVBFBoundingBoxStyle()
	{
		color				= osg::Vec4f(0.0f, 1.0f, 1.0f, 0.2f);
		fLineWidth			= 2.0f;	
		fExpand				= 0.05f;

		nFlickerTimes		= 3;
		nFlickerInterval	= 20;
        bFlickerAlways		= false;

        // 包围盒的六个面的可见性
        for(int i=0; i<6; i++)
        {
            bFaceVisible[i] = true;
        }
	}

	_tagVBFBoundingBoxStyle& operator=(const _tagVBFBoundingBoxStyle& src)
	{
		if(this==&src) return *this;

		color				= src.color;
		fLineWidth			= src.fLineWidth;	
		fExpand				= src.fExpand;

		nFlickerTimes		= src.nFlickerTimes;
		nFlickerInterval	= src.nFlickerInterval;
		bFlickerAlways		= src.bFlickerAlways;

        // 包围盒的六个面的可见性
        for(int i=0; i<6; i++)
        {
            bFaceVisible[i] = src.bFaceVisible[i];
        }

		return *this;
	}

	bool operator==(const _tagVBFBoundingBoxStyle& src)
	{
		if(this==&src) return true;

		if(color!=src.color) return false; 
		if(!osg::equivalent(fLineWidth, src.fLineWidth)) return false;	
		if(!osg::equivalent(fExpand, src.fExpand)) return false;

		if(nFlickerTimes!=src.nFlickerTimes) return false;
		if(nFlickerInterval!=src.nFlickerInterval) return false;
		if(bFlickerAlways!=src.bFlickerAlways) return false;

        // 包围盒的六个面的可见性
        for(int i=0; i<6; i++)
        {
            if(bFaceVisible[i]!=src.bFaceVisible[i]) return false;
        }

		return true;
	}

} VBF_BOUNDINGBOXSTYLE;


//-------------------------------------------------------------------
// 定义枚举：VBF_TEXENV_MODE
// 枚举描述：同时使用顶点颜色与纹理时，二者的混合方式（用于实体部分的着色器）
//-------------------------------------------------------------------
enum EVBF_TEXENV_MODE
{
	VBF_TEXENV_MODULATE		= 0,	// 乘色：     rgba=colorVert*colorTex（默认）
	VBF_TEXENV_REPLACE		= 1,	// 替换：     rgb=colorVert.rgb, a=colorVert.a*colorTex.a
	VBF_TEXENV_DECAL		= 2,	// 贴花：     rgb=mix(colorTex.rgb, colorVert.rgb, colorTex.a), a=colorVert.a
	VBF_TEXENV_ALPHAREPLACE	= 3		// Alpha替换：rgb=colorVert.rgb, a=colorTex.a
};


//-------------------------------------------------------------------
// 定义结构体：VBF_LINETEXSTYLE
// 结构体描述：沿某条折线重复贴的纹理的样式
//-------------------------------------------------------------------
typedef struct _tagVBFLineTexStyle
{
	ref_ptr<osg::Image>		piImage;			// 纹理图像
	bool					bTexToCache;		// 纹理是否放入缓存
	float					fDynSpeed;			// 纹理动态变化的速度，每帧变化一个纹理周期的比例
	osg::Vec4f				color;				// 与纹理相混合的颜色（纹理有可能是黑白色）

	// 顶点颜色与纹理的混合方式
	EVBF_TEXENV_MODE		nTexEnvMode;

	// 可选项（如果用户未设置，系统内部自动计算）
	CVBF_Optional<int>		nCycleLength;		// 纹理图像一个重复周期在屏幕上所占的像素数（默认值为纹理图像的宽度，单位：像素）
	CVBF_Optional<int>		nWidth;				// 线段宽度（默认值为纹理图像的高度，单位：像素）
	CVBF_Optional<int>		nRepeatTimes;		// 纹理重复的次数（如果用户未设置，系统内部自动计算）

	// 构造函数
	_tagVBFLineTexStyle()
	{
		bTexToCache	= false;
		fDynSpeed	= 0.01f;
		color		= osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
		nTexEnvMode	= VBF_TEXENV_MODULATE;
	}

	_tagVBFLineTexStyle& operator=(const _tagVBFLineTexStyle& src)
	{
		if(this==&src) return *this;

		bTexToCache		= src.bTexToCache;
		piImage			= src.piImage;
		fDynSpeed		= src.fDynSpeed;
		color			= src.color;

		nCycleLength	= src.nCycleLength;
		nWidth			= src.nWidth;
		nRepeatTimes	= src.nRepeatTimes;
		nTexEnvMode		= src.nTexEnvMode;

		return *this;
	}

	bool operator==(const _tagVBFLineTexStyle& src)
	{
		if(bTexToCache!=src.bTexToCache) return false;
		if(piImage.get()!=src.piImage.get()) return false;
		if(!osg::equivalent(fDynSpeed, src.fDynSpeed)) return false;
		if(color!=src.color) return false;
		if(nCycleLength!=src.nCycleLength) return false;
		if(nWidth!=src.nWidth) return false;
		if(nRepeatTimes!=src.nRepeatTimes) return false;
		if(nTexEnvMode!=src.nTexEnvMode) return false;

		return true;
	}

} VBF_LINETEXSTYLE;


#endif
