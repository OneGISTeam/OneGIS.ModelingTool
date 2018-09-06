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

    // ������ʽ
    VBF_POLYGON2DSTYLE& GetOddStyle()	{ return m_StyleOdd; } // ��������ʽ
    VBF_POLYGON2DSTYLE& GetEvenStyle()	{ return m_StyleEven; }// ż������ʽ
    VBF_POLYGON2DSTYLE& GetTitleStyle()	{ return m_StyleTitle; }// ��������ʽ

    // ��߿���ʽ
    VBF_LINESTYLE& GetOuterStyle()	{ return m_lsOuter; }

    // ������ʽ
    VBF_TEXTSTYLE& GetTitleTextStyle()	{ return m_TextStyleTitle; }
    VBF_TEXTSTYLE& GetGridTextStyle()	{ return m_TextStyleGrid; }

    // ������������
    void SetTitleText(int nCol,std::string& sText);

    // ����/��ȡ��Ԫ�����������
    void SetGridText(int nRow,int nCol,std::string& sText);
    const std::string& GetGridText(int nRow,int nCol) { return m_vTextStringGrid[nRow*m_numCol + nCol]; }

    // ����/��ȡ��Ԫ���ͼ������
    void SetGridGraphics(int nRow,int nCol,CVBF_Chart* pGraphics);
    CVBF_Chart* GetGridGraphics(int nRow,int nCol){ return m_vGraphicsGrid[nRow*m_numCol + nCol]; }


    void SetTitleHeight(double dH) { m_dTitleHeight = dH; } // ��ͷ�ĸ߶�

    std::vector<float>& GetColumnWidth(){ return m_vCellWidth; }

    virtual void Update(); // ����

private:
    // �������ɸ�ͼ�ε�����Drawable
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
    ref_ptr<osg::Geometry> m_ipDrawableTitle; // ������
    ref_ptr<osg::Geometry> m_ipDrawableOuter; // ������
private:
    ref_ptr<osg::Vec3Array>		m_ipVerts;	// Grid�Ķ���

    bool m_bHasTitle;// �Ƿ��б�ͷ

    unsigned int m_numRow; // ��������
    unsigned int m_numCol; // ��������

    std::vector<float> m_vCellWidth; // ���ÿ�еĿ��

    double m_dTitleHeight; // ��ͷ�ĸ߶�


    VBF_POLYGON2DSTYLE	m_StyleOdd;  // ������
    VBF_POLYGON2DSTYLE	m_StyleEven; // ż����
    VBF_POLYGON2DSTYLE	m_StyleTitle; // ������

    VBF_LINESTYLE m_lsOuter; // ����������ʽ

    // ������
    std::vector<std::string>  m_vTextStringTitle; // �ı�����
    std::vector< ref_ptr<osgText::Text> > m_vTextTitle; // Titleע��
    VBF_TEXTSTYLE	m_TextStyleTitle;	// Title�ı���ʽ

    // �������
    std::vector<std::string>  m_vTextStringGrid;  // ���ĵ��ı�����
    std::vector< ref_ptr<osgText::Text> > m_vTextGrid; // Gridע��
    VBF_TEXTSTYLE	m_TextStyleGrid;	// Grid�ı���ʽ
    std::vector< ref_ptr<CVBF_Chart> >  m_vGraphicsGrid;  // ���ĵ���ͼ

};


#endif
