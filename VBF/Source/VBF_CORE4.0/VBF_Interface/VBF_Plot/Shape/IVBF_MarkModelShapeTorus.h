//*******************************************************************
// FileName：IVBF_MarkModelShapeTorus.h
// Function：军标实体模型：圆环
// Author:   杜莹
// Date:     2013-10-10
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_TORUS_H__
#define __IVBF_MARK_MODEL_SHAPE_TORUS_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>

//--------------------------------------------------------------------
// 定义枚举：EVBF_TORUS_PART
// 枚举描述：圆环的各个部分
//--------------------------------------------------------------------
enum EVBF_TORUS_PART
{
	VBF_TORUS_PART_BODY	= 0,		// 主体
	VBF_TORUS_PART_COUNT			// 总数
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeTorus
// 接口描述：圆环
//--------------------------------------------------------------------
class IVBF_MarkModelShapeTorus : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeTorus() {}

public:

	// 设置/获取圆环的内外半径，默认值分别为：1.0, 4.0
	virtual void SetTess(float fRadiusInner, float fRadiusOuter)=0;
	virtual void GetTess(float& fRadiusInner, float& fRadiusOuter)=0;

	// 设置圆环纵横方向的分割数，默认值分为12, 36
	virtual void SetNumSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSplit(int& nNumSplitRow, int& nNumSplitCol)=0;
};


#endif 
