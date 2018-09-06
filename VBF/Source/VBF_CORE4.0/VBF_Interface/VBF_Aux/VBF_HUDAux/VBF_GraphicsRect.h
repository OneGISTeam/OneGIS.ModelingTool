//*******************************************************************
// FileName：VBF_GraphicsRect.h
// Function：二维图形：矩形
// Author:   杜莹
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_RECT_H__
#define __VBF_GRAPHICS_RECT_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsShape.h>



class VBF_HUDAUX_EXPORT CVBF_GraphicsRect : public CVBF_GraphicsShape
{
public:
	CVBF_GraphicsRect(const std::string& strName="");
	virtual ~CVBF_GraphicsRect();

	// 设置/获取矩形的屏幕坐标
	void SetPos(float x0, float x1, float y0, float y1);
	void GetPos(float& x0, float& x1, float& y0, float& y1) { x0 = m_x0; y0 = m_y0; x1 = m_x1; y1 = m_y1; }

    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    // 设置渲染状态
    virtual void SetStateSet();

private:

    // 创建矩形的实体和边线部分
    osg::Geometry* CreateSolid();
    osg::Geometry* CreateLine();

    // 更新矩形四个顶点的坐标
    void UpdateVerts(osg::Geometry* pGeom);

private:

	// 屏幕坐标
	float					m_x0, m_x1, m_y0, m_y1;

	// 与场景图有关的内容
	ref_ptr<osg::Geometry>	m_piGeomSolid;
	ref_ptr<osg::Geometry>	m_piGeomLine;
};


#endif 
