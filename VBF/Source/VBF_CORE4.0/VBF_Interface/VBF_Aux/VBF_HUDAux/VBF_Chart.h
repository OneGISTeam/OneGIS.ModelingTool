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
    // 设置/获取定位点的屏幕坐标（单位：像素，默认值为(0,0,-1)）
    virtual void SetPos(const osg::Vec2f& pt);
    osg::Vec2f GetPos() { return m_pt; }

    virtual void SetSize(unsigned int nWidth,unsigned int nHeight);

    double GetWidth()  { return m_nWidth; }
    double GetHeight() { return m_nHeight; }

    void SetBackGround(CVBF_Chart* pBk) { m_ipBackGround = pBk; }
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);
    virtual void Update();

    // 在SetPos之后调用才有效
    virtual void AddText(float fOffX,float fOffY,osgText::Text* pText);
    virtual osgText::Text* AddText(float fOffX,float fOffY,std::string& sText,VBF_TEXTSTYLE& ts,osgText::Text::AlignmentType alignment);

    // 在SetPos之后调用才有效
    virtual void AddChart(float fOffX,float fOffY,CVBF_Chart* pChart);

    void SetLegend(CVBF_ChartParkLegend* pLegend);


protected:
    osg::Vec2f	m_pt;// 定位点屏幕坐标
    unsigned int m_nWidth;
    unsigned int m_nHeight;
    ref_ptr<CVBF_Chart> m_ipBackGround; // 背景
    std::vector< ref_ptr<osgText::Text> > m_vText; // 文字

    ref_ptr<CVBF_ChartParkLegend> m_ipLegend; // 图例
    std::vector< ref_ptr<CVBF_Chart> > m_vSubChart; // 子图

    bool m_bDirtyPos;

};

// 一个系列，就是一组数据及其表现方式
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
    std::string m_sStack; // 分类，压在一起
    std::vector<float> m_vData;

    // 数据精度（位数）
};



#endif 
