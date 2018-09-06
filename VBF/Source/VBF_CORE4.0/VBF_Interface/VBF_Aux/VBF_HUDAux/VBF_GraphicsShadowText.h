//*******************************************************************
// FileName��VBF_GraphicsShadowText.h
// Function����άͼ�Σ�����Ӱ���ı�
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

    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);
    void SetShadowOffset(osg::Vec2f vOffset) { m_vShadowOffset = vOffset; }
    void SetShadowColor(osg::Vec4f color) { m_colorShadow = color; }
private:

	// �����ı�
    virtual void CreateText();

	// �����ı����뷽ʽ����ƽ��
    virtual void Translate();

private:
    ref_ptr<osgText::Text>	m_ipShadowText;	// ��Ӱ�ı�

    osg::Vec2f m_vShadowOffset;
    osg::Vec4f m_colorShadow;

};


#endif 
