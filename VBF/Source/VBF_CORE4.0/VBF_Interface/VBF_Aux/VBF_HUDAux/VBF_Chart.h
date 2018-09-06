#ifndef __VBF_CHART_H__
#define __VBF_CHART_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Aux/VBF_HUDAux/VBF_ChartPartLegend.h>


class VBF_HUDAUX_EXPORT CVBF_Chart : public CVBF_Graphics
{
public:
    CVBF_Chart(const std::string& strName):CVBF_Graphics(strName)
    {
        m_pt = osg::Vec2f(0.0, 0.0);
        m_nWidth  = 200;
        m_nHeight = 80;
        m_bDirtyPos = true;
    }
    // ����/��ȡ��λ�����Ļ���꣨��λ�����أ�Ĭ��ֵΪ(0,0,-1)��
    virtual void SetPos(const osg::Vec2f& pt);
    osg::Vec2f GetPos() { return m_pt; }

    virtual void SetSize(unsigned int nWidth,unsigned int nHeight);

    double GetWidth()  { return m_nWidth; }
    double GetHeight() { return m_nHeight; }

    void SetBackGround(CVBF_Chart* pBk) { m_ipBackGround = pBk; }
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);
    virtual void Update();

    // ��SetPos֮����ò���Ч
    virtual void AddText(float fOffX,float fOffY,osgText::Text* pText);
    virtual osgText::Text* AddText(float fOffX,float fOffY,std::string& sText,VBF_TEXTSTYLE& ts,osgText::Text::AlignmentType alignment);

    // ��SetPos֮����ò���Ч
    virtual void AddChart(float fOffX,float fOffY,CVBF_Chart* pChart);

    void SetLegend(CVBF_ChartParkLegend* pLegend);


protected:
    osg::Vec2f	m_pt;// ��λ����Ļ����
    unsigned int m_nWidth;
    unsigned int m_nHeight;
    ref_ptr<CVBF_Chart> m_ipBackGround; // ����
    std::vector< ref_ptr<osgText::Text> > m_vText; // ����

    ref_ptr<CVBF_ChartParkLegend> m_ipLegend; // ͼ��
    std::vector< ref_ptr<CVBF_Chart> > m_vSubChart; // ��ͼ

    bool m_bDirtyPos;

};

// һ��ϵ�У�����һ�����ݼ�����ַ�ʽ
class VBF_HUDAUX_EXPORT CVBF_ChartSeries
{
public:
    enum EType
    {
       line,
       bar
    };

    CVBF_ChartSeries()
    {
        m_sName = "NULL";
        m_eType = line;
        m_sStack = "NULL";
    }

    CVBF_ChartSeries& operator=(const CVBF_ChartSeries& r)
    {
        m_sName     = r.m_sName;
        m_eType     = r.m_eType;
        m_vData     = r.m_vData;
        m_sStack    = r.m_sStack;

        return *this;
    }

    std::string&        Name() { return m_sName; }
    EType&              Type() { return m_eType; }
    std::vector<float>& Data() { return m_vData; }
    std::string&        Stack() { return m_sStack; }
private:

    std::string m_sName;
    EType       m_eType;
    std::string m_sStack; // ���࣬ѹ��һ��
    std::vector<float> m_vData;

    // ���ݾ��ȣ�λ����
};



#endif 
