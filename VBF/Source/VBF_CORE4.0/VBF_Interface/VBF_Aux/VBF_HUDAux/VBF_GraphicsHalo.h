//*******************************************************************
// FileName：VBF_GraphicsHalo.h
// Function：光晕圈效果
// Author:
// Date:
//*******************************************************************

#ifndef __VBF_GRAPHICS_HALO_H__
#define __VBF_GRAPHICS_HALO_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>


class VBF_HUDAUX_EXPORT CVBF_GraphicsHalo : public CVBF_Graphics
{
public:
    CVBF_GraphicsHalo(const std::string& strName="");
    virtual ~CVBF_GraphicsHalo();

    // 设置/获取定位点的屏幕坐标（单位：像素，默认值为(0,0,-1)）
    void SetPos(const osg::Vec2f& pt)
    {
        m_pt = pt;
        DirtyModel();// 使模型节点失效
    }
    osg::Vec2f GetPos() { return m_pt; }

	// 设置/获取纹理图像指针
    void		SetTexImage(osg::Image* pImage);
    osg::Image* GetTexImage() { return m_ipImage.get(); }

    void SetColor(osg::Vec4 vColor0,osg::Vec4 vColor1);// 实现颜色渐变
    void SetSize(double dMinR,double dMaxR) { m_dMaxR = dMaxR; m_dMinR = dMinR; } // 实现大小渐变

    // 设置每个循环的帧数
    void SetFramePerCycle(int numFrame) { m_numFrame = numFrame; }

    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    // 设置渲染状态
    virtual void SetStateSet();
private:
    // 创建矩形的实体部分
    osg::Geometry* CreateSolid();


private:
    osg::Vec2f	m_pt;// 定位点屏幕坐标
    osg::Vec4f m_vColor0;
    osg::Vec4f m_vColor1;

    ref_ptr<osg::Image>		m_ipImage;// 纹理

	// 与场景图有关的内容
    ref_ptr<osg::Geometry>	m_ipGeomSolid;

    double m_dMinR; // 最小半径
    double m_dMaxR; // 最大半径

    int m_numFrame;
};


#endif 
