#ifndef __VBF_CHART_RULAR_RING_H__
#define __VBF_CHART_RULAR_RING_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>

class VBF_HUDAUX_EXPORT CVBF_ChartRularRing : public CVBF_Chart
{
public:
    CVBF_ChartRularRing(const std::string& strName);
    virtual ~CVBF_ChartRularRing();


private:
    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);





private:

};


#endif 
