#ifndef OSGEARTH_ELEVATION_QUERY_H
#define OSGEARTH_ELEVATION_QUERY_H 1

#include <VBF_3DMap/VBF_Terrain/VBF_MapFrame.h>
#include <VBF_Common/VBF_Utils/VBF_CacheLRU.h>

namespace osgEarth
{
    // �̲߳�ѯ����ȡ���Ǹ̵߳�ԭʼ���ݡ����Բ�ѯ��ͼ���κ�λ�õĸ߳����ݣ��÷������ǲ��������ཻ�İ취������ֱ�ӷ��ʵ�����Ƭ
    class OSGEARTH_EXPORT ElevationQuery
    {
    public:
        ElevationQuery( const CVBF_Map* map );
        ElevationQuery( const CVBF_MapFrame& mapFrame );
        virtual ~ElevationQuery();


        // ��ȡ������ĸ̣߳�pointΪ������꣬dOutHΪ���صĸ߳�
        // dResDesiredΪ�����ķֱ��ʣ�0Ϊ���ŷֱ��ʣ�dResActualΪʵ�ʵķֱ���
        bool getElevation( const GeoPoint& point,double& dOutH,
            double dResDesired=0.0, double* dResActual =0L );

        // ���صĸ߳�ֵ����z�����У����"ignoreZ"Ϊfalse���µ�Zֵ����ԭʼ��zֵ�Ͻ���ƫ��
        bool getElevations( std::vector<osg::Vec3d>& vPoints,
            const CVBF_SpatialReference* pSRS,
            bool ignoreZ = true, double  desiredResolution =0.0 );

        bool getElevations( const std::vector<osg::Vec3d>& vPoints,
            const CVBF_SpatialReference* pSRS,
            std::vector<double>&  out_elevations, double desiredResolution = 0.0 );

        // ����/��ȡ����������Ƭ��
        void setMaxTilesToCache( int value );
        int getMaxTilesToCache() const;
        
        // �������LOD�����ֵΪ-1��رոù���
        void setMaxLevelOverride(int maxLevelOverride);
        int getMaxLevelOverride() const;

        // ��ȡÿ�β�ѯ��ƽ��ʱ��
        double getAverageQueryTime() const { return _queries > 0.0 ? _totalTime/_queries : 0.0; }

        // ��ȡָ�������ݵ����LOD��Ϊ��������ܱ�����Ч��ѯ
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
