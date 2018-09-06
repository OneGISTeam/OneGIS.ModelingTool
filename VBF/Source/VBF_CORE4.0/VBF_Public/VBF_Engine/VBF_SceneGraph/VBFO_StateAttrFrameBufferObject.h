
// initial FBO support written by Marco Jez, June 2005.

#ifndef OSG_FRAMEBUFFEROBJECT
#define OSG_FRAMEBUFFEROBJECT 1

#include <VBF_Engine/VBF_SceneGraph/VBF_GLFBO.h>
//#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture.h>
#include <VBF_Engine/VBF_SceneGraph/buffered_value>
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>



namespace osg
{

/**************************************************************************
 * FBOExtensions
 **************************************************************************/

    class OSG_EXPORT FBOExtensions : public ::CVBF_Referenced
    {
    public:
        typedef void GL_APIENTRY TglBindRenderbuffer(GLenum, GLuint);
        typedef void GL_APIENTRY TglDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers);
        typedef void GL_APIENTRY TglGenRenderbuffers(GLsizei, GLuint *);
        typedef void GL_APIENTRY TglRenderbufferStorage(GLenum, GLenum, GLsizei, GLsizei);
        typedef void GL_APIENTRY TglRenderbufferStorageMultisample(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
        typedef void GL_APIENTRY TglRenderbufferStorageMultisampleCoverageNV(GLenum, GLsizei, GLsizei, GLenum, GLsizei, GLsizei);
        typedef void GL_APIENTRY TglBindFramebuffer(GLenum, GLuint);
        typedef void GL_APIENTRY TglDeleteFramebuffers(GLsizei n, const GLuint *framebuffers);
        typedef void GL_APIENTRY TglGenFramebuffers(GLsizei, GLuint *);
        typedef GLenum GL_APIENTRY TglCheckFramebufferStatus(GLenum);
        typedef void GL_APIENTRY TglFramebufferTexture1D(GLenum, GLenum, GLenum, GLuint, GLint);
        typedef void GL_APIENTRY TglFramebufferTexture2D(GLenum, GLenum, GLenum, GLuint, GLint);
        typedef void GL_APIENTRY TglFramebufferTexture3D(GLenum, GLenum, GLenum, GLuint, GLint, GLint);
        typedef void GL_APIENTRY TglFramebufferTexture(GLenum, GLenum, GLint, GLint);
        typedef void GL_APIENTRY TglFramebufferTextureLayer(GLenum, GLenum, GLuint, GLint, GLint);
        typedef void GL_APIENTRY TglFramebufferRenderbuffer(GLenum, GLenum, GLenum, GLuint);
        typedef void GL_APIENTRY TglGenerateMipmap(GLenum);
        typedef void GL_APIENTRY TglBlitFramebuffer(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
        typedef void GL_APIENTRY TglGetRenderbufferParameteriv(GLenum, GLenum, GLint*);

        TglBindRenderbuffer* glBindRenderbuffer;
        TglGenRenderbuffers* glGenRenderbuffers;
        TglDeleteRenderbuffers* glDeleteRenderbuffers; 
        TglRenderbufferStorage* glRenderbufferStorage;
        TglRenderbufferStorageMultisample* glRenderbufferStorageMultisample;
        TglRenderbufferStorageMultisampleCoverageNV* glRenderbufferStorageMultisampleCoverageNV;
        TglBindFramebuffer* glBindFramebuffer;
        TglDeleteFramebuffers* glDeleteFramebuffers;
        TglGenFramebuffers* glGenFramebuffers;
        TglCheckFramebufferStatus* glCheckFramebufferStatus;
        TglFramebufferTexture1D* glFramebufferTexture1D;
        TglFramebufferTexture2D* glFramebufferTexture2D;
        TglFramebufferTexture3D* glFramebufferTexture3D;
        TglFramebufferTexture* glFramebufferTexture;
        TglFramebufferTextureLayer* glFramebufferTextureLayer;
        TglFramebufferRenderbuffer* glFramebufferRenderbuffer;
        TglGenerateMipmap* glGenerateMipmap;
        TglBlitFramebuffer* glBlitFramebuffer;
        TglGetRenderbufferParameteriv* glGetRenderbufferParameteriv;

        static FBOExtensions* instance(unsigned contextID, bool createIfNotInitalized);

        bool isSupported() const { return _supported; }
        bool isMultisampleSupported() const { return glRenderbufferStorageMultisample != 0; }
        bool isMultisampleCoverageSupported() const { return glRenderbufferStorageMultisampleCoverageNV != 0; }
        bool isPackedDepthStencilSupported() const { return _packed_depth_stencil_supported; }

    protected:
        FBOExtensions(unsigned int contextID);

        bool _supported;
        bool _packed_depth_stencil_supported;
    };

/**************************************************************************
 * RenderBuffer
 **************************************************************************/

    class OSG_EXPORT RenderBuffer: public CVBF_Object
    {
    public:
        RenderBuffer();
        RenderBuffer(int width, int height, GLenum internalFormat, int samples=0, int colorSamples=0);
        RenderBuffer(const RenderBuffer& copy, const CopyOp& copyop = CopyOp::SHALLOW_COPY);

        META_Object(osg, RenderBuffer);

        inline int getWidth() const;
        inline int getHeight() const;
        inline void setWidth(int w);
        inline void setHeight(int h);
        inline void setSize(int w, int h);
        inline GLenum getInternalFormat() const;
        inline void setInternalFormat(GLenum format);
        inline int getSamples() const;
        inline int getColorSamples() const;
        inline void setSamples(int samples);
        inline void setColorSamples(int colorSamples);

        GLuint getObjectID(unsigned int contextID, const FBOExtensions *ext) const;
        inline int compare(const RenderBuffer &rb) const;

        /** Mark internal RenderBuffer for deletion.
          * Deletion requests are queued until they can be executed
          * in the proper GL context. */
        static void deleteRenderBuffer(unsigned int contextID, GLuint rb);

        /** flush all the cached RenderBuffers which need to be deleted
          * in the OpenGL context related to contextID.*/
        static void flushDeletedRenderBuffers(unsigned int contextID,double currentTime, double& availableTime);

        /** discard all the cached RenderBuffers which need to be deleted in the OpenGL context related to contextID.
          * Note, unlike flush no OpenGL calls are made, instead the handles are all removed.
          * this call is useful for when an OpenGL context has been destroyed. */
        static void discardDeletedRenderBuffers(unsigned int contextID);

        static int getMaxSamples(unsigned int contextID, const FBOExtensions *ext);

        /** Resize any per context GLObject buffers to specified size. */
        virtual void resizeGLObjectBuffers(unsigned int maxSize);

        /** If State is non-zero, this function releases any associated OpenGL objects for
           * the specified graphics context. Otherwise, releases OpenGL objexts
           * for all graphics contexts. */
        virtual void releaseGLObjects(osg::State* = 0) const;

    protected:
        virtual ~RenderBuffer();
        RenderBuffer &operator=(const RenderBuffer &) { return *this; }

        inline void dirtyAll() const;

    private:
        mutable buffered_value<GLuint> _objectID;
        mutable buffered_value<int> m_bDirty;

        GLenum _internalFormat;
        int _width;
        int _height;
        // "samples" in the framebuffer_multisample extension is equivalent to
        // "coverageSamples" in the framebuffer_multisample_coverage extension.
        int _samples;
        int _colorSamples;
    };

    // INLINE METHODS

    inline int RenderBuffer::getWidth() const
    {
        return _width;
    }

    inline int RenderBuffer::getHeight() const
    {
        return _height;
    }

    inline void RenderBuffer::setWidth(int w)
    {
        _width = w;
        dirtyAll();
    }

    inline void RenderBuffer::setHeight(int h)
    {
        _height = h;
        dirtyAll();
    }

    inline void RenderBuffer::setSize(int w, int h)
    {
        _width = w;
        _height = h;
        dirtyAll();
    }

    inline GLenum RenderBuffer::getInternalFormat() const
    {
        return _internalFormat;
    }

    inline void RenderBuffer::setInternalFormat(GLenum format)
    {
        _internalFormat = format;
        dirtyAll();
    }

    inline int RenderBuffer::getSamples() const
    {
        return _samples;
    }

    inline int RenderBuffer::getColorSamples() const
    {
        return _colorSamples;
    }

    inline void RenderBuffer::setSamples(int samples)
    {
        _samples = samples;
        dirtyAll();
    }

    inline void RenderBuffer::setColorSamples(int colorSamples)
    {
        _colorSamples = colorSamples;
        dirtyAll();
    }

    inline void RenderBuffer::dirtyAll() const
    {
        m_bDirty.setAllElementsTo(1);
    }

    inline int RenderBuffer::compare(const RenderBuffer &rb) const
    {
        if (&rb == this) return 0;
        if (_internalFormat < rb._internalFormat) return -1;
        if (_internalFormat > rb._internalFormat) return 1;
        if (_width < rb._width) return -1;
        if (_width > rb._width) return 1;
        if (_height < rb._height) return -1;
        if (_height > rb._height) return 1;
        return 0;
    }

/**************************************************************************
 * FrameBufferAttachement
 **************************************************************************/
    class Texture1D;
    class Texture2D;
    class Texture2DMultisample;
    class Texture3D;
    class Texture2DArray;
    class TextureCubeMap;
    class TextureRectangle;

    class OSG_EXPORT FrameBufferAttachment
    {
    public:
        FrameBufferAttachment();
        FrameBufferAttachment(const FrameBufferAttachment& copy);

        explicit FrameBufferAttachment(RenderBuffer* target);
        explicit FrameBufferAttachment(Texture1D* target, unsigned int level = 0);
        explicit FrameBufferAttachment(Texture2D* target, unsigned int level = 0);
        explicit FrameBufferAttachment(Texture2DMultisample* target, unsigned int level = 0);
        explicit FrameBufferAttachment(Texture3D* target, unsigned int zoffset, unsigned int level = 0);
        explicit FrameBufferAttachment(Texture2DArray* target, unsigned int layer, unsigned int level = 0);
        explicit FrameBufferAttachment(TextureCubeMap* target, unsigned int face, unsigned int level = 0);
        explicit FrameBufferAttachment(TextureRectangle* target);
        explicit FrameBufferAttachment(Camera::Attachment& attachment);
        
        ~FrameBufferAttachment();

        FrameBufferAttachment&operator = (const FrameBufferAttachment& copy);        

        bool isMultisample() const;
        void createRequiredTexturesAndApplyGenerateMipMap(State& state, const FBOExtensions* ext) const;
        void attach(State &state, GLenum target, GLenum attachment_point, const FBOExtensions* ext) const;
        int compare(const FrameBufferAttachment &fa) const;

        RenderBuffer* getRenderBuffer();
        const RenderBuffer* getRenderBuffer() const;

        Texture* getTexture();
        const Texture* getTexture() const;

        unsigned int getCubeMapFace() const;
        unsigned int getTextureLevel() const;
        unsigned int getTexture3DZOffset() const;
        unsigned int getTextureArrayLayer() const;

    private:
        // use the Pimpl idiom to avoid dependency from
        // all Texture* headers
        struct Pimpl;
        Pimpl* _ximpl;
    };

/**************************************************************************
 * FrameBufferObject
 **************************************************************************/
    class OSG_EXPORT FrameBufferObject: public StateAttribute
    {
    public:
        typedef std::map<Camera::BufferComponent, FrameBufferAttachment> AttachmentMap;
        typedef std::vector<GLenum> MultipleRenderingTargets;
        
        typedef Camera::BufferComponent BufferComponent;

        FrameBufferObject();
        FrameBufferObject(const FrameBufferObject& copy, const CopyOp& copyop = CopyOp::SHALLOW_COPY);

        META_StateAttribute(osg, FrameBufferObject, (StateAttribute::Type)0x101010/*FrameBufferObject*/);

        inline const AttachmentMap& getAttachmentMap() const;
        

        void setAttachment(BufferComponent attachment_point, const FrameBufferAttachment &attachment);
        inline const FrameBufferAttachment& getAttachment(BufferComponent attachment_point) const;
        inline bool hasAttachment(BufferComponent attachment_point) const;
        
        inline bool hasMultipleRenderingTargets() const { return !_drawBuffers.empty(); }
        inline const MultipleRenderingTargets& getMultipleRenderingTargets() const { return _drawBuffers; }

        bool isMultisample() const;

        int compare(const StateAttribute &sa) const;
        
        void apply(State &state) const;

        enum BindTarget
        {
            READ_FRAMEBUFFER = GL_READ_FRAMEBUFFER_EXT,
            DRAW_FRAMEBUFFER = GL_DRAW_FRAMEBUFFER_EXT,
            READ_DRAW_FRAMEBUFFER = GL_FRAMEBUFFER_EXT
        };

        /** Bind the FBO as either the read or draw target, or both. */
        void apply(State &state, BindTarget target) const;

        /** Mark internal FBO for deletion.
          * Deletion requests are queued until they can be executed
          * in the proper GL context. */
        static void deleteFrameBufferObject(unsigned int contextID, GLuint program);

        /** flush all the cached FBOs which need to be deleted
          * in the OpenGL context related to contextID.*/
        static void flushDeletedFrameBufferObjects(unsigned int contextID,double currentTime, double& availableTime);

        /** discard all the cached FBOs which need to be deleted
          * in the OpenGL context related to contextID.*/
        static void discardDeletedFrameBufferObjects(unsigned int contextID);

        /** Resize any per context GLObject buffers to specified size. */
        virtual void resizeGLObjectBuffers(unsigned int maxSize);

        /** If State is non-zero, this function releases any associated OpenGL objects for
           * the specified graphics context. Otherwise, releases OpenGL objexts
           * for all graphics contexts. */
        virtual void releaseGLObjects(osg::State* = 0) const;

    protected:
        virtual ~FrameBufferObject();
        FrameBufferObject& operator = (const FrameBufferObject&) { return *this; }

        void updateDrawBuffers();
        
        inline void dirtyAll();

        GLenum convertBufferComponentToGLenum(BufferComponent attachment_point) const;

    private:        
        AttachmentMap               _attachments;

        // Buffers passed to glDrawBuffers when using multiple render targets.
        MultipleRenderingTargets    _drawBuffers;

        mutable buffered_value<int>         _dirtyAttachmentList;
        mutable buffered_value<int>         _unsupported;
        mutable buffered_value<GLuint>      _fboID;
        
    };

    // INLINE METHODS

    inline const FrameBufferObject::AttachmentMap &FrameBufferObject::getAttachmentMap() const
    {
        return _attachments;
    }

    inline bool FrameBufferObject::hasAttachment(FrameBufferObject::BufferComponent attachment_point) const
    {
        return _attachments.find(attachment_point) != _attachments.end();
    }

    inline const FrameBufferAttachment &FrameBufferObject::getAttachment(FrameBufferObject::BufferComponent attachment_point) const
    {
        return _attachments.find(attachment_point)->second;
    }

    inline void FrameBufferObject::dirtyAll()
    {
        _dirtyAttachmentList.setAllElementsTo(1);
    }


}

#endif

