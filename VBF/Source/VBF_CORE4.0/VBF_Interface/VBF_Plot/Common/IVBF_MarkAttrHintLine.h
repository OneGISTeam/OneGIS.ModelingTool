//*******************************************************************
// FileName：IVBF_MarkAttrHintLine.h
// Function：模型属性接口：高度线，用于提示用户模型当前的位置
// Author:   杜莹
// Date:     2013-12-05
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_HINTLINE_H__
#define __IVBF_MARK_ATTR_HINTLINE_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <Types/VBF_3DStyles.h>


class IVBF_MarkAttrHintLine : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrHintLine() {}

	// 设置/获取高度线的样式
	virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;
};


#endif 
