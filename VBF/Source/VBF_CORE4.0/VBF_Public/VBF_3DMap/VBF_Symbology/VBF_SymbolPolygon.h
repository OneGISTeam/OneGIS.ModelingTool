#ifndef OSGEARTHSYMBOLOGY_GEOMETRY_SYMBOL_H
#define OSGEARTHSYMBOLOGY_GEOMETRY_SYMBOL_H 1

#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_3DMap/VBF_Symbology/Fill.h>

namespace osgEarth { namespace Symbology
{

    // �����
    class OSGEARTHSYMBOLOGY_EXPORT PolygonSymbol : public Symbol
    {
    public:
        META_Symbol(PolygonSymbol);

        PolygonSymbol( const CVBF_Config& conf =CVBF_Config() );
        virtual ~PolygonSymbol();

		// �������
        CVBF_Optional<Fill>& fill() { return _fill; }
        const CVBF_Optional<Fill>& fill() const { return _fill; }

        // ϸ������
        CVBF_Optional<float>& Subdivider() { return m_optSubdivider; }
        const CVBF_Optional<float>& Subdivider() const { return m_optSubdivider; }



    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig(const CVBF_Config& conf);
        static void parseSLD(const CVBF_Config& c, class Style& style);

    protected:
        CVBF_Optional<Fill> _fill;
        CVBF_Optional<float> m_optSubdivider;// ϸ�����ȣ���λ��
    };


} } // namespace osgEarth::Symbology

#endif // OSGEARTH_SYMBOLOGY_SYMBOL_H
