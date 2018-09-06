#ifndef OSGEARTHFEATURES_BUFFER_FILTER_H
#define OSGEARTHFEATURES_BUFFER_FILTER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;


     // 缓冲区过滤器：对每一个输入的图形进行膨胀或侵蚀，距离为正进行膨胀，距离为负进行收缩，输出总是多边形
     // (参见http://en.wikipedia.org/wiki/Morphological_image_processing)

    class OSGEARTHFEATURES_EXPORT BufferFilter : public FeatureFilter
    {
    public:
        // Call this determine whether this filter is available. This filter uses
        // the GEOS library, so you must compile osgEarth against GEOS for this 
        // filter to be available.
        static bool isSupported();

    public:
        BufferFilter();
        BufferFilter( const BufferFilter& rhs );
        BufferFilter( const CVBF_Config& conf );

        virtual CVBF_Config getConfig() const;


        virtual ~BufferFilter() { }

    public:
        // how far to buffer; positive to dialate, negative to erode
        CVBF_Optional<double>& distance() { return _distance; }
        const CVBF_Optional<double>& distance() const { return _distance; }

        // for ENDCAP_ROUND, controls the tessellation detail for corners, 
        // measured in the number of segments to create per 90 degrees
        int numQuadrantSegments() const { return _numQuadSegs; }
        int& numQuadrantSegments() { return _numQuadSegs; }

        // tessellation style of buffered corners and line ends
        const Stroke::LineCapStyle& capStyle() const { return _capStyle; }
        Stroke::LineCapStyle& capStyle() { return _capStyle; }

    public:
        virtual FilterContext push( FeatureList& input, FilterContext& context );

    protected:
        CVBF_Optional<double> _distance;
        int                  _numQuadSegs;
        Stroke::LineCapStyle _capStyle;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_BUFFER_FILTER_H
