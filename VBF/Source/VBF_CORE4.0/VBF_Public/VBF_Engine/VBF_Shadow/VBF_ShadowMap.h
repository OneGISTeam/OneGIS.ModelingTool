#ifndef OSGSHADOW_SHADOWEMAP
#define OSGSHADOW_SHADOWEMAP 1

#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupLightSource.h>

#include <VBF_Engine/VBF_Shadow/VBF_ShadowTechnique.h>

namespace osgShadow {

// 贴图阴影技术，用贴图技术实现阴影
class OSGSHADOW_EXPORT ShadowMap : public ShadowTechnique
{
    public :
        ShadowMap();
        ShadowMap(const ShadowMap& es, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
            
        META_Object(osgShadow, ShadowMap);
        
 		// 设置/获取阴影纹理的纹理单元
        void setTextureUnit(unsigned int unit);
        unsigned int getTextureUnit() const { return _shadowTextureUnit; }

		// 设置/获取polygon offset
        void setPolygonOffset(const osg::Vec2& polyOffset);
        const osg::Vec2& getPolygonOffset() const { return _polyOffset; }

		// 设置/获取shader使用的环境偏离率
        void setAmbientBias(const osg::Vec2& ambientBias );
        const osg::Vec2& getAmbientBias() const { return _ambientBias; }

		// 设置/获取阴影纹理的尺寸（pixels x / y）
        void setTextureSize(const osg::Vec2s& textureSize);
        const osg::Vec2s& getTextureSize() const { return _textureSize; }

		// 设置投影所用的光源
        void setLight(osg::Light* light);
        void setLight(osg::CVBF_SGNodeGroupLightSource* ls);

        typedef std::vector< ref_ptr<osg::Uniform> > UniformList;

        typedef std::vector< ref_ptr<osg::Shader> > ShaderList;

        /** Add a shader to internal list, will be used instead of the default ones */
        inline void addShader(osg::Shader* shader) { _shaderList.push_back(shader); }
        
        /** Reset internal shader list */
        inline void clearShaderList() { _shaderList.clear(); }

        /** initialize the ShadowedScene and local cached data structures.*/
        virtual void init();
        
        /** run the update traversal of the ShadowedScene and update any loca chached data structures.*/
        virtual void update(osg::NodeVisitor& nv);
        
        /** run the cull traversal of the ShadowedScene and set up the rendering for this ShadowTechnique.*/
        virtual void cull(osgUtil::CullVisitor& cv);
        
        /** Clean scene graph from any shadow technique specific nodes, state and drawables.*/
        virtual void cleanSceneGraph();
        
        // debug methods

        ref_ptr<osg::IVBF_Camera> makeDebugHUD();

    protected:
        virtual ~ShadowMap(void) {};

        /** Create the managed Uniforms */
        virtual void createUniforms();

        virtual void createShaders();
        
        // forward declare, interface and implementation provided in ShadowMap.cpp
        class DrawableDrawWithDepthShadowComparisonOffCallback;

        ref_ptr<osg::IVBF_Camera>       _camera;
        ref_ptr<osg::TexGen>       _texgen;
        ref_ptr<osg::Texture2D>    _texture;
        ref_ptr<osg::StateSet>     _stateset;
        ref_ptr<osg::Program>      _program;
        ref_ptr<osg::Light>        _light;

        ref_ptr<osg::CVBF_SGNodeGroupLightSource>  _ls;

        ref_ptr<osg::Uniform>      _ambientBiasUniform;
        UniformList                     _uniformList;
        ShaderList                      _shaderList;
        unsigned int                    _baseTextureUnit;
        unsigned int                    _shadowTextureUnit;
        osg::Vec2                        _polyOffset;
        osg::Vec2                       _ambientBias;
        osg::Vec2s                      _textureSize;

    };

}

#endif
