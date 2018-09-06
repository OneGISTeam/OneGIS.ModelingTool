#ifndef __VBF_CHART_PART_GRID_H__
#define __VBF_CHART_PART_GRID_H__

#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>
// ��������
class VBF_HUDAUX_EXPORT CVBF_ChartPartGrid : public CVBF_Chart
{
public:
    CVBF_ChartPartGrid();

    void Set(int numRow,int numCol);// �����������������������ߵ���Ŀ��������������1��
    void SetGridLineVisible(bool bVisibleH,bool bVisibleV);// �����������Ƿ�ɼ�
    void SetGridFillVisible(bool bVisible); // ���������Ƿ����

    // ��ȡ��/�����ʽ
    VBF_LINESTYLE&      GetLineStyle()    { return m_lsGrid; }
    VBF_POLYGON2DSTYLE& GetFillStyleOdd() { return m_StyleOdd; }
    VBF_POLYGON2DSTYLE& GetFillStyleEven(){ return m_StyleEven; }

    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);
    virtual void Update();
private:
    void CreateGridLineH(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables);
    void CreateGridLineV(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables);
    void CreateFillOddRow(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables);
    void CreateFillEvenRow(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables);

    int m_numRow; // ��
    int m_numCol; // ��

    VBF_LINESTYLE       m_lsGrid;
    VBF_POLYGON2DSTYLE	m_StyleOdd;  // ������/��
    VBF_POLYGON2DSTYLE	m_StyleEven; // ż����/��

    bool m_bVisibleLineH;
    bool m_bVisibleLineV;
    bool m_bVisibleFill;

    ref_ptr<osg::Vec3Array>		m_ipVertsH;		// ˮƽ����
    ref_ptr<osg::Geometry>		m_ipDrawableLineH;	//

    ref_ptr<osg::Vec3Array>		m_ipVertsV;		// ��ֱ����
    ref_ptr<osg::Geometry>		m_ipDrawableLineV;	//

    ref_ptr<osg::Geometry>		m_ipDrawableOddRow;	//
    ref_ptr<osg::Geometry>		m_ipDrawableEvenRow;//


};

#endif 
