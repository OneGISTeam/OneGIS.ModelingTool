#ifndef OSGEARTHSYMBOLOGY_EXTRUSION_SYMBOL_H
#define OSGEARTHSYMBOLOGY_EXTRUSION_SYMBOL_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_3DMap/VBF_Symbology/Expression.h>

namespace osgEarth { namespace Symbology
{
    using namespace osgEarth;

    // ͹����š�ָʾGeometryCompiler����2Dʸ�����ݼ���3Dͼ��
    class OSGEARTHSYMBOLOGY_EXPORT ExtrusionSymbol : public Symbol
    {
    public:
        enum HeightReference
        {            
            HEIGHT_REFERENCE_Z,// �߶�ֵ�����������ļ������Zֵ��ʹ�øò����ǴӼ�����ԭ����λ�ü���
            HEIGHT_REFERENCE_MSL// �߶�ֵ�������MSL��ƽ����ˮ�棩��ʹ�øò����Ǵ�ˮƽ�漷��
        };
    public:
        META_Symbol(ExtrusionSymbol);

        ExtrusionSymbol( const CVBF_Config& conf =CVBF_Config() );
        virtual ~ExtrusionSymbol();

        // �����強���ĸ߶ȣ���HeightReference���
        CVBF_Optional<float>& height() { return _height; }
        const CVBF_Optional<float>& height() const { return _height; }

        // ����߶ȵļ򵥱��ʽ
        CVBF_Optional<NumericExpression>& heightExpression() { return _heightExpr; }
        const CVBF_Optional<NumericExpression>& heightExpression() const { return _heightExpr; }

        // �߶�ֵ�Ĳο���׼
        CVBF_Optional<HeightReference>& heightReference() { return _heightRef; }
        const CVBF_Optional<HeightReference>& heightReference() const { return _heightRef; }

        // �����ļ�����Ķ����Ƿ���ƽ��
        CVBF_Optional<bool>& flatten() { return _flatten; }
        const CVBF_Optional<bool>& flatten() const { return _flatten; }

        // ������ʹ�õ�style������
        CVBF_Optional<std::string>& wallStyleName() { return _wallStyleName; }
        const CVBF_Optional<std::string>& wallStyleName() const { return _wallStyleName; }

        // ������ʹ�õ�style������
        CVBF_Optional<std::string>& roofStyleName() { return _roofStyleName; }
        const CVBF_Optional<std::string>& roofStyleName() const { return _roofStyleName; }

        /** �ٷֱ�to darken the color of the bottom of the walls relative
            to the main wall color (default = 0.0, range = [0..1]) */
        CVBF_Optional<float>& wallGradientPercentage() { return _wallGradientPercentage; }
        const CVBF_Optional<float>& wallGradientPercentage() const { return _wallGradientPercentage; }
        
    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );
        static void parseSLD(const CVBF_Config& c, class Style& style);

    protected:
        CVBF_Optional<float>             _height;
        CVBF_Optional<bool>              _flatten; // ƽ�ģ������ж���һ����
        CVBF_Optional<NumericExpression> _heightExpr;
        CVBF_Optional<HeightReference>   _heightRef;
        CVBF_Optional<std::string>       _wallStyleName;
        CVBF_Optional<std::string>       _roofStyleName;
        CVBF_Optional<float>             _wallGradientPercentage;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_EXTRUSION_SYMBOL_H
