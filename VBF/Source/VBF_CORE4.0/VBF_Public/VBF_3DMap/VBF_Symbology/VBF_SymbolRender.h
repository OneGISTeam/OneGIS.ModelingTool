#ifndef OSGEARTHSYMBOLOGY_RENDER_SYMBOL_H
#define OSGEARTHSYMBOLOGY_RENDER_SYMBOL_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeDepthOffset.h>
#include <VBF_3DMap/VBF_Terrain/GeoMath.h>
#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_Base/VBF_Referenced.h>
#include <vector>

namespace osgEarth { namespace Symbology
{
    /** 
     * Symbol that contains general rendering settings.
     */
    class OSGEARTHSYMBOLOGY_EXPORT RenderSymbol : public Symbol
    {
    public:
        META_Symbol(RenderSymbol);

        /** construct a render symbol */
        RenderSymbol(const CVBF_Config& conf =CVBF_Config());

        /** whether to perform depth buffer testing */
        CVBF_Optional<bool>& depthTest() { return _depthTest; }
        const CVBF_Optional<bool>& depthTest() const { return _depthTest; }

        /** whether to force lighting on/off */
        CVBF_Optional<bool>& lighting() { return _lighting; }
        const CVBF_Optional<bool>& lighting() const { return _lighting; }

        /** depth offset properties */
        CVBF_Optional<CVBF_DepthOffsetOptions>& depthOffset() { return _depthOffset; }
        const CVBF_Optional<CVBF_DepthOffsetOptions>& depthOffset() const { return _depthOffset; }

    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );
        static void parseSLD(const CVBF_Config& c, class Style& style);

    protected:
        CVBF_Optional<bool>               _depthTest;
        CVBF_Optional<bool>               _lighting;
        CVBF_Optional<CVBF_DepthOffsetOptions> _depthOffset;
        
        virtual ~RenderSymbol();
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_RENDER_SYMBOL_H
