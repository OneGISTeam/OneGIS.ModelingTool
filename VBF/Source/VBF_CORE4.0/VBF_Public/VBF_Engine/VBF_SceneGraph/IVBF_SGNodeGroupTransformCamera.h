#ifndef IVBF_SG_NODE_GROUP_TRANSFORM_CAMERA_H
#define IVBF_SG_NODE_GROUP_TRANSFORM_CAMERA_H 1

#include <VBF_Engine/VBF_SceneGraph/OperationThread>
#include <VBF_Engine/VBF_SceneGraph/GraphicsThread>

#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture.h>


#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrColorMask.h>
#include <VBF_Engine/VBF_SceneGraph/CullSettings>

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransform.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrViewport.h>

class CVBF_Stats;

namespace osg {

class IVBF_ViewBrief;
class RenderInfo;


class IVBF_Camera : public IVBF_SGNodeGroupTransform, public CullSettings
{
public:
	IVBF_Camera(){}
    IVBF_Camera(const IVBF_Camera& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroupTransform(cs,copyop),CullSettings(cs) {}

	explicit IVBF_Camera(bool threadSafeRefUnref):IVBF_SGNodeGroupTransform(threadSafeRefUnref){}

    // 设置/获取相机所属的视图
    virtual void setView(IVBF_ViewBrief* view)  =0;
    virtual IVBF_ViewBrief* getView() =0;
    virtual const IVBF_ViewBrief* getView() const =0;

    // 设置/获取统计对象，用于统计帧相关的时间和场景图数据
    virtual void setStats(::CVBF_Stats* stats) =0;
	virtual ::CVBF_Stats* getStats() =0;
	virtual const ::CVBF_Stats* getStats() const  =0;

    // 设置/获取是否允许接收事件
    virtual void setAllowEventFocus(bool focus) =0;
	virtual bool getAllowEventFocus() const =0;

    // 设置/获取显示设置DisplaySettings
    virtual void setDisplaySettings(osg::DisplaySettings* ds) =0;
    virtual osg::DisplaySettings* getDisplaySettings()  =0;
    virtual const osg::DisplaySettings* getDisplaySettings() const =0;

    // 设置/获取glClear()中使用的clear mask，默认为GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
	virtual void setClearMask(GLbitfield mask) =0;
	virtual GLbitfield getClearMask() const =0;

    // 设置/获取glClearColor中所用的颜色，仅当mask&GL_COLOR_BUFFER_BIT为真时有效
	virtual void setClearColor(const osg::Vec4& color)  =0;
	virtual const osg::Vec4& getClearColor() const  =0;

    // 设置/获取glClearAccum中所用的颜色，仅当mask&GL_ACCUM_BUFFER_BIT为真时有效
	virtual void setClearAccum(const osg::Vec4& color)  =0;
	virtual const osg::Vec4& getClearAccum() const =0;

    // 设置/获取glClearDepth所用的深度值，默认为1.0，仅当mask&GL_DEPTH_BUFFER_BIT为真时有效
	virtual void setClearDepth(double depth) =0;
	virtual double getClearDepth() const =0;

    // 设置/获取glClearStencil所用的模板值，仅当mask&GL_STENCIL_BUFFER_BIT为真时有效
	virtual void setClearStencil(int stencil) =0;
	virtual int getClearStencil() const =0;

    // 设置/获取color mask
	virtual void setColorMask(osg::ColorMask* colorMask) =0;
	virtual void setColorMask(bool red, bool green, bool blue, bool alpha) =0;
	virtual const ColorMask* getColorMask() const  =0;
	virtual ColorMask* getColorMask() =0;


    // 设置/获取视口信息
	virtual void setViewport(osg::Viewport* viewport) =0;
	virtual void setViewport(int x,int y,int width,int height) =0;
	virtual const Viewport* getViewport() const  =0;
	virtual Viewport* getViewport() =0;


    enum TransformOrder
    {
        PRE_MULTIPLY,   // 前乘
        POST_MULTIPLY   // 后乘
    };
    // 设置/获取世界坐标系与模型坐标系之间矩阵变换的顺序，
    virtual void setTransformOrder(TransformOrder order) =0;
    virtual TransformOrder getTransformOrder() const  =0;


	enum ProjectionResizePolicy
	{
        FIXED,      // 保持投影矩阵固定不变，不管窗口大小如何改变
        HORIZONTAL, // 当窗口大小改变时，调整视图的HORIZONTAL域
        VERTICAL    // 当窗口大小改变时，调整视图的VERTICAL域
	};
    // 设置/获取窗口大小改变时是否以及如何调整投影矩阵
	virtual void setProjectionResizePolicy(ProjectionResizePolicy policy) =0;
	virtual ProjectionResizePolicy getProjectionResizePolicy() const =0;


    // 设置投影矩阵，可认为是设置相机的镜头
    virtual  void setProjectionMatrix(const osg::Matrixf& matrix) =0;
    virtual  void setProjectionMatrix(const osg::Matrixd& matrix) =0;

    // 设置为一个正射投影，参见OpenGL glOrtho、glOrtho2D相关文档
    virtual void setProjectionMatrixAsOrtho(double left, double right, double bottom, double top, double zNear, double zFar)  =0;
    virtual void setProjectionMatrixAsOrtho2D(double left, double right, double bottom, double top) =0;

    // 设置为一个透视投影，参见OpenGL glFrustum相关文档
    virtual void setProjectionMatrixAsFrustum(double left, double right, double bottom, double top, double zNear, double zFar)  =0;

    // 设置为一个对称的透视投影，参见OpenGL gluPerspective相关文档。Aspect ratio 定义为width/height
    virtual void setProjectionMatrixAsPerspective(double fovy,double aspectRatio, double zNear, double zFar) =0;

    // 获取投影矩阵
    virtual osg::Matrixd& getProjectionMatrix() =0;
    virtual const osg::Matrixd& getProjectionMatrix() const =0;

    // 获取正射投影矩阵的参数。如果矩阵不是正射投影矩阵返回false，参数无效
    virtual bool getProjectionMatrixAsOrtho(double& left, double& right, double& bottom, double& top, double& zNear, double& zFar) const =0;

    // 获取透视投影矩阵的参数。如果矩阵不是透视投影矩阵返回false，参数无效
    virtual bool getProjectionMatrixAsFrustum(double& left, double& right, double& bottom, double& top, double& zNear, double& zFar) const =0;


    // 获取对称透视投影矩阵的参数。如果矩阵不是对称透视投影矩阵返回false，参数无效。
    // 注：如果矩阵不是对称透视投影矩阵，切变（shear）失效。非对称矩阵出现在stereo, power walls, caves and reality center display等处
    // 此时，应使用'getProjectionMatrixAsFrustum'
     virtual bool getProjectionMatrixAsPerspective(double& fovy,double& aspectRatio, double& zNear, double& zFar) const =0;

    // 设置视图矩阵，可认为是设置世界相对于相机的位置（在相机坐标系中）
    virtual void setViewMatrix(const osg::Matrixf& matrix) =0;
    virtual void setViewMatrix(const osg::Matrixd& matrix) =0;
    virtual osg::Matrixd& getViewMatrix() =0;
    virtual const osg::Matrixd& getViewMatrix() const =0;

    // 设置/获取视图矩阵的位置和朝向，参见gluLookAt
    virtual void setViewMatrixAsLookAt(const osg::Vec3d& eye,const osg::Vec3d& center,const osg::Vec3d& up)=0;
    virtual void getViewMatrixAsLookAt(osg::Vec3d& eye,osg::Vec3d& center,osg::Vec3d& up,double lookDistance=1.0) const=0;
    virtual void getViewMatrixAsLookAt(osg::Vec3f& eye,osg::Vec3f& center,osg::Vec3f& up,float lookDistance=1.0f) const=0;

    virtual Matrixd getInverseViewMatrix() const=0;

    enum RenderOrder
    {
        PRE_RENDER,
        NESTED_RENDER,
        POST_RENDER
    };
    // 设置/获取相机子图的渲染顺序，相机嵌套。渲染到纹理使用PRE_RENDER，渲染"屏显"使用POST_RENDER
    virtual void setRenderOrder(RenderOrder order, int orderNum = 0)=0;
    virtual RenderOrder getRenderOrder() const=0;
    virtual int getRenderOrderNum() const=0;

    // 是否为渲染到纹理相机，指定了一个纹理
    virtual bool isRenderToTextureCamera() const=0;

    enum RenderTargetImplementation
    {
        FRAME_BUFFER_OBJECT, // 帧缓存对象（Frame Buffer Object），可以用来实现离屏渲染，渲染结果不会体现在图形窗口中
        PIXEL_BUFFER_RTT,    // 纹理烘焙（Render To Texture，RTT）
        PIXEL_BUFFER,        // 像素缓存（Pixel Buffer）
        FRAME_BUFFER,        // 帧缓存（Frame Buffer），可以适用于较广泛的硬件平台上
        SEPERATE_WINDOW
    };

    // 设置/获取渲染目标实现方式
    virtual void setRenderTargetImplementation(RenderTargetImplementation impl)=0;
    virtual RenderTargetImplementation getRenderTargetImplementation() const=0;
	// 设置渲染目标实现方式，and fall-back that's used if the former isn't available
    virtual void setRenderTargetImplementation(RenderTargetImplementation impl, RenderTargetImplementation fallback)=0;
    // Get the render target fallback.
    virtual RenderTargetImplementation getRenderTargetFallback() const=0;


	// 设置/获取draw buffer，在每帧绘制开始时采用。GL_NONE表示选择最合适的buffer
    virtual void setDrawBuffer(GLenum buffer)=0;
    virtual GLenum getDrawBuffer() const=0;

	// 设置/获取read buffer，在每帧绘制开始时采用。GL_NONE表示选择最合适的buffer
    virtual void setReadBuffer(GLenum buffer)=0;
    virtual GLenum getReadBuffer() const =0;


	    enum BufferComponent
        {
            DEPTH_BUFFER,                       // 深度缓存（DEPTH_BUFFER）
            STENCIL_BUFFER,
            PACKED_DEPTH_STENCIL_BUFFER,
            COLOR_BUFFER,                       // 颜色缓存（COLOR_BUFFER）
            COLOR_BUFFER0,                      // OpenGL为多重渲染目标（MRT）的支持提供了多达十六个颜色缓存，0-15
            COLOR_BUFFER1 = COLOR_BUFFER0+1,
            COLOR_BUFFER2 = COLOR_BUFFER0+2,
            COLOR_BUFFER3 = COLOR_BUFFER0+3,
            COLOR_BUFFER4 = COLOR_BUFFER0+4,
            COLOR_BUFFER5 = COLOR_BUFFER0+5,
            COLOR_BUFFER6 = COLOR_BUFFER0+6,
            COLOR_BUFFER7 = COLOR_BUFFER0+7,
            COLOR_BUFFER8 = COLOR_BUFFER0+8,
            COLOR_BUFFER9 = COLOR_BUFFER0+9,
            COLOR_BUFFER10 = COLOR_BUFFER0+10,
            COLOR_BUFFER11 = COLOR_BUFFER0+11,
            COLOR_BUFFER12 = COLOR_BUFFER0+12,
            COLOR_BUFFER13 = COLOR_BUFFER0+13,
            COLOR_BUFFER14 = COLOR_BUFFER0+14,
            COLOR_BUFFER15 = COLOR_BUFFER0+15
        };

   

/*
	需要特别注意的是：如果希望使用 FBO来实现纹理烘焙或者场景截图的话，不可以将场景主摄像机的setRenderTargetImplementation直接设置为相应的枚举量，那样将无法正常
	地看到场景（因为主摄像机对应的渲染台已经将场景绘制的结果绑定到FBO 上了）。正确的作法是在场景树中增加一个Camera 节点，设置“渲染目标实现方式”为FBO 方式；并通
	过Camera::setRenderOrder 设定它的渲染顺序，设置为PRE_RENDER 可以保证这个摄像机在主场景之前执行绘制（它创建了一个“前序渲染台”，存入RenderStage::_preRenderList
	列表），从而实现“渲染到纹理”的效果。
	*/

        // 关联一个缓存（用指定的OpenGL内部格式）
        virtual void attach(BufferComponent buffer, GLenum internalFormat)=0;

        // 把一个纹理关联到指定的缓存。level控制关联纹理的MipMap级数
        // face控制Cube纹理的face或3D纹理的z level，mipMapGeneration控制是否为纹理生成MipMap
        virtual void attach(BufferComponent buffer, osg::Texture* texture, unsigned int level = 0, unsigned int face=0, bool mipMapGeneration=false,
            unsigned int multisampleSamples = 0, unsigned int multisampleColorSamples = 0)=0;

        // 把一个图像关联到指定的缓存。
        virtual void attach(BufferComponent buffer, osg::Image* image, unsigned int multisampleSamples = 0, unsigned int multisampleColorSamples = 0)=0;

        // 解除关联
        virtual void detach(BufferComponent buffer)=0;

        struct Attachment
        {
            Attachment(): _internalFormat(GL_NONE), _level(0), _face(0),
                _mipMapGeneration(false), _multisampleSamples(0), _multisampleColorSamples(0) {}

            int width() const
            {
                if (_texture.valid()) return _texture->getTextureWidth();
                if (_image.valid()) return _image->s();
                return 0;
            }

            int height() const
            {
                if (_texture.valid()) return _texture->getTextureHeight();
                if (_image.valid()) return _image->t();
                return 0;
            }

            int depth() const
            {
                if (_texture.valid()) return _texture->getTextureDepth();
                if (_image.valid()) return _image->r();
                return 0;
            }

            GLenum              _internalFormat;
            ref_ptr<Image>      _image;
            ref_ptr<Texture>    _texture;
            unsigned int        _level;
            unsigned int        _face;
            bool                _mipMapGeneration;
            unsigned int        _multisampleSamples;
            unsigned int        _multisampleColorSamples;
        };

        typedef std::map< BufferComponent, Attachment> BufferAttachmentMap;

        /** Get the BufferAttachmentMap, used to configure frame buffer objects, pbuffers and texture reads.*/
        virtual BufferAttachmentMap& getBufferAttachmentMap() =0;
        virtual const BufferAttachmentMap& getBufferAttachmentMap() const =0;


	enum ImplicitBufferAttachment
	{
		IMPLICIT_DEPTH_BUFFER_ATTACHMENT = DisplaySettings::IMPLICIT_DEPTH_BUFFER_ATTACHMENT,
		IMPLICIT_STENCIL_BUFFER_ATTACHMENT = DisplaySettings::IMPLICIT_STENCIL_BUFFER_ATTACHMENT,
		IMPLICIT_COLOR_BUFFER_ATTACHMENT = DisplaySettings::IMPLICIT_COLOR_BUFFER_ATTACHMENT,
		USE_DISPLAY_SETTINGS_MASK = (~0)
	};

	typedef int ImplicitBufferAttachmentMask;

	virtual void setImplicitBufferAttachmentMask(ImplicitBufferAttachmentMask renderMask = DisplaySettings::DEFAULT_IMPLICIT_BUFFER_ATTACHMENT, ImplicitBufferAttachmentMask resolveMask = DisplaySettings::DEFAULT_IMPLICIT_BUFFER_ATTACHMENT)=0;
	virtual void setImplicitBufferAttachmentRenderMask(ImplicitBufferAttachmentMask implicitBufferAttachmentRenderMask)=0;

	virtual void setImplicitBufferAttachmentResolveMask(ImplicitBufferAttachmentMask implicitBufferAttachmentResolveMask)=0;
	virtual ImplicitBufferAttachmentMask getImplicitBufferAttachmentRenderMask(bool effectiveMask = false) const=0;
	virtual ImplicitBufferAttachmentMask getImplicitBufferAttachmentResolveMask(bool effectiveMask = false) const=0;


    // 为该相机/指定创建一个操作（operation）线程
    virtual void createCameraThread()=0;
    virtual void setCameraThread(OperationThread* gt)=0;

    // 获取相机的操作线程
    virtual OperationThread* getCameraThread()=0;
    virtual const OperationThread* getCameraThread() const =0;

    // 设置/获取图形环境
    virtual void setGraphicsContext(GraphicsContext* context)=0;
    virtual GraphicsContext* getGraphicsContext()=0;
    virtual const GraphicsContext* getGraphicsContext() const=0;

    // 设置Rendering object，用于实现子图渲染
    virtual void setRenderer(osg::GraphicsOperation* rc)=0;
    virtual osg::GraphicsOperation* getRenderer()=0;
    virtual const osg::GraphicsOperation* getRenderer() const=0;
		
    /** Set the Rendering cache that is used for cached objects associated with rendering of subgraphs.*/
    virtual void setRenderingCache(osg::CVBF_Object* rc)=0;
    virtual osg::CVBF_Object* getRenderingCache()=0;
    virtual const osg::CVBF_Object* getRenderingCache() const =0;



    // 自定义的绘制回调
	struct OSG_EXPORT DrawCallback : virtual public CVBF_Object
	{
		DrawCallback() {}
		DrawCallback(const DrawCallback&,const CopyOp&) {}
		META_Object(osg, DrawCallback);

        // 渲染线程调用的方法，重载该函数可实现抓屏等操作
		virtual void operator () (osg::RenderInfo& renderInfo) const;
        // 同上，用于向后兼容
		virtual void operator () (const osg::IVBF_Camera& /*camera*/) const {}
	};

    // 设置/获取自定义的绘图初始化（initial draw），用于绘制相机的子树及每一个渲染台之前进行初始化。
	virtual void setInitialDrawCallback(DrawCallback* cb)  =0;
	virtual DrawCallback* getInitialDrawCallback() =0;
	virtual const DrawCallback* getInitialDrawCallback() const =0;

    // 设置渲染前回调，以便在渲染场景之前（此时需要的渲染台已经准备好）进行自定义的操作
    virtual void setPreDrawCallback(DrawCallback* cb) =0;
	virtual DrawCallback* getPreDrawCallback()  =0;
	virtual const DrawCallback* getPreDrawCallback() const  =0;

    // 设置渲染后回调，以便在绘制场景后（此时需要的渲染台已经准备好）进行自定义的操作
	virtual void setPostDrawCallback(DrawCallback* cb)  =0;
	virtual DrawCallback* getPostDrawCallback() =0;
	virtual const DrawCallback* getPostDrawCallback() const  =0;

    // 设置绘图最后的回调，此时与相机子图绘制有关的所有工作都做完了
	virtual void setFinalDrawCallback(DrawCallback* cb)  =0;
	virtual DrawCallback* getFinalDrawCallback()  =0;
	virtual const DrawCallback* getFinalDrawCallback() const =0;

	virtual OpenThreads::Mutex* getDataChangeMutex() const =0;

};

OSG_EXPORT osg::IVBF_Camera* VBF_CreateCamera() ;
OSG_EXPORT osg::IVBF_Camera* VBF_CreateCamera(const osg::IVBF_Camera& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;
}
#endif
