#ifndef OSGEARTHFEATURES_SCATTER_FILTER_H
#define OSGEARTHFEATURES_SCATTER_FILTER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_Common/VBF_Math/VBF_Random.h>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

    // ɢ����������ѵ����ɢ�䣬����һ�����ܶ�ɢ�䣬���ڹ���ɢ��ͼ
    class OSGEARTHFEATURES_EXPORT ScatterFilter : public FeatureFilter
    {
    public:
        static bool isSupported() { return true; }

    public:
        ScatterFilter();

        virtual ~ScatterFilter() { }

        // �����ܶȣ�ÿƽ������ĵ���
        void setDensity( float value ) { _density = value; }
        float getDensity() const { return _density; }

        // �Ƿ������ɢ�䣨���ܶ�ɢ�䣩
        void setRandom( bool value ) { _random = value; }
        bool getRandom() const { return _random; }

        // ������������������ӣ���λ����򳤶��ϵ���������
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
