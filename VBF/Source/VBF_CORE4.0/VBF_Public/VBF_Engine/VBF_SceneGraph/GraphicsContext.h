#ifndef OSG_GRAPHICSCONTEXT
#define OSG_GRAPHICSCONTEXT 1



#include <VBF_Engine/VBF_SceneGraph/VBF_StateMachine.h>
#include <VBF_Engine/VBF_SceneGraph/GraphicsThread>

//#include <VBF_Base/VBF_Timer.h>
//
//#include <vector>


namespace osg {


class IVBF_Camera;

// �����͹���ͼ�λ�����Windowing API�Ļ���
class OSG_EXPORT GraphicsContext : public CVBF_Object
{
    public:  

        struct OSG_EXPORT ScreenIdentifier //��Ļ��ʶ��
        {
            ScreenIdentifier();
            ScreenIdentifier(int in_screenNum);
            ScreenIdentifier(const std::string& in_hostName,int in_displayNum, int in_screenNum);
            virtual ~ScreenIdentifier();
            
            // ����display name����ʽΪhostName::displayNum:screenNum
            std::string displayName() const;
            
            /** ��ȡDISPLAY��������������Ӧ������ScreenIdentifier�����displayNum��screenNumû��������Ϊ-1��ʾ��û���á�
              * ������readDISPLAY()֮�����setUndefinedScreenDetalstoDefaultScreen()ȷ��ֵ��Ч�� */
            void readDISPLAY();
            
            /** ͨ��displayName�ַ���������Ļ��ʶ��*/
            void setScreenIdentifier(const std::string& displayName);

            /** ����δ�����displayNum��screenNum (i.e. -1)Ϊȱʡ�ģ�0����*/
            void setUndefinedScreenDetailsToDefaultScreen()
            {
                if (displayNum<0) displayNum = 0;
                if (screenNum<0) screenNum = 0;
            }

            std::string  hostName;
            int displayNum;
            int screenNum;
        };
    



        // GraphicsContext�����ԣ�����ʹ��ʲô���͵�GC
        struct OSG_EXPORT Traits : public ::CVBF_Referenced, public ScreenIdentifier
        {
            Traits(DisplaySettings* ds=0);
            ~Traits();
                            
            // GC��ԭ��ʹ�С
            int x;       // ԭ��x����
            int y;		 // ԭ��y����
            int width;   // ��
            int height;  // ��

            
            // ����װ�κ���Ϊ
            std::string windowName;         // ��������
            bool        windowDecoration;   // �Ƿ�֧�ִ���װ�Σ�Win32�е�style��
            bool        supportsResize;     // �Ƿ�֧�ִ�������
            
            // ��������ȣ�0��ʾ�ر�
            unsigned int red;		// ��ɫ��Ĭ��8λ
            unsigned int blue;		// ��ɫ��Ĭ��8λ
            unsigned int green;		// ��ɫ��Ĭ��8λ
            unsigned int alpha;		// Alpha��Ĭ��0λ��ΪRGB��ʽ
            unsigned int depth;		// ��ȣ�16��24��32����Ĭ��24λ������ZBUFFER
            unsigned int stencil;	// ģ�建�棬Ĭ����

            // ���������
            unsigned int sampleBuffers; // �������棬Ĭ����
            unsigned int samples;		// ��������������ݵı�������Ĭ����

            // ��������
            bool pbuffer;				// P-Buffer��Ĭ�ϲ�֧��
            bool quadBufferStereo;		// �����Ļ��棬Ĭ�ϲ�֧�֣���Ҫ�ڸ߶��Կ�����
            bool doubleBuffer;			// �Ƿ�֧��˫���棬Ĭ�ϲ�֧��

            // ��Ⱦ������render to texture
            GLenum          target;		// Ŀ��
            GLenum          format;		// ��ʽ
            unsigned int    level;		// Ƕ�׵Ĳ�Σ�Ĭ����
            unsigned int    face;		// ��
            unsigned int    mipMapGeneration; // �Ƿ�֧������Mipmap��Ĭ�ϲ�֧��
            
            // ��ֱͬ�� V-sync
            bool            vsync;		// �Ƿ�ֱͬ����Ĭ��ͬ��
            
