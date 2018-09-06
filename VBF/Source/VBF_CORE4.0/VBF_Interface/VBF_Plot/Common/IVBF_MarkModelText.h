//*******************************************************************
// FileName：IVBF_MarkModelText.h
// Function：军标实体模型接口：文本
// Author:   杜莹
// Date:     2013-12-04
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_TEXT_H__
#define __IVBF_MARK_MODEL_TEXT_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <string>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_TEXTPOS_TYPE
// 枚举描述：文本的定位方式
//--------------------------------------------------------------------
enum EVBF_TEXTPOS_TYPE
{
	VBF_TEXTPOS_GEO					= 0,	// 用户设置的地理坐标
	VBF_TEXTPOS_WORLD				= 1,	// 用户设置的世界坐标
	VBF_TEXTPOS_SCREEN				= 2,	// 用户设置的屏幕坐标
	VBF_TEXTPOS_PARENTGEO			= 3,	// 父模型的地理坐标（默认值）
    VBF_TEXTPOS_PARENTBOXTOPCENTER	= 4,	// 父模型包围盒顶部中心的地理坐标（注意：此时要求父模型必须为Raster类）
    VBF_TEXTPOS_PARENTBOXBOTTOMCENTER= 5,   // 父模型包围盒顶部中心的地理坐标（注意：此时要求父模型必须为Raster类）
    VBF_TEXTPOS_PARENTBOXCENTERRIGHT = 6    // 父模型包围盒顶部中心的地理坐标（注意：此时要求父模型必须为Raster类）
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelText
// 接口描述：文本型军标实体模型
//--------------------------------------------------------------------
class IVBF_MarkModelText : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelText() {}

	// 设置/获取文本内容
	virtual void			   SetText(const std::string& strText)=0;
	virtual const std::string& GetText()=0;

	// 设置/获取文本样式
	virtual void                 SetTextStyle(const VBF_TEXTSTYLE& style)=0;
	virtual const VBF_TEXTSTYLE& GetTextStyle()=0;

	// 设置/获取文本背景框的可见性
	virtual void SetFrameVisible(bool bVisible)=0;
	virtual bool IsFrameVisible()=0;

	// 设置/获取文本背景框的样式
	virtual void                      SetFrameStyle(const VBF_POLYGON2DSTYLE& style)=0;
	virtual const VBF_POLYGON2DSTYLE& GetFrameStyle()=0;

	// 设置/获取是否绘制背景框中的定位标识符（即文本矩形左边的小三角形，默认为true）
	virtual void SetIndicatorVisible(bool bVisible)=0;
	virtual bool IsIndicatorVisible()=0;

	// 设置/获取定位方式
    virtual void              SetPosType(EVBF_TEXTPOS_TYPE nPosType)=0;
    virtual EVBF_TEXTPOS_TYPE GetPosType()=0;

	// 设置世界坐标系下的坐标
	virtual void SetWorldPos(const osg::Vec3d& vPos)=0;

	// 设置/获取屏幕坐标系下的坐标（单位：像素，默认值为(0,0,-1)）
	virtual void       SetScreenPos(const osg::Vec3d& vPos)=0;
	virtual osg::Vec3d GetScreenPos()=0;

	// 设置/获取屏幕坐标系下的偏移量（单位：像素，默认值均为0）
	virtual void SetScreenOffset(float fOffsetX, float fOffsetY)=0;
	virtual void GetScreenOffset(float& fOffsetX, float& fOffsetY)=0;

    // 获取文本框当前占据的屏幕位置（注意：x0<x1, y0<y1）
    virtual void GetScreenRect(float& x0, float& y0, float& x1, float& y1)=0;
};


#endif 
