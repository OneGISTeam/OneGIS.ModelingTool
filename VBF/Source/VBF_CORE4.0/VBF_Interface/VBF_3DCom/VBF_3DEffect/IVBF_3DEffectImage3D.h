//*******************************************************************
// FileName：IVBF_3DEffectImage3D.h
// Function：3D图像特效接口
// Author:   杜莹
// Date:     2012-04-29
//*******************************************************************

#ifndef __IVBF_3DEFFECT_IMAGE3D_H__
#define __IVBF_3DEFFECT_IMAGE3D_H__

#include "IVBF_3DEffect.h"

// 该文件中定义了高程值夹取方式
#include "VBF_3DCom/VBF_AltitudeClampTypes.h"


class IVBF_3DEffectImage3D : public IVBF_3DEffect
{
public:	
	virtual ~IVBF_3DEffectImage3D() {}

	// 设置地理坐标
	virtual void SetGeoPosition(double L, double B, double H, const char* szAltitudeClamp)=0;

	// 添加一个LOD子节点，图像文件名，出现和消失的视线距离，缩放比(单位：米)
	// 参数：bAutoScaleToScreen -- 是否固定像素数	
	//       fSizeInWorld       -- 世界坐标系下的尺寸 (单位：米)，只有当bAutoScaleToScreen=false时才启用, 此时忽略fScale
	//       fScale				-- 缩放系数，只有当bAutoScaleToScreen=true时才启用
	virtual bool AddLodChild(const char* szImgFn, float fRangeMin, float fRangeMax, bool bAutoScaleToScreen, float fSizeInWorld, float fScale)=0;

	// 函数：创建一个3D图像动画
	// 参数：szType				-- 动作类型，参见动作类型定义
	//       (L, B, H)			-- 图片的地理坐标
	//		 nClampMode			-- 高程值夹取方式，参见枚举VBF_ALTITUDE_CLAMP的定义
	//		 nDurationFrames	-- 动画持续帧数
	//		 fAlpha				-- 图片的透明度，对于淡入动画，图片透明度从0渐变到alpha；对于淡出动画，图片透明度从alpha渐变到0
	//                             对于其他动画，图片一直保持alpha的透明度
	//		 fScale				-- 图片的缩放大小
	// 返回：动画执行成功，返回true，否则返回false
	virtual bool StartAction(const char* szType, int nDurationFrames)=0;	
};

#endif 
