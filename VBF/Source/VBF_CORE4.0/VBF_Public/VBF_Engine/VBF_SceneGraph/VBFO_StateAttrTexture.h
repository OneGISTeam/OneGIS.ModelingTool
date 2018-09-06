#ifndef OSG_TEXTURE
#define OSG_TEXTURE 1


#include <VBF_Engine/VBF_SceneGraph/VBF_GLTexture.h>

#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttribute.h>
#include <VBF_Engine/VBF_SceneGraph/GraphicsContext.h>
//#include <VBF_Engine/VBF_SceneGraph/VBF_StateMachine.h>
#include <VBF_Base/ref_ptr>
#include <Types/Vec4>
#include <Types/Vec4d>
#include <VBF_Engine/VBF_SceneGraph/buffered_value>
#include <VBF_Engine/VBF_SceneGraph/VBFR_GL2Extensions.h>

#include <list>
#include <map>

namespace osg {

// 纹理的基类，封装了OpenGL的各种纹理的纹理功能
class OSG_EXPORT Texture : public osg::StateAttribute
{
    public :
        Texture();
        Texture(const Texture& text,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        virtual osg::CVBF_Object* cloneType() const = 0;
        virtual osg::CVBF_Object* clone(const CopyOp& copyop) const = 0;
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const Texture *>(obj)!=NULL; }
        virtual const char* libraryName() const { return "osg"; }
        virtual const char* className() const { return "Texture"; }

        /** Fast alternative to dynamic_cast<> for determining if state attribute is a Texture.*/
        virtual Texture* asTexture() { return this; }
        
        /** Fast alternative to dynamic_cast<> for determining if state attribute is a Texture.*/
        virtual const Texture* asTexture() const { return this; }

        virtual Type getType() const { return TEXTURE; }

        virtual bool isTextureAttribute() const { return true; }

        virtual GLenum getTextureTarget() const = 0;

        virtual bool getModeUsage(StateAttribute::ModeUsage& usage) const
        {
            usage.usesTextureMode(getTextureTarget());
            return true;
        }

        virtual int getTextureWidth() const { return 0; }
        virtual int getTextureHeight() const { return 0; }
        virtual int getTextureDepth() const { return 0; }

        enum WrapParameter 
		{
            WRAP_S, // x轴
            WRAP_T, // y轴
            WRAP_R  // z轴
        };

        enum WrapMode // 纹理缠绕模式
		{
            CLAMP  = GL_CLAMP,					// 截取
            CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,	// 边框始终被忽略
            CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER_ARB, // 
            REPEAT = GL_REPEAT,					// 纹理重复映射
            MIRROR = GL_MIRRORED_REPEAT_IBM		// 纹理镜像的重复映射
        };

        /** Sets the texture wrap mode. */
        void setWrap(WrapParameter which, WrapMode wrap);
        /** Gets the texture wrap mode. */
        WrapMode getWrap(WrapParameter which) const;


        /** Sets the border color. Only used when wrap mode is CLAMP_TO_BORDER.
         * The border color will be casted to the appropriate type to match the
         * internal pixel format of the texture. */
        void setBorderColor(const Vec4d& color) { _borderColor = color; dirtyTextureParameters(); }

        /** Gets the border color. */
        const Vec4d& getBorderColor() const { return _borderColor; }

        /** Sets the border width. */
        void setBorderWidth(GLint width) { _borderWidth = width; dirtyTextureParameters(); }
        
        GLint getBorderWidth() const { return _borderWidth; }

        enum FilterParameter // 纹理过滤参数类型
		{
            MIN_FILTER, // 用于缩小
            MAG_FILTER	// 用于放大
        };

        enum FilterMode		// 纹理过滤模式
		{
            LINEAR                    = GL_LINEAR,				
            LINEAR_MIPMAP_LINEAR      = GL_LINEAR_MIPMAP_LINEAR,
            LINEAR_MIPMAP_NEAREST     = GL_LINEAR_MIPMAP_NEAREST,
            NEAREST                   = GL_NEAREST,
            NEAREST_MIPMAP_LINEAR     = GL_NEAREST_MIPMAP_LINEAR,
            NEAREST_MIPMAP_NEAREST    = GL_NEAREST_MIPMAP_NEAREST
        };


        // 设置/获取纹理过滤模式
        void setFilter(FilterParameter which, FilterMode filter);
        FilterMode getFilter(FilterParameter which) const;

        /** Sets the maximum anisotropy value, default value is 1.0 for no
          * anisotropic filtering. If hardware does not support anisotropic
          * filtering, use normal filtering (equivalent to a max anisotropy
          * value of 1.0. Valid range is 1.0f upwards.  The maximum value
          * depends on the graphics system. */
        void setMaxAnisotropy(float anis);
        
        /** Gets the maximum anisotropy value. */
        inline float getMaxAnisotropy() const { return _maxAnisotropy; }

