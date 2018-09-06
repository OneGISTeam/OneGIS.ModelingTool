#ifndef OSGEARTHFEATURES_POLYGONIZE_LINES_H
#define OSGEARTHFEATURES_POLYGONIZE_LINES_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_3DMap/VBF_Symbology/Stroke.h>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>

namespace osgEarth { namespace Features
{
    using namespace osgEarth::Symbology;

    // 把线（有粗度）转换成三角面
    class OSGEARTHFEATURES_EXPORT PolygonizeLinesOperator
    {
    public:
        PolygonizeLinesOperator(const Stroke& stoke);

        osg::Geometry* operator()(osg::Vec3Array* verts, osg::Vec3Array* normals) const;

    protected:
        Stroke _stroke;
        bool   _makeScalable;
        friend class PolygonizeLinesFilter;
    };

    // 过滤器：把线（有粗度）转换成三角面
    class OSGEARTHFEATURES_EXPORT PolygonizeLinesFilter : public FeaturesToNodeFilter
    {
    public:
        PolygonizeLinesFilter(const Style& style);
        osg::IVBF_SGNode* push( FeatureList& input, FilterContext& context );

    protected:

        Style _style;
        bool  _makeScalable;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_POLYGONIZE_LINES_H
