#ifndef OSGEARTHFEATURES_BUILD_GEOMETRY_FILTER_H
#define OSGEARTHFEATURES_BUILD_GEOMETRY_FILTER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Terrain/GeoMath.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>

namespace osgEarth { namespace Features 
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;


    // 根据输入的地物构建几何节点
    class OSGEARTHFEATURES_EXPORT BuildGeometryFilter : public FeaturesToNodeFilter
    {
    public:
        BuildGeometryFilter( const Style& style =Style() );

        virtual ~BuildGeometryFilter() { }

        osg::IVBF_SGNode* push( FeatureList& input, FilterContext& context );

        const Style& getStyle() { return _style; }
        void setStyle(const Style& s) { _style = s; }

        /**
         * For geocentric data, sets the granularity of edges created by the filter. This
         * is the maximum angle (in degrees) between the vectors representing two geocentric
         * points comprising an edge. Since large polygons won't naturally conform to the
         * ellipsoid very well, this setting lets you specify a minimum edge size so that they
         * will break down and conform better.
         */
        CVBF_Optional<double>& maxGranularity() { return _maxAngle_deg; }
        const CVBF_Optional<double>& maxGranularity() const { return _maxAngle_deg; }

        // 差值方法，默认为等角航线（GEOINTERP_RHUMBLINE）
        CVBF_Optional<GeoInterpolation>& geoInterp() { return _geoInterp; }
        const CVBF_Optional<GeoInterpolation>& geoInterp() const { return _geoInterp; }

        /**
         * Whether to merge the geometries from mutliple features together. Doing this can
         * help performance by batching geometries together. The downside will be that individual
         * geometries are no longer addressable in the scene graph. Default is FALSE.
         */
        CVBF_Optional<bool>& mergeGeometry() { return _mergeGeometry; }
        const CVBF_Optional<bool>& mergeGeometry() const { return _mergeGeometry; }

        // 设置表达式，该表达式用于设置地物的名字
        CVBF_Optional<StringExpression>& featureName() { return _featureNameExpr; }
        const CVBF_Optional<StringExpression>& featureName() const { return _featureNameExpr; }

        // 是否使用VBO
        CVBF_Optional<bool>& useVertexBufferObjects() { return _useVertexBufferObjects;}
        const CVBF_Optional<bool>& useVertexBufferObjects() const { return _useVertexBufferObjects;}

    protected:
        ref_ptr<osg::IVBF_SGNode> _result;
        ref_ptr<osg::IVBF_SGNodeGeometry> _geode;
        Style _style;
        CVBF_Optional<double> _maxAngle_deg;
        CVBF_Optional<GeoInterpolation> _geoInterp;
        CVBF_Optional<bool> _mergeGeometry;
        CVBF_Optional<StringExpression> _featureNameExpr;
        CVBF_Optional<bool> _useVertexBufferObjects;
        bool _hasPoints;
        bool _hasLines;
        bool _hasPolygons;

        void reset();
        
        bool process( FeatureList& input, const FilterContext& context );
        
        void buildPolygon( Geometry* input, const CVBF_SpatialReference* featureSRS,
            const CVBF_SpatialReference* mapSRS,
            bool makeECEF, bool tessellate, osg::Geometry* osgGeom);
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_BUILD_GEOMETRY_FILTER_H
