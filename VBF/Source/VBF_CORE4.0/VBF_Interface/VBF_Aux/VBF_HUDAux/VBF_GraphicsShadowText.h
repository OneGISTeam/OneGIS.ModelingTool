//*******************************************************************
// FileName：VBF_GraphicsShadowText.h
// Function：二维图形：带阴影的文本
// Author:
// Date:
//*******************************************************************

#ifndef __VBF_GRAPHICS_SHADOW_TEXT_H__
#define __VBF_GRAPHICS_SHADOW_TEXT_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsText.h>


class VBF_HUDAUX_EXPORT CVBF_GraphicsShadowText : public CVBF_GraphicsText
{
public:
    CVBF_GraphicsShadowText(const std::string& strName="");
    virtual ~CVBF_GraphicsShadowText();

    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);
    void SetShadowOffset(osg::Vec2f vOffset) { m_vShadowOffset = vOffset; }
    void SetShadowColor(osg::Vec4f color) { m_colorShadow = color; }
private:

	// 创建文本
    virtual void CreateText();

	// 根据文本对齐方式进行平移
    virtual void Translate();

private:
    ref_ptr<osgText::Text>	m_ipShadowText;	// 阴影文本

    osg::Vec2f m_vShadowOffset;
    osg::Vec4f m_colorShadow;

};


#endif 
