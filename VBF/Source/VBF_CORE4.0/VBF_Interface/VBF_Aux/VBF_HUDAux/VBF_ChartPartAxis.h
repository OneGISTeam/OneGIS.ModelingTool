#ifndef __VBF_CHART_PART_AXIS_H__
#define __VBF_CHART_PART_AXIS_H__

#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>


// 图表部件，坐标轴
#include <VBF_Engine/VBF_Text/Text>
class VBF_HUDAUX_EXPORT CVBF_ChartAxis
{
public:
    CVBF_ChartAxis();
    void SetVisible(bool bVisible) { m_bVisible = bVisible;}
    void SetPos(const osg::Vec2f& pt)    { m_pt = pt;                   m_bDirty = true;}

    void SetLength(float fAxisLen);
    float GetLength(){ return m_dLength; }

    void SetLabelRotateAngle(int nAngle) { m_nLabelRotateAngle = nAngle;m_bDirty = true;}
    void SetOrignPointLB(bool bLB)       { m_bOrignPointLB = bLB;       m_bDirty = true; }// 原点是否在左下方位，影响注记的位置


    // 获取线样式和注记样式
    VBF_TEXTSTYLE& GetTextStyle(){ return m_TextStyle; }
    VBF_LINESTYLE& GetLineStyle(){ return m_lsAxis; }

    virtual void Update();
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);
    void SetHorizontal(bool bHorizontal) { m_bHorizontal = bHorizontal; m_bDirty = true;}

protected:
    void UpdateVerts();

    bool m_bVisible;
    osg::Vec2f	m_pt;// 定位点屏幕坐标

    ref_ptr<osg::Geometry>		m_ipDrawable;
    ref_ptr<osg::Vec3Array>		m_ipVertsAxis;		// 坐标轴的顶点

    bool m_bHorizontal;
    bool m_bOrignPointLB;// 原点是否在左下方位

    double m_dLength;
    int    m_nLabelRotateAngle; // 注记的旋转角（度）

    VBF_LINESTYLE  m_lsAxis;    // 轴的线样式
    VBF_TEXTSTYLE  m_TextStyle;	// 注记的文本样式

    bool m_bDirty;

};

class VBF_HUDAUX_EXPORT CVBF_ChartAxisAttr : public CVBF_ChartAxis
{
public:
    CVBF_ChartAxisAttr();

    void SetAttrsName(std::vector<std::string>& vAttrName);
    const std::vector<std::string>& GetAttrsName() {return m_vStringAttr; }

    void SetBarWidth(int nBarWidth,int nBarSpace);// 用于计算注记的位置
    void SetHeadSapce(float fSpace) { m_fHeadfSpace = fSpace; m_bDirty = true;}

    virtual void Update();
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);
private:
    std::vector<std::string> m_vStringAttr; //属性文本
    std::vector< ref_ptr<osgText::Text> > m_vTextAxisAttr; // 属性轴注记
    int m_nBarWidth;
    int m_nBarSpace;
    float m_fHeadfSpace;

};
// 数据轴
class VBF_HUDAUX_EXPORT CVBF_ChartAxisValue : public CVBF_ChartAxis
{
public:
    CVBF_ChartAxisValue();

    void SetMaxValue(double dMaxValue);// 设置最大值
    void SetTickMarkNum(int num);      // 设置刻度线的个数
    int  GetTickMarkNum() { return m_numTickMark; }
    double GetMaxValue() { return m_dMaxValue; }

    virtual void Update();
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    float ValueToLength( float fValue)
    {
        return m_dLength* fValue/m_dMaxValue;
    }
private:
    std::vector< ref_ptr<osgText::Text> > m_vTextAxisData; // 数据轴注记

    int m_numTickMark;
    double m_dMaxValue;


};


#endif 
