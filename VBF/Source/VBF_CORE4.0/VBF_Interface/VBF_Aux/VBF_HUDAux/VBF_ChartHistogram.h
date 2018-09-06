#ifndef __VBF_CHART_HISTOGRAM_H__
#define __VBF_CHART_HISTOGRAM_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsText.h>
#include <VBF_Aux/VBF_HUDAux/VBF_ChartPartAxis.h>
#include <VBF_Aux/VBF_HUDAux/VBF_ChartPartGrid.h>

// 柱状图
// 大的Bar由属性的个数确定
class VBF_HUDAUX_EXPORT CVBF_ChartHistogram : public CVBF_Chart
{
public:
    enum Mode
    {
        ACCUMULATION, // 累加
        APPOSITION    // 并列，并置

    };
    CVBF_ChartHistogram(const std::string& strName,int numAttr,int numSeries);
    virtual ~CVBF_ChartHistogram();

    // 设置数据
    int  GetValue(int nSeries, int nAttr) { return m_vSeries[nSeries].Data()[nAttr]; }
    void SetValue(int nSeries,int nAttr,double dValue) { m_vSeries[nSeries].Data()[nAttr] = dValue; }
    CVBF_ChartSeries& GetSeries(int idx) { return m_vSeries[idx]; }

    // 设置模式
    void SetMode(Mode eMode) { m_eMode = eMode; }

    // 设置样式
    void                SetSeriesStyle(int idx,const VBF_POLYGON2DSTYLE& style);
    VBF_POLYGON2DSTYLE& GetSeriesStyle(int idx){ return m_vSeriesStyles[idx]; }

    void                SetAttrStyle(int idx,const VBF_POLYGON2DSTYLE& style);
    VBF_POLYGON2DSTYLE& GetAttrStyle(int idx){ return m_vAttrStyles[idx]; }

    void SetMaxValue(int nMaxLength,double dMaxValue);
    void SetBarWidth(int nWidth,int nSpace);  // 宽度,间距

    // 获取/设置部件（轴、网格）
    CVBF_ChartAxisAttr&  GetAxisAttr()  { return m_AxisAttr;  } // 获取属性轴（变量）
    CVBF_ChartAxisValue& GetAxisValue() { return m_AxisValue; } // 获取数据轴（值）
    CVBF_ChartPartGrid&  GetGrid() { return m_Grid; } // 网格

    void SeAttrValueVisible( bool bVisible) { m_bVisibleAttrValue = bVisible;}
    VBF_TEXTSTYLE& GetValueTextStyle(){ return m_TextStyleValue; }// 获取属性值注记字体

    virtual void SetPos(const osg::Vec2f& pt);
    void SetSpaceToAxis(float fDis) { m_fSpaceToAxis = fDis; }

    virtual void Update(); // 更新

    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

private:

    void CreateSolid(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables);
    void CreateWireframe(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables);
    void CreateShadow(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables);
    void CreateValueText(const CVBF_GraphicsContext& context,CVBF_DrawableList& vDrawables);// 创建属性值注记


    void UpdateVerts();
    void UpdateShadowVerts();


    float m_fSpaceToAxis; // 属性轴上第一个柱与轴之间的空白距离

protected:
    Mode m_eMode;
    // 如表示1980、1990、2000、2010、2020五个年份的人均GDP、人均收入，其中数据系列有两个（人均GDP、人均收入），属性有五个（1980、1990、2000、2010、2020）
    int m_numSeries;// 数据系列的个数
    int m_numAttr;  // 表示的属性的个数

    int         m_nMaxLength; // 最大长度
    double      m_dMaxValue;  // 最大的值

    int			m_nBarWidth;    // 每条的高度（单位：像素）
    int         m_nBarSpace;    // 每条之间的间隔

    std::vector<CVBF_ChartSeries> m_vSeries;

    // 二者选其一
    std::vector<VBF_POLYGON2DSTYLE>	m_vSeriesStyles; // 每一种数据使用的样式
    std::vector<VBF_POLYGON2DSTYLE>	m_vAttrStyles;   // 每一种属性使用的样式

    // 记录顶点及Drawable，以便修改时使用
    ref_ptr<osg::Vec3Array>		m_ipVerts;			// 柱的顶点
    ref_ptr<osg::Vec3Array>		m_ipVertsShadow;	// 阴影的顶点

    ref_ptr<osg::Geometry>		m_ipDrawableShadow;     // 阴影
    ref_ptr<osg::Geometry>		m_ipDrawableSolid;      // 实体
    ref_ptr<osg::Geometry>		m_ipDrawableWireframe;	// 网格



    bool m_bHorizontal;// 是否水平的

    // 属性值注记
    bool m_bVisibleAttrValue;// 属性值注记是否显示
    int           m_idxTextValue;   // 注记系列的索引（-1不注记）
    VBF_TEXTSTYLE m_TextStyleValue;	// 文本样式
    std::vector< ref_ptr<osgText::Text> > m_vTextValue;    // 属性值注记


    // 坐标轴
    CVBF_ChartAxisAttr  m_AxisAttr;
    CVBF_ChartAxisValue m_AxisValue;


    // 坐标网格
    CVBF_ChartPartGrid m_Grid;
};

class VBF_HUDAUX_EXPORT CVBF_ChartHistogramH: public CVBF_ChartHistogram
{
public:
    CVBF_ChartHistogramH(const std::string& strName,int numAttr,int numSeries);
};
class VBF_HUDAUX_EXPORT CVBF_ChartHistogramV: public CVBF_ChartHistogram
{
public:
    CVBF_ChartHistogramV(const std::string& strName,int numAttr,int numSeries);
};
#endif 
