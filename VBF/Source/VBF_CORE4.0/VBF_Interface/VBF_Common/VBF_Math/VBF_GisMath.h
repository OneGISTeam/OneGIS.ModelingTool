#ifndef __VBF_GIS_MATH_H__
#define __VBF_GIS_MATH_H__

#include <VBF_Common/VBF_Math/VBF_Export.h>
#include <Types/Vec3f>
#include <Types/Vec3d>
#include <vector>
// 设置椭球参数：长短半轴（单位：米）
VBF_MATH_EXPORT void VBF_SetEllipParam(double a0, double b0);

// 用高斯算法解大地正解公式 (已知B1,L1,A1,S，求B2,L2)
VBF_MATH_EXPORT void CalLBH_Gauss(double L1, double B1, double A1, double S, double& dL, double& dB, double& dA);

// 用高斯算法解大地反解公式 (已知B1,L1,B2,L2，求A1,S)
VBF_MATH_EXPORT void CalSA_Gauss(double L1, double B1, double L2, double B2, double& S, double& A1, double& A2);

// 用贝塞尔方法计算大地线长度及大地方位角
VBF_MATH_EXPORT bool CalSA_Bessel(double L1, double B1, double L2, double B2, double& S, double& A);

// 地理坐标与大地直角坐标之间的转换
VBF_MATH_EXPORT void XYZToLBH(const osg::Vec3d& ptXYZ, osg::Vec3d& ptLBH);
VBF_MATH_EXPORT void LBHToXYZ(const osg::Vec3d& ptLBH, osg::Vec3d& ptXYZ);

VBF_MATH_EXPORT void XYZToLBH(double X, double Y, double Z, double& L, double& B, double& H);
VBF_MATH_EXPORT void LBHToXYZ(double L, double B, double H, double& X, double& Y, double& Z);

// 求射线与椭球的交点（世界坐标系下）
VBF_MATH_EXPORT bool VBF_RayIntersectEllipsoid(const osg::Vec3d& ptStart, const osg::Vec3d& vDir, double dHeightAdjust,
                                               osg::Vec3d& ptIntersect, double& dDist);

// 求线段与椭球的交点（世界坐标系下）
VBF_MATH_EXPORT bool VBF_LineSegIntersectEllipsoid(const osg::Vec3d& ptStart, const osg::Vec3d& ptEnd, double dHeightAdjust,
                                                   osg::Vec3d& ptIntersect, double& dDist);
VBF_MATH_EXPORT bool VBF_OpenCubicSpline(std::vector<osg::Vec3d>& aSrc, std::vector<osg::Vec3d>& aDst, double dStep);
VBF_MATH_EXPORT bool VBF_OpenCubicSpline(const std::vector<osg::Vec2f>& aSrcConst, std::vector<osg::Vec2f>& aDst, double dStep);

#endif
