#ifndef __VBF_CHART_PROCESSLINE_H__
#define __VBF_CHART_PROCESSLINE_H__

#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>

// ��������ͼ
class VBF_HUDAUX_EXPORT CVBF_ChartProcessLine : public CVBF_Chart
{
public:
    CVBF_ChartProcessLine(const std::string& strName,bool bVLine = true);
    virtual ~CVBF_ChartProcessLine();
    void SetColor(osg::Vec4& vColor) { m_vColor = vColor; }


    virtual void Update(){}// ����

private:
    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    unsigned int m_nWidth;
    unsigned int m_nHeight;

    osg::Vec4 m_vColor;
    bool m_bVLine;
};


#endif 
