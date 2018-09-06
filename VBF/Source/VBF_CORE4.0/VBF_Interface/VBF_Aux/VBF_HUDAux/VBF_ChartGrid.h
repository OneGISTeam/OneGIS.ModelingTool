#ifndef __VBF_CHART_GRID_H__
#define __VBF_CHART_GRID_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsText.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>


class VBF_HUDAUX_EXPORT CVBF_ChartGrid : public CVBF_Chart
{
public:
    CVBF_ChartGrid(const std::string& strName,unsigned int numRow,unsigned int numCol,bool bHasTitle);
    virtual ~CVBF_ChartGrid();

    // 背景样式
    VBF_POLYGON2DSTYLE& GetOddStyle()	{ return m_StyleOdd; } // 奇数行样式
    VBF_POLYGON2DSTYLE& GetEvenStyle()	{ return m_StyleEven; }// 偶数行样式
    VBF_POLYGON2DSTYLE& GetTitleStyle()	{ return m_StyleTitle; }// 标题行样式

    // 外边框样式
    VBF_LINESTYLE& GetOuterStyle()	{ return m_lsOuter; }

    // 文字样式
    VBF_TEXTSTYLE& GetTitleTextStyle()	{ return m_TextStyleTitle; }
    VBF_TEXTSTYLE& GetGridTextStyle()	{ return m_TextStyleGrid; }

    // 设置文字内容
    void SetTitleText(int nCol,std::string& sText);

    // 设置/获取单元格的文字内容
    void SetGridText(int nRow,int nCol,std::string& sText);
    const std::string& GetGridText(int nRow,int nCol) { return m_vTextStringGrid[nRow*m_numCol + nCol]; }

    // 设置/获取单元格的图表内容
    void SetGridGraphics(int nRow,int nCol,CVBF_Chart* pGraphics);
    CVBF_Chart* GetGridGraphics(int nRow,int nCol){ return m_vGraphicsGrid[nRow*m_numCol + nCol]; }


    void SetTitleHeight(double dH) { m_dTitleHeight = dH; } // 表头的高度

    std::vector<float>& GetColumnWidth(){ return m_vCellWidth; }

    virtual void Update(); // 更新

private:
    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    void CreateGridOdd(const CVBF_GraphicsContext& context,CVBF_DrawableList& vDrawables);
    void CreateGridEven(const CVBF_GraphicsContext& context,CVBF_DrawableList& vDrawables);
    void CreateGridTitle(const CVBF_GraphicsContext& context,CVBF_DrawableList& vDrawables);
    void CreateGridOuter(const CVBF_GraphicsContext& context,CVBF_DrawableList& vDrawables);

    void CreateTextTitle(const CVBF_GraphicsContext& context,CVBF_DrawableList& vDrawables);
    void CreateTextGrid(const CVBF_GraphicsContext& context,CVBF_DrawableList& vDrawables);
    void CreateGraphicsGrid(const CVBF_GraphicsContext& context,CVBF_DrawableList& vDrawables);

    ref_ptr<osg::Geometry> m_ipDrawableOdd;
    ref_ptr<osg::Geometry> m_ipDrawableEven;
    ref_ptr<osg::Geometry> m_ipDrawableTitle; // 标题条
    ref_ptr<osg::Geometry> m_ipDrawableOuter; // 外轮廓
private:
    ref_ptr<osg::Vec3Array>		m_ipVerts;	// Grid的顶点

    bool m_bHasTitle;// 是否有表头

    unsigned int m_numRow; // 表格的行数
    unsigned int m_numCol; // 表格的列数

    std::vector<float> m_vCellWidth; // 表格每列的宽度

    double m_dTitleHeight; // 表头的高度


    VBF_POLYGON2DSTYLE	m_StyleOdd;  // 奇数行
    VBF_POLYGON2DSTYLE	m_StyleEven; // 偶数行
    VBF_POLYGON2DSTYLE	m_StyleTitle; // 标题条

    VBF_LINESTYLE m_lsOuter; // 外轮廓线样式

    // 表格标题
    std::vector<std::string>  m_vTextStringTitle; // 文本内容
    std::vector< ref_ptr<osgText::Text> > m_vTextTitle; // Title注记
    VBF_TEXTSTYLE	m_TextStyleTitle;	// Title文本样式

    // 表格正文
    std::vector<std::string>  m_vTextStringGrid;  // 正文的文本内容
    std::vector< ref_ptr<osgText::Text> > m_vTextGrid; // Grid注记
    VBF_TEXTSTYLE	m_TextStyleGrid;	// Grid文本样式
    std::vector< ref_ptr<CVBF_Chart> >  m_vGraphicsGrid;  // 正文的子图

};


#endif