            // Swap Group
            bool            swapGroupEnabled;
            GLuint          swapGroup;
            GLuint          swapBarrier;

            // �Ƿ�ʹ�ö��̵߳�OpenGL���� (��OS X)
            bool            useMultiThreadedOpenGLEngine; // �Ƿ�ʹ�ö��̵߳�OpenGL���棬Ĭ�ϲ�֧�� 
            
            // �Ƿ�ʹ�ù��
            bool            useCursor;	// �Ƿ�ʹ�ù�꣬Ĭ��ʹ��

            // settings used in set up of graphics context, only presently used by GL3 build of OSG.
            std::string     glContextVersion;
            unsigned int    glContextFlags;
            unsigned int    glContextProfileMask;
            
            
            // �����GC
            GraphicsContext* sharedContext;
            
            ref_ptr<CVBF_Referenced> inheritedWindowData;
            
            // ask the GraphicsWindow implementation to set the pixel format of an inherited window
            bool setInheritedWindowPixelFormat; // �Ƿ�̳�Window�е�λ��ʽ
            
            // X11 hint whether to override the window managers window size/position redirection
            bool overrideRedirect;

            void SetWindowName(const std::string& sName);

            DisplaySettings::SwapMethod swapMethod;
        };

        
        struct ScreenSettings 
		{
			// '0' ֵ����'unset'
            ScreenSettings() : 
		                    width(0), height(0), refreshRate(0), colorDepth(0)
            {
			}
            ScreenSettings(int width, int height, double refreshRate=0, unsigned int colorDepth=0) :
							width(width), height(height), refreshRate(refreshRate), colorDepth(colorDepth)
            {
			}

            int width;
            int height;
            double refreshRate;         ///< Screen refresh rate, in Hz.
            unsigned int colorDepth;    ///< RGB(A) color buffer depth.
        };

        typedef std::vector<ScreenSettings> ScreenSettingsList;



        /** �ص�������Windows/pbuffers�ľ���ʵ��Callback to be implemented to provide access to Windowing API's ability to create Windows/pbuffers.*/
        struct WindowingSystemInterface : public ::CVBF_Referenced
        {
            virtual unsigned int getNumScreens(const ScreenIdentifier& screenIdentifier = ScreenIdentifier()) = 0;

            virtual void getScreenSettings(const ScreenIdentifier& screenIdentifier, ScreenSettings & resolution) = 0;
            virtual bool setScreenSettings(const ScreenIdentifier& /*screenIdentifier*/, const ScreenSettings & /*resolution*/) { return false; }

            virtual void enumerateScreenSettings(const ScreenIdentifier& screenIdentifier, ScreenSettingsList & resolutionList) = 0;

            virtual GraphicsContext* createGraphicsContext(Traits* traits) = 0;
            
            virtual ~WindowingSystemInterface() {}


            /** ��ȡ/������Ļ�ֱ��ʣ�û��ʹ��ScreenResolution�ṹ�����ѷ�������Ϊ��������*/
            inline void getScreenResolution(const ScreenIdentifier& screenIdentifier, unsigned int& width, unsigned int& height)
            {
                ScreenSettings settings;
                getScreenSettings(screenIdentifier, settings);
                width = settings.width;
                height = settings.height;
            }

            inline bool setScreenResolution(const ScreenIdentifier& screenIdentifier, unsigned int width, unsigned int height)
            {
                return setScreenSettings(screenIdentifier, ScreenSettings(width, height));
            }


            /** �ѷ�������Ϊ�������� */
            inline bool setScreenRefreshRate(const ScreenIdentifier& screenIdentifier, double refreshRate)
            {
                ScreenSettings settings;
                getScreenSettings(screenIdentifier, settings);
                settings.refreshRate = refreshRate;
                return setScreenSettings(screenIdentifier, settings);
            }
        };
    
    






        /** Set the query the windowing system for screens and create graphics context - this functor should be supplied by the windows toolkit. */
        static void setWindowingSystemInterface(WindowingSystemInterface* wsInterface);
        static WindowingSystemInterface* getWindowingSystemInterface();
    


        /** Create a graphics context for a specified set of traits.*/
        static GraphicsContext* createGraphicsContext(Traits* traits);
        
