#ifndef OSGEARTH_GEOMATH_H
#define OSGEARTH_GEOMATH_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/GeoCommon.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupCoordSys.h>

namespace osgEarth
{

	// �Ƕȵ�λ�û��ȣ����뵥λ����
    class OSGEARTH_EXPORT GeoMath
    {
    public:

		// ����������룺ʹ��Haversine��ʽ������Ϊ���γ�ȡ����ȡ��յ�γ�ȡ����ȡ�����뾶
        static double distance(double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad,
                               double radius = osg::WGS_84_RADIUS_EQUATOR);

		// ������ľ��룺ʹ��Haversine��ʽ�����õ��������ʾ����λΪ��
        static double distance(const std::vector< osg::Vec3d > &points, double radius = osg::WGS_84_RADIUS_EQUATOR);

		// ��������ľ���
        static double distance(const osg::Vec3d& p1, const osg::Vec3d& p2, const CVBF_SpatialReference* srs);
            
		// ���㷽λ������Ϊ���ά�ȡ����ȡ��յ�ά�ȡ�����
        static double bearing(double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad);

		// ����������е㣺����Ϊ���ά�ȡ����ȡ��յ�ά�ȡ�����
        static void midpoint(double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad,
                             double &out_latRad, double &out_lonRad);

		// ���������Ĵ�Բ��ֵ��t��ʾ���λ�ã�[0..1]��
        static void interpolate( double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad,
                                 double t, double& out_latRad, double& out_lonRad );

       // ͨ����ʼ�㡢��λ�����룬����Ŀ���
        static void destination(double lat1Rad, double lon1Rad, double bearingRad, double distance,
                                double &out_latRad, double &out_lonRad, double radius = osg::WGS_84_RADIUS_EQUATOR);

		// ���������Ĵ�Բ���ϵ������Сά�ȷ�Χ
        static void greatCircleMinMaxLatitude( double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad,
                                        double& out_minLatRad, double& out_maxLatRad);

		// ���������ĵȽǺ��ߵľ���
        static double rhumbDistance(double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad,
                           double radius = osg::WGS_84_RADIUS_EQUATOR);

		// �������ĵȽǺ��ߵľ��룬��λΪ��
        static double rhumbDistance(const std::vector< osg::Vec3d > &points, double radius = osg::WGS_84_RADIUS_EQUATOR);

		// ���������ķ�λ���ȽǺ��ߣ�
        static double rhumbBearing(double lat1Rad, double lon1Rad, double lat2Rad, double lon2Rad);

		// ͨ����ʼ�㡢��λ�����룬����Ŀ��㣨�ȽǺ����ϣ�
        static void rhumbDestination(double lat1Rad, double lon1Rad,double bearing, double distance,
                            double &out_latRad, double &out_lonRad, double radius = osg::WGS_84_RADIUS_EQUATOR);
    };
};

#endif
