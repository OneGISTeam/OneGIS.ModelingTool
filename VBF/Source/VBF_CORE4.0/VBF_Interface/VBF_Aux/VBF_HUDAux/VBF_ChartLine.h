#ifndef __VBF_CHART_LINE_H__
#define __VBF_CHART_LINE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsText.h>
#include <VBF_Aux/VBF_HUDAux/VBF_ChartPartAxis.h>
#include <VBF_Aux/VBF_HUDAux/VBF_ChartPartGrid.h>

typedef struct _tagVBFPointStyleEx
{
    float			fSize;		// 点的大小
    osg::Vec4f		color;		// 点的颜色
    std::string     sTexFn;     // 纹理文件名

    // 构造函数
    _tagVBFPointStyleEx()
    {
        fSize	= 1.0f;
        color	= osg::Vec4f(1.0f, 0.0f, 0.0f, 1.0f);
    }

    _tagVBFPointStyleEx& operator=(const _tagVBFPointStyleEx& src)
    {
        if(this==&src) return *this;

        fSize	= src.fSize;
        color	= src.color;
        sTexFn  = src.sTexFn;

        return *this;
    }

    bool operator==(const _tagVBFPointStyleEx& src)
    {
        if(this==&src) return true;

        if(!osg::equivalent(fSize, src.fSize)) return false;
        if(color!=src.color) return false;
        if(sTexFn!=src.sTexFn) return false;

        return true;
    }

} VBF_POINTSTYLEEX;

// 折线图

class VBF_HUDAUX_EXPORT CVBF_ChartLine : public CVBF_Chart
{
public:
    CVBF_ChartLine(const std::string& strName,int numSeries);
    virtual ~CVBF_ChartLine();

    virtual void Update(); // 更新

    CVBF_ChartSeries& GetSeries(int idx) { return m_vSeries[idx]; }
    VBF_LINESTYLE&    GetLineStyle(int idx) { return m_vLineStyle[idx]; }
    VBF_POINTSTYLEEX& GetPointStyle(int idx) { return m_vPointStyle[idx]; }

    virtual void SetSize(unsigned int nWidth,unsigned int nHeight);
    virtual void SetPos(const osg::Vec2f& pt);

    // 获取/设置部件（轴、网格）
    CVBF_ChartAxisAttr&  GetAxisAttr()  { return m_AxisAttr;  } // 获取属性轴（变量）
    CVBF_ChartAxisValue& GetAxisValue() { return m_AxisValue; } // 获取数据轴（值）
    CVBF_ChartPartGrid&  GetGrid() { return m_Grid; } // 网格

    void SetAxisAtRight(bool bRight);
    void SetValueTextVisible(bool bVisible) { m_bVisibleValueText = bVisible;} // 值注记是否可见
    void SetFillVisible(bool bVisible) { m_bFillVisible = bVisible; }
private:
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    void CreateValueText(CVBF_DrawableList& vDrawables);// 创建属性值注记
    void CalLineVerts(osg::Vec3Array* pVerts,std::vector<float>& vData);
    void CalAreaVerts(osg::Vec3Array* pVerts,std::vector<float>& vData);

    void CalculateAxisPos();
    void UpdateText();

    std::vector<CVBF_ChartSeries> m_vSeries;
    std::vector<VBF_LINESTYLE>    m_vLineStyle;
    std::vector<VBF_POINTSTYLEEX> m_vPointStyle;

    std::vector< ref_ptr<osg::Vec3Array> > m_vVerts;// 顶点数组(点与线)，用于动态更新，与m_vSeries对应，每个Series对应一个Vec3Array
    std::vector< ref_ptr<osg::Vec3Array> > m_vVertsArea;

    VBF_TEXTSTYLE m_TextStyleValue;	// 文本样式
    std::vector< ref_ptr<osgText::Text> > m_vTextValue;    // 属性值注记

    // 坐标轴
    CVBF_ChartAxisAttr  m_AxisAttr;
    CVBF_ChartAxisValue m_AxisValue;

    // 坐标网格
    CVBF_ChartPartGrid m_Grid;

    bool m_bAxisAtRight;
    bool m_bVisibleValueText;// 值注记是否可见
    bool m_bFillVisible;// 是否填充
};


#endif
