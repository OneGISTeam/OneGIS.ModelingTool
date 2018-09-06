//*******************************************************************
// FileName：VBF_GraphicsMeteorLine.h
// Function：二维图形：流星线
// Author:
// Date:
//*******************************************************************

#ifndef __VBF_GRAPHICS_METEORLINE_H__
#define __VBF_GRAPHICS_METEORLINE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>

class CVBF_GraphicsImage;

class VBF_HUDAUX_EXPORT CVBF_GraphicsMeteorLine : public CVBF_Graphics
{
public:
    CVBF_GraphicsMeteorLine(const std::string& strName="");
    virtual ~CVBF_GraphicsMeteorLine();

    // 设置/获取折线样式
    void                 SetLineStyle(const VBF_LINESTYLE& style);
    const VBF_LINESTYLE& GetLineStyle() { return m_LineStyle; }

    void SetPath(const std::vector<osg::Vec3f>& vPoints);

    void SetTexImage(osg::Image* pImage, bool bTexToCache);

    osg::Vec3& GetImagePos(){ return m_vImagePos; }

    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

private:

    void CreateLine();
    void CreateImage();
private:

    std::vector<osg::Vec3f>	m_vPoints;	// 折线坐标串
    VBF_LINESTYLE			m_LineStyle;// 折线的样式


    ref_ptr<osg::Vec3Array>	m_ipVerts;	// 顶点
    ref_ptr<osg::Geometry>  m_ipGeomLine;

    ref_ptr<osg::Image>		m_piImage;
    bool					m_bTexToCache;	// 纹理是否需要放入缓存，默认为false

    ref_ptr<osg::Geometry> m_ipGraphicsImage;

    osg::Vec3 m_vImagePos;

};


#endif 
