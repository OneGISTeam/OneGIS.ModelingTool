//*******************************************************************
// FileName：IVBF_MarkAttrTrailLine.h
// Function：模型属性接口：模型的运动轨迹（折线形）
// Author:   杜莹
// Date:     2013-12-05
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_TRAIL_LINE_H__
#define __IVBF_MARK_ATTR_TRAIL_LINE_H__


#include <VBF_Plot/Common/IVBF_MarkAttrTrail.h>
#include <Types/VBF_3DStyles.h>


//=======================================================================
// 定义接口：IVBF_MarkAttrTrailLine
// 接口描述：轨迹线，不带渐变效果（速度较快）
//=======================================================================
class IVBF_MarkAttrTrailLine: public IVBF_MarkAttrTrail
{
public:
	virtual ~IVBF_MarkAttrTrailLine() {}

	// 设置/获取轨迹线是否渐变（默认值为false，开启渐变会降低系统运行速度）
	virtual void EnableFade(bool bEnable)=0;
	virtual bool IsFadeEnabled()=0;

	// 设置/获取轨迹线的样式
	virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;
};



#endif 
