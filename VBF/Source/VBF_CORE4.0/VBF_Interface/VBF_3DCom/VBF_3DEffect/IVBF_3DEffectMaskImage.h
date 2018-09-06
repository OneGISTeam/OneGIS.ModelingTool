//***************************************************************************************
// FileName：IVBF_3DEffectMaskImage.h
// Function：3D图像蒙板类接口
// Author:   SunC
// Date:     2012-04-23
//***************************************************************************************

#ifndef __IVBF_3DEFFECT_MASKIMAGE_H__
#define __IVBF_3DEFFECT_MASKIMAGE_H__

#include "IVBF_3DEffect.h"
#include <string>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <Types/Vec2d>
#include <Types/Vec4f>



//-------------------------------------------------------------------
// 定义接口：IVBF_3DEffectMaskImage
// 接口描述：图像蒙板特效
//-------------------------------------------------------------------
class IVBF_3DEffectMaskImage : public IVBF_3DEffect
{
public:
	virtual ~IVBF_3DEffectMaskImage() {}

public:   

	// 设置图像的文件名
	virtual bool SetImageFileName(const char* szImgFn)=0;

	// 设置图像的地理范围
	virtual bool SetGeoBounds(double xmin, double ymin, double xmax, double ymax)=0;

	// 设置透明度
	virtual void SetAlpha(float fAlpha)=0;

	// 设置相对地面的高度
	virtual void SetRelativeHeight(double dheight)=0;

    //-------------------------------------------------------------------------------------------------
	// 函数：StartAction()
	// 描述：由对象创建动作
	// 参数：EffectType			-- 动作类型，参见动作类型定义
	//		nDurationFrames		-- 动作持续帧数
	// 备注：目前高于地面的图像蒙版未加入拉伸动画,使用此动画时SetHeight()中dHeight应设置为0.0
	//-------------------------------------------------------------------------------------------------
	virtual bool StartAction(const char* szEffectType, int nDurationFrames)=0;
};

#endif