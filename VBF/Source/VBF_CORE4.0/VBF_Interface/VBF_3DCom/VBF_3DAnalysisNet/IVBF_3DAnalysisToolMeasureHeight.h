//*******************************************************************
// FileName：IVBF_3DAnalysisToolMeasureHeight.h
// Function：三维分析工具：量高分析
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_MEASUREHEIGHT_H__
#define __IVBF_3DANALYSIS_TOOL_MEASUREHEIGHT_H__


#include <VBF_3DCom/VBF_3DAnalysisNet/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolMeasureHeight : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolMeasureHeight() {}

    //函数功能:两固定点量高结果
    //输入参数：ptStart--起始点屏幕坐标，ptEnd--终止点屏幕坐标,textVisible--文字标注是否显示(默认显示)
    //输出参数：height--两点垂直高度差(m)
    //返回值：无
    virtual void GetP2PMeasureHeight(const osg::Vec2f ptStart,const osg::Vec2f ptEnd,
                                     double& height,bool textVisible=true)=0;

};

#endif
