#ifndef __VBF_CHART_ARC_H__
#define __VBF_CHART_ARC_H__

#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>

// 饼状图
class VBF_HUDAUX_EXPORT CVBF_ChartArc : public CVBF_Chart
{
public:
    CVBF_ChartArc(const std::string& strName): CVBF_Chart(strName)
    {
        // 初始化样式
        m_Style.bShadowed     = true;
        m_Style.bOutlined	  = true;
        m_Style.colorFill     = osg::Vec4f(1, 1, 0, 0.4);
        m_Style.colorOutline  = osg::Vec4f(1, 1, 0, 1.0);
        m_Style.colorShadow   = osg::Vec4f(0.1, 0.1, 0.1, 1.0);
        m_Style.nShadowOffset = 4;

        m_dAngle  = 20.0;
        m_dAngle0 = 0.0;
        m_dRadiusInner = 100;
        m_dRadiusOuter = 200;
    }
    void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);


    void CreateInner(CVBF_DrawableList& vDrawables);
    void CreateOuter(CVBF_DrawableList& vDrawables);
    void CreateSolid(CVBF_DrawableList& vDrawables);

    void SetAngle(double dAngle) { m_dAngle = dAngle; }
    void SetAngle0(double dAngle) { m_dAngle0 = dAngle; }

    double GetAngle() { return m_dAngle; }
    double& GetAngle0() { return m_dAngle0; }

    const VBF_POLYGON2DSTYLE& GetStyle() { return m_Style; }
    void SetStyle(const VBF_POLYGON2DSTYLE& style){ m_Style = style; }
    void SetRadius(double dRadiusInner,double dRadiusOuter)
    {
        m_dRadiusInner = dRadiusInner;
        m_dRadiusOuter = dRadiusOuter;
    }
private:
    double m_dRadiusInner; // 内半径
    double m_dRadiusOuter; // 外半径
    double m_dAngle;    // 张角，单位度
    double m_dAngle0;   // 起始角
    VBF_POLYGON2DSTYLE	 m_Style;

    ref_ptr<osg::Vec3Array>	m_ipVerts;	// 顶点
    ref_ptr<osg::Geometry>	m_ipDrawableSolid;      // 实体部分

    ref_ptr<osg::Geometry>	m_ipDrawableWireframeInner;	// 网格部分
    ref_ptr<osg::Geometry>	m_ipDrawableWireframeOuter;	// 网格部分
    ref_ptr<osg::Geometry>	m_ipDrawableWireframeSplit;	// 网格部分

};

#endif 
