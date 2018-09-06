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
        std::vector< ref_ptr<osgText::Text> >     m_vText; // ע��
        std::vector< ref_ptr<CVBF_ChartImage> >   m_vImage;// ͼ��

    };
    CVBF_ChartRollInfo(const std::string& strName,unsigned int numRow,unsigned int numCol);
    virtual ~CVBF_ChartRollInfo();

    // ������ʽ
    VBF_TEXTSTYLE& GetGridTextStyle()	{ return m_TextStyleGrid; }


    // ����/��ȡ��Ԫ�����������
    void SetGridText(int nRow,int nCol,std::string& sText);
//    const std::string& GetGridText(int nRow,int nCol) { return m_vTextStringGrid[nRow*m_numCol + nCol]; }

    // ����/��ȡ��Ԫ���ͼ������
    void SetGridGraphics(int nRow,int nCol,CVBF_Chart* pGraphics);
//    const CVBF_Chart* GetGridGraphics(int nRow,int nCol){ return m_vGraphicsGrid[nRow*m_numCol + nCol]; }

    std::vector<float>& GetColumnWidth(){ return m_vCellWidth; }

    virtual void Update(); // ����

private:
    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    void CreateTextGrid(const CVBF_GraphicsContext& context,CVBF_DrawableList& vDrawables);
    void CreateGraphicsGrid(const CVBF_GraphicsContext& context,CVBF_DrawableList& vDrawables);

private:

    unsigned int m_numRow; // ��������
    unsigned int m_numCol; // ��������

    std::vector<float> m_vCellWidth; // ���ÿ�еĿ��

    // ���е���ʾ��Ϣ����ѭ������ʹ��
    std::list< ref_ptr<CVBF_ChartRollInfo::Row> > m_listRow;
    //std::list< ref_ptr<CVBF_ChartRollInfo::Row> > m_listImage; // �������

    // �������
    VBF_TEXTSTYLE	m_TextStyleGrid;	// Grid�ı���ʽ
    std::vector<std::string>  m_vTextStringGrid;  // ���ĵ��ı�����

//    std::vector< ref_ptr<osgText::Text> > m_vTextGrid; // Gridע��


//    std::vector< ref_ptr<CVBF_Chart> >  m_vGraphicsGrid;  // ���ĵ���ͼ

    float m_fScroll;
};


#endif
