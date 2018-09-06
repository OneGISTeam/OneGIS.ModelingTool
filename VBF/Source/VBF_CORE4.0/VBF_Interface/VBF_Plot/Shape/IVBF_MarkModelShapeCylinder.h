//*******************************************************************
// FileName：IVBF_MarkModelShapeCylinder.h
// Function：军标实体模型：圆柱体/椭圆柱体
// Author:   杜莹
// Date:     2013-09-03
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_CYLINDER_H__
#define __IVBF_MARK_MODEL_SHAPE_CYLINDER_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_CYLINDER_PART
// 枚举描述：圆柱体的各个部分
//--------------------------------------------------------------------
enum EVBF_CYLINDER_PART
{
	VBF_CYLINDER_PART_BODY			= 0,	// 主体
	VBF_CYLINDER_PART_TOP			= 1,	// 顶面
	VBF_CYLINDER_PART_BOTTOM		= 2,	// 底面
	VBF_CYLINDER_PART_SIDE_START	= 3,	// 起始侧面
	VBF_CYLINDER_PART_SIDE_END		= 4,	// 终止侧面
	VBF_CYLINDER_PART_COUNT					// 总数
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeCylinder
// 接口描述：圆柱体
//--------------------------------------------------------------------
class IVBF_MarkModelShapeCylinder : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeCylinder() {}

public:

	/*
	* 构造圆柱体（默认情况下：原点位于圆柱体底部，底面半径和高度均为1）
	* 参数: fStratAngle -- 扇形圆柱的起始角度，值域为[0, 360]，默认值为0
	*       fEndAngle   -- 扇形圆柱的终止角度，值域为[fStratAngle, 360]，默认值为360
	*/
	virtual void SetTess(float fStartAngle, float fEndAngle)=0;
	virtual void GetTess(float& fStartAngle, float& fEndAngle)=0;

	/* 设置/获取圆柱体的圆周分割数，默认值为36 */
	virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;

	/* 设置/获取圆柱体的顶面圆环分割数，默认值为6 */
	virtual void SetNumTopSplit(int nNumSplit)=0;
	virtual int  GetNumTopSplit()=0;

	/* 设置/获取圆柱体的侧面圆环分割数，默认值为6 */
	virtual void SetNumSideSplit(int nNumSplit)=0;
	virtual int  GetNumSideSplit()=0;
	
	/* 设置/获取圆柱体底面长短轴的半径，二者不相等表示椭圆柱体，二者相等表示圆柱体 */
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;

	/* 设置/获取圆柱体高度 */
	virtual void  SetHeight(float fHeight)=0;
	virtual float GetHeight()=0;
};


#endif 
