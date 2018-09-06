#ifndef __VBF_CHART_PIE_H__
#define __VBF_CHART_PIE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>
#include <VBF_Aux/VBF_HUDAux/VBF_ChartArc.h>
// 饼状图

class VBF_HUDAUX_EXPORT CVBF_ChartPie : public CVBF_Chart
{
public:
    CVBF_ChartPie(const std::string& strName,int numAttr);
    virtual ~CVBF_ChartPie();

    void                      SetStyle(int idx,const VBF_POLYGON2DSTYLE& style);
    const VBF_POLYGON2DSTYLE& GetStyle(int idx)	{ return m_vParts[idx]->GetStyle(); }

    void SetAngle(int idx,double dAngle) { m_vParts[idx]->SetAngle(dAngle); }
    void SetAngle0(double dAngle) { m_dAngle0 = dAngle; }

    void SetRadius(int idx,double dRadiusInner,double dRadiusOuter) { m_vParts[idx]->SetRadius(dRadiusInner,dRadiusOuter); }

    virtual void Update(); // 更新

private:
    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    void CreateSolid();

private:
    int m_numAttr;// 表示的属性的个数
    double m_dAngle0;

    std::vector< ref_ptr<CVBF_ChartArc> > m_vParts;

};


#endif 
