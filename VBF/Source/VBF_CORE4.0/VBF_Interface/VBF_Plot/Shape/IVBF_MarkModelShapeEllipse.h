//*******************************************************************
// FileName：VBF_MarkModelShapeEllipse.h
// Function：实体模型：二维和三维空间中的椭圆（长短半轴相等时为圆）
// Author:   杜莹
// Date:     2017-08-04
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_ELLIPSE_H__
#define __IVBF_MARK_MODEL_SHAPE_ELLIPSE_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_ELLIPSE_PART
// 枚举描述：椭圆的各个部分
//--------------------------------------------------------------------
enum EVBF_ELLIPSE_PART
{
    VBF_ELLIPSE_PART_LINE			= 0,	// 线
    VBF_ELLIPSE_PART_FILL			= 1,	// 面
    VBF_ELLIPSE_PART_COUNT					// 总数
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeEllipse2D
// 接口描述：二维空间中的椭圆
//--------------------------------------------------------------------
class IVBF_MarkModelShapeEllipse2D : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeEllipse2D() {}

	// 设置/获取坐标原点是否位于屏幕左上角（默认为true）
	virtual void SetOriginTopLeft(bool bTopLeft)=0;
	virtual bool IsOriginTopLeft()=0;

	// 设置/获取椭圆的圆心坐标（在视口中的坐标）
	virtual void			  SetCenter(const osg::Vec3f& vPos)=0;
	virtual const osg::Vec3f& GetCenter()=0;
	
    // 设置/获取椭圆的长短半轴，二者相等时为圆（单位：像素）
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;

	// 设置/获取圆周分割数，默认值为36
    virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeEllipse3D
// 接口描述：三维空间中的椭圆
//--------------------------------------------------------------------
class IVBF_MarkModelShapeEllipse3D : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeEllipse3D() {}
	
    // 设置椭圆的长短半轴，二者相等时为圆（单位：米）
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;

	// 设置/获取圆周分割数，默认值为36
    virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;
};


#endif 
