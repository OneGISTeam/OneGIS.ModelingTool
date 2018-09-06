#ifndef __VBF_CHART_PART_GRID_H__
#define __VBF_CHART_PART_GRID_H__

#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>
// 坐标网格
class VBF_HUDAUX_EXPORT CVBF_ChartPartGrid : public CVBF_Chart
{
public:
    CVBF_ChartPartGrid();

    void Set(int numRow,int numCol);// 设置网格行列数（是网格线的数目，行列数比这少1）
    void SetGridLineVisible(bool bVisibleH,bool bVisibleV);// 设置网格线是否可见
    void SetGridFillVisible(bool bVisible); // 设置网格是否填充

    // 获取线/填充样式
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

    int m_numRow; // 行
    int m_numCol; // 列

    VBF_LINESTYLE       m_lsGrid;
    VBF_POLYGON2DSTYLE	m_StyleOdd;  // 奇数行/列
    VBF_POLYGON2DSTYLE	m_StyleEven; // 偶数行/列

    bool m_bVisibleLineH;
    bool m_bVisibleLineV;
    bool m_bVisibleFill;

    ref_ptr<osg::Vec3Array>		m_ipVertsH;		// 水平顶点
    ref_ptr<osg::Geometry>		m_ipDrawableLineH;	//

    ref_ptr<osg::Vec3Array>		m_ipVertsV;		// 垂直顶点
    ref_ptr<osg::Geometry>		m_ipDrawableLineV;	//

    ref_ptr<osg::Geometry>		m_ipDrawableOddRow;	//
    ref_ptr<osg::Geometry>		m_ipDrawableEvenRow;//


};

#endif 
