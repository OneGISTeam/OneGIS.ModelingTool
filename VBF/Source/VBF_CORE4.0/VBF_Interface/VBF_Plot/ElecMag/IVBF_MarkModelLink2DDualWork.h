//*******************************************************************
// FileName：IVBF_MarkModelLink2DDualWork.h
// Function：实体模型接口：连通线（用二维空间中的矩形+纹理实现）
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_LINK_2D_DUAL_WORK_H__
#define __IVBF_MARK_MODEL_LINK_2D_DUAL_WORK_H__

#include <VBF_Plot/ElecMag/IVBF_MarkModelLink.h>

class IVBF_MarkModelLink2DDualWork : public IVBF_MarkModelLink
{
public:

    virtual ~IVBF_MarkModelLink2DDualWork() {}

	// 设置/获取连通线的纹理样式
    virtual void                    SetTextureStyle(bool bForLink, const VBF_LINETEXSTYLE& style)=0;
    virtual const VBF_LINETEXSTYLE& GetTextureStyle(bool bForLink)=0;

	// 设置/获取是否左向（默认值为true）
    virtual void  SetDirectionLeft(bool bLeft)=0;
	virtual bool  IsDirectionLeft()=0;
};

#endif 
