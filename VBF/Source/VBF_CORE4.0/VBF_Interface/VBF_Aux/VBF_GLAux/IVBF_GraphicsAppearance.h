//*******************************************************************
// FileName：IVBF_GraphicsAppearance.h
// Function：各种自定义图形的外观属性
// Author:   杜莹
// Date:     2013-11-11
//*******************************************************************

#ifndef __IVBF_APPEARANCE_ATTR_H__
#define __IVBF_APPEARANCE_ATTR_H__


#include <Types/Vec4>
#include <string>
#include <vector>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <Types/VBF_3DStyles.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_GEOMETRY_STYLE
// 接口描述：自定义图形的几何样式，可以是如下枚举值的单个
//--------------------------------------------------------------------
enum EVBF_GEOMETRY_STYLE
{
	VBF_GEOMETRY_STYLE_SOLID		= 0x01,		// 只绘制实体
	VBF_GEOMETRY_STYLE_WIREFRAME	= 0x02,		// 只绘制网格
	VBF_GEOMETRY_STYLE_COMPOSITE	= (VBF_GEOMETRY_STYLE_SOLID | VBF_GEOMETRY_STYLE_WIREFRAME)		// 同时绘制实心和网格
};

//--------------------------------------------------------------------
// 定义枚举：EVBF_SHADE_STYLE
// 接口描述：自定义图形的着色方式，可以是如下枚举值的单个
//--------------------------------------------------------------------
enum EVBF_SHADE_STYLE
{
	VBF_SHADE_STYLE_COLOR		= 0x01,		// 只使用颜色
	VBF_SHADE_STYLE_TEXTURE		= 0x02,		// 只使用纹理
	VBF_SHADE_STYLE_COMPOSITE	= (VBF_SHADE_STYLE_COLOR | VBF_SHADE_STYLE_TEXTURE)		// 同时使用颜色和纹理
};


//--------------------------------------------------------------------
// 定义接口：IVBF_GraphicsAppearance
// 接口描述：各种自定义图形的外观属性
//--------------------------------------------------------------------
class IVBF_GraphicsAppearance
{
public:
	virtual ~IVBF_GraphicsAppearance() {}

public:
	// 设置/获取几何体某个部分是否可见，默认值为true
	virtual void SetVisible(int nPart, bool bVisible)=0;
	virtual bool IsVisible(int nPart)=0;

	// 设置/获取某个部分的几何样式，默认为：实心+网格, 
	virtual void                SetGeometryStyle(int nPart, EVBF_GEOMETRY_STYLE nStyle)=0;
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle(int nPart)=0;

	// 设置/获取某个部分的着色样式，默认为：只使用颜色
	virtual void             SetShadeStyle(int nPart, EVBF_SHADE_STYLE nStyle)=0;
	virtual EVBF_SHADE_STYLE GetShadeStyle(int nPart)=0;

	// 设置某个部分的单一色（该颜色作用于整个几何体），默认值为(1, 1, 1, 1) 
	virtual void       SetColor(int nPart, const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetColor(int nPart)=0;

	// 设置某个部分的渐变色（该颜色从几何体顶部平滑渐变到底部），默认值均为(1, 1, 1, 1) 
	// 如果没有设置渐变色，GetColor()函数返回false
	virtual void SetColor(int nPart, const osg::Vec4f& color0, const osg::Vec4f& color1)=0;
	virtual bool GetColor(int nPart, osg::Vec4f& color0, osg::Vec4f& color1)=0;

	// 如果某个部分的样式中包含线框，设置线的粗度（线的颜色与几何体相同）
    virtual void  SetLineStyle(int nPart, const VBF_LINESTYLE& ls)=0;
    virtual VBF_LINESTYLE& GetLineStyle(int nPart)=0;

	// 设置/获取某个部分的纹理在纵横方向的重复次数，默认值均为1
	virtual void SetNumTexRepeats(int nPart, int nNumRows, int nNumCols)=0;
	virtual void GetNumTexRepeats(int nPart, int& nNumRows, int& nNumCols)=0;

	// 判断某个部分是否正在使用单一色/渐变色/静态纹理/动态纹理
	virtual bool IsUsingSingleColor(int nPart)=0;
	virtual bool IsUsingFadedColor(int nPart)=0;
	virtual bool IsUsingStaticTexture(int nPart)=0;
	virtual bool IsUsingDynamicTexture(int nPart)=0;

	// 获取/设置某个部分的纹理图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void		SetTexImage(int nPart, osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage(int nPart)=0;
};



//--------------------------------------------------------------------
// 定义枚举：EVBF_APPEARANCE_ATTR
// 枚举描述：自定义图形的外观属性
//--------------------------------------------------------------------
enum EVBF_APPEARANCE_ATTR
{
	VBF_APPEARANCE_ATTR_VISIBILITY		= 0,	// 可见性
	VBF_APPEARANCE_ATTR_COLOR			= 1,	// 颜色
	VBF_APPEARANCE_ATTR_LINEWIDTH		= 2,	// 线宽
	VBF_APPEARANCE_ATTR_GEOMETRYSTYLE	= 3,	// 几何样式：实体/网格
	VBF_APPEARANCE_ATTR_SHADESTYLE		= 4,	// 着色样式：纹理/颜色
	VBF_APPEARANCE_ATTR_TEXTURE			= 5,	// 静态纹理
	VBF_APPEARANCE_ATTR_DYNTEXTURE		= 6,	// 动态纹理
	VBF_APPEARANCE_ATTR_TEXTURECOORDS	= 7		// 纹理坐标
};


//--------------------------------------------------------------------
// 定义接口：IVBF_GraphicsAppearanceOwner
// 接口描述：各种自定义图形的外观属性的所有者
//--------------------------------------------------------------------
class IVBF_GraphicsAppearanceOwner
{
public:
	virtual ~IVBF_GraphicsAppearanceOwner() {}

	// 响应外观改变的消息，参数nAttr表示外观中的某个属性
	virtual void OnAppearanceChanged(EVBF_APPEARANCE_ATTR nAttr)=0;
};


#endif 