        /** Create a contextID for a new graphics context, this contextID is used to set up the osg::State associate with context.
          * Automatically increments the usage count of the contextID to 1.*/
        static unsigned int createNewContextID();

        /** Get the current max ContextID.*/
        static unsigned int getMaxContextID();

        /** Increment the usage count associate with a contextID. The usage count specifies how many graphics contexts a specific contextID is shared between.*/
        static void incrementContextIDUsageCount(unsigned int contextID);

        /** Decrement the usage count associate with a contextID. Once the contextID goes to 0 the contextID is then free to be reused.*/
        static void decrementContextIDUsageCount(unsigned int contextID);
    
        typedef std::vector<GraphicsContext*> GraphicsContexts;
        
        /** Get all the registered graphics contexts.*/
        static GraphicsContexts getAllRegisteredGraphicsContexts();
        
        /** Get all the registered graphics contexts associated with a specific contextID.*/
        static GraphicsContexts getRegisteredGraphicsContexts(unsigned int contextID);
        
        /** Get the GraphicsContext for doing background compilation for GraphicsContexts associated with specified contextID.*/
        static void setCompileContext(unsigned int contextID, GraphicsContext* gc);

        /** Get existing or create a new GraphicsContext to do background compilation for GraphicsContexts associated with specified contextID.*/
        static  GraphicsContext* getOrCreateCompileContext(unsigned int contextID);
        
        /** Get the GraphicsContext for doing background compilation for GraphicsContexts associated with specified contextID.*/
        static GraphicsContext* getCompileContext(unsigned int contextID);

    public:
    
        /** Add operation to end of OperationQueue.*/
        void add(Operation* operation);
        
        /** Remove operation from OperationQueue.*/
        void remove(Operation* operation);

        /** Remove named operation from OperationQueue.*/
        void remove(const std::string& name);

        /** Remove all operations from OperationQueue.*/
        void removeAllOperations();

        /** Run the operations. */
        void runOperations();

        typedef std::list< ref_ptr<Operation> > GraphicsOperationQueue;
        
        /** Get the operations queue, not you must use the OperationsMutex when accessing the queue.*/
        GraphicsOperationQueue& getOperationsQueue() { return _operations; }

        /** Get the operations queue mutex.*/
        OpenThreads::Mutex* getOperationsMutex() { return &_operationsMutex; }

        /** Get the operations queue block used to mark an empty queue, if you end items into the empty queue you must release this block.*/
        osg::RefBlock* getOperationsBlock() { return _operationsBlock.get(); }

        /** Get the current operations that is being run.*/
        Operation* getCurrentOperation() { return _currentOperation.get(); }


    public:
    
        /** Get the traits of the GraphicsContext.*/
        inline const Traits* getTraits() const { return _traits.get(); }

        /** Return whether a valid and usable GraphicsContext has been created.*/
        virtual bool valid() const = 0;


        /** Set the State object which tracks the current OpenGL state for this graphics context.*/
        inline void setState(State* state) { _state = state; }
        
        /** Get the State object which tracks the current OpenGL state for this graphics context.*/
        inline State* getState() { return _state.get(); }
        
        /** Get the const State object which tracks the current OpenGL state for this graphics context.*/
        inline const State* getState() const { return _state.get(); }


		// ���û�ȡ��������ɫ��clear color��
        inline void setClearColor(const Vec4& color) { _clearColor = color; }
        inline const Vec4& getClearColor() const { return _clearColor; }
        
		// ����/��ȡClear Mark������glClear(..)
        /** Defaults to 0 - so no clear is done by default by the GraphicsContext, instead the Camera's attached the GraphicsContext will do the clear. 
          * GraphicsContext::setClearMask() is useful for when the Camera's Viewports don't conver the whole context, so the context will fill in the gaps. */
        inline void setClearMask(GLbitfield mask) { _clearMask = mask; }
        inline GLbitfield getClearMask() const { return _clearMask; }
        

        /** Do an OpenGL clear of the full graphics context/window.
          * Note, must only be called from a thread with this context current.*/
        virtual void clear();
        
        double getTimeSinceLastClear() const { return CVBF_Timer::instance()->delta_s(_lastClearTick, CVBF_Timer::instance()->tick()); }
        

