//*******************************************************************
// FileName：IVBF_MarkAttrLabelChained.h
// Function：模型属性接口：散列式标签，用于沿线标注折线型模型
// Author:   杜莹
// Date:     2014-09-01
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_LABEL_CHAINED_H__
#define __IVBF_MARK_ATTR_LABEL_CHAINED_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <VBF_Plot/Common/IVBF_MarkModelText.h>



class IVBF_MarkAttrLabelChained : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrLabelChained() {}

    // 添加一串沿线散列的文本
    virtual void AddText(const std::string& strText, const std::vector<osg::Vec3d>& vPointsGeo)=0;

	// 设置/获取文本样式
	virtual void                 SetTextStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetTextStyle()=0;
};


#endif 
