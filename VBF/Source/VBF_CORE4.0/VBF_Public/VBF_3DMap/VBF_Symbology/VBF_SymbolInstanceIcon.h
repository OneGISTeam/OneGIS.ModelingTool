#ifndef OSGEARTHSYMBOLOGY_ICON_SYMBOL_H
#define OSGEARTHSYMBOLOGY_ICON_SYMBOL_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolInstance.h>

namespace osgEarth { namespace Symbology
{
    class Style;
    class InstanceResource;

    /**
     * Represents a 2D icon for instancing
     */
    class OSGEARTHSYMBOLOGY_EXPORT IconSymbol : public InstanceSymbol
    {
    public:
        // note: these are similar to the values in osgText::Text::AlignmentType
        enum Alignment
        {
            ALIGN_LEFT_TOP,
            ALIGN_LEFT_CENTER,
            ALIGN_LEFT_BOTTOM,

            ALIGN_CENTER_TOP,
            ALIGN_CENTER_CENTER,
            ALIGN_CENTER_BOTTOM,

            ALIGN_RIGHT_TOP,
            ALIGN_RIGHT_CENTER,
            ALIGN_RIGHT_BOTTOM,
        };

    public:
        META_Symbol(IconSymbol);

        IconSymbol( const CVBF_Config& conf =CVBF_Config() );
        virtual ~IconSymbol();

        /** Alignment of the marker relative to center pixels */
        CVBF_Optional<Alignment>& alignment() { return _alignment; }
        const CVBF_Optional<Alignment>& alignment() const { return _alignment; }

        /** Heading. Semantically this differs from an model's heading */
        CVBF_Optional<NumericExpression>& heading() { return _heading; }
        const CVBF_Optional<NumericExpression>& heading() const { return _heading; }

        /** Decluttering */
        CVBF_Optional<bool>& declutter() { return _declutter; }
        const CVBF_Optional<bool>& declutter() const { return _declutter; }
        
    public: // non-serialized properties (for programmatic use only)

        /** Explicit image to use for 2D icon placemet */
        void setImage( osg::Image* image ) { _image = image; }
        osg::Image* getImage( unsigned maxSize =INT_MAX ) const;

    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );
        static void parseSLD(const CVBF_Config& c, class Style& style);

    public: // InstanceSymbol
        virtual InstanceResource* createResource() const;

    protected:
        CVBF_Optional<Alignment>              _alignment;
        CVBF_Optional<NumericExpression>      _heading;
        CVBF_Optional<bool>                   _declutter;
        mutable ref_ptr<osg::Image> _image;
    };

} } // namespace osgEarth::Symbology

#endif
