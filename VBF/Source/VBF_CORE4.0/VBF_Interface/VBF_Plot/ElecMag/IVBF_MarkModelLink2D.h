//*******************************************************************
// FileName：IVBF_MarkModelLink2D.h
// Function：实体模型接口：连通线（用二维空间中的矩形+纹理实现）
// Author:   杜莹
// Date:     2013-11-13
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_LINK_2D_H__
#define __IVBF_MARK_MODEL_LINK_2D_H__

#include <VBF_Plot/ElecMag/IVBF_MarkModelLink.h>

class IVBF_MarkModelLink2D : public IVBF_MarkModelLink
{
public:
	virtual ~IVBF_MarkModelLink2D() {}

	// 设置/获取连通线的纹理样式
	virtual void                    SetTextureStyle(bool bForLink, const VBF_LINETEXSTYLE& style)=0;
	virtual const VBF_LINETEXSTYLE& GetTextureStyle(bool bForLink)=0;
};

#endif 
