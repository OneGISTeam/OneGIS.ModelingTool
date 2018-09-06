#ifndef __VBF_CHART_INSTRUMENT_H__
#define __VBF_CHART_INSTRUMENT_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>

// ÒÇ±íÍ¼
class VBF_HUDAUX_EXPORT CVBF_ChartInstrument : public CVBF_Chart
{
public:
    CVBF_ChartInstrument(const std::string& strName);
    virtual ~CVBF_ChartInstrument();

    virtual void Update(); // ¸üÐÂ

     void SetBkImageFn(std::string& sFn);
     void SetPointerImageFn(std::string& sFn);
     void SetSize(double dSize);
     void SetPointerAngle(double dA) { m_dPointerAngle = dA; }

     virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

     double GetPointerAngle() { return m_dPointerAngle; }
private:
    virtual void SetStateSet();

    void CreateImageDrawable(CVBF_DrawableList& vDrawables,ref_ptr<osg::Geometry>& ipDrawable);

    ref_ptr<osg::Geometry>  m_ipDrawableBK;
    ref_ptr<osg::Image>		m_ipBkImage;

    ref_ptr<osg::Geometry>  m_ipDrawablePointer;
    ref_ptr<osg::Image>		m_ipPointerImage;

    double m_dSize;
    double m_dPointerAngle;
};


#endif 
