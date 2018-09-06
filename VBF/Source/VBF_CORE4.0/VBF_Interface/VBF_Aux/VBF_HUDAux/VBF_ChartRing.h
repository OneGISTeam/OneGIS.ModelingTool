#ifndef __VBF_CHART_RING_H__
#define __VBF_CHART_RING_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>
#include <VBF_Aux/VBF_HUDAux/VBF_ChartArc.h>
class VBF_HUDAUX_EXPORT CVBF_ChartRing : public CVBF_Chart
{
public:
    CVBF_ChartRing(const std::string& strName,int numAttr);
    virtual ~CVBF_ChartRing();

    void SetStyle(int idx,const VBF_POLYGON2DSTYLE& style);
    const VBF_POLYGON2DSTYLE& GetStyle(int idx)	{ return m_vPartsStatic[idx]->GetStyle(); }

    void SetAngle(int idx,double dAngle) { m_vPartsStatic[idx]->SetAngle(dAngle); }
    void SetAngle0(int idx,double dAngle) { m_vPartsStatic[idx]->SetAngle0(dAngle); }

    void SetRadius(int idx,double dRadiusInner,double dRadiusOuter) { m_vPartsStatic[idx]->SetRadius(dRadiusInner,dRadiusOuter); }


    void SetStyleDynamic(int idx,const VBF_POLYGON2DSTYLE& style);
    const VBF_POLYGON2DSTYLE& GetStyleDynamic(int idx)	{ return m_vPartsDynamic[idx]->GetStyle(); }

    void SetAngleDynamic(int idx,double dAngle) { m_vPartsDynamic[idx]->SetAngle(dAngle); }
    void SetAngle0Dynamic(int idx,double dAngle) { m_vPartsDynamic[idx]->SetAngle0(dAngle); }

    void SetRadiusDynamic(int idx,double dRadiusInner,double dRadiusOuter) { m_vPartsDynamic[idx]->SetRadius(dRadiusInner,dRadiusOuter); }


    virtual void Update(); // ¸üÐÂ

    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

private:
    int m_numAttr;
    std::vector< ref_ptr<CVBF_ChartArc> > m_vPartsStatic;
    std::vector< ref_ptr<CVBF_ChartArc> > m_vPartsDynamic;

};


#endif 
