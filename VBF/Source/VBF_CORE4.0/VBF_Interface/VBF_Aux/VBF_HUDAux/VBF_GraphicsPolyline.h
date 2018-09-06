//*******************************************************************
// FileName：VBF_GraphicsPolyline.h
// Function：二维图形：折线
// Author:   杜莹
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_POLYLINE_H__
#define __VBF_GRAPHICS_POLYLINE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>


class VBF_HUDAUX_EXPORT CVBF_GraphicsPolyline : public CVBF_Graphics
{
public:
	CVBF_GraphicsPolyline(const std::string& strName="");
	virtual ~CVBF_GraphicsPolyline();

	// 设置/获取折线的坐标串
	void SetPoints(const std::vector<osg::Vec2f>& vPoints);
	const std::vector<osg::Vec2f>& GetPoints() { return m_vPoints; }

	// 设置/获取折线样式
	void                 SetLineStyle(const VBF_LINESTYLE& style);
	const VBF_LINESTYLE& GetLineStyle() { return m_LineStyle; }

	// 设置/获取坐标点是否可见（默认值为true）
	void SetPointVisible(bool bVisible);
	bool IsPointVisible()	{ return m_bPointVisible; }

    // 设置/获取坐标点的样式
    void                  SetPointStyle(const VBF_POINTSTYLE& style);
    const VBF_POINTSTYLE& GetPointStyle()	{ return m_PointStyle; }

    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    virtual void SetStateSet();

private:

    // 创建折线和坐标点
    osg::Geometry* CreateLine();
    osg::Geometry* CreatePoints();

private:

	// 坐标串
	std::vector<osg::Vec2f>		m_vPoints;	// 折线坐标串

	// 坐标点（用GL_POINTS方式绘制）
	bool						m_bPointVisible;	// 是否显示坐标点
	VBF_POINTSTYLE				m_PointStyle;		// 坐标点的样式

	// 折线的样式
	VBF_LINESTYLE				m_LineStyle;

    ref_ptr<osg::Geometry>	m_ipGeomLine;
};


#endif 
