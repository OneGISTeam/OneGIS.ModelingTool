#ifndef OSGEARTHFEATURES_EXTRUDE_GEOMETRY_FILTER_H
#define OSGEARTHFEATURES_EXTRUDE_GEOMETRY_FILTER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_3DMap/VBF_Symbology/Expression.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>

namespace osgEarth { namespace Features 
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;
    
    class FeatureSourceIndex;


    // 根据2D图形向Z方向挤出3D图形
    class OSGEARTHFEATURES_EXPORT ExtrudeGeometryFilter : public FeaturesToNodeFilter
    {
    public:
        struct HeightCallback : public ::CVBF_Referenced
        {
            virtual float operator()( Feature* input, const FilterContext& cx ) =0;
        };

    public:
        ExtrudeGeometryFilter();
        virtual ~ExtrudeGeometryFilter() { }

        // 设置挤出的样式设置
        void setStyle( const Style& style );

        osg::IVBF_SGNode* push( FeatureList& input, FilterContext& context );

    public:

        // 设置不需要新的法向量的最大拐角（maximum wall angle）
        void setWallAngleThreshold( float angle_deg ) { _wallAngleThresh_deg = angle_deg; }

        /**
         * Sets whether to render a bottom top. Useful for creating stencil volumes.
         */
        void setMakeStencilVolume( bool value ) { _makeStencilVolume = value; }
        
        /**
         * Sets the expression to evaluate when setting a feature name.
         * NOTE: setting this forces geometry-merging to OFF
         */
        void setFeatureNameExpr( const StringExpression& expr ) { _featureNameExpr = expr; }
        const StringExpression& getFeatureNameExpr() const { return _featureNameExpr; }

        // 是否使用VBO
        CVBF_Optional<bool>& useVertexBufferObjects() { return _useVertexBufferObjects;}
        const CVBF_Optional<bool>& useVertexBufferObjects() const { return _useVertexBufferObjects;}


    protected:

        // a set of geodes indexed by stateset pointer, for pre-sorting geodes based on 
        // their texture usage
        typedef std::map<osg::StateSet*, ref_ptr<osg::IVBF_SGNodeGeometry> > SortedGeodeMap;
        SortedGeodeMap                 _geodes;
        ref_ptr<osg::StateSet>    _noTextureStateSet;

        CVBF_Optional<double>               _maxAngle_deg;
        CVBF_Optional<bool>                 _mergeGeometry;
        float                          _wallAngleThresh_deg;
        float                          _cosWallAngleThresh;
        StringExpression               _featureNameExpr;
        ref_ptr<HeightCallback>   _heightCallback;
        CVBF_Optional<NumericExpression>    _heightOffsetExpr;
        CVBF_Optional<NumericExpression>    _heightExpr;
        bool                           _makeStencilVolume;
        CVBF_Optional<bool>                 _useVertexBufferObjects;

        Style                          _style;
        bool                           _styleDirty;

        ref_ptr<const ExtrusionSymbol> _extrusionSymbol;
        ref_ptr<const SkinSymbol>      _wallSkinSymbol;
        ref_ptr<const PolygonSymbol>   _wallPolygonSymbol;
        ref_ptr<const SkinSymbol>      _roofSkinSymbol;
        ref_ptr<const PolygonSymbol>   _roofPolygonSymbol;
        ref_ptr<const LineSymbol>      _outlineSymbol;
        ref_ptr<ResourceLibrary>       _wallResLib;
        ref_ptr<ResourceLibrary>       _roofResLib;

        void reset( const FilterContext& context );
        
        void addDrawable( 
            osg::Drawable*      drawable, 
            osg::StateSet*      stateSet, 
            const std::string&  name,
            Feature*            feature,
            FeatureSourceIndex* index);
        
        bool process( 
            FeatureList&     input,
            FilterContext&   context );

        bool extrudeGeometry(
            const Geometry*      input,
            double               height,
            double               offset,
            bool                 uniformHeight,
            osg::Geometry*       walls,
            osg::Geometry*       top_cap,
            osg::Geometry*       bottom_cap,
            osg::Geometry*       outline,
            const osg::Vec4&     wallColor,
            const osg::Vec4&     wallBaseColor,
            const osg::Vec4&     roofColor,
            const osg::Vec4&     outlineColor,
            const SkinResource*  wallSkin,
            const SkinResource*  roofSkin,
            FilterContext&       cx );
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_BUILD_GEOMETRY_FILTER_H
