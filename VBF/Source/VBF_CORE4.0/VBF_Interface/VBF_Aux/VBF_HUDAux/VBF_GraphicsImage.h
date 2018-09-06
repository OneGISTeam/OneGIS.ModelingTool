//*******************************************************************
// FileName：VBF_GraphicsImage.h
// Function：二维图形：图像
// Author:   杜莹
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_IMAGE_H__
#define __VBF_GRAPHICS_IMAGE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>


class VBF_HUDAUX_EXPORT CVBF_GraphicsImage : public CVBF_Graphics
{
public:
	CVBF_GraphicsImage(const std::string& strName="");
	virtual ~CVBF_GraphicsImage();

	// 设置/获取图像的屏幕坐标
	void SetPos(float x0, float x1, float y0, float y1);
	void GetPos(float& x0, float& x1, float& y0, float& y1) { x0 = m_x0; y0 = m_y0; x1 = m_x1; y1 = m_y1; }

	// 设置/获取纹理图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	void		SetTexImage(osg::Image* pImage, bool bTexToCache);
	osg::Image* GetTexImage() { return m_piImage.get(); }

	// 设置/获取纹理透明度（默认值为1.0）
    void  SetColor(osg::Vec4f color);
    osg::Vec4f GetColor() { return m_vColor; }

	// 设置/获取绕图像中心点的旋转角，默认值为0.0（逆时针为正，单位：角度）
	void  SetRotate(float fRotate)	{ m_fRotate = fRotate; DirtyModel(); }
	float GetRotate()				{ return m_fRotate; }

    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);


    // 设置渲染状态
    virtual void SetStateSet();

private:

    // 创建矩形的实体部分
    osg::Geometry* CreateSolid();

	// 对顶点进行缩放、旋转和平移
	void Transform(osg::Vec3Array* pVerts);

private:

	// 屏幕坐标
	float					m_x0, m_x1, m_y0, m_y1;

	// 图像变换
	float					m_fRotate;		// 绕图像中心点的旋转角

	// 纹理
	ref_ptr<osg::Image>		m_piImage;
	bool					m_bTexToCache;	// 纹理是否需要放入缓存，默认为false
    osg::Vec4f				m_vColor;	// 纹理透明度

	// 与场景图有关的内容
    ref_ptr<osg::Geometry>	m_piGeomSolid;
};


#endif 
