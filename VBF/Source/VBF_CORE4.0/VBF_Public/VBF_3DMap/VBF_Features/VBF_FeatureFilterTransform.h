#ifndef OSGEARTHFEATURES_TRANSFORM_FILTER_H
#define OSGEARTHFEATURES_TRANSFORM_FILTER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <Types/VBF_BoundingBox.h>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;

    // 从一种FeatureProfile变换到另一种
    class OSGEARTHFEATURES_EXPORT TransformFilter : public FeatureFilter
    {
    public:
        TransformFilter();
        TransformFilter( const osg::Matrixd& xform );
        TransformFilter( const CVBF_SpatialReference* outputSRS );

        virtual ~TransformFilter() { }

        /** Transform matrix to apply to each point. If there's is also an SRS conversion,
            the matrix will be applied first. */
        void setMatrix( const osg::Matrixd& mat ) { _mat = mat; }
        const osg::Matrixd& getMatrix() const { return _mat; }

        /** Whether to localize coordinates to the bounding box centroid (to avoid precision jitter
            when turning the data into OSG geometry) */
        void setLocalizeCoordinates( bool value ) { _localize = value; }
        bool getLocalizeCoordinates() const { return _localize; }

    public:
        FilterContext push( FeatureList& features, FilterContext& context );

    protected:
        ref_ptr<const CVBF_SpatialReference> _outputSRS;
        osg::BoundingBoxd _bbox;
        bool _localize;
        osg::Matrixd _mat;
        
        bool push( Feature* feature, FilterContext& context );
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_TRANSFORM_FILTER_H
