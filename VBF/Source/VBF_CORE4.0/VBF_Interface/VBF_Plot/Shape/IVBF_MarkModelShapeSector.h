//*******************************************************************
// FileName：IVBF_MarkModelShapeSector.h
// Function：军标实体模型：扇形
// Author:   杜莹
// Date:     2015-08-17
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_SECTOR_H__
#define __IVBF_MARK_MODEL_SHAPE_SECTOR_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_SECTOR_PART
// 枚举描述：扇形的各个部分
//--------------------------------------------------------------------
enum EVBF_SECTOR_PART
{
	VBF_SECTOR_PART_BODY		= 0,	// 主体
	VBF_SECTOR_PART_CONE_INNER	= 1,	// 内锥面
	VBF_SECTOR_PART_CONE_OUTER	= 2,	// 外锥面
	VBF_SECTOR_PART_SIDE_START	= 3,	// 起始侧面
	VBF_SECTOR_PART_SIDE_END	= 4,	// 终止侧面
	VBF_SECTOR_PART_COUNT				// 总数
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeSector
// 接口描述：扇形
//--------------------------------------------------------------------
class IVBF_MarkModelShapeSector : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeSector() {}

public:

	// 设置/获取扇形水平和垂直方向的起始角和终止角，值域分别为[0, 360],[0, 180]
	// 说明：垂直角为0度表示北极，垂直角为180度表示南极（默认情况下：原点位于球心，半径为1）
	virtual void SetTess(float fAngleH0, float fAngleH1, float fAngleV0, float fAngleV1)=0;
	virtual void GetTess(float& fAngleH0, float& fAngleH1, float& fAngleV0, float& fAngleV1)=0;

	// 设置纵横方向的分割数，默认值分为18, 36
	virtual void SetNumSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSplit(int& nNumSplitRow, int& nNumSplitCol)=0;

	// 设置/获取内外锥面的圆环分割数，默认值为6
	virtual void SetNumConeSplit(int nNumSplit)=0;
	virtual int  GetNumConeSplit()=0;

	// 设置/获取侧面圆环分割数，默认值为6
	virtual void SetNumSideSplit(int nNumSplit)=0;
	virtual int  GetNumSideSplit()=0;

	// 设置/获取扇形底面长短轴的半径及高度（三者完全相等时表示球体，默认值均为1.0）
	virtual void SetSize(float fSizeX, float fSizeY, float fSizeZ)=0;
	virtual void GetSize(float& fSizeX, float& fSizeY, float& fSizeZ)=0;
};


#endif 
