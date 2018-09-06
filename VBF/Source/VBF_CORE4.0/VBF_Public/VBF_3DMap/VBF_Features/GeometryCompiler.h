#ifndef OSGEARTH_FEATURES_GEOMETRY_COMPILER_H
#define OSGEARTH_FEATURES_GEOMETRY_COMPILER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/FeatureCursor.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilterResample.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Terrain/GeoMath.h>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

	// 编译器选项
    class OSGEARTHFEATURES_EXPORT GeometryCompilerOptions : public CVBF_Options
    {
    public:
        GeometryCompilerOptions( const CVBF_Options& conf =CVBF_Options() );      
        virtual ~GeometryCompilerOptions() { }

    public:
        // 生成的边的最大跨度（单位度），仅用于geocentric地图
        CVBF_Optional<double>& maxGranularity() { return _maxGranularity_deg; }
        const CVBF_Optional<double>& maxGranularity() const { return _maxGranularity_deg; }

 		// 地理点的差值类型（大圆线或等角航线）
        CVBF_Optional<GeoInterpolation>& geoInterp() { return _geoInterp; }
        const CVBF_Optional<GeoInterpolation>& geoInterp() const { return _geoInterp; }

		// 是否合并多个features的geometry 
        CVBF_Optional<bool>& mergeGeometry() { return _mergeGeometry; }
        const CVBF_Optional<bool>& mergeGeometry() const { return _mergeGeometry; }
	
		// 提取feature名字的求值表达式
        CVBF_Optional<StringExpression>& featureName() { return _featureNameExpr; }
        const CVBF_Optional<StringExpression>& featureName() const { return _featureNameExpr; }

		// 是否把feature的geometries聚簇在一起以提高速度
        CVBF_Optional<bool>& clustering() { return _clustering; }
        const CVBF_Optional<bool>& clustering() const { return _clustering; }

        /** Whether to enabled draw-instancing for model substitution */
        CVBF_Optional<bool>& instancing() { return _instancing; }
        const CVBF_Optional<bool>& instancing() const { return _instancing; }

        /** Whether to ignore the altitude filter (e.g. if you plan to do auto-clamping layer) */
        CVBF_Optional<bool>& ignoreAltitudeSymbol() { return _ignoreAlt; }
        const CVBF_Optional<bool>& ignoreAltitudeSymbol() const { return _ignoreAlt; }

        //todo: merge this with geoInterp()
        CVBF_Optional<osgEarth::Features::ResampleFilter::ResampleMode>& resampleMode() { return _resampleMode;}
        const CVBF_Optional<osgEarth::Features::ResampleFilter::ResampleMode>& resampleMode() const { return _resampleMode;}

        CVBF_Optional<double>& resampleMaxLength() { return _resampleMaxLength; }
        const CVBF_Optional<double>& resampleMaxLength() const { return _resampleMaxLength;}

        CVBF_Optional<bool>& useVertexBufferObjects() { return _useVertexBufferObjects;}
        const CVBF_Optional<bool>& useVertexBufferObjects() const { return _useVertexBufferObjects;}

        CVBF_Optional<ShaderPolicy>& shaderPolicy() { return _shaderPolicy; }
        const CVBF_Optional<ShaderPolicy>& shaderPolicy() const { return _shaderPolicy; }


    public:
        CVBF_Config getConfig() const;
        void mergeConfig( const CVBF_Config& conf );

    private:
        CVBF_Optional<double>               _maxGranularity_deg;
        CVBF_Optional<GeoInterpolation>     _geoInterp;
        CVBF_Optional<bool>                 _mergeGeometry;
        CVBF_Optional<StringExpression>     _featureNameExpr;
        CVBF_Optional<bool>                 _clustering;
        CVBF_Optional<bool>                 _instancing;
        CVBF_Optional<ResampleFilter::ResampleMode> _resampleMode;
        CVBF_Optional<double>               _resampleMaxLength;
        CVBF_Optional<bool>                 _ignoreAlt;
        CVBF_Optional<bool>                 _useVertexBufferObjects;
        CVBF_Optional<ShaderPolicy>         _shaderPolicy;

        void fromConfig( const CVBF_Config& conf );
    };


	// 矢量特征数据编译器：把矢量特征数据集合编译为场景图节点
    class OSGEARTHFEATURES_EXPORT GeometryCompiler
    {
    public:
        GeometryCompiler();
        GeometryCompiler( const GeometryCompilerOptions& options );     
        virtual ~GeometryCompiler() { }
        
        // 获取编译选项
        const GeometryCompilerOptions& options() const { return _options; }
        GeometryCompilerOptions& options() { return _options; }

    public:

        // 把矢量特征数据集合编译为场景图节点
        osg::IVBF_SGNode* compile( FeatureCursor* input, const Style& style, const FilterContext& context);
        osg::IVBF_SGNode* compile( Feature* input, const Style& style, const FilterContext& context);
        osg::IVBF_SGNode* compile( Feature* input, const FilterContext& context);
        osg::IVBF_SGNode* compile( Geometry* geom, const Style& style, const FilterContext& context);
        osg::IVBF_SGNode* compile( Geometry* geom, const FilterContext& context );
        osg::IVBF_SGNode* compile( FeatureList& mungeableInput, const Style& style, const FilterContext& context);

    protected:
        GeometryCompilerOptions _options;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTH_FEATURES_GEOMETRY_COMPILER_H
