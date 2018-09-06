//*******************************************************************
// FileName：IVBF_MarkModelShape.h
// Function：各种形状军标实体模型的基类，如球体、圆锥体、圆柱体等
// Author:   杜莹
// Date:     2013-08-01
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_H__
#define __IVBF_MARK_MODEL_SHAPE_H__


#include <VBF_Plot/Common/IVBF_MarkModelGraphics.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>



// 定义各种几何体的唯一ID号
const unsigned int VBF_MARK_SHAPE_DOME				= VBF_PLOT_SHAPE + 1;	// 圆顶体
const unsigned int VBF_MARK_SHAPE_SPHERE			= VBF_PLOT_SHAPE + 2;	// 球体
const unsigned int VBF_MARK_SHAPE_HEMISPHERE		= VBF_PLOT_SHAPE + 3;	// 半球体
const unsigned int VBF_MARK_SHAPE_CONE			    = VBF_PLOT_SHAPE + 4;	// 圆锥体
const unsigned int VBF_MARK_SHAPE_CYLINDER			= VBF_PLOT_SHAPE + 5;	// 圆柱体
const unsigned int VBF_MARK_SHAPE_OVAL			    = VBF_PLOT_SHAPE + 6;	// 椭圆柱体
const unsigned int VBF_MARK_SHAPE_PRISM				= VBF_PLOT_SHAPE + 7;	// 棱柱
const unsigned int VBF_MARK_SHAPE_FRUSTUM_FLAT		= VBF_PLOT_SHAPE + 8;	// 平截头体（扁平状）
const unsigned int VBF_MARK_SHAPE_FRUSTUM_DOME		= VBF_PLOT_SHAPE + 9;	// 平截头体（球状）
const unsigned int VBF_MARK_SHAPE_PLANE             = VBF_PLOT_SHAPE + 10;	// 平面
const unsigned int VBF_MARK_SHAPE_CUBOID            = VBF_PLOT_SHAPE + 11;	// 长方体
const unsigned int VBF_MARK_SHAPE_CUBE              = VBF_PLOT_SHAPE + 12;	// 正方体
const unsigned int VBF_MARK_SHAPE_TORUS				= VBF_PLOT_SHAPE + 13;	// 圆环
const unsigned int VBF_MARK_SHAPE_TETRAHEDRON		= VBF_PLOT_SHAPE + 14;	// 四面体
const unsigned int VBF_MARK_SHAPE_REVOSURFACE		= VBF_PLOT_SHAPE + 15;	// 简单回转面
const unsigned int VBF_MARK_SHAPE_SPHERE_ATTITUDE	= VBF_PLOT_SHAPE + 16;	// 姿态球
const unsigned int VBF_MARK_SHAPE_SECTOR			= VBF_PLOT_SHAPE + 17;	// 扇形
const unsigned int VBF_MARK_SHAPE_POINT2D			= VBF_PLOT_SHAPE + 18;	// 二维点
const unsigned int VBF_MARK_SHAPE_POINT3D			= VBF_PLOT_SHAPE + 19;	// 三维点
const unsigned int VBF_MARK_SHAPE_CYLINDERS			= VBF_PLOT_SHAPE + 20;	// 分层圆柱体
const unsigned int VBF_MARK_SHAPE_ELLIPSE2D			= VBF_PLOT_SHAPE + 21;	// 二维空间中的椭圆
const unsigned int VBF_MARK_SHAPE_ELLIPSE3D			= VBF_PLOT_SHAPE + 22;	// 三维空间中的椭圆
const unsigned int VBF_MARK_SHAPE_ARC2D				= VBF_PLOT_SHAPE + 23;	// 二维空间中的弧段
const unsigned int VBF_MARK_SHAPE_ARC3D				= VBF_PLOT_SHAPE + 24;	// 三维空间中的弧段
const unsigned int VBF_MARK_SHAPE_RECT2D			= VBF_PLOT_SHAPE + 25;  // 二维空间中的矩形
const unsigned int VBF_MARK_SHAPE_RECT3D			= VBF_PLOT_SHAPE + 26;  // 三维空间中的矩形


// 定义球体横方向（沿纬度方向）分割数的最小最大值
#define VBF_SPHERE_SPLIT_ROW_MIN	3
#define VBF_SPHERE_SPLIT_ROW_MAX	180


// 定义球体纵方向（沿经度方向）分割数的最小最大值
#define VBF_SPHERE_SPLIT_COL_MIN	3
#define VBF_SPHERE_SPLIT_COL_MAX	3600
#define VBF_SPHERE_SPLIT_OUTER		3600


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShape
// 接口描述：各种形状军标实体模型的基类，如球体、圆锥体、圆柱体等
//--------------------------------------------------------------------
class IVBF_MarkModelShape : public IVBF_MarkModelGraphics
{
public:
	virtual ~IVBF_MarkModelShape() {}

    // 计算模型与地面的所有交点（地理坐标）
    virtual void CalIntersectWithEarth(bool bOnlyOnGeoid, std::vector<osg::Vec3d>& vPointsGeo)=0;
};



#endif 
