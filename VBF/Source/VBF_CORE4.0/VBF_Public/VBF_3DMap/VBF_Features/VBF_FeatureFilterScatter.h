#ifndef OSGEARTHFEATURES_SCATTER_FILTER_H
#define OSGEARTHFEATURES_SCATTER_FILTER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_Common/VBF_Math/VBF_Random.h>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

    // 散射过滤器：把点随机散射，或按照一定的密度散射，用于构建散点图
    class OSGEARTHFEATURES_EXPORT ScatterFilter : public FeatureFilter
    {
    public:
        static bool isSupported() { return true; }

    public:
        ScatterFilter();

        virtual ~ScatterFilter() { }

        // 设置密度，每平方公里的点数
        void setDensity( float value ) { _density = value; }
        float getDensity() const { return _density; }

        // 是否是随机散射（或按密度散射）
        void setRandom( bool value ) { _random = value; }
        bool getRandom() const { return _random; }

        // 设置随机数产生的种子（单位面积或长度上的最大点数）
        void setRandomSeed( unsigned value ) { _randomSeed = value; }
        unsigned getRandomSeed() const { return _randomSeed; }

    public:
        virtual FilterContext push( FeatureList& input, FilterContext& context );

    protected:
        void polyScatter( const Geometry* input,const CVBF_SpatialReference* inputSRS,
            const FilterContext& context,PointSet* output);

        void lineScatter( const Geometry* input, const CVBF_SpatialReference* inputSRS,
            const FilterContext& context, PointSet* output);

    private:
        float    _density;
        bool     _random;
        unsigned _randomSeed;
        CVBF_Random   _prng;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_SUBSTITUTE_MODEL_FILTER_H
