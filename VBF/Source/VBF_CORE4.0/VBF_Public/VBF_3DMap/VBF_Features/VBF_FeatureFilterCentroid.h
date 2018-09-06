#ifndef OSGEARTHFEATURES_CENTROID_FILTER_H
#define OSGEARTHFEATURES_CENTROID_FILTER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

    // 用几何中心点替换feature的几何数据
    class OSGEARTHFEATURES_EXPORT CentroidFilter : public FeatureFilter
    {
    public:
        CentroidFilter();
        virtual ~CentroidFilter() { }

    public:
        virtual FilterContext push( FeatureList& input, FilterContext& context );
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_CENTROID_FILTER_H
