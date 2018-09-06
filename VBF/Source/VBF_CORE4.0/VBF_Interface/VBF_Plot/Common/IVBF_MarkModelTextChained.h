//*******************************************************************
// FileName：IVBF_MarkModelTextChained.h
// Function：军标实体模型接口：散列式
// Author:   杜莹
// Date:     2013-12-04
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_TEXT_CHAINED_H__
#define __IVBF_MARK_MODEL_TEXT_CHAINED_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <string>
#include <vector>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelTextChained
// 接口描述：散列式文本
//--------------------------------------------------------------------
class IVBF_MarkModelTextChained : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelTextChained() {}

	// 设置/获取文本内容
    virtual void			   SetText(const std::string& strText, const std::vector<osg::Vec3d>& vPointsGeo)=0;
	virtual const std::string& GetText()=0;

	// 获取文本对应的坐标串
	virtual const std::vector<osg::Vec3d>& GetPointsGeo()=0;

	// 设置/获取文本样式
	virtual void                 SetTextStyle(const VBF_TEXTSTYLE& style)=0;
	virtual const VBF_TEXTSTYLE& GetTextStyle()=0;
};


#endif 
