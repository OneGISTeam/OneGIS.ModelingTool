#ifndef OSGEARTHSYMBOLOGY_ALTITUDE_SYMBOL_H
#define OSGEARTHSYMBOLOGY_ALTITUDE_SYMBOL_H 1

#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_3DMap/VBF_Symbology/Expression.h>

namespace osgEarth { namespace Symbology
{
	// 传送关于高度和地形交互的信息
    class OSGEARTHSYMBOLOGY_EXPORT AltitudeSymbol : public Symbol
    {
    public:

		// 控制模型如何贴地表
        enum Clamping
        {
            CLAMP_NONE,  // 不把Z值贴地表，但仍使用offset（如果合适的话）			
            CLAMP_TO_TERRAIN,// 把地物要素（feature）的Z值设为地形高度（贴地表），忽略地物原来的Z值
            CLAMP_RELATIVE_TO_TERRAIN,// 获取地表的高度，并把地物的原始Z值加上地表的高度
            CLAMP_ABSOLUTE// 地物拥有一个属性值描述相对于基准面（参考椭球面或平均海水面）的高度。While this will not actually modify thefeature's geometry, it will install ...
        };
		
		enum Technique // 什么时间和地点进行Clamping
		{
			TECHNIQUE_MAP, //Clamp geometry to the map model's elevation data
			TECHNIQUE_SCENE, // Clamp geometry to the terrain's scene graph
			TECHNIQUE_GPU, // Clamp geometry to the terrain as they are rendered by the GPU
			TECHNIQUE_DRAPE  // Clamp geometry at draw time using projective texturing
		};

	
        enum Binding // Binding-在什么粒度执行夹紧
        {
            BINDING_VERTEX,  // 每一个顶点（独立进行）
            BINDING_CENTROID // 几何体的中心（centroid）
        };

    public:
        META_Symbol(AltitudeSymbol);

        AltitudeSymbol( const CVBF_Config& conf =CVBF_Config() );

        // 如何把要素clamp到地形，默认为CLAMP_NONE
        CVBF_Optional<Clamping>& clamping() { return _clamping; }
        const CVBF_Optional<Clamping>& clamping() const { return _clamping; }

        // clamp到地形的技术，默认为TECHNIQUE_MAP
        CVBF_Optional<Technique>& technique() { return _technique; }
        const CVBF_Optional<Technique>& technique() const { return _technique; }

        // 执行clamp的地形分辨率（使用map单位）
        CVBF_Optional<float>& clampingResolution() { return _resolution; }
        const CVBF_Optional<float>& clampingResolution() const { return _resolution; }

        // clamp几何体的粒度（是每个顶点？还是仅几何中心？）
        CVBF_Optional<Binding>& binding() { return _binding; }
        const CVBF_Optional<Binding>& binding() const { return _binding; }

        // clamp后几何体的垂直偏移
        CVBF_Optional<NumericExpression>& verticalOffset() { return _verticalOffset; }
        const CVBF_Optional<NumericExpression>& verticalOffset() const { return _verticalOffset; }

        // clamp后应用于几何体Z值的垂直缩放因子
        CVBF_Optional<NumericExpression>& verticalScale() { return _verticalScale; }
        const CVBF_Optional<NumericExpression>& verticalScale() const { return _verticalScale; }

    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );
        static void parseSLD(const CVBF_Config& c, class Style& style);

    protected:
        virtual ~AltitudeSymbol();

        CVBF_Optional<Clamping>           _clamping;
        CVBF_Optional<Technique>          _technique;
        CVBF_Optional<Binding>            _binding;
        CVBF_Optional<float>              _resolution;
        CVBF_Optional<NumericExpression>  _verticalOffset;
        CVBF_Optional<NumericExpression>  _verticalScale;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTH_SYMBOLOGY_SYMBOL_H
