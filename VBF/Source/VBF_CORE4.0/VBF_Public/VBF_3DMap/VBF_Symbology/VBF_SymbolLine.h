#ifndef OSGEARTHSYMBOLOGY_LINE_SYMBOL_H
#define OSGEARTHSYMBOLOGY_LINE_SYMBOL_H 1

#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_3DMap/VBF_Symbology/Stroke.h>

namespace osgEarth { namespace Symbology
{
	// �߷���
    class OSGEARTHSYMBOLOGY_EXPORT LineSymbol : public Symbol
    {
    public:
        META_Symbol(LineSymbol);

        LineSymbol(const CVBF_Config& conf =CVBF_Config());
        virtual ~LineSymbol();

		// �ߵıʻ�����
        CVBF_Optional<Stroke>& stroke() { return _stroke; }
        const CVBF_Optional<Stroke>& stroke() const { return _stroke; }

 		// �Է��߶�����ÿ�Σ�
        CVBF_Optional<unsigned>& tessellation() { return _tessellation; }
        const CVBF_Optional<unsigned>& tessellation() const { return _tessellation; }

    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );
        static void parseSLD(const CVBF_Config& c, class Style& style);

    protected:
        CVBF_Optional<Stroke>   _stroke;
        CVBF_Optional<unsigned> _tessellation;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_LINE_SYMBOL_H
