#ifndef OSGSHADOW_SHADOWETEXTURE
#define OSGSHADOW_SHADOWETEXTURE 1

#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>

#include <VBF_Engine/VBF_Shadow/VBF_ShadowTechnique.h>

namespace osgShadow {

// 纹理阴影技术，用纹理技术实现阴影
class OSGSHADOW_EXPORT ShadowTexture : public ShadowTechnique
{
    public :
        ShadowTexture();

        ShadowTexture(const ShadowTexture& es, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
            
        META_Object(osgShadow, ShadowTexture);
        
        /** Set the texture unit that the shadow texture will be applied on.*/
        void setTextureUnit(unsigned int unit);

        /** Get the texture unit that the shadow texture will be applied on.*/
        unsigned int getTextureUnit() const { return _textureUnit; }
        
        
        /** initialize the ShadowedScene and local cached data structures.*/
        virtual void init();
        
        /** run the update traversal of the ShadowedScene and update any loca chached data structures.*/
        virtual void update(osg::NodeVisitor& nv);
        
        /** run the cull traversal of the ShadowedScene and set up the rendering for this ShadowTechnique.*/
        virtual void cull(osgUtil::CullVisitor& cv);
        
        /** Clean scene graph from any shadow technique specific nodes, state and drawables.*/
        virtual void cleanSceneGraph();
        

    protected :

        virtual ~ShadowTexture() {}

        ref_ptr<osg::IVBF_Camera>       _camera;
        ref_ptr<osg::TexGen>       _texgen;
        ref_ptr<osg::Texture2D>    _texture;
        ref_ptr<osg::StateSet>     _stateset;
        ref_ptr<osg::Material>     _material;
        unsigned int                    _textureUnit;
};

}

#endif