        /** Realize the GraphicsContext.*/
        bool Realize();

        /** close the graphics context.
          * close(bool) stops any associated graphics threads, releases the contextID for the GraphicsContext then
          * optional calls closeImplementation() to do the actual deletion of the graphics.  This call is made optional
          * as there are times when the graphics context has already been deleted externally and only the OSG side
          * of the its data need to be closed down. */
        void close(bool callCloseImplementation=true);

        void swapBuffers(); // ����ǰ�󻺴�

        inline bool IsRealized() const { return isRealizedImplementation(); } // �Ƿ��ʼ��������


        /** Make this graphics context current.
          * Implemented by calling makeCurrentImplementation(). 
          * Returns true on success. */
        bool makeCurrent();
        
        /** Make this graphics context current with specified read context.
          * Implemented by calling makeContextCurrentImplementation().
          * Returns true on success. */
        bool makeContextCurrent(GraphicsContext* readContext);
        
        /** Release the graphics context.
          * Returns true on success. */
        bool releaseContext();
        
        /** Return true if the current thread has this OpenGL graphics context.*/
        inline bool isCurrent() const { return _threadOfLastMakeCurrent == OpenThreads::Thread::CurrentThread(); }

        /** Bind the graphics context to associated texture.*/
        inline void bindPBufferToTexture(GLenum buffer) { bindPBufferToTextureImplementation(buffer); }



        /** Create a graphics thread to the graphics context, so that the thread handles all OpenGL operations.*/
        void createGraphicsThread();

        /** Assign a graphics thread to the graphics context, so that the thread handles all OpenGL operations.*/
        void setGraphicsThread(GraphicsThread* gt);

        /** Get the graphics thread assigned the graphics context.*/
        GraphicsThread* getGraphicsThread() { return _graphicsThread.get(); }

        /** Get the const graphics thread assigned the graphics context.*/
        const GraphicsThread* getGraphicsThread() const { return _graphicsThread.get(); }


        /** Realize the GraphicsContext implementation, 
          * Pure virtual - must be implemented by concrete implementations of GraphicsContext. */
        virtual bool realizeImplementation() = 0;

        /** Return true if the graphics context has been realized, and is ready to use, implementation.
          * Pure virtual - must be implemented by concrete implementations of GraphicsContext. */
        virtual bool isRealizedImplementation() const = 0;

        /** Close the graphics context implementation.
          * Pure virtual - must be implemented by concrete implementations of GraphicsContext. */
        virtual void closeImplementation() = 0;

        /** Make this graphics context current implementation.
          * Pure virtual - must be implemented by concrete implementations of GraphicsContext. */
        virtual bool makeCurrentImplementation() = 0;
        
        /** Make this graphics context current with specified read context implementation.
          * Pure virtual - must be implemented by concrete implementations of GraphicsContext. */
        virtual bool makeContextCurrentImplementation(GraphicsContext* readContext) = 0;

        /** Release the graphics context implementation.*/
        virtual bool releaseContextImplementation() = 0;

        /** Pure virtual, Bind the graphics context to associated texture implementation.
          * Pure virtual - must be implemented by concrete implementations of GraphicsContext. */
        virtual void bindPBufferToTextureImplementation(GLenum buffer) = 0;

        struct SwapCallback : public ::CVBF_Referenced
        {
            virtual void swapBuffersImplementation(GraphicsContext* gc) = 0;
        };
        /** Set the swap callback which overrides the
          * GraphicsContext::swapBuffersImplementation(), allowing
          * developers to provide custom behavior for swap.
          * The callback must call
          * GraphicsContext::swapBuffersImplementation() */  
        void setSwapCallback(SwapCallback* rc) { _swapCallback = rc; }

        /** Get the swap callback which overrides the GraphicsContext::swapBuffersImplementation().*/
        SwapCallback* getSwapCallback() { return _swapCallback.get(); }

        /** Get the const swap callback which overrides the GraphicsContext::swapBuffersImplementation().*/
        const SwapCallback* getSwapCallback() const { return _swapCallback.get(); }

