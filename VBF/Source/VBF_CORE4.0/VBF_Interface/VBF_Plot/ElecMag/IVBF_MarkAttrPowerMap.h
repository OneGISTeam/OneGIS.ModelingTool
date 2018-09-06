//*******************************************************************
// FileName：IVBF_MarkAttrPowerMap.h
// Function：威力图
// Author:   杜莹
// Date:     2013-11-11 
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_POWER_MAP_H__
#define __IVBF_MARK_ATTR_POWER_MAP_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkAttrPowerMap
// 接口描述：威力图
//--------------------------------------------------------------------
class IVBF_MarkAttrPowerMap : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrPowerMap() {}

public:

	// 设置/获取威力图水平和垂直方向的起始角和终止角，值域分别为[0, 360],[0, 180]
	// 说明：垂直角为0度表示北极，垂直角为180度表示南极（默认情况下：原点位于球心，半径为1）
	virtual void SetTess(float fAngleH0, float fAngleH1, float fAngleV0, float fAngleV1)=0;
	virtual void GetTess(float& fAngleH0, float& fAngleH1, float& fAngleV0, float& fAngleV1)=0;

	// 设置/获取威力图半径（默认值为了1.0e5）
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;

	// 设置/获取威力图的颜色
	virtual void       SetColor(const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetColor()=0;
	
	// 设置/获取威力图的几何样式，默认为：实心+网格
	virtual void                SetGeometryStyle(EVBF_GEOMETRY_STYLE nStyle)=0;
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle()=0;
};



#endif 
