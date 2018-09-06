//***************************************************************************************
// FileName： IVBF_3DPlotEditor.h
// Function： 3D标图编辑器接口，负责模型的编辑
// Author:    杜莹
// Date:      2015-01-02
//***************************************************************************************

#ifndef __IVBF_3DPLOT_EDITOR_H__
#define __IVBF_3DPLOT_EDITOR_H__


#include <VBF_Base/VBF_Referenced.h>
#include <string>
#include <Types/Vec4>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>

//------------------------------------------------------------------
// 定义枚举：EVBF_EDITOR_ROTATE_TYPE
// 枚举描述：模型编辑时的旋转方式
//------------------------------------------------------------------
enum EVBF_EDITOR_ROTATE_TYPE
{
	VBF_EDITOR_ROTATE_NONE	= 0,		// 禁止旋转
	VBF_EDITOR_ROTATE_XYZ	= 1,		// 同时在三个平面内旋转
	VBF_EDITOR_ROTATE_Z		= 2			// 仅在xoy平面旋转
};

//------------------------------------------------------------------
// 定义枚举：EVBF_EDITOR_SCALE_TYPE
// 枚举描述：模型编辑时的缩放方式
//------------------------------------------------------------------
enum EVBF_EDITOR_SCALE_TYPE
{
	VBF_EDITOR_SCALE_NONE	= 0,		// 禁止缩放
	VBF_EDITOR_SCALE_XYZ	= 1			// 同时沿三个轴缩放
};

//------------------------------------------------------------------
// 定义枚举：EVBF_EDITOR_TRANSLATE_TYPE
// 枚举描述：模型编辑时的平移方式
//------------------------------------------------------------------
enum EVBF_EDITOR_TRANSLATE_TYPE
{
	VBF_EDITOR_TRANSLATE_NONE				= 0,	// 禁止平移
	VBF_EDITOR_TRANSLATE_XYPLANE_ZAXIS		= 1,	// 整体沿xy平面、z轴全局平移
	VBF_EDITOR_TRANSLATE_LOCAL_SAMEHEIGHT	= 2,	// 局部控制点在相同高度移动
	VBF_EDITOR_TRANSLATE_LOCAL_DIFFHEIGHT	= 3		// 局部控制点在不同高度移动
};
class IVBF_MarkModel;
// 快速选择信息提示，采用自定义图表时图表的创建器
class IVBF_MarkGraphicsCreator : public CVBF_Referenced
{
public:
    virtual CVBF_Graphics* CreateGraphics(IVBF_MarkModel* pIMark)=0;
};
//------------------------------------------------------------------
// 定义接口：IVBF_3DPlotEditor
// 接口描述：3D军标模型的编辑接口
//------------------------------------------------------------------
class IVBF_3DPlotEditor : public CVBF_Referenced
{
public:
	virtual ~IVBF_3DPlotEditor() {}

    // 设置/获取模型编辑使用的Dragger是否固定大小 (单位：像素)
	virtual void SetDraggerFixedSizeInPixels(bool bEnable, float fSizeInPixels=260)=0;
	virtual void GetDraggerFixedSizeInPixels(bool& bEnable, float& fSizeInPixels)=0;

	// 设置/获取Dragger中线段的宽度（默认值为2.0）
	virtual void  SetDraggerLineWidth(float fWidth)=0;
	virtual float GetDraggerLineWidth()=0;

	// 设置/获取Dragger中线段是否光滑（默认值为true，如果某些显卡的线段中出现黑色细线，可将该选项设置为false）
	virtual void EnableDraggerLineSmooth(bool bEnable)=0;
	virtual bool IsDraggerLineSmoothEnabled()=0;

	// 设置/获取Dragger中三个坐标轴的颜色（默认值分别为红、绿、蓝）
	virtual void SetDraggerAxisColor(const osg::Vec4f& colorX, const osg::Vec4f& colorY, const osg::Vec4f& colorZ)=0;
	virtual void GetDraggerAxisColor(osg::Vec4f& colorX, osg::Vec4f& colorY, osg::Vec4f& colorZ)=0;
    virtual void SetQuickSelectInfTipAsChart(IVBF_MarkGraphicsCreator* pICreator)=0;
};


#endif
