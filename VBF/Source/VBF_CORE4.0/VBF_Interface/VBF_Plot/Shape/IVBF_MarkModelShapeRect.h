//*******************************************************************
// FileName：IVBF_MarkModelRect.h
// Function：实体模型：二维和三维空间中的矩形
// Author:   杜莹
// Date:     2017-08-05
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RECT_H__
#define __IVBF_MARK_MODEL_RECT_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_RECT_PART
// 枚举描述：矩形的各个部分
//--------------------------------------------------------------------
enum EVBF_RECT_PART
{
    VBF_RECT_PART_LINE		= 0,	// 线
    VBF_RECT_PART_FILL		= 1,	// 面
    VBF_RECT_PART_COUNT				// 总数
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeRect2D
// 接口描述：二维空间中的矩形
//--------------------------------------------------------------------
class IVBF_MarkModelShapeRect2D : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeRect2D() {}

	// 设置/获取坐标原点是否位于屏幕左上角（默认为true）
	virtual void SetOriginTopLeft(bool bTopLeft)=0;
	virtual bool IsOriginTopLeft()=0;

	// 设置/获取矩形的屏幕坐标范围
	virtual void SetClientRect(float x0, float x1, float y0, float y1)=0;
	virtual void GetClientRect(float& x0, float& x1, float& y0, float& y1)=0;

	// 设置矩形纵横方向的分割数，默认为6*6
	virtual void SetNumSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSplit(int& nNumSplitRow, int& nNumSplitCol)=0;
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeRect3D
// 接口描述：三维空间中的矩形
//--------------------------------------------------------------------
class IVBF_MarkModelShapeRect3D : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeRect3D() {}

	// 设置/获取矩形的长和宽，二者相等表示正方形
	// （默认情况下：原点位于矩形的几何中心）
	virtual void SetSize(float length, float width)=0;
	virtual void GetSize(float& length, float& width)=0;

	// 设置/获取矩形纵横方向的分割数，默认为6*6
	virtual void SetNumSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSplit(int& nNumSplitRow, int& nNumSplitCol)=0;
};

#endif 
