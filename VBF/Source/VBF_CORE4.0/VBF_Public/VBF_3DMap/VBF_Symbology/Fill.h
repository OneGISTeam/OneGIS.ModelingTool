#ifndef OSGEARTHSYMBOLOGY_FILL_H
#define OSGEARTHSYMBOLOGY_FILL_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <Types/VBF_Color.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>


namespace osgEarth { namespace Symbology
{
	// Ìî³ä²ÎÊý
    class OSGEARTHSYMBOLOGY_EXPORT Fill
    {
    public:
        Fill();
        Fill(const Fill& rhs);
        Fill( float r, float g, float b, float a );
        Fill( const VBFCOLOR& color );
        Fill( const CVBF_Config& conf );

        virtual ~Fill();

        VBFCOLOR& color() { return _color; }
        const VBFCOLOR& color() const { return _color; }

    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );

    protected:
        VBFCOLOR _color;
        void init();
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_FILL_H
