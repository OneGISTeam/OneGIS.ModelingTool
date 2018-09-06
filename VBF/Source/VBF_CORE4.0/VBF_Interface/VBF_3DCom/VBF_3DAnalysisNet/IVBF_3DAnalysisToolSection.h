//*******************************************************************
// FileName：IVBF_3DAnalysisToolSection.h
// Function：三维分析工具：两点之间的剖面分析
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_SECTION_H__
#define __IVBF_3DANALYSIS_TOOL_SECTION_H__


#include <VBF_3DCom/VBF_3DAnalysisNet/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolSection : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolSection() {}

	// 设置/获取分析结果中墙的顶部颜色
	virtual void SetWallColor(const osg::Vec4f& colorTop, const osg::Vec4f& colorBottom)=0;
	virtual void GetWallColor(osg::Vec4f& colorTop, osg::Vec4f& colorBottom)=0;

	// 设置/获取分析结果中墙的顶部曲线颜色
	virtual void                 SetWallLineStyleTop(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetWallLineStyleTop()=0;

	// 设置/获取分析结果中墙的底部曲线颜色
	virtual void                 SetWallLineStyleBottom(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetWallLineStyleBottom()=0;

	// 设置/获取分析结果中垂线的样式
	virtual void                 SetVertLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetVertLineStyle()=0;

	// 设置/获取分析结果中起点/终点/最大最小高程点的样式
	virtual void                  SetMinMaxPointStyle(const VBF_POINTSTYLE& style)=0;
	virtual const VBF_POINTSTYLE& GetMinMaxPointStyle()=0;

	// 设置/获取分析结果中当前选中点的样式
	virtual void                  SetSelectedPointStyle(const VBF_POINTSTYLE& style)=0;
	virtual const VBF_POINTSTYLE& GetSelectedPointStyle()=0;
};

#endif
