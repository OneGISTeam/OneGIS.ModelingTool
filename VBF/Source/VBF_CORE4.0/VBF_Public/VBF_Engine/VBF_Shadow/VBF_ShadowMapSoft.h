#ifndef OSGSHADOW_SOFTSHADOWMAP
#define OSGSHADOW_SOFTSHADOWMAP 1

#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupLightSource.h>

#include <VBF_Engine/VBF_Shadow/VBF_ShadowMap.h>

namespace osgShadow {

class OSGSHADOW_EXPORT SoftShadowMap : public ShadowMap
{
    public :
        SoftShadowMap();

        SoftShadowMap(const SoftShadowMap& es, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

        META_Object(osgShadow, SoftShadowMap);

        /** Set the values for width of the soft penumbra the shader will use.
         *  Zero is for hard shadow (no penumbra). 0.01 is already very soft penumbra.
         *  Default is 0.005.*/
        void setSoftnessWidth(float softnessWidth);

        /** Get the value used for width of the soft penumbra in the shader.*/
        float getSoftnessWidth() const { return _softnessWidth; }

        /** Set the values for jittering scale the shader will use.
         *  Zero is no jittering (i.e. see the banding in penumbra)
         *  High values (>64) cause 'pixelization' of the penumbra.
         *  Usually but not necessarily power of two number.
         *  Default is 32. */
        void setJitteringScale(float jitteringScale);

        /** Get the value used for jittering scale in the shader.*/
        float getJitteringScale() const { return _jitteringScale; }

        /** Set the texture unit that the jitter texture will be applied on.*/
        void setJitterTextureUnit(unsigned int jitterTextureUnit);

        /** Get the texture unit that the jitter texture will be applied on.*/
        unsigned int getJitterTextureUnit() const { return _jitterTextureUnit; }


        /** Add a small bias to the z-value, this can reduce 
         *  shadow acne problem. 
         *  This is the same as calling setPolygonOffset(osg::Vec2(bias,0));
         *  Suitable values are 0-0.005 
         *  Default is 0. */
        void setBias(float bias) { setPolygonOffset(osg::Vec2(bias,0)); }
        
        /** Return the bias value */
        float getBias() const { return getPolygonOffset().x(); }


    protected:
        virtual ~SoftShadowMap(void) {};
        
        /** Create the managed Uniforms */
        void createUniforms();
        void createShaders();
        void initJittering(osg::StateSet *ss);
        
        ref_ptr<osg::Uniform>      _softnessWidthUniform;
        ref_ptr<osg::Uniform>      _jitteringScaleUniform;
        float                           _softnessWidth;
        float                           _jitteringScale;
        unsigned int                    _jitterTextureUnit;

    

};

}

#endif
