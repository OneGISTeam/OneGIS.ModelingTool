#ifndef _VBF_COORD_CONVERTER_H_
#define _VBF_COORD_CONVERTER_H_

#include <VBF_Common/VBF_Math/VBF_Export.h>
#include <Types/Vec3d>
#include <Types/VBF_Matrix.h>


/**
*@note: 重置椭球体的长短轴半径，用于坐标转换的计算
*/
VBF_MATH_EXPORT void ResetEllipRadius(double radiusEquator, double radiusPolar);

/**
*@note: 转换本地经纬坐标为世界坐标系，本地坐标采用弧度表示
*/
VBF_MATH_EXPORT void RadianLLH2XYZ(const osg::Vec3d& vecLLH, osg::Vec3d& vecXYZ);

/**
*@note: 转换本地经纬坐标为世界坐标系，本地坐标采用角度表示
*/
VBF_MATH_EXPORT void DegreeLLH2XYZ(const osg::Vec3d& vecLLH, osg::Vec3d& vecXYZ);

/**
*@note: 转换世界坐标系为本地经纬坐标，本地坐标采用弧度表示
*/
VBF_MATH_EXPORT void XYZ2RadianLLH(const osg::Vec3d& vecXYZ, osg::Vec3d& vecLLH);

/**
*@note: 转换世界坐标系为本地经纬坐标，本地坐标采用角度表示
*/
VBF_MATH_EXPORT void XYZ2DegreeLLH(const osg::Vec3d& vecXYZ, osg::Vec3d& vecLLH);

/**
*@note: 转换本地经纬坐标为Matrix，本地坐标采用弧度表示
*/
VBF_MATH_EXPORT void RadiaLLH2Matrix(const osg::Vec3d& vecLLH,osg::Matrix& matrix );

/**
*@note: 转换本地经纬坐标为Matrix，本地坐标采用角度表示
*/
VBF_MATH_EXPORT void DegreeLLH2Matrix(const osg::Vec3d& vecLLH,osg::Matrix& matrix );

/**
*@note: 由经纬度求得实际高度,经纬采用弧度计算
*/
VBF_MATH_EXPORT void DegreeLL2LLH(osg::Vec3d& vecLLA);
		
/**
*@note: 由经纬度求得实际高度,经纬采用弧度计算
*/
//VBF_MATH_EXPORT void RadiaLL2LLH(osg::Vec3d& vecLLA);

/**
*@note: 局部世界坐标转成屏幕坐标
*/
//VBF_MATH_EXPORT void ConvertLocalWorldCoordToScreen(const osg::Vec3d& pos, osg::Vec2d& screenPos);

/**
*@note: 获得GeoDistance距离，获得地球坐标下的两点距离,输入的经纬度采用弧度
*/
//VBF_MATH_EXPORT double GetGeoDistance(double dSLon, double dSLat, double dELon, double dELat);

#endif
