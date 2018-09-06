#ifndef __VBF_CHART_PART_BK_H__
#define __VBF_CHART_PART_BK_H__

#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>


// ͼ����������
class VBF_HUDAUX_EXPORT CVBF_ChartParkBK:public CVBF_Chart
{
public:
    CVBF_ChartParkBK(const std::string& strName);
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    void SetHorizontal(bool bHorizontal) { m_bHorizontal = bHorizontal; }
protected:
    ref_ptr<osg::Geometry>		m_ipDrawable;
    ref_ptr<osg::Vec3Array>		m_ipVerts;		// ������Ķ���
    bool m_bHorizontal;
    std::string  m_sFnColorTable;// ɫ���ļ���
};


#endif 
