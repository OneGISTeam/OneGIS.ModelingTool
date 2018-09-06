#ifndef OSGEARTHSYMBOLOGY_POINT_SYMBOL_H
#define OSGEARTHSYMBOLOGY_POINT_SYMBOL_H 1

#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_3DMap/VBF_Symbology/Fill.h>

namespace osgEarth { namespace Symbology
{
	// 点符号
    class OSGEARTHSYMBOLOGY_EXPORT PointSymbol : public Symbol
    {
    public:
        META_Symbol(PointSymbol);

        PointSymbol( const CVBF_Config& conf =CVBF_Config() );
        virtual ~PointSymbol();

        // 填充属性
        CVBF_Optional<Fill>& fill() { return _fill; }
        const CVBF_Optional<Fill>& fill() const { return _fill; }

		// 点的大小属性
        CVBF_Optional<float>& size() { return _size; }
        const CVBF_Optional<float>& size() const { return _size; }

    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );
        static void parseSLD(const CVBF_Config& c, class Style& style);

    protected:
        CVBF_Optional<Fill>  _fill;
        CVBF_Optional<float> _size;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_POINT_SYMBOL_H
