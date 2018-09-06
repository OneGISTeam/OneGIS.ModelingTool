//*******************************************************************
// FileName：VBF_ChartImage.h
// Function：图像
// Author:
// Date:
//*******************************************************************

#ifndef __VBF_CHART_IMAGE_H__
#define __VBF_CHART_IMAGE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>


class VBF_HUDAUX_EXPORT CVBF_ChartImage : public CVBF_Chart
{
public:
    CVBF_ChartImage(const std::string& strName="");
    virtual ~CVBF_ChartImage();


	// 设置/获取纹理图像指针
    void		SetTexImage(osg::Image* pImage);
	osg::Image* GetTexImage() { return m_piImage.get(); }

	// 设置/获取纹理透明度（默认值为1.0）
    void  SetColor(osg::Vec4f color);
    osg::Vec4f GetColor() { return m_vColor; }


    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);
    virtual void Update();// 更新


private:
    // 设置渲染状态
    virtual void SetStateSet();

    // 创建矩形的实体部分
    osg::Geometry* CreateSolid();

private:
	// 纹理
	ref_ptr<osg::Image>		m_piImage;
    ref_ptr<osg::Vec3Array>	m_ipVerts;

    osg::Vec4f				m_vColor;	// 纹理透明度

	// 与场景图有关的内容
    ref_ptr<osg::Geometry>	m_piGeomSolid;
};


#endif 
