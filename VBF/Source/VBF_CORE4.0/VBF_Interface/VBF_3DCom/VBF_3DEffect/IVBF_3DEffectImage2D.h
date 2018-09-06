//*******************************************************************
// FileName：IVBF_3DEffectImage2D.h
// Function：2D图像特效接口
// Author:   SunC
// Date:     2012-04-12
//*******************************************************************

#ifndef __IVBF_3DEFFECT_IMAGE2D_H__
#define __IVBF_3DEFFECT_IMAGE2D_H__

#include "IVBF_3DEffect.h"


class IVBF_3DEffectImage2D : public IVBF_3DEffect
{
public:	
	virtual ~IVBF_3DEffectImage2D() {}	

	// 设置图像文件名，不含绝对路径
	virtual bool SetImageFileName(const char* szFileName)=0;

	// 函数：执行动作
	// 参数：szType				-- 动作类型，参见动作类型定义
	//       (x, y)				-- 图片中心在视口中的相对位置, 值域为[0,1]
	//		 nDurationFrames	-- 动画持续帧数
	//		 fAlpha				-- 图片的透明度，对于淡入动画，图片透明度从0渐变到alpha；对于淡出动画，图片透明度从alpha渐变到0
	//                             对于其他动画，图片一直保持alpha的透明度
	//		 fScale				-- 图片的缩放大小
	// 返回：动画执行成功，返回true，否则返回false
	virtual bool StartAction(const char* szType, float x, float y, int nDurationFrames, float fAlpha, float fScale )=0;

	// 是否需要将图像框定在视口范围以内
	virtual void SetLockInViewport(bool bLocked)=0;

	// 如果需要将图像根据视口范围缩放，确保Image2D特效在屏幕中占据固定的百分比
	virtual void SetScaleWithViewport(bool bScale)=0;
};

#endif 
