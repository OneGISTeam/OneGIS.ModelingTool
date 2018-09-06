//*******************************************************************
// FileName：IVBF_MarkModelLinkRing.h
// Function：实体模型接口：连通线（用三维空间中的环+纹理实现）
// Author:   杜莹
// Date:     2013-11-13 
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_LINK_RING_H__
#define __IVBF_MARK_MODEL_LINK_RING_H__

#include <VBF_Plot/ElecMag/IVBF_MarkModelLink.h>


class IVBF_MarkModelLinkRing : public IVBF_MarkModelLink
{
public:
	virtual ~IVBF_MarkModelLinkRing() {}

	// 设置/获取连通线的纹理样式
	virtual void                    SetTextureStyle(bool bForLink, const VBF_LINETEXSTYLE& style)=0;
	virtual const VBF_LINETEXSTYLE& GetTextureStyle(bool bForLink)=0;

	// 设置/获取线段是否可见（穿插在圆环中间，默认为false）
	virtual void SetLineVisible(bool bVisible)=0;
	virtual bool IsLineVisible()=0;

	// 设置/获取连通线的线段样式
	virtual void				 SetLineStyle(bool bForLink, const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle(bool bForLink)=0;

	// 设置/获取弧段的最大高度，默认值为0
	virtual void   SetArcMaxHeight(double dHeight)=0;
	virtual double GetArcMaxHeight()=0;

	// 设置/获取圆周分割数
	virtual void SetNumSplitCircle(int num)=0;
	virtual int  GetNumSplitCircle()=0;
};

#endif 
