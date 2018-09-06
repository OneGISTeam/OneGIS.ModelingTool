#ifndef OSGEARTH_SHADER_UTILS_H
#define OSGEARTH_SHADER_UTILS_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <VBF_Engine/VBF_SceneGraph/Uniform>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLight.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>
#include <VBF_Base/observer_ptr>

namespace osgEarth
{
    /**
     * ShaderPolicy encodes general behavior when deciding how to
     * employ shaders in certain situations
     */
    enum ShaderPolicy
    {
        SHADERPOLICY_DISABLE,
        SHADERPOLICY_GENERATE,
        SHADERPOLICY_INHERIT
    };


    /**
    * Container for light uniforms
    */
    //light product
    struct osg_LightProducts 
    { 
        osg_LightProducts(int id);
        
        ref_ptr<osg::Uniform> ambient; // vec4 
        ref_ptr<osg::Uniform> diffuse; // vec4
        ref_ptr<osg::Uniform> specular; //vec4

        // GLSL strings
        static std::string glslDefinition();
    };


    struct osg_LightSourceParameters 
    { 
        osg_LightSourceParameters(int id);
        
        void setUniformsFromOsgLight(const osg::Light* light, osg::Matrix viewMatrix, const osg::Material* frontMat);
        void applyState(osg::StateSet* stateset);
        
        ref_ptr<osg::Uniform>  ambient; // vec4
        ref_ptr<osg::Uniform>  diffuse; // vec4 
        ref_ptr<osg::Uniform>  specular; // vec4
        ref_ptr<osg::Uniform>  position; // vec4
        ref_ptr<osg::Uniform>  halfVector; // vec4 
        ref_ptr<osg::Uniform>  spotDirection; // vec3 
        ref_ptr<osg::Uniform>  spotExponent; // float
        ref_ptr<osg::Uniform>  spotCutoff; // float
        ref_ptr<osg::Uniform>  spotCosCutoff; // float
        ref_ptr<osg::Uniform>  constantAttenuation; // float 
        ref_ptr<osg::Uniform>  linearAttenuation; // float
        ref_ptr<osg::Uniform>  quadraticAttenuation; // float

        //just store the light product in here
        osg_LightProducts _frontLightProduct;

        // GLSL strings
        static std::string glslDefinition();
    };

    /**
     * Preprocesses GLES shader source to include our osg_LightProducts and osg_LightSourceParameters
     * definitions and uniforms.
     */
    class OSGEARTH_EXPORT ShaderPreProcessor
    {
    public:
        static void run(osg::Shader* shader);
    };

    /**
     * A callback that will update the osgEarth lighting uniforms (based on the
     * FFP lighting state) if necessary.
     */
    class OSGEARTH_EXPORT UpdateLightingUniformsHelper : public osg::NodeCallback
    {
    public:
        UpdateLightingUniformsHelper( bool useUpdateTraversal =false );
        virtual ~UpdateLightingUniformsHelper();

        void cullTraverse( osg::IVBF_SGNode* node, osg::NodeVisitor* nv );
        void updateTraverse( osg::IVBF_SGNode* node );

    public: // NodeCallback
        // for use as a cull callback.
        virtual void operator()(osg::IVBF_SGNode*, osg::NodeVisitor* nv);

    protected:
        int   _maxLights;
        bool* _lightEnabled;
        bool  _lightingEnabled;
        bool  m_bDirty;
        bool  _applied;
        bool  _useUpdateTrav;
        OpenThreads::Mutex _stateSetMutex;

        ref_ptr<osg::Uniform> _lightingEnabledUniform;
        ref_ptr<osg::Uniform> _lightEnabledUniform;
         
        std::vector<osg_LightSourceParameters>   _osgLightSourceParameters; 
    };

    /**
     * Helper class for dealing with array uniforms. Array uniform naming works
     * differently on different drivers (ATI vs NVIDIA), so this class helps mitigate
     * those differences.
     */
    class OSGEARTH_EXPORT ArrayUniform //  : public ::CVBF_Referenced
    {
    public:
        ArrayUniform() { }

        /**
         * Creates or retrieves a named uniform array.
         */
        ArrayUniform( const std::string& name,
            osg::Uniform::Type type, osg::StateSet* stateSet,
            unsigned  size =1 );

        virtual ~ArrayUniform() { }

        void attach( const std::string& name,
            osg::Uniform::Type type, osg::StateSet* stateSet,
            unsigned size =1 );

        void detach();

        void setElement( unsigned index, int value );
        void setElement( unsigned index, unsigned value );
        void setElement( unsigned index, bool value );
        void setElement( unsigned index, float value );
        void setElement( unsigned index, const osg::Matrix& value );
        void setElement( unsigned index, const osg::Vec3& value );

        bool getElement( unsigned index, int& out_value ) const;
        bool getElement( unsigned index, unsigned& out_value ) const;
        bool getElement( unsigned index, bool& out_value ) const;
        bool getElement( unsigned index, float& out_value ) const;
        bool getElement( unsigned index, osg::Matrix& out_value ) const;
        bool getElement( unsigned index, osg::Vec3& out_value ) const;

        bool isValid() const { return _uniform.valid() && _uniformAlt.valid(); }
        int getNumElements() const { return isValid() ? _uniform->getNumElements() : -1; }

        bool isDirty() const { return
            (_uniform.valid() && _uniform->getModifiedCount() > 0) ||
            (_uniformAlt.valid() && _uniformAlt->getModifiedCount() > 0); }

    private:
        ref_ptr<osg::Uniform>       _uniform;
        ref_ptr<osg::Uniform>       _uniformAlt;
        observer_ptr<osg::StateSet> _stateSet;

        void ensureCapacity( unsigned newSize );
    };
}

#endif // OSGEARTH_SHADER_UTILS_H
