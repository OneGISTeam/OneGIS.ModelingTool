//*******************************************************************
// FileName：IVBF_MarkAttrIntersect.h
// Function：属性：模型与地面的交线，目前只有Shape类模型可以添加此属性
// Author:   杜莹
// Date:     2015-03-20
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_INTERSECT_H__
#define __IVBF_MARK_ATTR_INTERSECT_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <Types/VBF_3DStyles.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkAttrIntersect
// 接口描述：属性：模型与地面的交线，目前只有Shape类模型可以添加此属性
//--------------------------------------------------------------------
class IVBF_MarkAttrIntersect : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrIntersect() {}

	// 设置/获取是否用填充多边形表现地面交线（默认值为false，用多边形会影响绘制速度）
	virtual void SetUsePolygon(bool bPolygon)=0;
	virtual bool IsPolygonUsed()=0;

	// 设置/获取是否只计算与大地水准面（即海平面，高程为0）的交点，默认值为false
	//（这是一种概略计算，当场景中所有Dem高程值均为0时，可设置为true，以便提高计算速度）
	virtual void SetOnlyOnGeoid(bool bOnGeoid)=0;
	virtual bool IsOnlyOnGeoid()=0;

	// 设置/获取帧间隔，即间隔几帧绘制一次交线（避免交线数据量过大，默认值为2）
	virtual void SetNumFrameInterval(int num)=0;
	virtual int  GetNumFrameInterval()=0;

	// 设置/获取是否开启地面交线的深度测试（默认为false，以便解决z-buffer争夺问题）
	virtual void EnableLineDepthTest(bool bEnable)=0;
	virtual bool IsLineDepthTestEnabled()=0;

	// 设置/获取地面交线的高度调整值（默认调整值为0.1米，以便解决z-buffer争夺问题）
	virtual void  SetLineHeightAdjust(float fHeightAdjust)=0;
	virtual float GetLineHeightAdjust()=0;

	// 设置/获取与地面交线的样式
	virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;

	// 设置/获取地面交线多边形的填充样式
	virtual void                      SetPolygonStyle(const VBF_POLYGON3DSTYLE& style)=0;
	virtual const VBF_POLYGON3DSTYLE& GetPolygonStyle()=0;

	// 开始/结束计算与地面的交线
	virtual void BeginCal()=0;
	virtual void EndCal()=0;

	// 清除所有交线
	virtual void Clear()=0;
};


#endif 
