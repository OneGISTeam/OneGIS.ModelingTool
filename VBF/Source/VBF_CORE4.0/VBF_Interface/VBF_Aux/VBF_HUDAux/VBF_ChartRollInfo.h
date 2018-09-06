#ifndef __VBF_CHART_ROLL_INFO_H__
#define __VBF_CHART_ROLL_INFO_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsText.h>
#include <VBF_Aux/VBF_HUDAux/VBF_ChartImage.h>


class VBF_HUDAUX_EXPORT CVBF_ChartRollInfo : public CVBF_Chart
{
public:
    class Row : public CVBF_Referenced
    {
    public:
        Row(int size)
        {
//            m_vTextString.resize(size);
//            m_vImageFN.resize(size);
            m_vText.resize(size);
            m_vImage.resize(size);
        }
        std::vector< ref_ptr<osgText::Text> >& GetText() { return m_vText; }
        std::vector< ref_ptr<CVBF_ChartImage> >& GetChart() {return m_vImage;}
//        std::vector< std::string > m_vTextString;
//        std::vector< std::string > m_vImageFN;
    private:
        std::vector< ref_ptr<osgText::Text> >     m_vText; // 注记
        std::vector< ref_ptr<CVBF_ChartImage> >   m_vImage;// 图像

    };
    CVBF_ChartRollInfo(const std::string& strName,unsigned int numRow,unsigned int numCol);
    virtual ~CVBF_ChartRollInfo();

    // 文字样式
    VBF_TEXTSTYLE& GetGridTextStyle()	{ return m_TextStyleGrid; }


    // 设置/获取单元格的文字内容
    void SetGridText(int nRow,int nCol,std::string& sText);
//    const std::string& GetGridText(int nRow,int nCol) { return m_vTextStringGrid[nRow*m_numCol + nCol]; }

    // 设置/获取单元格的图表内容
    void SetGridGraphics(int nRow,int nCol,CVBF_Chart* pGraphics);
//    const CVBF_Chart* GetGridGraphics(int nRow,int nCol){ return m_vGraphicsGrid[nRow*m_numCol + nCol]; }

    std::vector<float>& GetColumnWidth(){ return m_vCellWidth; }

    virtual void Update(); // 更新

private:
    // 创建构成该图形的所有Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    void CreateTextGrid(const CVBF_GraphicsContext& context,CVBF_DrawableList& vDrawables);
    void CreateGraphicsGrid(const CVBF_GraphicsContext& context,CVBF_DrawableList& vDrawables);

private:

    unsigned int m_numRow; // 表格的行数
    unsigned int m_numCol; // 表格的列数

    std::vector<float> m_vCellWidth; // 表格每列的宽度

    // 各行的显示信息，可循环反复使用
    std::list< ref_ptr<CVBF_ChartRollInfo::Row> > m_listRow;
    //std::list< ref_ptr<CVBF_ChartRollInfo::Row> > m_listImage; // 待加入的

    // 表格正文
    VBF_TEXTSTYLE	m_TextStyleGrid;	// Grid文本样式
    std::vector<std::string>  m_vTextStringGrid;  // 正文的文本内容

//    std::vector< ref_ptr<osgText::Text> > m_vTextGrid; // Grid注记


//    std::vector< ref_ptr<CVBF_Chart> >  m_vGraphicsGrid;  // 正文的子图

    float m_fScroll;
};


#endif
