//*******************************************************************
// FileName：IVBF_MarkModelShapeFrustum.h
// Function：军标实体模型：平截头体（原点位于锥尖处）
// Author:   杜莹
// Date:     2013-09-05
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_FRUSTUM_H__
#define __IVBF_MARK_MODEL_SHAPE_FRUSTUM_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>
#include <Types/Vec3f>



//--------------------------------------------------------------------
// 定义枚举：EVBF_FRUSTUM_DOME_PART
// 枚举描述：圆顶状平截头体的各个部分
//--------------------------------------------------------------------
enum EVBF_FRUSTUM_DOME_PART
{
	VBF_FRUSTUM_DOME_PART_HEAD		= 0,	// 头部
	VBF_FRUSTUM_DOME_PART_LEFT		= 1,	// 左面
	VBF_FRUSTUM_DOME_PART_RIGHT		= 2,	// 右面
	VBF_FRUSTUM_DOME_PART_FRONT		= 3,	// 前面
	VBF_FRUSTUM_DOME_PART_BACK		= 4,	// 后面
	VBF_FRUSTUM_DOME_PART_COUNT				// 总数
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeFrustum
// 接口描述：平截头体
//--------------------------------------------------------------------
class IVBF_MarkModelShapeFrustum : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeFrustum() {}

public:

	// 设置/获取平截头体水平/垂直张角的一半，值域分别为[0, 90], [0, 180]
	// （默认情况下：原点位于锥尖，即最近距离=0处）
	virtual void SetTess(float fHalfAngleH, float fHalfAngleV)=0;
	virtual void GetTess(float& fHalfAngleH, float& fHalfAngleV)=0;

	// 设置/获取平截头体的旋转轴，默认为(0,0,1)
	virtual void SetAxis(const osg::Vec3f& vAxis)=0;
	virtual osg::Vec3f GetAxis()=0;

	// 设置/获取顶面横方向的分割数，默认为6*6
	virtual void SetNumHeadSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumHeadSplit(int& nNumSplitRow, int& nNumSplitCol)=0;

	// 设置/获取侧面纵横方向的分割数，默认为6
	virtual void SetNumSideSplitRow(int nNumSplit)=0;
	virtual int  GetNumSideSplitRow()=0;
};


//--------------------------------------------------------------------
// 定义枚举：EVBF_FRUSTUM_FLAT_PART
// 枚举描述：扁平状平截头体的各个部分
//--------------------------------------------------------------------
enum EVBF_FRUSTUM_FLAT_PART
{
	VBF_FRUSTUM_FLAT_PART_TOP		= 0,	// 顶面（即近裁剪面）
	VBF_FRUSTUM_FLAT_PART_BOTTOM	= 1,	// 底面（即远裁剪面）
	VBF_FRUSTUM_FLAT_PART_LEFT		= 2,	// 左面
	VBF_FRUSTUM_FLAT_PART_RIGHT		= 3,	// 右面
	VBF_FRUSTUM_FLAT_PART_FRONT		= 4,	// 前面
	VBF_FRUSTUM_FLAT_PART_BACK		= 5,	// 后面
	VBF_FRUSTUM_FLAT_PART_COUNT				// 总数
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeFrustumFlat
// 接口描述：扁平状平截头体
//--------------------------------------------------------------------
class IVBF_MarkModelShapeFrustumFlat : public IVBF_MarkModelShapeFrustum
{
public:
	virtual ~IVBF_MarkModelShapeFrustumFlat() {}

	// 设置/获取扁平状平截头体的远近裁剪面，默认值分别为0, 1
	virtual void SetNearFar(float fNear, float fFar)=0;
	virtual void GetNearFar(float& fNear, float& fFar)=0;
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeFrustumDome
// 接口描述：圆顶状平截头体
//--------------------------------------------------------------------
class IVBF_MarkModelShapeFrustumDome : public IVBF_MarkModelShapeFrustum
{
public:
	virtual ~IVBF_MarkModelShapeFrustumDome() {}

	// 设置/获取圆顶状平截头体的半径
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;
};


#endif 
