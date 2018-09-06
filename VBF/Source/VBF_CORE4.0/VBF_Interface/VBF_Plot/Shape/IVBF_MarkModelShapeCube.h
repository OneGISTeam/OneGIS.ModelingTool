//*******************************************************************
// FileName：IVBF_MarkModelShapeCube.h
// Function：军标实体模型：正方体
// Author:   杜莹
// Date:     2013-10-12
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_CUBE_H__
#define __IVBF_MARK_MODEL_SHAPE_CUBE_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShapeCuboid.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeCube
// 接口描述：正方体
//--------------------------------------------------------------------
class IVBF_MarkModelShapeCube : public IVBF_MarkModelShapeCuboid
{
public:
	virtual ~IVBF_MarkModelShapeCube() {}

public:

    // 设置/获取正方体的边长（此时IVBF_MarkModelShapeCuboid::SetTess()函数失效）
	// （默认情况下：原点位于正方体几何中心，边长为1）
	virtual void  SetSize(float fSize)=0;
	virtual float GetSize()=0;
};


#endif 
