//***************************************************************************************
// FileName：IVBF_3DEffectMask.h
// Function：3D蒙板类接口
// Author:   SunC
// Date:     2012-04-07
//***************************************************************************************

#ifndef __IVBF_3DEFFECT_MASK_H__
#define __IVBF_3DEFFECT_MASK_H__

#include "IVBF_3DEffect.h"
#include <string>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <Types/Vec2d>
#include <Types/Vec4f>


//-------------------------------------------------------------------
// 定义结构体：VBF_3DMASKSTYLE
// 结构体描述：蒙板样式
//-------------------------------------------------------------------
typedef struct _tagVBF3DMaskStyle
{
	osg::Vec4f			cFillColor;				// 蒙板填充的颜色
	osg::Vec4f			cLineColor;				// 蒙板边界线的颜色
	float				fLineWidth;				// 蒙板边界线的线宽
	float				fExtrusionHeight;		// 蒙板挤出的高度

	// 构造函数
	_tagVBF3DMaskStyle()
	{
		cFillColor		  = osg::Vec4f(0.1f, 0.6f, 0.6f, 0.5f);	
		cLineColor		  = osg::Vec4f(0.1f, 0.6f, 0.6f, 0.5f);	
		fLineWidth		  = 1.0f;
		fExtrusionHeight  = 0.0f;
	}

	_tagVBF3DMaskStyle& operator=(const _tagVBF3DMaskStyle& src)
	{
		this->cFillColor		    = src.cFillColor;
		this->cLineColor		    = src.cLineColor;
		this->fLineWidth		    = src.fLineWidth;
		this->fExtrusionHeight  = src.fExtrusionHeight;

		return *this;
	}

} VBF_3DMASKSTYLE;


//-------------------------------------------------------------------
// 定义接口：IVBF_3DEffectMask
// 接口描述：蒙板特效
//-------------------------------------------------------------------
class IVBF_3DEffectMask : public IVBF_3DEffect
{
public:
	virtual ~IVBF_3DEffectMask() {}

public:

	// 设置地理坐标串
	virtual bool SetGeoVertices(osg::Vec3dArray* pVertices)=0;

	// 设置样式
	virtual bool SetStyle(VBF_3DMASKSTYLE* pStyle)=0;

	// 设置标签
	virtual bool SetLabel(const char* szLabel)=0;

    //-------------------------------------------------------------------------------------------------
	// 函数：StartAction()
	// 描述：由对象创建动作
	// 参数：EffectType			-- 动作类型，参见动作类型定义
	//		nDurationFrames		-- 动作持续帧数
	//		alpha				-- 透明度，对于淡入动作，透明度从0渐变到alpha,对于淡出动作，透明度从alpha渐变到0,对于其他动作，一直保持alpha的透明度
	//		extrusionHeight		-- 蒙板挤出高度
	//-------------------------------------------------------------------------------------------------
	virtual bool StartAction(const char* szEffectType, int nDurationFrames, float fAlpha)=0;	
};

#endif