        /** Sets the hardware mipmap generation hint. If enabled, it will
          * only be used if supported in the graphics system. */
        inline void setUseHardwareMipMapGeneration(bool useHardwareMipMapGeneration) { _useHardwareMipMapGeneration = useHardwareMipMapGeneration; }

        /** Gets the hardware mipmap generation hint. */
        inline bool getUseHardwareMipMapGeneration() const { return _useHardwareMipMapGeneration; }

        /** Sets whether or not the apply() function will unreference the image
          * data. If enabled, and the image data is only referenced by this
          * Texture, apply() will delete the image data. */
		// 当该值设置为true时，在应用过该纹理对象后（apply），自动释放其对Image对象的引用，以减少内存占用。
        inline void setUnRefImageDataAfterApply(bool flag) { _unrefImageDataAfterApply = flag; }
        
        /** Gets whether or not apply() unreferences image data. */
        inline bool getUnRefImageDataAfterApply() const { return _unrefImageDataAfterApply; }

        /** Sets whether to use client storage for the texture, if supported
          * by the graphics system. Note: If enabled, and the graphics system
          * supports it, the osg::Image(s) associated with this texture cannot
          * be deleted, so the UnRefImageDataAfterApply flag would be ignored. */
        inline void setClientStorageHint(bool flag) { _clientStorageHint = flag; }

        /** Gets whether to use client storage for the texture. */
        inline bool getClientStorageHint() const { return _clientStorageHint; }

        /** Sets whether to force the texture to resize images that have dimensions 
          * that are not a power of two. If enabled, NPOT images will be resized,
          * whether or not NPOT textures are supported by the hardware. If disabled,
          * NPOT images will not be resized if supported by hardware. */
        inline void setResizeNonPowerOfTwoHint(bool flag) { _resizeNonPowerOfTwoHint = flag; }

        /** Gets whether texture will force non power to two images to be resized. */
        inline bool getResizeNonPowerOfTwoHint() const { return _resizeNonPowerOfTwoHint; }

        enum InternalFormatMode 
		{
            USE_IMAGE_DATA_FORMAT,
            USE_USER_DEFINED_FORMAT,
            USE_ARB_COMPRESSION,
            USE_S3TC_DXT1_COMPRESSION,
            USE_S3TC_DXT3_COMPRESSION,
            USE_S3TC_DXT5_COMPRESSION,
            USE_PVRTC_2BPP_COMPRESSION,
            USE_PVRTC_4BPP_COMPRESSION,
            USE_ETC_COMPRESSION,
            USE_RGTC1_COMPRESSION,
            USE_RGTC2_COMPRESSION,
            USE_S3TC_DXT1c_COMPRESSION,
            USE_S3TC_DXT1a_COMPRESSION
        };

        /** Sets the internal texture format mode. Note: If the texture format is
          * USE_IMAGE_DATA_FORMAT, USE_ARB_COMPRESSION, or USE_S3TC_COMPRESSION,
          * the internal format mode is set automatically and will overwrite the
          * previous _internalFormat. */
        inline void setInternalFormatMode(InternalFormatMode mode) { _internalFormatMode = mode; }

        /** Gets the internal texture format mode. */
        inline InternalFormatMode getInternalFormatMode() const { return _internalFormatMode; }

        /** Sets the internal texture format. Implicitly sets the
          * internalFormatMode to USE_USER_DEFINED_FORMAT.
          * The corresponding internal format type will be computed. */
        inline void setInternalFormat(GLint internalFormat)
        {
            _internalFormatMode = USE_USER_DEFINED_FORMAT;
            _internalFormat = internalFormat;
            computeInternalFormatType();
        }


        /** Gets the internal texture format. */
        inline GLint getInternalFormat() const { if (_internalFormat==0) computeInternalFormat(); return _internalFormat; }
        
        /** Return true if the internal format is one of the compressed formats.*/
        bool isCompressedInternalFormat() const;

        /** Sets the external source image format, used as a fallback when no osg::Image is attached to provide the source image format. */
        inline void setSourceFormat(GLenum sourceFormat) { _sourceFormat = sourceFormat; }

        /** Gets the external source image format. */
        inline GLenum getSourceFormat() const { return _sourceFormat; }

        /** Sets the external source data type, used as a fallback when no osg::Image is attached to provide the source image format.*/
        inline void setSourceType(GLenum sourceType) { _sourceType = sourceType; }

        /** Gets the external source data type.*/
        inline GLenum getSourceType() const { return _sourceType; }

        /** Texture type determined by the internal texture format */
        enum InternalFormatType{

            //! default OpenGL format (clamped values to [0,1) or [0,255])
            NORMALIZED = 0x0,

            //! float values, Shader Model 3.0 (see ARB_texture_float)
            FLOAT = 0x1,

            //! Signed integer values (see EXT_texture_integer)
            SIGNED_INTEGER = 0x2,

            //! Unsigned integer value (see EXT_texture_integer)
            UNSIGNED_INTEGER = 0x4
        };
        
        /** Get the internal texture format type. */
        inline InternalFormatType getInternalFormatType() const { return _internalFormatType; }
        
