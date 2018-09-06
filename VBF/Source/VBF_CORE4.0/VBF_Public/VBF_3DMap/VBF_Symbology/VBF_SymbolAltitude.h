#ifndef OSGEARTHSYMBOLOGY_ALTITUDE_SYMBOL_H
#define OSGEARTHSYMBOLOGY_ALTITUDE_SYMBOL_H 1

#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_3DMap/VBF_Symbology/Expression.h>

namespace osgEarth { namespace Symbology
{
	// ���͹��ڸ߶Ⱥ͵��ν�������Ϣ
    class OSGEARTHSYMBOLOGY_EXPORT AltitudeSymbol : public Symbol
    {
    public:

		// ����ģ��������ر�
        enum Clamping
        {
            CLAMP_NONE,  // ����Zֵ���ر�����ʹ��offset��������ʵĻ���			
            CLAMP_TO_TERRAIN,// �ѵ���Ҫ�أ�feature����Zֵ��Ϊ���θ߶ȣ����ر������Ե���ԭ����Zֵ
            CLAMP_RELATIVE_TO_TERRAIN,// ��ȡ�ر�ĸ߶ȣ����ѵ����ԭʼZֵ���ϵر�ĸ߶�
            CLAMP_ABSOLUTE// ����ӵ��һ������ֵ��������ڻ�׼�棨�ο��������ƽ����ˮ�棩�ĸ߶ȡ�While this will not actually modify thefeature's geometry, it will install ...
        };
		
		enum Technique // ʲôʱ��͵ص����Clamping
		{
			TECHNIQUE_MAP, //Clamp geometry to the map model's elevation data
			TECHNIQUE_SCENE, // Clamp geometry to the terrain's scene graph
			TECHNIQUE_GPU, // Clamp geometry to the terrain as they are rendered by the GPU
			TECHNIQUE_DRAPE  // Clamp geometry at draw time using projective texturing
		};

	
        enum Binding // Binding-��ʲô����ִ�мн�
        {
            BINDING_VERTEX,  // ÿһ�����㣨�������У�
            BINDING_CENTROID // ����������ģ�centroid��
        };

    public:
        META_Symbol(AltitudeSymbol);

        AltitudeSymbol( const CVBF_Config& conf =CVBF_Config() );

        // ��ΰ�Ҫ��clamp�����Σ�Ĭ��ΪCLAMP_NONE
        CVBF_Optional<Clamping>& clamping() { return _clamping; }
        const CVBF_Optional<Clamping>& clamping() const { return _clamping; }

        // clamp�����εļ�����Ĭ��ΪTECHNIQUE_MAP
        CVBF_Optional<Technique>& technique() { return _technique; }
        const CVBF_Optional<Technique>& technique() const { return _technique; }

        // ִ��clamp�ĵ��ηֱ��ʣ�ʹ��map��λ��
        CVBF_Optional<float>& clampingResolution() { return _resolution; }
        const CVBF_Optional<float>& clampingResolution() const { return _resolution; }

        // clamp����������ȣ���ÿ�����㣿���ǽ��������ģ���
        CVBF_Optional<Binding>& binding() { return _binding; }
        const CVBF_Optional<Binding>& binding() const { return _binding; }

        // clamp�󼸺���Ĵ�ֱƫ��
        CVBF_Optional<NumericExpression>& verticalOffset() { return _verticalOffset; }
        const CVBF_Optional<NumericExpression>& verticalOffset() const { return _verticalOffset; }

        // clamp��Ӧ���ڼ�����Zֵ�Ĵ�ֱ��������
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
