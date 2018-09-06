#ifndef OSGEARTH_TEXTURE_COMPOSITOR_MULTI_TEXTURE_H
#define OSGEARTH_TEXTURE_COMPOSITOR_MULTI_TEXTURE_H 1

#include <VBF_3DMap/VBF_Terrain/TextureCompositor.h>

namespace osgEarth
{
    /**
     * Texture compositor that implements multitexturing. It supports either GPU multitexturing
     * (using shaders and taking advantage of all the hardware's resources) or FFP (fixed-function
     * pipeline) multitexturing, which limits you to the old ARB texture unit limit (usually 4).
     */
    class TextureCompositorMultiTexture : public TextureCompositorTechnique
    {
    public:
        TextureCompositorMultiTexture( bool useGPU, const CVBF_OptionsTerrain& options );
        virtual ~TextureCompositorMultiTexture() { }

        static bool isSupported( bool useGPU );

    public:
        bool requiresUnitTextureSpace() const { return false; }

        bool usesShaderComposition() const { return _useGPU; }

        bool blendingRequiresSecondarySlot() const { return true; }

        void updateMasterStateSet( osg::StateSet* stateSet, const TextureLayout& layout ) const;

        bool supportsLayerUpdate() const { return true; }

        void applyLayerUpdate( 
            osg::StateSet* stateSet, UID layerUID,
            const GeoImage& preparedImage, const CVBF_TileKey& tileExtent,
            const TextureLayout& layout, osg::StateSet* parentStateSet) const;

        osg::Shader* createSamplerFunction(
            UID layerUID, 
            const std::string& functionName,
            osg::Shader::Type type,
            const TextureLayout& layout ) const;


    private:
        float _lodTransitionTime;
        bool _useGPU;
        bool _enableMipmappingOnUpdatedTextures;
        bool _enableMipmapping;

        osg::Texture::FilterMode _minFilter;
        osg::Texture::FilterMode _magFilter;
    };
}

#endif // OSGEARTH_TEXTURE_COMPOSITOR_MULTI_TEXTURE_H
