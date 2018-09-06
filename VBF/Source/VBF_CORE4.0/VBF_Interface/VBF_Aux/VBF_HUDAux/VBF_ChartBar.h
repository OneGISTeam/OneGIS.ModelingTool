#ifndef __VBF_CHART_BAR_H__
#define __VBF_CHART_BAR_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsText.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>

// 条状图，用于显示类似进度条
class VBF_HUDAUX_EXPORT CVBF_ChartBar : public CVBF_Chart
{
public:
    CVBF_ChartBar(const std::string& strName,const std::string& sFnColorTable,unsigned int numBar,double dMaxValue);
    virtual ~CVBF_ChartBar();

    virtual void Update(); // 更新

    void SetValue(double dValue) { m_dValue = dValue; m_bDirtyData = true; }
    double GetValue() { return m_dValue; }
    void SetBlankRatio(double dRatio) { m_dBlankRatio = dRatio; }
    void SetSameColorPerBar(bool bSame) { m_bSameColorPerBar = bSame; }
    void SetHorizontal(bool bHorizontal){ m_bHorizontal = bHorizontal; }
    void SetRightAline(bool bRightAline){ m_bRightAline = bRightAline; }
private:
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    ref_ptr<osg::Vec3Array>	m_ipVerts;			// 顶点
    ref_ptr<osg::Geometry>  m_ipDrawable;

    unsigned int m_numBar;
    double       m_dMaxValue;
    std::string  m_sFnColorTable;// 色谱文件名

    double m_dValue;

    double m_dBlankRatio; // 空白所占的比例
    bool   m_bSameColorPerBar;// 每个条的左右颜色是否一致
    bool   m_bHorizontal;
    bool   m_bRightAline;




};


#endif
