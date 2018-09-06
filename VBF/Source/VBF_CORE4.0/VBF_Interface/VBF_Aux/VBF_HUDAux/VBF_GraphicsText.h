//*******************************************************************
// FileName：VBF_GraphicsText.h
// Function：二维图形：文本
// Author:   杜莹
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_TEXT_H__
#define __VBF_GRAPHICS_TEXT_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>
#include <VBF_Engine/VBF_Text/Text>


//--------------------------------------------------------------------
// 定义枚举：文本对齐方式，即定位点与文本包围盒的位置关系
// 枚举描述：EVBF_TEXT_ALIGN
//--------------------------------------------------------------------
enum EVBF_TEXT_ALIGN
{
	VBF_TEXT_ALIGN_LEFT_TOP,		// 左上（默认值）
	VBF_TEXT_ALIGN_LEFT_CENTER,		// 左中
	VBF_TEXT_ALIGN_LEFT_BOTTOM,		// 左下

    VBF_TEXT_ALIGN_CENTER_TOP,		// 中上
    VBF_TEXT_ALIGN_CENTER_CENTER,	// 中心
    VBF_TEXT_ALIGN_CENTER_BOTTOM,	// 中下

    VBF_TEXT_ALIGN_RIGHT_TOP,		// 右上
    VBF_TEXT_ALIGN_RIGHT_CENTER,	// 右中
    VBF_TEXT_ALIGN_RIGHT_BOTTOM     // 右下
};


class VBF_HUDAUX_EXPORT CVBF_GraphicsText : public CVBF_Graphics
{
public:
	CVBF_GraphicsText(const std::string& strName="");
	virtual ~CVBF_GraphicsText();

	// 设置/获取文本内容
	void               SetText(const std::string& strText);
	const std::string& GetText() { return m_strText; }

	// 设置/获取文本的屏幕坐标（单位：像素，默认值为(0,0,-1)）
	void       SetPos(const osg::Vec2f& ptText);
	osg::Vec2f GetPos() { return m_ptText; }

	// 设置/获取文本样式
	void                 SetTextStyle(const VBF_TEXTSTYLE& style);
	const VBF_TEXTSTYLE& GetTextStyle() { return m_TextStyle; }

	// 设置/获取文本对齐方式（默认值为VBF_TEXT_ALIGN_LEFT_TOP）
	void            SetTextAlign(EVBF_TEXT_ALIGN nAlign);
	EVBF_TEXT_ALIGN GetTextAlign() { return m_nTextAlign; }

	// 设置/获取文本背景框的可见性
	void SetFrameVisible(bool bVisible);
	bool IsFrameVisible() { return m_bFrameVisible; }

	// 设置/获取文本背景框的样式
	void                      SetFrameStyle(const VBF_POLYGON2DSTYLE& style);
	const VBF_POLYGON2DSTYLE& GetFrameStyle()	{ return m_FrameStyle; }

    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

protected:

	// 创建文本
    virtual void CreateText();

	// 创建背景框
	void CreateFrame();

	osg::Geometry* CreateFrame_Solid();
	osg::Geometry* CreateFrame_Wireframe();
	osg::Geometry* CreateFrame_Shadow();

	// 根据文本内容和样式计算背景框尺寸
	void UpdateFrameSize(bool bForceUpdate=false);
	void UpdateFrameVerts();
	void UpdateFrameShadowVerts();

	// 从映射表中获取一种字体
	osgText::Font* GetFont(const std::string& strFont);

	// 根据文本对齐方式进行平移
    virtual void Translate();

protected:

	// 文本的屏幕坐标
	osg::Vec2f					m_ptText;

	// 文本对齐方式
	EVBF_TEXT_ALIGN				m_nTextAlign;

	// 文本
	std::string					m_strText;		// 文本内容
	VBF_TEXTSTYLE				m_TextStyle;	// 文本样式

	// 背景框的样式
	bool						m_bFrameVisible;	// 背景框是否可见
	int							m_nFrameSizeX;		// 宽度（单位：像素）
	int							m_nFrameSizeY;		// 高度（单位：像素）
	VBF_POLYGON2DSTYLE			m_FrameStyle;

	// 背景框：以屏幕左下角点为原点，背景框左边为小三角形（等腰），右边为文本矩形
	ref_ptr<osg::Vec3Array>		m_piFrameVerts;			// 背景框的7个顶点
	ref_ptr<osg::Vec3Array>		m_piFrameShadowVerts;	// 背景框阴影的8个顶点

	// 记录各个Drawable，以便修改时使用
	ref_ptr<osgText::Text>		m_piText;				// 文本
	ref_ptr<osg::Geometry>		m_piGeomFrameShadow;	// 背景框阴影
	ref_ptr<osg::Geometry>		m_piGeomFrameSolid;		// 背景框实体部分
	ref_ptr<osg::Geometry>		m_piGeomFrameWireframe;	// 背景框网格部分
};


#endif 
