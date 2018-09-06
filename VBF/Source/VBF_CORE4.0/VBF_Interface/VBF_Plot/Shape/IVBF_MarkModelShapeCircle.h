//*******************************************************************
// FileName：IVBF_MarkModelShapeCircle.h
// Function：军标实体模型：
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_CIRCLE_H__
#define __IVBF_MARK_MODEL_SHAPE_CIRCLE_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_CYLINDER_PART
// 枚举描述：圆柱体的各个部分
//--------------------------------------------------------------------
enum EVBF_CIRCLE_PART
{
    VBF_CIRCLE_PART_LINE			= 0,	// 线
    VBF_CIRCLE_PART_FILL			= 1,	// 面
    VBF_CIRCLE_PART_COUNT					// 总数
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeCircle
// 接口描述：圆柱体
//--------------------------------------------------------------------
class IVBF_MarkModelShapeCircle : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeCircle() {}

    // 设置/获取圆周分割数，默认值为36
    virtual void SetNumSplit(int numSplit)=0;
	virtual int  GetNumSplit()=0;
	
    // 设置半径，不等时为椭圆
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;
};


#endif 
