#ifndef OSG_CAMERA
#define OSG_CAMERA 1





//#include <VBF_Engine/VBF_SceneGraph/Image>
//#include <VBF_Engine/VBF_SceneGraph/GraphicsContext.h>
#include <VBF_Base/VBF_Stats.h>

//#include <OpenThreads/Mutex>

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_Camera.h>

namespace osg {


class OSG_EXPORT Camera : public IVBF_SGNodeGroupTransformImpl<IVBF_Camera>
{
    public :


        Camera();

        /** 拷贝构造函数，CopyOp决定深拷贝或浅拷贝。 */
        Camera(const Camera&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        META_Node(osg, Camera);

        /** 设置/获取相机所属的视图 */
        void setView(IVBF_ViewBrief* view) { _view = view; }
        IVBF_ViewBrief* getView() { return _view; }
        const IVBF_ViewBrief* getView() const { return _view; }


        /** 设置/获取统计对象，用于统计帧相关的时间和场景图数据 */
        void setStats(::CVBF_Stats* stats) { _stats = stats; }
		::CVBF_Stats* getStats() { return _stats.get(); }
	    const ::CVBF_Stats* getStats() const { return _stats.get(); }


        /** 设置/获取是否允许接收事件 */
        void setAllowEventFocus(bool focus) { _allowEventFocus = focus; }
	    bool getAllowEventFocus() const { return _allowEventFocus; }


        /** 设置/获取显示设置DisplaySettings*/
        void setDisplaySettings(osg::DisplaySettings* ds) { _displaySettings = ds; }
        osg::DisplaySettings* getDisplaySettings() { return _displaySettings.get(); }
        const osg::DisplaySettings* getDisplaySettings() const { return _displaySettings.get(); }


        /** 设置/获取glClear()中使用的clear mask，默认为GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT */
        inline void setClearMask(GLbitfield mask) { _clearMask = mask; applyMaskAction(CLEAR_MASK); }
        inline GLbitfield getClearMask() const { return _clearMask; }

        /** Set the clear color used in glClearColor().
          * glClearColor is only called if mask & GL_COLOR_BUFFER_BIT is true*/
        void setClearColor(const osg::Vec4& color) { _clearColor=color; applyMaskAction(CLEAR_COLOR); }
        const osg::Vec4& getClearColor() const { return _clearColor; }

        /** Set the clear accum used in glClearAccum().
          * glClearAcumm is only called if mask & GL_ACCUM_BUFFER_BIT is true. */
        void setClearAccum(const osg::Vec4& color) { _clearAccum=color; }
        const osg::Vec4& getClearAccum() const { return _clearAccum; }

        /** Set the clear depth used in glClearDepth(). Defaults to 1.0
          * glClearDepth is only called if mask & GL_DEPTH_BUFFER_BIT is true. */
        void setClearDepth(double depth) { _clearDepth=depth; }
        double getClearDepth() const { return _clearDepth; }

        /** Set the clear stencil value used in glClearStencil(). Defaults to 0;
          * glClearStencil is only called if mask & GL_STENCIL_BUFFER_BIT is true*/
        void setClearStencil(int stencil) { _clearStencil=stencil; }
        int getClearStencil() const { return _clearStencil; }


        /** Set the color mask of the camera to use specified osg::ColorMask. */
        void setColorMask(osg::ColorMask* colorMask);
        void setColorMask(bool red, bool green, bool blue, bool alpha);
        const ColorMask* getColorMask() const { return _colorMask.get(); }
        ColorMask* getColorMask() { return _colorMask.get(); }


        /** Set the viewport of the camera to use specified osg::Viewport. */
        void setViewport(osg::Viewport* viewport);
        void setViewport(int x,int y,int width,int height);
        const Viewport* getViewport() const { return _viewport.get(); }
        Viewport* getViewport() { return _viewport.get(); }


         /** Set the transformation order for world-to-local and local-to-world transformation.*/
        void setTransformOrder(TransformOrder order) { _transformOrder = order; }
        TransformOrder getTransformOrder() const { return _transformOrder; }

 
        /** Set the policy used to determine if and how the projection matrix should be adjusted on window resizes. */
        inline void setProjectionResizePolicy(ProjectionResizePolicy policy) { _projectionResizePolicy = policy; }

        /** Get the policy used to determine if and how the projection matrix should be adjusted on window resizes. */
        inline ProjectionResizePolicy getProjectionResizePolicy() const { return _projectionResizePolicy; }


        /** Set the projection matrix. Can be thought of as setting the lens of a camera. */
        inline void setProjectionMatrix(const osg::Matrixf& matrix) { _projectionMatrix.set(matrix); }
        inline void setProjectionMatrix(const osg::Matrixd& matrix) { _projectionMatrix.set(matrix); }

        /** Set to an orthographic projection. See OpenGL glOrtho for documentation further details.*/
        void setProjectionMatrixAsOrtho(double left, double right, double bottom, double top, double zNear, double zFar);

        /** Set to a 2D orthographic projection. See OpenGL glOrtho2D documentation for further details.*/
        void setProjectionMatrixAsOrtho2D(double left, double right, double bottom, double top);

        /** Set to a perspective projection. See OpenGL glFrustum documentation for further details.*/
        void setProjectionMatrixAsFrustum(double left, double right, double bottom, double top, double zNear, double zFar);

        /** Create a symmetrical perspective projection, See OpenGL gluPerspective documentation for further details.
          * Aspect ratio is defined as width/height.*/
        void setProjectionMatrixAsPerspective(double fovy,double aspectRatio, double zNear, double zFar);

        /** Get the projection matrix.*/
        osg::Matrixd& getProjectionMatrix() { return _projectionMatrix; }
        const osg::Matrixd& getProjectionMatrix() const { return _projectionMatrix; }

        /** Get the orthographic settings of the orthographic projection matrix.
          * Returns false if matrix is not an orthographic matrix, where parameter values are undefined.*/
        bool getProjectionMatrixAsOrtho(double& left, double& right, double& bottom, double& top, double& zNear, double& zFar) const;

        /** Get the frustum setting of a perspective projection matrix.
          * Returns false if matrix is not a perspective matrix, where parameter values are undefined.*/
        bool getProjectionMatrixAsFrustum(double& left, double& right, double& bottom, double& top, double& zNear, double& zFar) const;

        /** Get the frustum setting of a symmetric perspective projection matrix.
          * Returns false if matrix is not a perspective matrix, where parameter values are undefined.
          * Note, if matrix is not a symmetric perspective matrix then the shear will be lost.
          * Asymmetric matrices occur when stereo, power walls, caves and reality center display are used.
          * In these configurations one should use the 'getProjectionMatrixAsFrustum' method instead.*/
        bool getProjectionMatrixAsPerspective(double& fovy,double& aspectRatio, double& zNear, double& zFar) const;







        /** Set the view matrix. Can be thought of as setting the position of the world relative to the camera in camera coordinates. */
        inline void setViewMatrix(const osg::Matrixf& matrix) { _viewMatrix.set(matrix);  dirtyBound();}
        inline void setViewMatrix(const osg::Matrixd& matrix) { _viewMatrix.set(matrix);  dirtyBound();}
        osg::Matrixd& getViewMatrix() { return _viewMatrix; }
        const osg::Matrixd& getViewMatrix() const { return _viewMatrix; }

        /** Set to the position and orientation of view matrix, using the same convention as gluLookAt. */
        void setViewMatrixAsLookAt(const osg::Vec3d& eye,const osg::Vec3d& center,const osg::Vec3d& up);
        void getViewMatrixAsLookAt(osg::Vec3d& eye,osg::Vec3d& center,osg::Vec3d& up,double lookDistance=1.0) const;
        void getViewMatrixAsLookAt(osg::Vec3f& eye,osg::Vec3f& center,osg::Vec3f& up,float lookDistance=1.0f) const;

        Matrixd getInverseViewMatrix() const;


        /** 设置/获取相机子图的渲染顺序，relative to any camera that this subgraph is nested within.
          * 渲染到纹理选择PRE_RENDER，渲染"屏显"选择POST_RENDER.*/
        void setRenderOrder(RenderOrder order, int orderNum = 0) { _renderOrder = order; _renderOrderNum = orderNum; }
        RenderOrder getRenderOrder() const { return _renderOrder; }

        /** Get the rendering order number of this camera relative to any sibling cameras in this subgraph.*/
        int getRenderOrderNum() const { return _renderOrderNum; }

        /** Return true if this Camera is set up as a render to texture camera, i.e. it has textures assigned to it.*/
        bool isRenderToTextureCamera() const;

 

        /** Set the render target.*/
        void setRenderTargetImplementation(RenderTargetImplementation impl);

        /** Set the render target and fall-back that's used if the former isn't available.*/
        void setRenderTargetImplementation(RenderTargetImplementation impl, RenderTargetImplementation fallback);

        /** 获取渲染目标实现方式 */
        RenderTargetImplementation getRenderTargetImplementation() const { return _renderTargetImplementation; }

        /** Get the render target fallback.*/
        RenderTargetImplementation getRenderTargetFallback() const { return _renderTargetFallback; }


		/** 设置/获取draw buffer，在每帧绘制开始时采用。GL_NONE表示选择最合适的buffer */
        void setDrawBuffer(GLenum buffer) { _drawBuffer = buffer; applyMaskAction( DRAW_BUFFER ); }
        GLenum getDrawBuffer() const { return _drawBuffer; }

		/** 设置/获取read buffer，在每帧绘制开始时采用。GL_NONE表示选择最合适的buffer */
        void setReadBuffer(GLenum buffer) { _readBuffer = buffer; applyMaskAction( READ_BUFFER ); }
        GLenum getReadBuffer() const { return _readBuffer; }


  
        static const unsigned int FACE_CONTROLLED_BY_GEOMETRY_SHADER;

/*
	需要特别注意的是：如果希望使用 FBO来实现纹理烘焙或者场景截图的话，不可以将场景主摄像机的setRenderTargetImplementation直接设置为相应的枚举量，那样将无法正常
	地看到场景（因为主摄像机对应的渲染台已经将场景绘制的结果绑定到FBO 上了）。正确的作法是在场景树中增加一个Camera 节点，设置“渲染目标实现方式”为FBO 方式；并通
	过Camera::setRenderOrder 设定它的渲染顺序，设置为PRE_RENDER 可以保证这个摄像机在主场景之前执行绘制（它创建了一个“前序渲染台”，存入RenderStage::_preRenderList
	列表），从而实现“渲染到纹理”的效果。
	*/

        /** Attach a buffer with specified OpenGL internal format.*/
        void attach(BufferComponent buffer, GLenum internalFormat);

        /** Attach a Texture to specified buffer component.
          * The level parameter controls the mip map level of the texture that is attached.
          * The face parameter controls the face of texture cube map or z level of 3d texture.
          * The mipMapGeneration flag controls whether mipmap generation should be done for texture.*/
        void attach(BufferComponent buffer, osg::Texture* texture, unsigned int level = 0, unsigned int face=0, bool mipMapGeneration=false,
            unsigned int multisampleSamples = 0,
            unsigned int multisampleColorSamples = 0);

        /** Attach a Image to specified buffer component.*/
        void attach(BufferComponent buffer, osg::Image* image, unsigned int multisampleSamples = 0, unsigned int multisampleColorSamples = 0);

        /** Detach specified buffer component.*/
        void detach(BufferComponent buffer);

    
  
        /** Get the BufferAttachmentMap, used to configure frame buffer objects, pbuffers and texture reads.*/
        BufferAttachmentMap& getBufferAttachmentMap() { return _bufferAttachmentMap; }
        const BufferAttachmentMap& getBufferAttachmentMap() const { return _bufferAttachmentMap; }






        /** Explicit control over implicit allocation of buffers when using FBO.
         Implicit buffers are automatically substituted when user have not attached such buffer.

         Camera may set up two FBOs: primary Render FBO and secondary Resolve FBO for multisample usage.
         So in practive we have two masks defined for the Camera:
            implicitBufferAttachmentRenderMask
            implicitBufferAttachmentResolveMask
         They can be set together by setImplicitBufferAttachmentMask method, or separately
         by setImplicitBufferAttachmentRenderMask and setImplicitBufferAttachmentResolveMask.

         Camera defaults are USE_DISPLAY_SETTINGS_MASK which means that by default
         Camera chooses to substitue buffer attachments as defined by DisplaySettings.

         Usually DisplaySettings implicit buffer attachment selection defaults to: DEPTH and COLOR 
         for both primary (Render) FBO and seconday Multisample (Resolve) FBO
         ie: IMPLICT_DEPTH_BUFFER_ATTACHMENT | IMPLICIT_COLOR_BUFFER_ATTACHMENT

         If these masks are not changed and user did not attach depth buffer and/or color buffer 
         to Camera, then OSG implicitly substitues these buffers.
         By default it does not implicitly allocate a stencil buffer.
         Use implicti buffer attachment  masks to override default behavior: 
         to turn off DEPTH or COLOR buffer substitution or to enforce STENCIL buffer substitution.

         Note that both values are ignored if not using FBO.
         Note that the second mask value is ignored if not using MSFBO.
        */
        enum ImplicitBufferAttachment
        {
            IMPLICIT_DEPTH_BUFFER_ATTACHMENT = DisplaySettings::IMPLICIT_DEPTH_BUFFER_ATTACHMENT,
            IMPLICIT_STENCIL_BUFFER_ATTACHMENT = DisplaySettings::IMPLICIT_STENCIL_BUFFER_ATTACHMENT,
            IMPLICIT_COLOR_BUFFER_ATTACHMENT = DisplaySettings::IMPLICIT_COLOR_BUFFER_ATTACHMENT,
            USE_DISPLAY_SETTINGS_MASK = (~0)
        };

        typedef int ImplicitBufferAttachmentMask;

        void setImplicitBufferAttachmentMask(ImplicitBufferAttachmentMask renderMask = DisplaySettings::DEFAULT_IMPLICIT_BUFFER_ATTACHMENT, ImplicitBufferAttachmentMask resolveMask = DisplaySettings::DEFAULT_IMPLICIT_BUFFER_ATTACHMENT)
        {
            _implicitBufferAttachmentRenderMask = renderMask;
            _implicitBufferAttachmentResolveMask = resolveMask;
        }

        void setImplicitBufferAttachmentRenderMask(ImplicitBufferAttachmentMask implicitBufferAttachmentRenderMask)
        {
            _implicitBufferAttachmentRenderMask = implicitBufferAttachmentRenderMask;
        }

        void setImplicitBufferAttachmentResolveMask(ImplicitBufferAttachmentMask implicitBufferAttachmentResolveMask)
        {
            _implicitBufferAttachmentResolveMask = implicitBufferAttachmentResolveMask;
        }

        /** 
        Get mask selecting implict buffer attachments for Camera primary FBO 
        if effectiveMask parameter is set, method follows USE_DISPLAY_SETTINGS_MASK dependence and returns effective mask
        if effectiveMask parameter is reset, method returns nominal mask set by the Camera
        */
        ImplicitBufferAttachmentMask getImplicitBufferAttachmentRenderMask(bool effectiveMask = false) const
        { 
            if( effectiveMask && _implicitBufferAttachmentRenderMask == USE_DISPLAY_SETTINGS_MASK )
            {
                const DisplaySettings * ds = _displaySettings.valid() ? _displaySettings.get() : DisplaySettings::instance().get();
                return ds->getImplicitBufferAttachmentRenderMask();
            }
            else
            {
                return _implicitBufferAttachmentRenderMask;
            }
        }

        /** 
        Get mask selecting implict buffer attachments for Camera secondary MULTISAMPLE FBO 
        if effectiveMask parameter is set, method follows USE_DISPLAY_SETTINGS_MASK dependence and returns effective mask
        if effectiveMask parameter is reset, method returns nominal mask set by the Camera
        */
        ImplicitBufferAttachmentMask getImplicitBufferAttachmentResolveMask(bool effectiveMask = false) const
        { 
            if( effectiveMask && _implicitBufferAttachmentResolveMask == USE_DISPLAY_SETTINGS_MASK )
            {
                const DisplaySettings * ds = _displaySettings.valid() ? _displaySettings.get() : DisplaySettings::instance().get();
                return ds->getImplicitBufferAttachmentResolveMask();
            }
            else
            {
                return _implicitBufferAttachmentResolveMask;
            }
        }




        /** Create a operation thread for this camera.*/
        void createCameraThread();

        /** Assign a operation thread to the camera.*/
        void setCameraThread(OperationThread* gt);
        OperationThread* getCameraThread() { return _cameraThread.get(); }
        const OperationThread* getCameraThread() const { return _cameraThread.get(); }



        /** Set the GraphicsContext that provides the mechansim for managing the OpenGL graphics context associated with this camera.*/
        void setGraphicsContext(GraphicsContext* context);
        GraphicsContext* getGraphicsContext() { return _graphicsContext.get(); }
        const GraphicsContext* getGraphicsContext() const { return _graphicsContext.get(); }


        /** Set the Rendering object that is used to implement rendering of the subgraph.*/
        void setRenderer(osg::GraphicsOperation* rc) { _renderer = rc; }
        osg::GraphicsOperation* getRenderer() { return _renderer.get(); }
        const osg::GraphicsOperation* getRenderer() const { return _renderer.get(); }


		
        /** Set the Rendering cache that is used for cached objects associated with rendering of subgraphs.*/
        void setRenderingCache(osg::CVBF_Object* rc) { _renderingCache = rc; }
        osg::CVBF_Object* getRenderingCache() { return _renderingCache.get(); }
        const osg::CVBF_Object* getRenderingCache() const { return _renderingCache.get(); }


  

        /** 设置/获取自定义的绘图初始化（initial draw），用于绘制相机的子树及每一个渲染台之前进行初始化。*/
		void setInitialDrawCallback(DrawCallback* cb) { _initialDrawCallback = cb; }
		DrawCallback* getInitialDrawCallback() { return _initialDrawCallback.get(); }
        const DrawCallback* getInitialDrawCallback() const { return _initialDrawCallback.get(); }


        /** Set the pre draw callback for custom operations to be done before the drawing of the camera's subgraph but after any pre render stages have been completed.*/
        void setPreDrawCallback(DrawCallback* cb) { _preDrawCallback = cb; }
        DrawCallback* getPreDrawCallback() { return _preDrawCallback.get(); }
        const DrawCallback* getPreDrawCallback() const { return _preDrawCallback.get(); }


        /** Set the post draw callback for custom operations to be done after the drawing of the camera's subgraph but before the any post render stages have been completed.*/
        void setPostDrawCallback(DrawCallback* cb) { _postDrawCallback = cb; }
        DrawCallback* getPostDrawCallback() { return _postDrawCallback.get(); }
        const DrawCallback* getPostDrawCallback() const { return _postDrawCallback.get(); }


        /** Set the final draw callback for custom operations to be done after the drawing of the camera's subgraph and all of the post render stages has been completed.*/
        void setFinalDrawCallback(DrawCallback* cb) { _finalDrawCallback = cb; }
        DrawCallback* getFinalDrawCallback() { return _finalDrawCallback.get(); }
        const DrawCallback* getFinalDrawCallback() const { return _finalDrawCallback.get(); }


        OpenThreads::Mutex* getDataChangeMutex() const { return &_dataChangeMutex; }





        /** Resize any per context GLObject buffers to specified size. */
        virtual void resizeGLObjectBuffers(unsigned int maxSize);

        /** If State is non-zero, this function releases any associated OpenGL objects for
           * the specified graphics context. Otherwise, releases OpenGL objexts
           * for all graphics contexts. */
        virtual void releaseGLObjects(osg::State* = 0) const;

    public:

        /** Transform method that must be defined to provide generic interface for scene graph traversals.*/
        virtual bool computeLocalToWorldMatrix(Matrix& matrix,NodeVisitor*) const;

        /** Transform method that must be defined to provide generic interface for scene graph traversals.*/
        virtual bool computeWorldToLocalMatrix(Matrix& matrix,NodeVisitor*) const;

        /** Inherit the local cull settings variable from specified CullSettings object, according to the inheritance mask.*/
        virtual void inheritCullSettings(const CullSettings& settings, unsigned int inheritanceMask);

    protected :

        virtual ~Camera();

        mutable OpenThreads::Mutex          _dataChangeMutex;


        IVBF_ViewBrief*                      _view;

        ref_ptr< ::CVBF_Stats >            _stats;

        bool                                _allowEventFocus;

        ref_ptr<osg::DisplaySettings>  _displaySettings;

        GLbitfield                          _clearMask;
        osg::Vec4                           _clearColor;
        osg::Vec4                           _clearAccum;
        double                              _clearDepth;
        int                                 _clearStencil;

        ref_ptr<ColorMask>                  _colorMask;
        ref_ptr<Viewport>                   _viewport;

        TransformOrder                      _transformOrder;
        ProjectionResizePolicy              _projectionResizePolicy;

        Matrixd                             _projectionMatrix;
        Matrixd                             _viewMatrix;

        RenderOrder                         _renderOrder;
        int                                 _renderOrderNum;

        GLenum                              _drawBuffer;
        GLenum                              _readBuffer;

        RenderTargetImplementation          _renderTargetImplementation;
        RenderTargetImplementation          _renderTargetFallback;
        BufferAttachmentMap                 _bufferAttachmentMap;
        ImplicitBufferAttachmentMask        _implicitBufferAttachmentRenderMask;
        ImplicitBufferAttachmentMask        _implicitBufferAttachmentResolveMask;

        ref_ptr<OperationThread>            _cameraThread;

        ref_ptr<GraphicsContext>            _graphicsContext;

        ref_ptr<GraphicsOperation>          _renderer;
        ref_ptr<CVBF_Object>                     _renderingCache;

		// 用户自定义的回调接口
        ref_ptr<DrawCallback>               _initialDrawCallback; // 每次绘制之前（绘制子图和每一个渲染台之前）
        ref_ptr<DrawCallback>               _preDrawCallback;     // 绘制前调用
        ref_ptr<DrawCallback>               _postDrawCallback;    // 绘制后调用
        ref_ptr<DrawCallback>               _finalDrawCallback;   // 全部绘制结束后调用
};

}

#endif
