//*******************************************************************
// FileName：IVBF_MarkModelShapeCuboid.h
// Function：军标实体模型：长方体
// Author:   杜莹
// Date:     2013-10-12
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_IMPL_H__
#define __IVBF_MARK_MODEL_SHAPE_IMPL_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_CUBOID_PART
// 枚举描述：长方体的各个部分
//--------------------------------------------------------------------
enum EVBF_CUBOID_PART
{
	VBF_CUBOID_PART_TOP		= 0,	// 顶面
	VBF_CUBOID_PART_BOTTOM	= 1,	// 底面
	VBF_CUBOID_PART_LEFT	= 2,	// 左面
	VBF_CUBOID_PART_RIGHT	= 3,	// 右面
	VBF_CUBOID_PART_FRONT	= 4,	// 前面
	VBF_CUBOID_PART_BACK	= 5,	// 后面
	VBF_CUBOID_PART_COUNT			// 总数
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeCuboid
// 接口描述：长方体
//--------------------------------------------------------------------
class IVBF_MarkModelShapeCuboid : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeCuboid() {}

public:

	// 设置/获取长方体的长宽高，三者相等表示正方体
	// （默认情况下：原点位于长方体的几何中心）
	virtual void SetTess(float length, float width, float height)=0;
	virtual void GetTess(float& length, float& width, float& height)=0;

	// 设置/获取侧面纵横方向的分割数，默认为6*6
	virtual void SetNumSideSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSideSplit(int& nNumSplitRow, int& nNumSplitCol)=0;

	// 设置/获取顶面横方向的分割数，默认为6
	virtual void SetNumTopSplit(int nNumSplit)=0;
	virtual int  GetNumTopSplit()=0;
};


#endif 
