#ifndef OSGEARTH_GEOMATH_H
#define OSGEARTH_GEOMATH_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/GeoCommon.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupCoordSys.h>

namespace osgEarth
{

	// 角度单位用弧度，距离单位用米
    class OSGEARTH_EXPORT GeoMath
    {
    public:

		// 计算两点距离：使用Haversine公式，参数为起点纬度、经度、终点纬度、经度、地球半径
        static double distance(double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad,
                               double radius = osg::WGS_84_RADIUS_EQUATOR);

		// 计算多点的距离：使用Haversine公式，点用地理坐标表示，单位为度
        static double distance(const std::vector< osg::Vec3d > &points, double radius = osg::WGS_84_RADIUS_EQUATOR);

		// 计算两点的距离
        static double distance(const osg::Vec3d& p1, const osg::Vec3d& p2, const CVBF_SpatialReference* srs);
            
		// 计算方位：参数为起点维度、经度、终点维度、经度
        static double bearing(double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad);

		// 计算两点的中点：参数为起点维度、经度、终点维度、经度
        static void midpoint(double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad,
                             double &out_latRad, double &out_lonRad);

		// 计算两点间的大圆插值（t表示相对位置，[0..1]）
        static void interpolate( double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad,
                                 double t, double& out_latRad, double& out_lonRad );

       // 通过起始点、方位、距离，计算目标点
        static void destination(double lat1Rad, double lon1Rad, double bearingRad, double distance,
                                double &out_latRad, double &out_lonRad, double radius = osg::WGS_84_RADIUS_EQUATOR);

		// 计算过两点的大圆线上的最大最小维度范围
        static void greatCircleMinMaxLatitude( double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad,
                                        double& out_minLatRad, double& out_maxLatRad);

		// 计算两点间的等角航线的距离
        static double rhumbDistance(double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad,
                           double radius = osg::WGS_84_RADIUS_EQUATOR);

		// 计算多点间的等角航线的距离，单位为度
        static double rhumbDistance(const std::vector< osg::Vec3d > &points, double radius = osg::WGS_84_RADIUS_EQUATOR);

		// 计算两点间的方位（等角航线）
        static double rhumbBearing(double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad);

		// 通过起始点、方位、距离，计算目标点（等角航线上）
        static void rhumbDestination(double lat1Rad, double lon1Rad,double bearing, double distance,
                            double &out_latRad, double &out_lonRad, double radius = osg::WGS_84_RADIUS_EQUATOR);
    };
};

#endif
