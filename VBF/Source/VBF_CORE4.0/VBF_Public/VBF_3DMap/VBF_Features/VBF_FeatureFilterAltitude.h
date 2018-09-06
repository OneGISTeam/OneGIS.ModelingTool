#ifndef OSGEARTHFEATURES_CLAMP_FILTER_H
#define OSGEARTHFEATURES_CLAMP_FILTER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;

    // 高程过滤器：把几何体赋予高程值
    class OSGEARTHFEATURES_EXPORT AltitudeFilter : public FeatureFilter
    {
    public:
        AltitudeFilter();       
        virtual ~AltitudeFilter() { }

    public: // properties

        /** Shortcut to set any properties that are represented in a style. */
        void setPropertiesFromStyle( const Style& style );

        /** Maximum terrain resolution to consider when clamping */
        void setMaxResolution( double value ) { _maxRes = value; }
        double getMaxResolution() const { return _maxRes; }

    public:
        virtual FilterContext push( FeatureList& input, FilterContext& cx );

    protected:
        ref_ptr<const AltitudeSymbol> _altitude;
        double                             _maxRes;
        std::string                        _maxZAttr, _minZAttr, _terrainZAttr;

        void pushAndClamp( FeatureList& input, FilterContext& cx );
        void pushAndDontClamp( FeatureList& input, FilterContext& cx );
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_CLAMP_FILTER_H
