//*******************************************************************
// FileName：IVBF_MarkModelLinkMeteor.h
// Function：实体模型接口：连通线（用流星线方式实现）
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_LINK_METEOR_H__
#define __IVBF_MARK_MODEL_LINK_METEOR_H__


#include <VBF_Plot/ElecMag/IVBF_MarkModelLink.h>
#include <VBF_Common/VBF_Math/VBF_Math.h>


class IVBF_MarkModelLinkMeteor : public IVBF_MarkModelLink
{
public:
    virtual ~IVBF_MarkModelLinkMeteor() {}

	// 设置/获取连通线的线段样式
	virtual void				 SetLineStyle(bool bForLink, const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetLineStyle(bool bForLink)=0;

    // 设置/获取背景线的线段样式
    virtual void				 SetBkLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetBkLineStyle()=0;

    virtual void SetTexImage(osg::Image* pImage)=0;
};

#endif 
