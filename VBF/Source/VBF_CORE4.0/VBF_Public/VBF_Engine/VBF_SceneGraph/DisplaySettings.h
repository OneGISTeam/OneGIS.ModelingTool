#ifndef OSG_DisplaySettings
#define OSG_DisplaySettings 1

#include <VBF_Engine/VBF_SceneGraph/Export>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Base/ref_ptr>
#include <VBF_Base/VBF_ArgumentParser.h>
#include <string>

namespace osg {

// 显示设置：如果希望更改DisplaySettings中的显示设置，务必在执行视景器的realize函数之前，就是仿真循环开始之前。这一点也是要切记的。
class OSG_EXPORT DisplaySettings : public ::CVBF_Referenced
{
    public:
		// singleton模式
        static ref_ptr<DisplaySettings>& instance();
// IE可能错误
        DisplaySettings(): CVBF_Referenced(true)
        {
            setDefaults();
            readEnvironmentalVariables();
        }
        
        DisplaySettings(::ArgumentParser& arguments): CVBF_Referenced(true)
        {
            setDefaults();
            readEnvironmentalVariables();
            readCommandLine(arguments);
        }

        DisplaySettings(const DisplaySettings& vs);
        

        DisplaySettings& operator = (const DisplaySettings& vs);
 
        void setDisplaySettings(const DisplaySettings& vs);
        
        void merge(const DisplaySettings& vs);

        void setDefaults();
        
        /** read the environmental variables.*/
        void readEnvironmentalVariables();

        /** read the commandline arguments.*/
        void readCommandLine(::ArgumentParser& arguments);
        
        
        enum DisplayType // 显示器类型
        {
            MONITOR,				// 监视器
            POWERWALL,				// 威力墙
            REALITY_CENTER,			// 虚拟实境中心
            HEAD_MOUNTED_DISPLAY	// 头盔显示器
        };

        void setDisplayType(DisplayType type) { _displayType = type; }
        
        DisplayType getDisplayType() const { return _displayType; }


        void setStereo(bool on) { _stereo = on; }
        bool getStereo() const { return _stereo; }

        enum StereoMode //立体显示模式
        {
            QUAD_BUFFER,			// 四方体缓冲
            ANAGLYPHIC,				// 互补色
            HORIZONTAL_SPLIT,		// 水平分割
            VERTICAL_SPLIT,			// 垂直分割
            LEFT_EYE,				// 左眼用
            RIGHT_EYE,				// 右眼用
            HORIZONTAL_INTERLACE,	// 水平交错
            VERTICAL_INTERLACE,		// 垂直交错
            CHECKERBOARD			// 棋盘式交错，用于DLP显示器
        };
        
        void setStereoMode(StereoMode mode) { _stereoMode = mode; }
        StereoMode getStereoMode() const { return _stereoMode; }

        void setEyeSeparation(float eyeSeparation) { _eyeSeparation = eyeSeparation; }
        float getEyeSeparation() const { return _eyeSeparation; }

        enum SplitStereoHorizontalEyeMapping
        {
            LEFT_EYE_LEFT_VIEWPORT,	// 左眼渲染左视口
            LEFT_EYE_RIGHT_VIEWPORT // 左眼渲染右视口
        };
        
        void setSplitStereoHorizontalEyeMapping(SplitStereoHorizontalEyeMapping m) { _splitStereoHorizontalEyeMapping = m; }
        SplitStereoHorizontalEyeMapping getSplitStereoHorizontalEyeMapping() const { return _splitStereoHorizontalEyeMapping; }

        void setSplitStereoHorizontalSeparation(int s) { _splitStereoHorizontalSeparation = s; }
        int getSplitStereoHorizontalSeparation() const { return _splitStereoHorizontalSeparation; }

        enum SplitStereoVerticalEyeMapping
        {
            LEFT_EYE_TOP_VIEWPORT,   // 左眼渲染顶视口
            LEFT_EYE_BOTTOM_VIEWPORT // 左眼渲染底视口
        };

        void setSplitStereoVerticalEyeMapping(SplitStereoVerticalEyeMapping m) { _splitStereoVerticalEyeMapping = m; }
        SplitStereoVerticalEyeMapping getSplitStereoVerticalEyeMapping() const { return _splitStereoVerticalEyeMapping; }

        void setSplitStereoVerticalSeparation(int s) { _splitStereoVerticalSeparation = s; }
        int getSplitStereoVerticalSeparation() const { return _splitStereoVerticalSeparation; }

        void setSplitStereoAutoAdjustAspectRatio(bool flag) { _splitStereoAutoAdjustAspectRatio=flag; }
        bool getSplitStereoAutoAdjustAspectRatio() const { return _splitStereoAutoAdjustAspectRatio; }


        void setScreenWidth(float width) { _screenWidth = width; }
        float getScreenWidth() const { return _screenWidth; }

