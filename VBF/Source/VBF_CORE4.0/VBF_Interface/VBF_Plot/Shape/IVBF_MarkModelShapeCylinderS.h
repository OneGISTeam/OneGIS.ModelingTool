//*******************************************************************
// FileName：IVBF_MarkModelShapeCylinderS.h
// Function：分层的圆柱
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_CYLINDERS_H__
#define __IVBF_MARK_MODEL_SHAPE_CYLINDERS_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_CYLINDER_PART
// 枚举描述：圆柱体的各个部分
//--------------------------------------------------------------------
enum EVBF_CYLINDERS_PART
{
    VBF_CYLINDERS_PART_TOP			= 0,	// 顶面
    VBF_CYLINDERS_PART_BOTTOM		= 1,	// 底面
    VBF_CYLINDERS_PART_BODY       	= 2,	// 起始侧面
    VBF_CYLINDERS_PART_COUNT				// 总数
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeCylinderS
// 接口描述：圆柱体
//--------------------------------------------------------------------
class IVBF_MarkModelShapeCylinderS : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeCylinderS() {}

public:

	/* 设置/获取圆柱体的圆周分割数，默认值为36 */
	virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;

	/* 设置/获取圆柱体的顶面圆环分割数，默认值为6 */
	virtual void SetNumTopSplit(int nNumSplit)=0;
	virtual int  GetNumTopSplit()=0;

	
	/* 设置/获取圆柱体底面长短轴的半径，二者不相等表示椭圆柱体，二者相等表示圆柱体 */
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;

    virtual void SetTopEdgeHeights(vector<double>& vHeight)=0;
    virtual void SetBottomEdgeHeights(vector<double>& vHeight)=0;
    virtual void SetTopHeights(vector<double>& vHeight)=0;


	/* 设置/获取圆柱体高度 */
	virtual void  SetHeight(float fHeight)=0;
	virtual float GetHeight()=0;
};


#endif 
