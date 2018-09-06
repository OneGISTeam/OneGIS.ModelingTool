//*******************************************************************
// FileName：VBF_MarkModelShapeArc.h
// Function：实体模型：二维和三维空间中的弧段（长短半轴相等时为圆弧段）
// Author:   杜莹
// Date:     2017-08-04
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_ARC_H__
#define __IVBF_MARK_MODEL_SHAPE_ARC_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_ARC_PART
// 枚举描述：弧段的各个部分
//--------------------------------------------------------------------
enum EVBF_ARC_PART
{
    VBF_ARC_PART_LINE			= 0,	// 线
    VBF_ARC_PART_FILL			= 1,	// 面
    VBF_ARC_PART_COUNT					// 总数
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeArc2D
// 接口描述：二维空间中的弧段
//--------------------------------------------------------------------
class IVBF_MarkModelShapeArc2D : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeArc2D() {}

	// 设置/获取坐标原点是否位于屏幕左上角（默认为true）
	virtual void SetOriginTopLeft(bool bTopLeft)=0;
	virtual bool IsOriginTopLeft()=0;

	// 设置/获取弧段的圆心坐标（在视口中的坐标）
	virtual void			  SetCenter(const osg::Vec3f& vPos)=0;
	virtual const osg::Vec3f& GetCenter()=0;
	
    // 设置/获取弧段的长短半轴，二者相等时为圆（单位：像素）
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;

	// 设置/获取弧段的起始角和终止角（单位：角度）
    // 参数：fAngleStart, fAngleEnd -- 起始和终止角度（与正北方向的夹角，单位：角度）
    virtual void SetTess(float fAngleStart, float fAngleEnd)=0;
    virtual void GetTess(float& fAngleStart, float& fAngleEnd)=0;

	// 设置/获取弧段分割数，默认值为36
    virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeArc3D
// 接口描述：三维空间中的弧段
//--------------------------------------------------------------------
class IVBF_MarkModelShapeArc3D : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeArc3D() {}
	
    // 设置弧段的长短半轴，二者相等时为圆（单位：米）
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;

	// 设置/获取弧段的起始角和终止角（单位：角度）
    // 参数：fAngleStart, fAngleEnd -- 起始和终止角度（与正北方向的夹角，单位：角度）
    virtual void SetTess(float fAngleStart, float fAngleEnd)=0;
    virtual void GetTess(float& fAngleStart, float& fAngleEnd)=0;

	// 设置/获取弧段分割数，默认值为36
    virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;
};


#endif 
