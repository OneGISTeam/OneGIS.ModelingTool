#ifndef OSGEARTHSYMBOLOGY_GEOMETRY_SYMBOL_H
#define OSGEARTHSYMBOLOGY_GEOMETRY_SYMBOL_H 1

#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_3DMap/VBF_Symbology/Fill.h>

namespace osgEarth { namespace Symbology
{

    // 面符号
    class OSGEARTHSYMBOLOGY_EXPORT PolygonSymbol : public Symbol
    {
    public:
        META_Symbol(PolygonSymbol);

        PolygonSymbol( const CVBF_Config& conf =CVBF_Config() );
        virtual ~PolygonSymbol();

		// 填充属性
        CVBF_Optional<Fill>& fill() { return _fill; }
        const CVBF_Optional<Fill>& fill() const { return _fill; }

        // 细分属性
        CVBF_Optional<float>& Subdivider() { return m_optSubdivider; }
        const CVBF_Optional<float>& Subdivider() const { return m_optSubdivider; }



    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig(const CVBF_Config& conf);
        static void parseSLD(const CVBF_Config& c, class Style& style);

    protected:
        CVBF_Optional<Fill> _fill;
        CVBF_Optional<float> m_optSubdivider;// 细分粒度，单位度
    };


} } // namespace osgEarth::Symbology

#endif // OSGEARTH_SYMBOLOGY_SYMBOL_H
