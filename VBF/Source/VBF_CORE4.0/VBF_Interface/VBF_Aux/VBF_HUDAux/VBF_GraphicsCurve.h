//*******************************************************************
// FileName：VBF_GraphicsCurve.h
// Function：二维图形：光滑曲线
// Author:   杜莹
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_CURVE_H__
#define __VBF_GRAPHICS_CURVE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>


class VBF_HUDAUX_EXPORT CVBF_GraphicsCurve : public CVBF_Graphics
{
public:
	CVBF_GraphicsCurve(const std::string& strName="");
	virtual ~CVBF_GraphicsCurve();

	// 获取曲线的原始坐标串
	const std::vector<osg::Vec2f>& GetOrignPoints() { return m_vPointsOrign; }

	// 设置/获取曲线样式
	void                 SetLineStyle(const VBF_LINESTYLE& style);
	const VBF_LINESTYLE& GetLineStyle() { return m_LineStyle; }

	// 设置/获取原始坐标点是否可见（默认值为true）
	void SetOrignPointVisible(bool bVisible);
	bool IsOrignPointVisible()	{ return m_bOrignPointVisible; }

    // 设置/获取原始坐标点的样式
    void                  SetOrignPointStyle(const VBF_POINTSTYLE& style);
    const VBF_POINTSTYLE& GetOrignPointStyle()	{ return m_PointStyle; }

    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    // 设置渲染状态
    virtual void SetStateSet();

protected:

    // 曲线光滑
    virtual void Smooth()=0;

    // 创建曲线和坐标点
    osg::Geometry* CreateLine();
    osg::Geometry* CreatePoints();

protected:

	// 坐标串
	std::vector<osg::Vec2f>		m_vPointsOrign;			// 曲线的原始坐标串
	std::vector<osg::Vec2f>		m_vPointsSmooth;			// 曲线的插值坐标串

	// 坐标点（用GL_POINTS方式绘制）
	bool						m_bOrignPointVisible;	// 是否显示原始坐标点
	VBF_POINTSTYLE				m_PointStyle;			// 坐标点的样式

	// 曲线的样式
	VBF_LINESTYLE				m_LineStyle;

	// 与场景图有关的内容
	ref_ptr<osg::Geometry>		m_piGeomLine;
	ref_ptr<osg::Geometry>		m_piGeomPoints;
};


#endif 