        class TextureObject;

        /** Returns a pointer to the TextureObject for the current context. */
        inline TextureObject* getTextureObject(unsigned int contextID) const
        {
            return _textureObjectBuffer[contextID].get();
        }

        inline void setTextureObject(unsigned int contextID, TextureObject* to)
        {
            _textureObjectBuffer[contextID] = to;
        }

        /** Forces a recompile on next apply() of associated OpenGL texture
          * objects. */
        void dirtyTextureObject();

        /** Returns true if the texture objects for all the required graphics
          * contexts are loaded. */
        bool areAllTextureObjectsLoaded() const;


        /** Gets the dirty flag for the current contextID. */
        inline unsigned int& getTextureParameterDirty(unsigned int contextID) const
        {
            return _texParametersDirtyList[contextID];
        }


        /** Force a reset on next apply() of associated OpenGL texture
          * parameters. */
        void dirtyTextureParameters();

        /** Force a manual allocation of the mipmap levels on the next apply() call.
          * User is responsible for filling the mipmap levels with valid data.
          * The OpenGL's glGenerateMipmapEXT function is used to generate the mipmap levels.
          * If glGenerateMipmapEXT is not supported or texture's internal format is not supported
          * by the glGenerateMipmapEXT, then empty mipmap levels will
          * be allocated manually. The mipmap levels are also allocated if a non-mipmapped
          * min filter is used. */
        void allocateMipmapLevels();


        /** Sets GL_TEXTURE_COMPARE_MODE_ARB to GL_COMPARE_R_TO_TEXTURE_ARB
          * See http://oss.sgi.com/projects/ogl-sample/registry/ARB/shadow.txt. */
        void setShadowComparison(bool flag) { _use_shadow_comparison = flag; }
        bool getShadowComparison() const { return _use_shadow_comparison; }
        
        enum ShadowCompareFunc {
            NEVER = GL_NEVER,
            LESS = GL_LESS,
            EQUAL = GL_EQUAL,
            LEQUAL = GL_LEQUAL,
            GREATER = GL_GREATER,
            NOTEQUAL = GL_NOTEQUAL,
            GEQUAL = GL_GEQUAL,
            ALWAYS = GL_ALWAYS
        };

        /** Sets shadow texture comparison function. */
        void setShadowCompareFunc(ShadowCompareFunc func) { _shadow_compare_func = func; }
        ShadowCompareFunc getShadowCompareFunc() const { return _shadow_compare_func; }

        enum ShadowTextureMode {
            LUMINANCE = GL_LUMINANCE,
            INTENSITY = GL_INTENSITY,
            ALPHA = GL_ALPHA
        };

        /** Sets shadow texture mode after comparison. */
        void setShadowTextureMode(ShadowTextureMode mode) { _shadow_texture_mode = mode; }
        ShadowTextureMode getShadowTextureMode() const { return _shadow_texture_mode; }

        /** Sets the TEXTURE_COMPARE_FAIL_VALUE_ARB texture parameter. See
          * http://oss.sgi.com/projects/ogl-sample/registry/ARB/shadow_ambient.txt. */
        void setShadowAmbient(float shadow_ambient) { _shadow_ambient = shadow_ambient; }
        float getShadowAmbient() const { return _shadow_ambient; }
        

        /** Sets the texture image for the specified face. */
        virtual void setImage(unsigned int face, Image* image) = 0;

        /** Gets the texture image for the specified face. */
        virtual Image* getImage(unsigned int face) = 0;

        /** Gets the const texture image for specified face. */
        virtual const Image* getImage(unsigned int face) const = 0;

        /** Gets the number of images that can be assigned to this Texture. */
        virtual unsigned int getNumImages() const = 0;


        /** Set the PBuffer graphics context to read from when using PBuffers for RenderToTexture.*/
        void setReadPBuffer(GraphicsContext* context) { _readPBuffer = context; }

        /** Get the PBuffer graphics context to read from when using PBuffers for RenderToTexture.*/
        GraphicsContext* getReadPBuffer() { return _readPBuffer.get(); }

        /** Get the const PBuffer graphics context to read from when using PBuffers for RenderToTexture.*/
        const GraphicsContext* getReadPBuffer() const { return _readPBuffer.get(); }

        /** Texture is a pure virtual base class, apply must be overridden. */
        virtual void apply(State& state) const = 0;

        /** Calls apply(state) to compile the texture. */
        virtual void compileGLObjects(State& state) const;

        /** Resize any per context GLObject buffers to specified size. */
        virtual void resizeGLObjectBuffers(unsigned int maxSize);

        /** If State is non-zero, this function releases OpenGL objects for
          * the specified graphics context. Otherwise, releases OpenGL objects
          * for all graphics contexts. */
        virtual void releaseGLObjects(State* state=0) const;

        /** Encapsulates queries of extension availability, obtains extension
          * function pointers, and provides convenience wrappers for
          * calling extension functions. */        
        class OSG_EXPORT Extensions : public ::CVBF_Referenced
        {
            public:
                Extensions(unsigned int contextID);

