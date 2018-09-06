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

	// ������ѡ��
    class OSGEARTHFEATURES_EXPORT GeometryCompilerOptions : public CVBF_Options
    {
    public:
        GeometryCompilerOptions( const CVBF_Options& conf =CVBF_Options() );      
        virtual ~GeometryCompilerOptions() { }

    public:
        // ���ɵıߵ�����ȣ���λ�ȣ���������geocentric��ͼ
        CVBF_Optional<double>& maxGranularity() { return _maxGranularity_deg; }
        const CVBF_Optional<double>& maxGranularity() const { return _maxGranularity_deg; }

 		// �����Ĳ�ֵ���ͣ���Բ�߻�ȽǺ��ߣ�
        CVBF_Optional<GeoInterpolation>& geoInterp() { return _geoInterp; }
        const CVBF_Optional<GeoInterpolation>& geoInterp() const { return _geoInterp; }

		// �Ƿ�ϲ����features��geometry 
        CVBF_Optional<bool>& mergeGeometry() { return _mergeGeometry; }
        const CVBF_Optional<bool>& mergeGeometry() const { return _mergeGeometry; }
	
		// ��ȡfeature���ֵ���ֵ���ʽ
        CVBF_Optional<StringExpression>& featureName() { return _featureNameExpr; }
        const CVBF_Optional<StringExpression>& featureName() const { return _featureNameExpr; }

		// �Ƿ��feature��geometries�۴���һ��������ٶ�
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


	// ʸ���������ݱ���������ʸ���������ݼ��ϱ���Ϊ����ͼ�ڵ�
    class OSGEARTHFEATURES_EXPORT GeometryCompiler
    {
    public:
        GeometryCompiler();
        GeometryCompiler( const GeometryCompilerOptions& options );     
        virtual ~GeometryCompiler() { }
        
        // ��ȡ����ѡ��
        const GeometryCompilerOptions& options() const { return _options; }
        GeometryCompilerOptions& options() { return _options; }

    public:

        // ��ʸ���������ݼ��ϱ���Ϊ����ͼ�ڵ�
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
