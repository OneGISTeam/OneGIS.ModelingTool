#ifndef OSGEARTHFEATURES_SCALE_FILTER_H
#define OSGEARTHFEATURES_SCALE_FILTER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;

    // Ëõ·Å¹ýÂËÆ÷£º
    class OSGEARTHFEATURES_EXPORT ScaleFilter : public FeatureFilter
    {
    public:
        ScaleFilter();
        ScaleFilter( double scale );

        virtual ~ScaleFilter() { }

        double scale() const { return _scale; }
        double& scale() { return _scale; }

    public:
        virtual FilterContext push( FeatureList& input, FilterContext& cx );

    protected:
        double _scale;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_SCALE_FILTER_H