                void setMultiTexturingSupported(bool flag) { _isMultiTexturingSupported=flag; }
                bool isMultiTexturingSupported() const { return _isMultiTexturingSupported; }

                void setTextureFilterAnisotropicSupported(bool flag) { _isTextureFilterAnisotropicSupported=flag; }
                bool isTextureFilterAnisotropicSupported() const { return _isTextureFilterAnisotropicSupported; }
                
                void setTextureCompressionARBSupported(bool flag) { _isTextureCompressionARBSupported=flag; }
                bool isTextureCompressionARBSupported() const { return _isTextureCompressionARBSupported; }

                void setTextureCompressionS3TCSupported(bool flag) { _isTextureCompressionS3TCSupported=flag; }
                bool isTextureCompressionS3TCSupported() const { return _isTextureCompressionS3TCSupported; }

                void setTextureCompressionPVRTC2BPPSupported(bool flag) { _isTextureCompressionPVRTC2BPPSupported=flag; }
                bool isTextureCompressionPVRTC2BPPSupported() const { return _isTextureCompressionPVRTC2BPPSupported; }
                
                void setTextureCompressionPVRTC4BPPSupported(bool flag) { _isTextureCompressionPVRTC4BPPSupported=flag; }
                bool isTextureCompressionPVRTC4BPPSupported() const { return _isTextureCompressionPVRTC4BPPSupported; }
                
                void setTextureCompressionETCSupported(bool flag) { _isTextureCompressionETCSupported=flag; }
                bool isTextureCompressionETCSupported() const { return _isTextureCompressionETCSupported; }

                void setTextureCompressionRGTCSupported(bool flag) { _isTextureCompressionRGTCSupported=flag; }
                bool isTextureCompressionRGTCSupported() const { return _isTextureCompressionRGTCSupported; }

                void setTextureCompressionPVRTCSupported(bool flag) { _isTextureCompressionPVRTCSupported=flag; }
                bool isTextureCompressionPVRTCSupported() const { return _isTextureCompressionPVRTCSupported; }

                void setTextureMirroredRepeatSupported(bool flag) { _isTextureMirroredRepeatSupported=flag; }
                bool isTextureMirroredRepeatSupported() const { return _isTextureMirroredRepeatSupported; }

                void setTextureEdgeClampSupported(bool flag) { _isTextureEdgeClampSupported=flag; }
                bool isTextureEdgeClampSupported() const { return _isTextureEdgeClampSupported; }

                void setTextureBorderClampSupported(bool flag) { _isTextureBorderClampSupported=flag; }
                bool isTextureBorderClampSupported() const { return _isTextureBorderClampSupported; }

                void setGenerateMipMapSupported(bool flag) { _isGenerateMipMapSupported=flag; }
                bool isGenerateMipMapSupported() const { return _isGenerateMipMapSupported; }

                void setTextureMultisampledSupported(bool flag) { _isTextureMultisampledSupported=flag; }
                bool isTextureMultisampledSupported() const { return _isTextureMultisampledSupported; }

                void setShadowSupported(bool flag) { _isShadowSupported = flag; }
                bool isShadowSupported() const { return _isShadowSupported; }

                void setShadowAmbientSupported(bool flag) { _isShadowAmbientSupported = flag; }
                bool isShadowAmbientSupported() const { return _isShadowAmbientSupported; }

                void setTextureMaxLevelSupported(bool flag) { _isTextureMaxLevelSupported = flag; }
                bool isTextureMaxLevelSupported() const { return _isTextureMaxLevelSupported; }

                void setMaxTextureSize(GLint maxsize) { _maxTextureSize=maxsize; }
                GLint maxTextureSize() const { return _maxTextureSize; }

                void setNumTextureUnits(GLint nunits ) { _numTextureUnits=nunits; }
                GLint numTextureUnits() const { return _numTextureUnits; }

                bool isCompressedTexImage2DSupported() const { return _glCompressedTexImage2D!=0; }
                bool isCompressedTexSubImage2DSupported() const { return _glCompressedTexSubImage2D!=0; }
                
                bool isClientStorageSupported() const { return _isClientStorageSupported; }

                bool isNonPowerOfTwoTextureSupported(GLenum filter) const
                {
                    return (filter==GL_LINEAR || filter==GL_NEAREST) ? 
                            _isNonPowerOfTwoTextureNonMipMappedSupported :
                            _isNonPowerOfTwoTextureMipMappedSupported;
                }

                void setTextureIntegerSupported(bool flag) { _isTextureIntegerEXTSupported=flag; }
                bool isTextureIntegerSupported() const { return _isTextureIntegerEXTSupported; }

                void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data) const
                {
                    _glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
                }

                void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data) const
                {
                    _glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
                }

                void glGetCompressedTexImage(GLenum target, GLint level, GLvoid *data) const
                {
                    _glGetCompressedTexImage(target, level, data);
                }

