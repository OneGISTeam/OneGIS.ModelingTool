//*******************************************************************
// FileName：VBF_GraphicsPolyPolygon.h
// Function：二维图形：一组多边形
// Author:   杜莹
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_POLY_POLYGON_H__
#define __VBF_GRAPHICS_POLY_POLYGON_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>
#include <VBF_Macros.h>


// 定义迭代器
typedef std::vector<osg::Vec2f>  CVBF_Point2DList;


// 定义结构体：二维多边形的信息
struct VBF_POLYGON2D : public ::CVBF_Referenced
{
public:
	std::string					m_strID;		// 用户设置的多边形ID号（在组中唯一）

	// 坐标串
	std::vector<osg::Vec2f>		m_vPoints;		// 用户设置的坐标串
	std::vector<osg::Vec2f>		m_vTexCoords;	// 用户设置的纹理坐标（可以为空）

	// 纹理重复次数
	int							m_nNumTexRows;		// 纹理重复次数（横向）
	int							m_nNumTexCols;		// 纹理重复次数（纵向）

	// 样式
	osg::Vec4f					m_colorSolid;
	VBF_LINESTYLE				m_LineStyle;

	// 剖分的结果
	int                         m_nNumTriangles;
	WORD*                       m_pIndices;

	// 与场景图有关的内容
	ref_ptr<osg::Vec3Array>		m_piVerts;		// 顶点数组
	ref_ptr<osg::Geometry>		m_piGeomSolid;
	ref_ptr<osg::Geometry>		m_piGeomLine;

	VBF_POLYGON2D(const std::string& strID)
	{
		m_strID				= strID;
		m_nNumTexRows		= 1;
		m_nNumTexCols		= 1;
		m_nNumTriangles		= 0;
		m_pIndices			= NULL;

		m_colorSolid		= osg::Vec4f(0, 1, 1, 0.6);
		m_LineStyle.fWidth  = 2.0f;
		m_LineStyle.color	= osg::Vec4f(0, 1, 1, 1.0);
	}

	virtual ~VBF_POLYGON2D()
	{
		SAFE_DELETE(m_pIndices);
	}
};

// 定义多边形列表
typedef std::vector< ref_ptr<VBF_POLYGON2D> >  CVBF_PolygonList;

class VBF_HUDAUX_EXPORT CVBF_GraphicsPolyPolygon : public CVBF_Graphics
{
public:
	CVBF_GraphicsPolyPolygon(const std::string& strName="");
	virtual ~CVBF_GraphicsPolyPolygon();

	// 添加一个多边形，参数strID表示多边形在组中的唯一ID号，不允许重复，如果该ID号已经存在返回false
	bool AddPolygon(const std::string& strID, const CVBF_Point2DList& vPoints);
	bool AddPolygonAndTexCoords(const std::string& strID, const CVBF_Point2DList& vPoints, const std::vector<osg::Vec2f>& vTexCoords);

	// 获取某个多边形的坐标串，如果多边形的ID号不存在返回false
	bool GetPolygon(const std::string& strID, CVBF_Point2DList& vPoints);

	// 删除一个多边形，如果多边形的ID号不存在返回false
	bool RemovePolygon(const std::string& strID);


	// 设置/获取所有多边形的几何样式，默认为：实心+边线
	virtual void                SetGeometryStyle(EVBF_GEOMETRY_STYLE nStyle);
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle() { return m_nStyleGeom; }

	// 设置/获取所有多边形的着色样式，默认为：只使用颜色
	virtual void             SetShadeStyle(EVBF_SHADE_STYLE nStyle);
	virtual EVBF_SHADE_STYLE GetShadeStyle() { return m_nStyleShade; }

	// 设置/获取某个多边形的实心颜色
	bool SetSolidColor(const std::string& strID, const osg::Vec4f& color);
	bool GetSolidColor(const std::string& strID, osg::Vec4f& color);

	// 设置/获取某个多边形的边线样式
	bool SetLineStyle(const std::string& strID, const VBF_LINESTYLE& style);
	bool GetLineStyle(const std::string& strID, VBF_LINESTYLE& style);

	// 设置/获取所有多边形的纹理图像指针（所有多边形使用同一个纹理）
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache);
	virtual osg::Image* GetTexImage() { return m_piImage.get(); }

	// 设置/获取某个多边形的纹理在纵横方向的重复次数，默认值均为1，如果多边形的ID号不存在返回false
	virtual bool SetNumTexRepeats(const std::string& strID, int nNumRows, int nNumCols);
	virtual bool GetNumTexRepeats(const std::string& strID, int& nNumRows, int& nNumCols);

	// 设置/获取所有多边形同时启用顶点颜色和纹理时，二者的混合方式
	virtual void SetTexEnvMode(EVBF_TEXENV_MODE	nMode);
	virtual EVBF_TEXENV_MODE GetTexEnvMode() { return m_nTexEnvMode; }

	// 设置/获取所有多边形的坐标点是否可见（默认值为false）
	void SetPointVisible(bool bVisible);
	bool IsPointVisible()	{ return m_bPointVisible; }

    // 设置/获取所有多边形的坐标点的样式
    void                  SetPointStyle(const VBF_POINTSTYLE& style);
    const VBF_POINTSTYLE& GetPointStyle()	{ return m_PointStyle; }

    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    // 设置渲染状态
    virtual void SetStateSet();

private:

	// 在列表中查找某一个多边形
	VBF_POLYGON2D* FindPolygon(const std::string& strID);

    // 创建顶点数组/纹理数组
    osg::Vec3Array* CreateVerts(VBF_POLYGON2D* pPolygon);
    osg::Vec2Array* CreateTexCoords(VBF_POLYGON2D* pPolygon);

    // 创建多边形的各个部分
    osg::Geometry* CreateSolid(VBF_POLYGON2D* pPolygon);
    osg::Geometry* CreateLine(VBF_POLYGON2D* pPolygon);
    osg::Geometry* CreatePoints();

private:

	// 多边形列表（由于需要根据用户调用AddPolygon()的顺序决定绘制顺序，所以此处不能使用std::map）
	CVBF_PolygonList			m_vPolygons;

	EVBF_GEOMETRY_STYLE			m_nStyleGeom;		// 几何绘制方式（实体/网格）
	EVBF_SHADE_STYLE			m_nStyleShade;		// 着色方式（颜色/纹理）
	EVBF_TEXENV_MODE			m_nTexEnvMode;		// 同时启用顶点颜色和纹理时，二者的混合方式

	// 坐标点（用GL_POINTS方式绘制）
	bool						m_bPointVisible;	// 是否显示坐标点
	VBF_POINTSTYLE				m_PointStyle;		// 坐标点的样式

	// 纹理（所有多边形共用一个纹理）
	ref_ptr<osg::Image>			m_piImage;
	bool						m_bTexToCache;      // 纹理是否需要放入缓存，默认为false

	// 所有坐标点共用一个Drawable
	ref_ptr<osg::Geometry>		m_piGeomPoints;
};


#endif 
