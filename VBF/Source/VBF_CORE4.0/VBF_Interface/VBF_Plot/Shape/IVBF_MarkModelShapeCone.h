//*******************************************************************
// FileName：IVBF_MarkModelShapeCone.h
// Function：军标实体模型：圆锥体
// Author:   杜莹
// Date:     2013-08-02
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_CONE_H__
#define __IVBF_MARK_MODEL_SHAPE_CONE_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


// 定义圆锥体半张角的最小最大值（单位：角度）
#define VBF_CONE_HALFANGLE_MIN		0.000001f
#define VBF_CONE_HALFANGLE_MAX		89.999999f


//--------------------------------------------------------------------
// 定义枚举：EVBF_CONE_PART
// 枚举描述：圆锥体的各个部分
//--------------------------------------------------------------------
enum EVBF_CONE_PART
{
	VBF_CONE_PART_BODY		= 0,	// 主体
	VBF_CONE_PART_HEAD		= 1,	// 顶部
	VBF_CONE_PART_SCANLINE	= 2,	// 动态扫描线
	VBF_CONE_PART_COUNT				// 总数
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeCone
// 接口描述：圆锥体
//--------------------------------------------------------------------
class IVBF_MarkModelShapeCone : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeCone() {}

public:

	// 设置/获取圆锥张角的一半，默认值为30度（默认情况下：原点位于锥尖，底面半径为1）
	virtual void SetTess(float fHalfAngle)=0;
	virtual void GetTess(float& fHalfAngle)=0;

	// 设置/获取圆锥的头部是否为扁平状（默认为true），为false时表示头部为球状
	virtual void SetHeadFlat(bool bFlat)=0;
	virtual bool IsHeadFlat()=0;

	/* 设置/获取圆锥的圆周分割数，默认值为36 */
	virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;

	/* 设置/获取圆锥的外锥面分割数，默认值为6 */
	virtual void SetNumBodySplit(int nNumSplit)=0;
	virtual int  GetNumBodySplit()=0;

	/* 设置/获取圆锥的顶面/底面圆环分割数，默认值为6 */
	virtual void SetNumTopSplit(int nNumSplit)=0;
	virtual int  GetNumTopSplit()=0;

	// 设置/获取圆锥体底面半径
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;
	
	// 设置/获取圆锥体高度
	virtual void  SetHeight(float fHeight)=0;
	virtual float GetHeight()=0;

	// 设置/获取是否开启动态扫描（默认为false）
	virtual void EnableScan(bool bEnable)=0;
	virtual bool IsScanEnabled()=0;

	// 设置/获取动态扫描的速度（单位：米/秒，默认值为0.3）
	virtual void  SetScanSpeed(float fSpeed)=0;
	virtual float GetScanSpeed()=0;

	// 设置/获取扫描线中圆环的个数（默认值为5）
	virtual void SetNumScanLines(int num)=0;
	virtual int  GetNumScanLines()=0;

	// 设置/获取扫描线高度占据整个圆锥的高度比例（默认值为0.2，值域为[0.0, 1.0]）
	virtual void  SetScanLineHeightRatio(float fRatio)=0;
	virtual float GetScanLineHeightRatio()=0;
};


#endif 