                void glTexImage2DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) const
                {
                    _glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
                }

                void glTexParameterIiv(GLenum target, GLenum pname, const GLint* data) const
                {
                    _glTexParameterIiv(target, pname, data);
                }

                void glTexParameterIuiv(GLenum target, GLenum pname, const GLuint* data) const
                {
                    _glTexParameterIuiv(target, pname, data);
                }

            protected:

                ~Extensions() {}// IE可能错误
                
                typedef void (GL_APIENTRY * CompressedTexImage2DArbProc) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
                typedef void (GL_APIENTRY * CompressedTexSubImage2DArbProc) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
                typedef void (GL_APIENTRY * GetCompressedTexImageArbProc) (GLenum target, GLint level, GLvoid *data);
                typedef void (GL_APIENTRY * TexImage2DMultisample)(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
                typedef void (GL_APIENTRY * TexParameterIivProc)(GLenum target, GLenum pname, const GLint* data);
                typedef void (GL_APIENTRY * TexParameterIuivProc)(GLenum target, GLenum pname, const GLuint* data);

                CompressedTexImage2DArbProc     _glCompressedTexImage2D;
                CompressedTexSubImage2DArbProc  _glCompressedTexSubImage2D;
                GetCompressedTexImageArbProc    _glGetCompressedTexImage;
                TexImage2DMultisample           _glTexImage2DMultisample;
                TexParameterIivProc             _glTexParameterIiv;
                TexParameterIuivProc            _glTexParameterIuiv;


                bool    _isMultiTexturingSupported;
                bool    _isTextureFilterAnisotropicSupported;
                bool    _isTextureCompressionARBSupported;
                bool    _isTextureCompressionS3TCSupported;
                bool    _isTextureCompressionPVRTC2BPPSupported;
                bool    _isTextureCompressionPVRTC4BPPSupported;
                bool    _isTextureCompressionETCSupported;
                bool    _isTextureCompressionRGTCSupported;
                bool    _isTextureCompressionPVRTCSupported;
                bool    _isTextureMirroredRepeatSupported;
                bool    _isTextureEdgeClampSupported;
                bool    _isTextureBorderClampSupported;
                bool    _isGenerateMipMapSupported;
                bool    _isTextureMultisampledSupported;
                bool    _isShadowSupported;
                bool    _isShadowAmbientSupported;
                bool    _isClientStorageSupported;
                bool    _isNonPowerOfTwoTextureMipMappedSupported;
                bool    _isNonPowerOfTwoTextureNonMipMappedSupported;
                bool    _isTextureIntegerEXTSupported;
                bool    _isTextureMaxLevelSupported;

                GLint   _maxTextureSize;
                GLint   _numTextureUnits;
        };
        
        /** Gets the extension for the specified context. Creates the
          * Extensions object for that context if it doesn't exist.
          * Returns NULL if the Extensions object for the context doesn't
          * exist and the createIfNotInitalized flag is false. */
        static Extensions* getExtensions(unsigned int contextID,bool createIfNotInitalized);

        /** Overrides Extensions objects across graphics contexts. Typically
          * used to ensure the same lowest common denominator of extensions
          * on systems with different graphics pipes. */
        static void setExtensions(unsigned int contextID,Extensions* extensions);

        /** Determine whether the given internalFormat is a compressed
          * image format. */
        static bool isCompressedInternalFormat(GLint internalFormat);
        
        /** Determine the size of a compressed image, given the internalFormat,
          * the width, the height, and the depth of the image. The block size
          * and the size are output parameters. */
        static void getCompressedSize(GLenum internalFormat, GLint width, GLint height, GLint depth, GLint& blockSize, GLint& size);


        /** Helper method. Creates the texture, but doesn't set or use a
          * texture binding. Note: Don't call this method directly unless
          * you're implementing a subload callback. */
        void applyTexImage2D_load(State& state, GLenum target, const Image* image, GLsizei width, GLsizei height,GLsizei numMipmapLevels) const;
        
        /** Helper method. Subloads images into the texture, but doesn't set
          * or use a texture binding. Note: Don't call this method directly
          * unless you're implementing a subload callback. */
        void applyTexImage2D_subload(State& state, GLenum target, const Image* image, GLsizei width, GLsizei height, GLint inInternalFormat, GLsizei numMipmapLevels) const;


        /** Returned by mipmapBeforeTexImage() to indicate what
          * mipmapAfterTexImage() should do */
        enum GenerateMipmapMode
        {
            GENERATE_MIPMAP_NONE,
            GENERATE_MIPMAP,
            GENERATE_MIPMAP_TEX_PARAMETER
        };

    protected :

        virtual ~Texture();

        virtual void computeInternalFormat() const = 0;
        
        /** Computes the internal format from Image parameters. */
        void computeInternalFormatWithImage(const osg::Image& image) const;

        /** Computes the texture dimension for the given Image. */
        void computeRequiredTextureDimensions(State& state, const osg::Image& image,GLsizei& width, GLsizei& height,GLsizei& numMipmapLevels) const;
        
        /** Computes the internal format type. */
        void computeInternalFormatType() const;

        /** Helper method. Sets texture parameters. */
        void applyTexParameters(GLenum target, State& state) const;

        /** Returns true if _useHardwareMipMapGeneration is true and either
          * glGenerateMipmapEXT() or GL_GENERATE_MIPMAP_SGIS are supported. */
        bool isHardwareMipmapGenerationEnabled(const State& state) const;

        /** Returns true if the associated Image should be released and it's safe to do so. */
        bool isSafeToUnrefImageData(const State& state) const {
            return (_unrefImageDataAfterApply && state.getMaxTexturePoolSize()==0 && areAllTextureObjectsLoaded());
        }

        /** Helper methods to be called before and after calling
          * gl[Compressed][Copy]Tex[Sub]Image2D to handle generating mipmaps. */
        GenerateMipmapMode mipmapBeforeTexImage(const State& state, bool hardwareMipmapOn) const;
        void mipmapAfterTexImage(State& state, GenerateMipmapMode beforeResult) const;

        /** Helper method to generate mipmap levels by calling of glGenerateMipmapEXT.
          * If it is not supported, then call the virtual allocateMipmap() method */
        void generateMipmap(State& state) const;

        /** Allocate mipmap levels of the texture by subsequent calling of glTexImage* function. */
        virtual void allocateMipmap(State& state) const = 0;

        /** Returns -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs. */
        int compareTexture(const Texture& rhs) const;

        /** Returns -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs. */
        int compareTextureObjects(const Texture& rhs) const;

        typedef buffered_value<unsigned int> TexParameterDirtyList;
        mutable TexParameterDirtyList _texParametersDirtyList;
        mutable TexParameterDirtyList _texMipmapGenerationDirtyList;

        WrapMode _wrap_s;
        WrapMode _wrap_t;
        WrapMode _wrap_r;

        FilterMode      _min_filter;
        FilterMode      _mag_filter;
        float           _maxAnisotropy;
        bool            _useHardwareMipMapGeneration;
        bool            _unrefImageDataAfterApply;
        bool            _clientStorageHint;
        bool            _resizeNonPowerOfTwoHint;

        Vec4d           _borderColor;
        GLint           _borderWidth;

        InternalFormatMode          _internalFormatMode;
        mutable InternalFormatType  _internalFormatType;
        mutable GLint       _internalFormat;
        mutable GLenum      _sourceFormat;
        mutable GLenum      _sourceType;

        bool                _use_shadow_comparison;
        ShadowCompareFunc   _shadow_compare_func;
        ShadowTextureMode   _shadow_texture_mode;
        float               _shadow_ambient;

    public:

        struct OSG_EXPORT TextureProfile
        {
            inline TextureProfile(GLenum target):
                _target(target),
                _numMipmapLevels(0),
                _internalFormat(0),
                _width(0),
                _height(0),
                _depth(0),
                _border(0),
                _size(0) {}

            inline TextureProfile(GLenum    target,
                                 GLint     numMipmapLevels,
                                 GLenum    internalFormat,
                                 GLsizei   width,
                                 GLsizei   height,
                                 GLsizei   depth,
                                 GLint     border):
                _target(target),
                _numMipmapLevels(numMipmapLevels),
                _internalFormat(internalFormat),
                _width(width),
                _height(height),
                _depth(depth),
                _border(border),
                _size(0) { computeSize(); }


            #define LESSTHAN(A,B) if (A<B) return true; if (B<A) return false;
            #define FINALLESSTHAN(A,B) return (A<B);

            bool operator < (const TextureProfile& rhs) const
            {
                LESSTHAN(_size,rhs._size);
                LESSTHAN(_target,rhs._target);
                LESSTHAN(_numMipmapLevels,rhs._numMipmapLevels);
                LESSTHAN(_internalFormat,rhs._internalFormat);
                LESSTHAN(_width,rhs._width);
                LESSTHAN(_height,rhs._height);
                LESSTHAN(_depth,rhs._depth);
                FINALLESSTHAN(_border, rhs._border);
            }

            bool operator == (const TextureProfile& rhs) const
            {
                return _target == rhs._target &&
                       _numMipmapLevels == rhs._numMipmapLevels &&
                       _internalFormat == rhs._internalFormat &&
                       _width == rhs._width &&
                       _height == rhs._height &&
                       _depth == rhs._depth &&
                       _border == rhs._border;
            }

            inline void set(GLint numMipmapLevels,
                            GLenum    internalFormat,
                            GLsizei   width,
                            GLsizei   height,
                            GLsizei   depth,
                            GLint     border)
            {
                _numMipmapLevels = numMipmapLevels;
                _internalFormat = internalFormat;
                _width = width;
                _height = height;
                _depth = depth;
                _border = border;
                computeSize();
            }

            inline bool match(GLenum    target,
                       GLint     numMipmapLevels,
                       GLenum    internalFormat,
                       GLsizei   width,
                       GLsizei   height,
                       GLsizei   depth,
                       GLint     border)
            {
                return (_target == target) &&
                       (_numMipmapLevels == numMipmapLevels) &&
                       (_internalFormat == internalFormat) &&
                       (_width == width) &&
                       (_height == height) &&
                       (_depth == depth) &&
                       (_border == border);
            }

            void computeSize();

            GLenum       _target;
            GLint        _numMipmapLevels;
            GLenum       _internalFormat;
            GLsizei      _width;
            GLsizei      _height;
            GLsizei      _depth;
            GLint        _border;
            unsigned int _size;
        };

        // forward declare
        class TextureObjectSet;
        class TextureObjectManager;

        class OSG_EXPORT TextureObject : public ::CVBF_Referenced
        {
        public:
// IE可能错误
            inline TextureObject(Texture* texture, GLuint id, GLenum target):
                _id(id),
                _profile(target),
                _set(0),
                _previous(0),
                _next(0),
                _texture(texture),
                _allocated(false),
                _timeStamp(0) {}

            inline TextureObject(Texture* texture, GLuint id, const TextureProfile& profile):
                _id(id),
                _profile(profile),
                _set(0),
                _previous(0),
                _next(0),
                _texture(texture),
                _allocated(false),
                _timeStamp(0) {}

            inline TextureObject(Texture* texture,
                          GLuint    id,
                          GLenum    target,
                          GLint     numMipmapLevels,
                          GLenum    internalFormat,
                          GLsizei   width,
                          GLsizei   height,
                          GLsizei   depth,
                          GLint     border):
                _id(id),
                _profile(target,numMipmapLevels,internalFormat,width,height,depth,border),
                _set(0),
                _previous(0),
                _next(0),
                _texture(texture),
                _allocated(false),
                _timeStamp(0) {}

            inline bool match(GLenum    target,
                       GLint     numMipmapLevels,
                       GLenum    internalFormat,
                       GLsizei   width,
                       GLsizei   height,
                       GLsizei   depth,
                       GLint     border)
            {
                return isReusable() &&
                       _profile.match(target,numMipmapLevels,internalFormat,width,height,depth,border);
            }


            void bind();

            inline GLenum id() const { return _id; }
            inline GLenum target() const { return _profile._target; }

            inline unsigned int size() const { return _profile._size; }

            inline void setTexture(Texture* texture) { _texture = texture; }
            inline Texture* getTexture() const { return _texture; }

            inline void setTimeStamp(double timestamp) { _timeStamp = timestamp; }
            inline double getTimeStamp() const { return _timeStamp; }

            inline void setAllocated(bool allocated=true) { _allocated = allocated; }

            void setAllocated(GLint     numMipmapLevels,
                              GLenum    internalFormat,
                              GLsizei   width,
                              GLsizei   height,
                              GLsizei   depth,
                              GLint     border);

            inline bool isAllocated() const { return _allocated; }

            inline bool isReusable() const { return _allocated && _profile._width!=0; }


            GLuint              _id;
            TextureProfile      _profile;
            TextureObjectSet*   _set;
            TextureObject*      _previous;
            TextureObject*      _next;
            Texture*            _texture;
            bool                _allocated;
            unsigned int        _frameLastUsed;
            double              _timeStamp;

        protected:
            virtual ~TextureObject();

        };

        typedef std::list< ref_ptr<TextureObject> > TextureObjectList;

        class OSG_EXPORT TextureObjectSet : public ::CVBF_Referenced
        {
        public:
            TextureObjectSet(TextureObjectManager* parent, const TextureProfile& profile);

            const TextureProfile& getProfile() const { return _profile; }

            void handlePendingOrphandedTextureObjects();

            void deleteAllTextureObjects();
            void discardAllTextureObjects();
            void flushAllDeletedTextureObjects();
            void discardAllDeletedTextureObjects();
            void flushDeletedTextureObjects(double currentTime, double& availableTime);

            TextureObject* takeFromOrphans(Texture* texture);
            TextureObject* takeOrGenerate(Texture* texture);
            void moveToBack(TextureObject* to);
            void addToBack(TextureObject* to);
            void orphan(TextureObject* to);
            void remove(TextureObject* to);
            void moveToSet(TextureObject* to, TextureObjectSet* set);

            unsigned int size() const { return _profile._size * _numOfTextureObjects; }

            bool makeSpace(unsigned int& size);

            bool checkConsistency() const;

            TextureObjectManager* getParent() { return _parent; }

            unsigned int computeNumTextureObjectsInList() const;
            unsigned int getNumOfTextureObjects() const { return _numOfTextureObjects; }
            unsigned int getNumOrphans() const { return _orphanedTextureObjects.size(); }
            unsigned int getNumPendingOrphans() const { return _pendingOrphanedTextureObjects.size(); }

        protected:

            virtual ~TextureObjectSet();

            OpenThreads::Mutex  _mutex;

            TextureObjectManager*       _parent;
            unsigned int                _contextID;
            TextureProfile              _profile;
            unsigned int                _numOfTextureObjects;
            TextureObjectList           _orphanedTextureObjects;
            TextureObjectList           _pendingOrphanedTextureObjects;

            TextureObject*              _head;
            TextureObject*              _tail;

        };

        class OSG_EXPORT TextureObjectManager : public ::CVBF_Referenced
        {
        public:
            TextureObjectManager(unsigned int contextID);

            unsigned int getContextID() const { return _contextID; }



            void setNumberActiveTextureObjects(unsigned int size) { _numActiveTextureObjects = size; }
            unsigned int& getNumberActiveTextureObjects() { return _numActiveTextureObjects; }
            unsigned int getNumberActiveTextureObjects() const { return _numActiveTextureObjects; }

            void setNumberOrphanedTextureObjects(unsigned int size) { _numOrphanedTextureObjects = size; }
            unsigned int& getNumberOrphanedTextureObjects() { return _numOrphanedTextureObjects; }
            unsigned int getNumberOrphanedTextureObjects() const { return _numOrphanedTextureObjects; }

            void setCurrTexturePoolSize(unsigned int size) { _currTexturePoolSize = size; }
            unsigned int& getCurrTexturePoolSize() { return _currTexturePoolSize; }
            unsigned int getCurrTexturePoolSize() const { return _currTexturePoolSize; }

            void setMaxTexturePoolSize(unsigned int size);
            unsigned int getMaxTexturePoolSize() const { return _maxTexturePoolSize; }

            bool hasSpace(unsigned int size) const { return (_currTexturePoolSize+size)<=_maxTexturePoolSize; }
            bool makeSpace(unsigned int size);

            TextureObject* generateTextureObject(const Texture* texture, GLenum target);
            TextureObject* generateTextureObject(const Texture* texture,
                                                        GLenum    target,
                                                        GLint     numMipmapLevels,
                                                        GLenum    internalFormat,
                                                        GLsizei   width,
                                                        GLsizei   height,
                                                        GLsizei   depth,
                                                        GLint     border);
            void handlePendingOrphandedTextureObjects();
            void deleteAllTextureObjects();
            void discardAllTextureObjects();
            void flushAllDeletedTextureObjects();
            void discardAllDeletedTextureObjects();
            void flushDeletedTextureObjects(double currentTime, double& availableTime);
            void releaseTextureObject(TextureObject* to);

            TextureObjectSet* getTextureObjectSet(const TextureProfile& profile);

            void newFrame(::CVBF_FrameStamp* fs);
            void resetStats();
            void reportStats(std::ostream& out);
            void recomputeStats(std::ostream& out) const;
            bool checkConsistency() const;

            unsigned int& getFrameNumber() { return _frameNumber; }
            unsigned int& getNumberFrames() { return _numFrames; }

            unsigned int& getNumberDeleted() { return _numDeleted; }
            double& getDeleteTime() { return _deleteTime; }

            unsigned int& getNumberGenerated() { return _numGenerated; }
            double& getGenerateTime() { return _generateTime; }

            unsigned int& getNumberApplied() { return _numApplied; }
            double& getApplyTime() { return _applyTime; }


        protected:

            typedef std::map< TextureProfile, ref_ptr<TextureObjectSet> > TextureSetMap;
            unsigned int        _contextID;
            unsigned int        _numActiveTextureObjects;
            unsigned int        _numOrphanedTextureObjects;
            unsigned int        _currTexturePoolSize;
            unsigned int        _maxTexturePoolSize;
            TextureSetMap       _textureSetMap;

            unsigned int        _frameNumber;

            unsigned int        _numFrames;
            unsigned int        _numDeleted;
            double              _deleteTime;

            unsigned int        _numGenerated;
            double              _generateTime;

            unsigned int        _numApplied;
            double              _applyTime;

        };

        static ref_ptr<Texture::TextureObjectManager>&  getTextureObjectManager(unsigned int contextID);

        static TextureObject* generateTextureObject(const Texture* texture, unsigned int contextID,GLenum target);

        static TextureObject* generateTextureObject(const Texture* texture,
                                                     unsigned int contextID,
                                                     GLenum    target,
                                                     GLint     numMipmapLevels,
                                                     GLenum    internalFormat,
                                                     GLsizei   width,
                                                     GLsizei   height,
                                                     GLsizei   depth,
                                                     GLint     border);

        static void deleteAllTextureObjects(unsigned int contextID);
        static void discardAllTextureObjects(unsigned int contextID);
        static void flushAllDeletedTextureObjects(unsigned int contextID);
        static void discardAllDeletedTextureObjects(unsigned int contextID);
        static void flushDeletedTextureObjects(unsigned int contextID,double currentTime, double& availableTime);
        static void releaseTextureObject(unsigned int contextID, TextureObject* to);

    protected:

        typedef buffered_object< ref_ptr<TextureObject> >  TextureObjectBuffer;
        mutable TextureObjectBuffer         _textureObjectBuffer;
        mutable ref_ptr<GraphicsContext>    _readPBuffer;

};

}

#endif
