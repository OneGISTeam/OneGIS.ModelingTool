//*******************************************************************
// FileName：IVBF_MarkModelRect2D.h
// Function：实体模型接口：2D矩形，使用屏幕坐标
// Author:   杜莹
// Date:     2014-12-26
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RECT2D_H__
#define __IVBF_MARK_MODEL_RECT2D_H__


#include <VBF_Plot/Common/IVBF_MarkModel2D.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <string>
#include <Types/VBF_3DStyles.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRect2D
// 接口描述：2D矩形，使用屏幕坐标
//--------------------------------------------------------------------
class IVBF_MarkModelRect2D : public IVBF_MarkModel2D
{
public:
	virtual ~IVBF_MarkModelRect2D() {}

	// 设置/获取矩形的几何样式，默认为：实心+边线
	virtual void                SetGeometryStyle(EVBF_GEOMETRY_STYLE nStyle)=0;
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle()=0;

	// 设置/获取矩形的实心颜色
	virtual void              SetSolidColor(const osg::Vec4f& color)=0;
	virtual const osg::Vec4f& GetSolidColor()=0;

	// 设置/获取矩形的边线样式
	virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;
};


#endif 
