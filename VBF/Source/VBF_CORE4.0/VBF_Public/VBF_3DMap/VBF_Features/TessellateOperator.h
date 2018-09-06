#ifndef OSGEARTHFEATURES_TESSELLATE_OPERATOR_H
#define OSGEARTHFEATURES_TESSELLATE_OPERATOR_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/FilterContext.h>

namespace osgEarth { namespace Features
{
    // 把几何数据中的线状数据分割
    class OSGEARTHFEATURES_EXPORT TessellateOperator
    {
    public:
        // 分割直角坐标的线
        static void tessellateLinear( const osg::Vec3d& p0,const osg::Vec3d& p1,
                            unsigned parts,std::vector<osg::Vec3d>& out );

        // 分割地理坐标的线（大圆线或等角航线）
        static void tessellateGeo( const osg::Vec3d& p0, const osg::Vec3d& p1,
            unsigned parts, GeoInterpolation interp, std::vector<osg::Vec3d>& out );

    public:
        TessellateOperator( unsigned numPartitions =20,
                    GeoInterpolation defaultInterp =GEOINTERP_GREAT_CIRCLE );
        virtual ~TessellateOperator() { }

        // 设置分割的段数
        void setNumPartitions( unsigned value ) { _numPartitions = value; }

        // 设置地理插值方式
        void setDefaultGeoInterp( GeoInterpolation value ) { _defaultInterp = value; }

    public:
        void operator()( Feature* feature, FilterContext& context ) const;

    protected:
        unsigned         _numPartitions;
        GeoInterpolation _defaultInterp;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_TESSELLATE_OPERATOR_H