        void setScreenHeight(float height) { _screenHeight = height; }
        float getScreenHeight() const { return _screenHeight; }

        void setScreenDistance(float distance) { _screenDistance = distance; }
        float getScreenDistance() const { return _screenDistance; }



        void setDoubleBuffer(bool flag) { _doubleBuffer = flag; }
        bool getDoubleBuffer() const { return _doubleBuffer; }


        void setRGB(bool flag) { _RGB = flag; }
        bool getRGB() const { return _RGB; }


        void setDepthBuffer(bool flag) { _depthBuffer = flag; }
        bool getDepthBuffer() const { return _depthBuffer; }


        void setMinimumNumAlphaBits(unsigned int bits) { _minimumNumberAlphaBits = bits; }
        unsigned int getMinimumNumAlphaBits() const { return _minimumNumberAlphaBits; }
        bool getAlphaBuffer() const { return _minimumNumberAlphaBits!=0; }

        void setMinimumNumStencilBits(unsigned int bits) { _minimumNumberStencilBits = bits; }
        unsigned int getMinimumNumStencilBits() const { return _minimumNumberStencilBits; }
        bool getStencilBuffer() const { return _minimumNumberStencilBits!=0; }

        void setMinimumNumAccumBits(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);
        unsigned int getMinimumNumAccumRedBits() const { return _minimumNumberAccumRedBits; }
        unsigned int getMinimumNumAccumGreenBits() const { return _minimumNumberAccumGreenBits; }
        unsigned int getMinimumNumAccumBlueBits() const { return _minimumNumberAccumBlueBits; }
        unsigned int getMinimumNumAccumAlphaBits() const { return _minimumNumberAccumAlphaBits; }
        bool getAccumBuffer() const { return (_minimumNumberAccumRedBits+_minimumNumberAccumGreenBits+_minimumNumberAccumBlueBits+_minimumNumberAccumAlphaBits)!=0; }


        void setMaxNumberOfGraphicsContexts(unsigned int num);
        unsigned int getMaxNumberOfGraphicsContexts() const;

        void setNumMultiSamples(unsigned int samples) { _numMultiSamples = samples; }
        unsigned int getNumMultiSamples() const { return _numMultiSamples; }
        bool getMultiSamples() const { return _numMultiSamples!=0; }
        
        void setCompileContextsHint(bool useCompileContexts) { _compileContextsHint = useCompileContexts; }
        bool getCompileContextsHint() const { return _compileContextsHint; }
        
        void setSerializeDrawDispatch(bool serializeDrawDispatch) { _serializeDrawDispatch = serializeDrawDispatch; }
        bool getSerializeDrawDispatch() const { return _serializeDrawDispatch; }
        
        /** Set the hint for the total number of threads in the DatbasePager set up, inclusive of the number of http dedicated threads.*/
        void setNumOfDatabaseThreadsHint(unsigned int numThreads) { _numDatabaseThreadsHint = numThreads; }
        unsigned int getNumOfDatabaseThreadsHint() const { return _numDatabaseThreadsHint; }

        /** Set the hint for number of threads in the DatbasePager to dedicate to reading http requests.*/
        void setNumOfHttpDatabaseThreadsHint(unsigned int numThreads) { _numHttpDatabaseThreadsHint = numThreads; }
        unsigned int getNumOfHttpDatabaseThreadsHint() const { return _numHttpDatabaseThreadsHint; }
        
        void setApplication(const std::string& application) { _application = application; }
        const std::string& getApplication() { return _application; }


        void setMaxTexturePoolSize(unsigned int size) { _maxTexturePoolSize = size; }
        unsigned int getMaxTexturePoolSize() const { return _maxTexturePoolSize; }

        void setMaxBufferObjectPoolSize(unsigned int size) { _maxBufferObjectPoolSize = size; }
        unsigned int getMaxBufferObjectPoolSize() const { return _maxBufferObjectPoolSize; }

        /** 
         Methods used to set and get defaults for Cameras implicit buffer attachments. 
         For more info: See description of Camera::setImplicitBufferAttachment method 

         DisplaySettings implicit buffer attachment selection defaults to: DEPTH and COLOR 
         for both primary (Render) FBO and seconday Multisample (Resolve) FBO
         ie: IMPLICT_DEPTH_BUFFER_ATTACHMENT | IMPLICIT_COLOR_BUFFER_ATTACHMENT
        **/
        enum ImplicitBufferAttachment
        {
            IMPLICIT_DEPTH_BUFFER_ATTACHMENT = (1 << 0),
            IMPLICIT_STENCIL_BUFFER_ATTACHMENT = (1 << 1),
            IMPLICIT_COLOR_BUFFER_ATTACHMENT = (1 << 2),
            DEFAULT_IMPLICIT_BUFFER_ATTACHMENT = IMPLICIT_COLOR_BUFFER_ATTACHMENT | IMPLICIT_DEPTH_BUFFER_ATTACHMENT
        };

