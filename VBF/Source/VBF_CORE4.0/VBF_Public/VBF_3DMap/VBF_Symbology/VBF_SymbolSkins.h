#ifndef OSGEARTHSYMBOLOGY_SKIN_RESOURCE_H
#define OSGEARTHSYMBOLOGY_SKIN_RESOURCE_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/VBF_Resource.h>
#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexEnv.h>

namespace osgEarth { namespace Symbology
{
    using namespace osgEarth;

    /**
     * 指向皮肤的资源，是一个纹理图像paired with
     * a collection of metadata that describes its suitability for use in a scene.
     */
    //
    class OSGEARTHSYMBOLOGY_EXPORT SkinResource : public Resource
    {
    public:
        SkinResource( const CVBF_Config& conf =CVBF_Config() );
        virtual ~SkinResource();

        /**
         * Creates a new StateSet containing a Texture based on this Skin.
         */
        osg::StateSet* createStateSet( const osgDB::Options* dbOptions ) const;

    public:
        /** Source location of the actual texture image.  */
        CVBF_Optional<URI>& imageURI() { return _imageURI; }
        const CVBF_Optional<URI>& imageURI() const { return _imageURI; }

        // 图像的真实宽度（Real-world），单位米
        CVBF_Optional<float>& imageWidth() { return _imageWidth; }
        const CVBF_Optional<float>& imageWidth() const { return _imageWidth; }

        // 图像的真实高度（Real-world），单位米
        CVBF_Optional<float>& imageHeight() { return _imageHeight; }
        const CVBF_Optional<float>& imageHeight() const { return _imageHeight; }

        /** Minimum acceptable real-world object height (meters) for which this image would make an appropriate texture */
        CVBF_Optional<float>& minObjectHeight() { return _minObjHeight; }
        const CVBF_Optional<float>& minObjectHeight() const { return _minObjHeight; }

        /** Maximum acceptable real-world object height (meters) for which this image would make an appropriate texture */
        CVBF_Optional<float>& maxObjectHeight() { return _maxObjHeight; }
        const CVBF_Optional<float>& maxObjectHeight() const { return _maxObjHeight; }

        /** Whether this image is suitable for use as a vertically repeating texture */
        CVBF_Optional<bool>& isTiled() { return _isTiled; }
        const CVBF_Optional<bool>& isTiled() const { return _isTiled; }

        /** GL texture application mode */
        CVBF_Optional<osg::TexEnv::Mode>& texEnvMode() { return _texEnvMode; }
        const CVBF_Optional<osg::TexEnv::Mode>& texEnvMode() const { return _texEnvMode; }

        /** The maximum allowable size of a texture (in either dimension) that uses this image. */
        CVBF_Optional<unsigned> maxTextureSpan() { return _maxTexSpan; }
        const CVBF_Optional<unsigned> maxTextureSpan() const { return _maxTexSpan; }

    public: // serialization methods

        virtual CVBF_Config getConfig() const;
        void mergeConfig( const CVBF_Config& conf );

    protected:

        osg::StateSet* createStateSet( osg::Image* image ) const;

        osg::Image* createImage( const osgDB::Options* options ) const;

    protected:

        CVBF_Optional<URI>               _imageURI;
        CVBF_Optional<float>             _imageWidth;
        CVBF_Optional<float>             _imageHeight;
        CVBF_Optional<float>             _minObjHeight;
        CVBF_Optional<float>             _maxObjHeight;
        CVBF_Optional<bool>              _isTiled;
        CVBF_Optional<osg::TexEnv::Mode> _texEnvMode;
        CVBF_Optional<unsigned>          _maxTexSpan;
    };


    /**
     * Query object that you can use to search for applicable Skin resources from the 
     * ResourceLibrary.
     */
    class OSGEARTHSYMBOLOGY_EXPORT SkinSymbol : public Taggable<Symbol>
    {
    public:
        META_Symbol(SkinSymbol);

        SkinSymbol( const CVBF_Config& conf =CVBF_Config() );
        virtual ~SkinSymbol();

    public: // query parameters

        /** Name of the resource library to use with this symbol. */
        CVBF_Optional<std::string>& libraryName() { return _libraryName; }
        const CVBF_Optional<std::string>& libraryName() const { return _libraryName; }

        /** Object height in meters (must fall in the skin's min/max object height range to be accepted) */
        CVBF_Optional<float>& objectHeight() { return _objHeight; }
        const CVBF_Optional<float>& objectHeight() const { return _objHeight; }

        /** Minimum acceptable real-world object height for which this image would make an appropriate texture */
        CVBF_Optional<float>& minObjectHeight() { return _minObjHeight; }
        const CVBF_Optional<float>& minObjectHeight() const { return _minObjHeight; }

        /** Maximum acceptable real-world object height for which this image would make an appropriate texture */
        CVBF_Optional<float>& maxObjectHeight() { return _maxObjHeight; }
        const CVBF_Optional<float>& maxObjectHeight() const { return _minObjHeight; }

        /** Whether this image is suitable for use as a vertically repeating texture */
        CVBF_Optional<bool>& isTiled() { return _isTiled; }
        const CVBF_Optional<bool>& isTiled() const { return _isTiled; }

        /** CVBF_Random number seed value (for picking a candidate) */
        CVBF_Optional<unsigned>& randomSeed() { return _randomSeed; }
        const CVBF_Optional<unsigned>& randomSeed() const { return _randomSeed; }

    public:
        void mergeConfig(const CVBF_Config& conf);
        CVBF_Config getConfig() const;
        static void parseSLD(const CVBF_Config& c, class Style& style);

    protected:
        CVBF_Optional<std::string> _libraryName;
        CVBF_Optional<float>       _objHeight;
        CVBF_Optional<float>       _minObjHeight;
        CVBF_Optional<float>       _maxObjHeight;
        CVBF_Optional<bool>        _isTiled;
        CVBF_Optional<unsigned>    _randomSeed;
    };

    typedef std::vector< ref_ptr<SkinResource> > SkinResourceVector;

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_SKIN_RESOURCE_H
