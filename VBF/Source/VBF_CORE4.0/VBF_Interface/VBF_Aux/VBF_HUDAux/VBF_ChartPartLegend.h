#ifndef __VBF_CHART_PART_LEGEND_H__
#define __VBF_CHART_PART_LEGEND_H__

#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>
// ͼ������ͼ��
class VBF_HUDAUX_EXPORT CVBF_ChartParkLegend : public ::CVBF_Referenced//:public CVBF_Chart
{
    // ÿ��ͼ�������ɫ��ע�����
    class CLegendItem
    {
    public:
        CLegendItem(std::string sLabel,osg::Vec4f color)
        {
            m_sLabel = sLabel;
            m_color  = color;
        }
        CLegendItem& operator=(const CLegendItem& r)
        {
            m_sLabel    = r.m_sLabel;
            m_color     = r.m_color;
            return *this;
        }

        std::string m_sLabel;
        osg::Vec4f  m_color;
    };


public:
    CVBF_ChartParkLegend();
    void AddItem(std::string sLabel,osg::Vec4f color);
    void SetPos(const osg::Vec2f& pt);
    void SetIconLength(float fLength) { m_fIconLength = fLength; }
    void SetLegendLength(float fLength) { m_fLegendLength = fLength; }
    VBF_TEXTSTYLE& GetTextStyle()	{ return m_TextStyle; }


    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables);

protected:
    osg::Vec2f	m_pt;// ��λ����Ļ����

    std::vector< CLegendItem >  m_vItem;
    VBF_TEXTSTYLE m_TextStyle;	// �ı���ʽ

    float m_fIconLength;
    float m_fLegendLength;


};
class VBF_HUDAUX_EXPORT CVBF_ChartParkLegendLine:public CVBF_ChartParkLegend
{
public:
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables);
};
class VBF_HUDAUX_EXPORT CVBF_ChartParkLegendRect:public CVBF_ChartParkLegend
{
public:
    CVBF_ChartParkLegendRect();
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables);
    float m_fIconHeight;
};
#endif 
