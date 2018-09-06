//*******************************************************************
// FileName：IVBF_MarkModelShapeSphere.h
// Function：军标实体模型：球体，实际上为Dome的一种特殊类型
// Author:   杜莹
// Date:     2013-07-12
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_SPHERE_H__
#define __IVBF_MARK_MODEL_SHAPE_SPHERE_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShapeDome.h>

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeSphere
// 接口描述：球体
//--------------------------------------------------------------------
class IVBF_MarkModelShapeSphere : public IVBF_MarkModelShapeDome
{
public:
	virtual ~IVBF_MarkModelShapeSphere() {}

public:

	// 设置/获取球体半径（默认情况下：原点位于球心，半径为1.0）
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeHemiSphere
// 接口描述：半球体
//--------------------------------------------------------------------
class IVBF_MarkModelShapeHemiSphere : public IVBF_MarkModelShapeSphere
{
public:
	virtual ~IVBF_MarkModelShapeHemiSphere() {}
};


#endif 
