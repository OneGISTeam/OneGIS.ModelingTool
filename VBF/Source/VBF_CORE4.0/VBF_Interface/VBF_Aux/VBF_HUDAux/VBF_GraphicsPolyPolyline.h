//*******************************************************************
// FileName：VBF_GraphicsPolyPolyline.h
// Function：二维图形：一组折线
// Author:   杜莹
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_POLY_POLYLINE_H__
#define __VBF_GRAPHICS_POLY_POLYLINE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>


// 定义迭代器
typedef std::vector<osg::Vec2f>  CVBF_Point2DList;


class VBF_HUDAUX_EXPORT CVBF_GraphicsPolyPolyline : public CVBF_Graphics
{
public:
	CVBF_GraphicsPolyPolyline(const std::string& strName="");
	virtual ~CVBF_GraphicsPolyPolyline();

	// 添加一条折线，参数strID表示折线在组中的唯一ID号，不允许重复，如果该ID号已经存在返回false
	bool AddLine(const std::string& strID, const CVBF_Point2DList& vPoints);

	// 获取某条折线的坐标串，如果折线的ID号不存在返回false
	bool GetLine(const std::string& strID, CVBF_Point2DList& vPoints);

	// 删除一条折线，如果折线的ID号不存在返回false
	bool RemoveLine(const std::string& strID);

	// 设置/获取所有折线的样式
	void                 SetLineStyle(const VBF_LINESTYLE& style);
	const VBF_LINESTYLE& GetLineStyle() { return m_LineStyle; }

	// 设置/获取所有坐标点是否可见（默认值为true）
	void SetPointVisible(bool bVisible);
	bool IsPointVisible()	{ return m_bPointVisible; }

    // 设置/获取所有坐标点的样式
    void                  SetPointStyle(const VBF_POINTSTYLE& style);
    const VBF_POINTSTYLE& GetPointStyle()	{ return m_PointStyle; }

    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

private:

    // 创建折线和坐标点
    osg::Geometry* CreateLine(const CVBF_Point2DList& vPoints);
    osg::Geometry* CreatePoints();

private:

	// 折线映射表，key=折线的ID号，value=折线的坐标串
	typedef std::map<std::string, CVBF_Point2DList>  CVBF_LineMap;
	CVBF_LineMap				m_mapLines;

	// 坐标点（用GL_POINTS方式绘制）
	bool						m_bPointVisible;	// 是否显示坐标点
	VBF_POINTSTYLE				m_PointStyle;		// 坐标点的样式

	// 折线的样式
	VBF_LINESTYLE				m_LineStyle;
};


#endif 
