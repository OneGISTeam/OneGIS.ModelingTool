//*******************************************************************
// FileName：VBF_GraphicsShape.h
// Function：各种自定义2D几何图形，继承自CVBF_Graphics
// Author:   杜莹
// Date:     2015-12-29
//*******************************************************************

#ifndef __VBF_GRAPHICS_SHAPE_H__
#define __VBF_GRAPHICS_SHAPE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>



//=============================================================================
// 定义类：CVBF_GraphicsShape
// 类描述：所有2D几何图形的基类
//=============================================================================
class VBF_HUDAUX_EXPORT CVBF_GraphicsShape : public CVBF_Graphics
{
public:
    CVBF_GraphicsShape(const std::string& strName="");
    virtual ~CVBF_GraphicsShape();

	// 设置/获取图形的几何样式，默认为：实心+边线
	virtual void                SetGeometryStyle(EVBF_GEOMETRY_STYLE nStyle);
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle() { return m_nStyleGeom; }

	// 设置/获取图形的着色样式，默认为：只使用颜色
	virtual void             SetShadeStyle(EVBF_SHADE_STYLE nStyle);
	virtual EVBF_SHADE_STYLE GetShadeStyle() { return m_nStyleShade; }

	// 设置/获取图形的实心颜色
	void              SetSolidColor(const osg::Vec4f& color);
	const osg::Vec4f& GetSolidColor() { return m_colorSolid; }

	// 设置/获取图形的边线样式
	void                 SetLineStyle(const VBF_LINESTYLE& style);
	const VBF_LINESTYLE& GetLineStyle() { return m_LineStyle; }

	// 设置/获取纹理图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache);
	virtual osg::Image* GetTexImage() { return m_piImage.get(); }

	// 设置/获取某个部分的纹理在纵横方向的重复次数，默认值均为1
	virtual void SetNumTexRepeats(int nNumRows, int nNumCols);
	virtual void GetNumTexRepeats(int& nNumRows, int& nNumCols) { nNumRows = m_nNumTexRows; nNumCols = m_nNumTexCols; }

	// 设置/获取同时启用顶点颜色和纹理时，二者的混合方式
	virtual void SetTexEnvMode(EVBF_TEXENV_MODE	nMode);
	virtual EVBF_TEXENV_MODE GetTexEnvMode() { return m_nTexEnvMode; }

	// 设置/获取绕图形中心点的旋转角，默认值为0.0（逆时针为正，单位：角度）
	virtual void  SetRotate(float fRotate)	{ m_fRotate = fRotate; DirtyModel(); }
	virtual float GetRotate()				{ return m_fRotate; }

protected:

	// 对顶点进行缩放、旋转和平移
	void Transform(osg::Vec3Array* pVerts);

protected:

	EVBF_GEOMETRY_STYLE		m_nStyleGeom;		// 几何绘制方式（实体/网格）
	EVBF_SHADE_STYLE		m_nStyleShade;		// 着色方式（颜色/纹理）

	// 样式
	osg::Vec4f				m_colorSolid;
	VBF_LINESTYLE			m_LineStyle;

	// 纹理
	ref_ptr<osg::Image>		m_piImage;
	bool					m_bTexToCache;      // 纹理是否需要放入缓存，默认为false
	int						m_nNumTexRows;		// 纹理重复次数（横向）
	int						m_nNumTexCols;		// 纹理重复次数（纵向）

	// 同时启用顶点颜色和纹理时，二者的混合方式
	EVBF_TEXENV_MODE		m_nTexEnvMode;

	// 图形变换
	float					m_fScaleX;		// 缩放（相对于单位图形）
	float					m_fScaleY;
	float					m_fRotate;		// 绕图形中心点的旋转角
	osg::Vec2				m_ptOffset;		// 平移（相对于单位图形的原点）
};



#endif
