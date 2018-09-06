#ifndef OSGEARTH_ELEVATION_QUERY_H
#define OSGEARTH_ELEVATION_QUERY_H 1

#include <VBF_3DMap/VBF_Terrain/VBF_MapFrame.h>
#include <VBF_Common/VBF_Utils/VBF_CacheLRU.h>

namespace osgEarth
{
    // 高程查询，获取的是高程的原始数据。可以查询地图上任何位置的高程数据，该方法不是采用射线相交的办法，而是直接访问地形瓦片
    class OSGEARTH_EXPORT ElevationQuery
    {
    public:
        ElevationQuery( const CVBF_Map* map );
        ElevationQuery( const CVBF_MapFrame& mapFrame );
        virtual ~ElevationQuery();


        // 获取给定点的高程，point为点的坐标，dOutH为返回的高程
        // dResDesired为期望的分辨率，0为最优分辨率，dResActual为实际的分辨率
        bool getElevation( const GeoPoint& point,double& dOutH,
            double dResDesired=0.0, double* dResActual =0L );

        // 返回的高程值存在z分量中，如果"ignoreZ"为false，新的Z值将在原始的z值上进行偏移
        bool getElevations( std::vector<osg::Vec3d>& vPoints,
            const CVBF_SpatialReference* pSRS,
            bool ignoreZ = true, double  desiredResolution =0.0 );

        bool getElevations( const std::vector<osg::Vec3d>& vPoints,
            const CVBF_SpatialReference* pSRS,
            std::vector<double>&  out_elevations, double desiredResolution = 0.0 );

        // 设置/获取缓存的最大瓦片书
        void setMaxTilesToCache( int value );
        int getMaxTilesToCache() const;
        
        // 设置最大LOD，如果值为-1则关闭该功能
        void setMaxLevelOverride(int maxLevelOverride);
        int getMaxLevelOverride() const;

        // 获取每次查询的平均时间
        double getAverageQueryTime() const { return _queries > 0.0 ? _totalTime/_queries : 0.0; }

        // 获取指定点数据的最大LOD，为了提高性能避免无效查询
        unsigned int getMaxLevel(double x, double y, const CVBF_SpatialReference* srs, const CVBF_Profile* profile ) const;

    private:
        CVBF_MapFrame  _mapf;
        unsigned  _maxCacheSize;
        int       _tileSize;        
        int       _maxLevelOverride;

        typedef CVBF_CacheLRU< CVBF_TileKey, ref_ptr<osg::HeightField> > TileCache;
        TileCache _tileCache;

        double _queries;
        double _totalTime;

    private:
        void postCTOR();
        void sync();

        bool getElevationImpl( const GeoPoint& point, double& out_elevation,
                                double dResDesired, double* dResActual=0L );
    };

} // namespace osgEarth

#endif // OSGEARTH_ELEVATION_QUERY_H
