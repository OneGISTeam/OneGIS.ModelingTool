//*******************************************************************
// FileName：VBF_GraphicsPolygon.h
// Function：二维图形：多边形
// Author:   杜莹
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_POLYGON_H__
#define __VBF_GRAPHICS_POLYGON_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>
#include <VBF_Macros.h>


class VBF_HUDAUX_EXPORT CVBF_GraphicsPolygon : public CVBF_Graphics
{
public:
	CVBF_GraphicsPolygon(const std::string& strName="");
	virtual ~CVBF_GraphicsPolygon();

	// 设置/获取多边形的坐标串
	void SetPoints(const std::vector<osg::Vec2f>& vPoints);
	const std::vector<osg::Vec2f>& GetPoints() { return m_vPoints; }

	// 设置/获取多边形的坐标串与第0遍纹理坐标（注意：这两组坐标数必须相等且顺序一致）
	virtual void SetPointsAndTexCoords(const std::vector<osg::Vec2f>& vPoints, const std::vector<osg::Vec2f>& vTexCoords);
	virtual void GetPointsAndTexCoords(std::vector<osg::Vec2f>& vPoints, std::vector<osg::Vec2f>& vTexCoords)
	{
		vPoints    = m_vPoints;
		vTexCoords = m_vTexCoords;
	}

	// 设置/获取多边形的几何样式，默认为：实心+边线
	virtual void                SetGeometryStyle(EVBF_GEOMETRY_STYLE nStyle);
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle() { return m_nStyleGeom; }

	// 设置/获取多边形的着色样式，默认为：只使用颜色
	virtual void             SetShadeStyle(EVBF_SHADE_STYLE nStyle);
	virtual EVBF_SHADE_STYLE GetShadeStyle() { return m_nStyleShade; }

	// 设置/获取多边形的实心颜色
	void              SetSolidColor(const osg::Vec4f& color);
	const osg::Vec4f& GetSolidColor() { return m_colorSolid; }

	// 设置/获取多边形的边线样式
	void                 SetLineStyle(const VBF_LINESTYLE& style);
	const VBF_LINESTYLE& GetLineStyle() { return m_LineStyle; }

	// 设置/获取纹理图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache);
	virtual osg::Image* GetTexImage() { return m_piImage.get(); }

	// 设置/获取纹理在纵横方向的重复次数，默认值均为1
	virtual void SetNumTexRepeats(int nNumRows, int nNumCols);
	virtual void GetNumTexRepeats(int& nNumRows, int& nNumCols) { nNumRows = m_nNumTexRows; nNumCols = m_nNumTexCols; }

	// 设置/获取同时启用顶点颜色和纹理时，二者的混合方式
	virtual void SetTexEnvMode(EVBF_TEXENV_MODE	nMode);
	virtual EVBF_TEXENV_MODE GetTexEnvMode() { return m_nTexEnvMode; }

	// 设置/获取坐标点是否可见（默认值为false）
	void SetPointVisible(bool bVisible);
	bool IsPointVisible()	{ return m_bPointVisible; }

    // 设置/获取坐标点的样式
    void                  SetPointStyle(const VBF_POINTSTYLE& style);
    const VBF_POINTSTYLE& GetPointStyle()	{ return m_PointStyle; }

    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    // 设置渲染状态
    virtual void SetStateSet();

protected:

    // 创建顶点数组/纹理数组
    osg::Vec3Array* CreateVerts();
    osg::Vec2Array* CreateTexCoords();

    // 创建多边形的各个部分
    osg::Geometry* CreateSolid();
    osg::Geometry* CreateLine();
    osg::Geometry* CreatePoints();

protected:

	// 坐标串
	std::vector<osg::Vec2f>		m_vPoints;			// 用户设置的坐标串
	std::vector<osg::Vec2f>		m_vTexCoords;		// 用户设置的纹理坐标（可以为空）

	EVBF_GEOMETRY_STYLE			m_nStyleGeom;		// 几何绘制方式（实体/网格）
	EVBF_SHADE_STYLE			m_nStyleShade;		// 着色方式（颜色/纹理）
	EVBF_TEXENV_MODE			m_nTexEnvMode;		// 同时启用顶点颜色和纹理时，二者的混合方式

	// 样式
	osg::Vec4f					m_colorSolid;
	VBF_LINESTYLE				m_LineStyle;

	// 坐标点（用GL_POINTS方式绘制）
	bool						m_bPointVisible;	// 是否显示坐标点
	VBF_POINTSTYLE				m_PointStyle;		// 坐标点的样式

	// 纹理
	ref_ptr<osg::Image>			m_piImage;
	bool						m_bTexToCache;      // 纹理是否需要放入缓存，默认为false
	int							m_nNumTexRows;		// 纹理重复次数（横向）
	int							m_nNumTexCols;		// 纹理重复次数（纵向）

    // 剖分的结果
    int                         m_nNumTriangles;
    WORD*                       m_pIndices;

	// 与场景图有关的内容
	ref_ptr<osg::Vec3Array>		m_piVerts;		// 顶点数组
	ref_ptr<osg::Geometry>		m_piGeomSolid;
	ref_ptr<osg::Geometry>		m_piGeomLine;
	ref_ptr<osg::Geometry>		m_piGeomPoints;
};


#endif 