        /** convinience method for handling whether to call swapbuffers callback or the standard context swapBuffersImplementation.
          * swapBuffersCallbackOrImplemenation() is called by swapBuffers() and osg::SwapBuffersOperation, end users should normally
          * call swapBuffers() rather than swapBuffersCallbackOrImplemenation(). */
        void swapBuffersCallbackOrImplemenation()
        {
            if (_state.valid()) _state->frameCompleted();

            if (_swapCallback.valid()) _swapCallback->swapBuffersImplementation(this);
            else swapBuffersImplementation();
        }

        /** Swap the front and back buffers implementation.
          * Pure virtual - must be implemented by concrete implementations of GraphicsContext. */
        virtual void swapBuffersImplementation() = 0;



        /** resized method should be called when the underlying window has been resized and the GraphicsWindow and associated Cameras must
            be updated to keep in sync with the new size. */
        void resized(int x, int y, int width, int height)
        {
            if (_resizedCallback.valid()) _resizedCallback->resizedImplementation(this, x, y, width, height);
            else resizedImplementation(x, y, width, height);
        }

        struct ResizedCallback : public ::CVBF_Referenced
        {
            virtual void resizedImplementation(GraphicsContext* gc, int x, int y, int width, int height) = 0;
        };

        /** Set the resized callback which overrides the GraphicsConext::realizedImplementation(), allow developers to provide custom behavior
          * in response to a window being resized.*/
        void setResizedCallback(ResizedCallback* rc) { _resizedCallback = rc; }

        /** Get the resized callback which overrides the GraphicsConext::realizedImplementation().*/
        ResizedCallback* getResizedCallback() { return _resizedCallback.get(); }

        /** Get the const resized callback which overrides the GraphicsConext::realizedImplementation().*/
        const ResizedCallback* getResizedCallback() const { return _resizedCallback.get(); }

        /** resized implementation, by default resizes the viewports and aspect ratios the cameras associated with the graphics Window. */
        virtual void resizedImplementation(int x, int y, int width, int height);


        typedef std::list< osg::IVBF_Camera* > CVBF_CameraList;

        /** Get the the list of cameras associated with this graphics context.*/
        CVBF_CameraList& getCameras() { return _cameras; }
        const CVBF_CameraList& getCameras() const { return _cameras; }
        
        /** set the default FBO-id, this id will be used when the rendering-backend is finished with RTT FBOs */
        void setDefaultFboId(GLuint i) { _defaultFboId = i; }      
        GLuint getDefaultFboId() const { return _defaultFboId; }

    public:

        virtual bool isSameKindAs(const CVBF_Object* object) const { return dynamic_cast<const GraphicsContext*>(object)!=0; }
        virtual const char* libraryName() const { return "osg"; }
        virtual const char* className() const { return "GraphicsContext"; }

        void addCamera(osg::IVBF_Camera* camera);
        void removeCamera(osg::IVBF_Camera* camera);


    protected:
        
        GraphicsContext();
        GraphicsContext(const GraphicsContext&, const osg::CopyOp&);

        virtual ~GraphicsContext();

        virtual CVBF_Object* cloneType() const { return 0; }
        virtual CVBF_Object* clone(const CopyOp&) const { return 0; }

        /** Register a GraphicsContext.*/
        static void registerGraphicsContext(GraphicsContext* gc);

        /** Unregister a GraphicsContext.*/
        static void unregisterGraphicsContext(GraphicsContext* gc);


        
        CVBF_CameraList _cameras;

//        friend class osg::Camera;

        ref_ptr<Traits>         _traits;        
        ref_ptr<State>          _state;

        Vec4                    _clearColor;
        GLbitfield              _clearMask;

        OpenThreads::Thread*    _threadOfLastMakeCurrent;
        
        OpenThreads::Mutex                  _operationsMutex;
        ref_ptr<osg::RefBlock>         _operationsBlock;
        GraphicsOperationQueue              _operations;
        ref_ptr<Operation>             _currentOperation;

        ref_ptr<GraphicsThread>             _graphicsThread;
        
        ref_ptr<ResizedCallback>            _resizedCallback;
        ref_ptr<SwapCallback>               _swapCallback;
        
        CVBF_Timer_t                             _lastClearTick;
        
        GLuint                              _defaultFboId;
};


}

#endif
