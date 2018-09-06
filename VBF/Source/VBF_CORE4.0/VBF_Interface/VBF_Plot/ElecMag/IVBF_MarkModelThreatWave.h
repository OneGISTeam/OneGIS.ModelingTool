//*******************************************************************
// FileName：IVBF_MarkModelThreatWave.h
// Function：军标实体模型：攻击波，类似于扫描波的一组动态多边形
// Author:   杜莹
// Date:     2015-11-26
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_THREAT_WAVE_H__
#define __IVBF_MARK_MODEL_THREAT_WAVE_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>
#include <Types/VBF_3DStyles.h>


// 攻击波的扫描方式
enum EVBF_THREATWAVE_SCAN_MODE
{
	VBF_THREATWAVE_SCAN_MOVE	= 0,	// 平移式
	VBF_THREATWAVE_SCAN_BOUNCE	= 1		// 弹跳式（默认）
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelThreatWave
// 接口描述：攻击波，一组动态多边形，形成一个隐形的圆锥体
//--------------------------------------------------------------------
class IVBF_MarkModelThreatWave : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelThreatWave() {}

public:

	// 设置/获取圆锥张角的一半，默认值为30度（默认情况下：原点位于锥尖，底面半径为1）
	virtual void SetTess(float fHalfAngle)=0;
	virtual void GetTess(float& fHalfAngle)=0;

	/* 设置/获取圆锥的圆周分割数，默认值为36 */
	virtual void SetNumSplitCircle(int nNumSplit)=0;
	virtual int  GetNumSplitCircle()=0;

	// 设置/获取圆锥体底部半径
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;

	// 设置/获取圆锥体高度
	virtual void  SetHeight(float fHeight)=0;
	virtual float GetHeight()=0;

	// 设置/获取动态扫描的速度（单位：米/秒，默认值为0.3）
	virtual void  SetScanSpeed(float fSpeed)=0;
	virtual float GetScanSpeed()=0;

	// 设置/获取扫描线中圆环的个数（默认值为5）
	virtual void SetNumScanLines(int num)=0;
	virtual int  GetNumScanLines()=0;

	// 设置/获取扫描线的样式
	virtual void                 SetScanLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetScanLineStyle()=0;

	// 设置/获取扫描线的渐变Alpha，值域均为[0, 1]，且fAlpha0 <= fAlpha1
	virtual void SetScanLineAlpha(float fAlpha0, float fAlpha1)=0;
	virtual void GetScanLineAlpha(float& fAlpha0, float& fAlpha1)=0;

	// 设置/获取扫描方式
	virtual void                      SetScanMode(EVBF_THREATWAVE_SCAN_MODE nMode)=0;
	virtual EVBF_THREATWAVE_SCAN_MODE GetScanMode()=0;

	// 平移方式下：设置/获取扫描线高度占据整个圆锥的高度比例（值域为[0.0, 1.0]，默认值为0.2）
	virtual void  SetScanLineHeightRatio(float fRatio)=0;
	virtual float GetScanLineHeightRatio()=0;

	// 弹跳方式下：设置/获取圆锥体尖部半径与底部半径的比值（值域为[0.0, 1.0]，默认值为0.3）
	virtual void  SetBounceScaleMin(float fScaleMin)=0;
	virtual float GetBounceScaleMin()=0;
};


#endif 