        typedef int ImplicitBufferAttachmentMask;

        void setImplicitBufferAttachmentMask(ImplicitBufferAttachmentMask renderMask = DisplaySettings::DEFAULT_IMPLICIT_BUFFER_ATTACHMENT, ImplicitBufferAttachmentMask resolveMask = DisplaySettings::DEFAULT_IMPLICIT_BUFFER_ATTACHMENT )
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

        /** Get mask selecting default implict buffer attachments for Cameras primary FBOs. */
        ImplicitBufferAttachmentMask getImplicitBufferAttachmentRenderMask() const {  return _implicitBufferAttachmentRenderMask; }

        /** Get mask selecting default implict buffer attachments for Cameras secondary MULTISAMPLE FBOs. */
        ImplicitBufferAttachmentMask getImplicitBufferAttachmentResolveMask() const { return _implicitBufferAttachmentResolveMask;}

        enum SwapMethod
        {
            SWAP_DEFAULT,   // Leave swap method at default returned by choose Pixel Format.
            SWAP_EXCHANGE,  // Flip front / back buffer. 
            SWAP_COPY,      // Copy back to front buffer. 
            SWAP_UNDEFINED  // Move back to front buffer leaving contents of back buffer undefined.
        };
        
        /** Select preferred swap method */
        void setSwapMethod( SwapMethod swapMethod ) { _swapMethod = swapMethod; }
        SwapMethod getSwapMethod( void ) { return _swapMethod; }

        /** Set the hint of which OpenGL version to attempt to create a graphics context for.*/
        void setGLContextVersion(const std::string& version) { _glContextVersion = version; }
        const std::string getGLContextVersion() const { return _glContextVersion; }

        /** Set the hint of the flags to use in when creating graphic contexts.*/
        void setGLContextFlags(unsigned int flags) { _glContextFlags = flags; }
        unsigned int getGLContextFlags() const { return _glContextFlags; }
        
        /** Set the hint of the profile mask to use in when creating graphic contexts.*/
        void setGLContextProfileMask(unsigned int mask) { _glContextProfileMask = mask; }
        unsigned int getGLContextProfileMask() const { return _glContextProfileMask; }

    protected:
    
        virtual ~DisplaySettings();


        DisplayType                     _displayType;	// 显示器类型，默认为MONITOR（监视器）
    
		bool                            _stereo;		// 是否立体显示
        StereoMode                      _stereoMode;	// 立体显示模式，默认为ANAGLYPHIC（互补色）
        float                           _eyeSeparation; // 双眼的物理距离，默认为0.05M
      	
		float                           _screenWidth;	// 屏幕的实际宽度和高度（物理值，单位米）
        float                           _screenHeight;
        float                           _screenDistance;// 人眼到屏幕的距离，默认为0.5

        SplitStereoHorizontalEyeMapping _splitStereoHorizontalEyeMapping; // 水平分割显示模式
        int                             _splitStereoHorizontalSeparation; // 左视口和右视口之间的距离（像素数），默认为0
 
		SplitStereoVerticalEyeMapping   _splitStereoVerticalEyeMapping;	  // 垂直分割显示模式
        int                             _splitStereoVerticalSeparation;	  // 顶视口和底视口之间的距离（像素数），默认为0
      
		bool                            _splitStereoAutoAdjustAspectRatio; //默认为true，用于屏幕分割之后对其宽高比进行补偿
    


        bool                            _doubleBuffer;
        bool                            _RGB;
        bool                            _depthBuffer;
        unsigned int                    _minimumNumberAlphaBits;
        unsigned int                    _minimumNumberStencilBits; // 模板缓存的最小位数
		unsigned int                    _minimumNumberAccumRedBits;
        unsigned int                    _minimumNumberAccumGreenBits;
        unsigned int                    _minimumNumberAccumBlueBits;
        unsigned int                    _minimumNumberAccumAlphaBits;

        unsigned int                    _maxNumOfGraphicsContexts; // 最多可用的GC图形设备上下文数目，默认为32个
        
        unsigned int                    _numMultiSamples; // 多重采样的子像素样本数，默认为0。如果显示卡支持的话，打开多重采样可以大幅改善反走样效果。
        
        bool                            _compileContextsHint;
        bool                            _serializeDrawDispatch;

        unsigned int                    _numDatabaseThreadsHint;
        unsigned int                    _numHttpDatabaseThreadsHint;
        
        std::string                     _application;

        unsigned int                    _maxTexturePoolSize;
        unsigned int                    _maxBufferObjectPoolSize;

        ImplicitBufferAttachmentMask    _implicitBufferAttachmentRenderMask;
        ImplicitBufferAttachmentMask    _implicitBufferAttachmentResolveMask;
        
        std::string                     _glContextVersion;
        unsigned int                    _glContextFlags;
        unsigned int                    _glContextProfileMask;

        SwapMethod                      _swapMethod;
};

}

# endif
