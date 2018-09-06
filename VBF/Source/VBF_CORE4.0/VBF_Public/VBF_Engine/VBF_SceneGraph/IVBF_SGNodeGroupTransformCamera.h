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

    // ����/��ȡ�����������ͼ
    virtual void setView(IVBF_ViewBrief* view)  =0;
    virtual IVBF_ViewBrief* getView() =0;
    virtual const IVBF_ViewBrief* getView() const =0;

    // ����/��ȡͳ�ƶ�������ͳ��֡��ص�ʱ��ͳ���ͼ����
    virtual void setStats(::CVBF_Stats* stats) =0;
	virtual ::CVBF_Stats* getStats() =0;
	virtual const ::CVBF_Stats* getStats() const  =0;

    // ����/��ȡ�Ƿ���������¼�
    virtual void setAllowEventFocus(bool focus) =0;
	virtual bool getAllowEventFocus() const =0;

    // ����/��ȡ��ʾ����DisplaySettings
    virtual void setDisplaySettings(osg::DisplaySettings* ds) =0;
    virtual osg::DisplaySettings* getDisplaySettings()  =0;
    virtual const osg::DisplaySettings* getDisplaySettings() const =0;

    // ����/��ȡglClear()��ʹ�õ�clear mask��Ĭ��ΪGL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
	virtual void setClearMask(GLbitfield mask) =0;
	virtual GLbitfield getClearMask() const =0;

    // ����/��ȡglClearColor�����õ���ɫ������mask&GL_COLOR_BUFFER_BITΪ��ʱ��Ч
	virtual void setClearColor(const osg::Vec4& color)  =0;
	virtual const osg::Vec4& getClearColor() const  =0;

    // ����/��ȡglClearAccum�����õ���ɫ������mask&GL_ACCUM_BUFFER_BITΪ��ʱ��Ч
	virtual void setClearAccum(const osg::Vec4& color)  =0;
	virtual const osg::Vec4& getClearAccum() const =0;

    // ����/��ȡglClearDepth���õ����ֵ��Ĭ��Ϊ1.0������mask&GL_DEPTH_BUFFER_BITΪ��ʱ��Ч
	virtual void setClearDepth(double depth) =0;
	virtual double getClearDepth() const =0;

    // ����/��ȡglClearStencil���õ�ģ��ֵ������mask&GL_STENCIL_BUFFER_BITΪ��ʱ��Ч
	virtual void setClearStencil(int stencil) =0;
	virtual int getClearStencil() const =0;

    // ����/��ȡcolor mask
	virtual void setColorMask(osg::ColorMask* colorMask) =0;
	virtual void setColorMask(bool red, bool green, bool blue, bool alpha) =0;
	virtual const ColorMask* getColorMask() const  =0;
	virtual ColorMask* getColorMask() =0;


    // ����/��ȡ�ӿ���Ϣ
	virtual void setViewport(osg::Viewport* viewport) =0;
	virtual void setViewport(int x,int y,int width,int height) =0;
	virtual const Viewport* getViewport() const  =0;
	virtual Viewport* getViewport() =0;


    enum TransformOrder
    {
        PRE_MULTIPLY,   // ǰ��
        POST_MULTIPLY   // ���
    };
    // ����/��ȡ��������ϵ��ģ������ϵ֮�����任��˳��
    virtual void setTransformOrder(TransformOrder order) =0;
    virtual TransformOrder getTransformOrder() const  =0;


	enum ProjectionResizePolicy
	{
        FIXED,      // ����ͶӰ����̶����䣬���ܴ��ڴ�С��θı�
        HORIZONTAL, // �����ڴ�С�ı�ʱ��������ͼ��HORIZONTAL��
        VERTICAL    // �����ڴ�С�ı�ʱ��������ͼ��VERTICAL��
	};
    // ����/��ȡ���ڴ�С�ı�ʱ�Ƿ��Լ���ε���ͶӰ����
	virtual void setProjectionResizePolicy(ProjectionResizePolicy policy) =0;
	virtual ProjectionResizePolicy getProjectionResizePolicy() const =0;


    // ����ͶӰ���󣬿���Ϊ����������ľ�ͷ
    virtual  void setProjectionMatrix(const osg::Matrixf& matrix) =0;
    virtual  void setProjectionMatrix(const osg::Matrixd& matrix) =0;

    // ����Ϊһ������ͶӰ���μ�OpenGL glOrtho��glOrtho2D����ĵ�
    virtual void setProjectionMatrixAsOrtho(double left, double right, double bottom, double top, double zNear, double zFar)  =0;
    virtual void setProjectionMatrixAsOrtho2D(double left, double right, double bottom, double top) =0;

    // ����Ϊһ��͸��ͶӰ���μ�OpenGL glFrustum����ĵ�
    virtual void setProjectionMatrixAsFrustum(double left, double right, double bottom, double top, double zNear, double zFar)  =0;

    // ����Ϊһ���ԳƵ�͸��ͶӰ���μ�OpenGL gluPerspective����ĵ���Aspect ratio ����Ϊwidth/height
    virtual void setProjectionMatrixAsPerspective(double fovy,double aspectRatio, double zNear, double zFar) =0;

    // ��ȡͶӰ����
    virtual osg::Matrixd& getProjectionMatrix() =0;
    virtual const osg::Matrixd& getProjectionMatrix() const =0;

    // ��ȡ����ͶӰ����Ĳ������������������ͶӰ���󷵻�false��������Ч
    virtual bool getProjectionMatrixAsOrtho(double& left, double& right, double& bottom, double& top, double& zNear, double& zFar) const =0;

    // ��ȡ͸��ͶӰ����Ĳ��������������͸��ͶӰ���󷵻�false��������Ч
    virtual bool getProjectionMatrixAsFrustum(double& left, double& right, double& bottom, double& top, double& zNear, double& zFar) const =0;


    // ��ȡ�Գ�͸��ͶӰ����Ĳ�������������ǶԳ�͸��ͶӰ���󷵻�false��������Ч��
    // ע����������ǶԳ�͸��ͶӰ�����б䣨shear��ʧЧ���ǶԳƾ��������stereo, power walls, caves and reality center display�ȴ�
    // ��ʱ��Ӧʹ��'getProjectionMatrixAsFrustum'
     virtual bool getProjectionMatrixAsPerspective(double& fovy,double& aspectRatio, double& zNear, double& zFar) const =0;

    // ������ͼ���󣬿���Ϊ��������������������λ�ã����������ϵ�У�
    virtual void setViewMatrix(const osg::Matrixf& matrix) =0;
    virtual void setViewMatrix(const osg::Matrixd& matrix) =0;
    virtual osg::Matrixd& getViewMatrix() =0;
    virtual const osg::Matrixd& getViewMatrix() const =0;

    // ����/��ȡ��ͼ�����λ�úͳ��򣬲μ�gluLookAt
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
    // ����/��ȡ�����ͼ����Ⱦ˳�����Ƕ�ס���Ⱦ������ʹ��PRE_RENDER����Ⱦ"����"ʹ��POST_RENDER
    virtual void setRenderOrder(RenderOrder order, int orderNum = 0)=0;
    virtual RenderOrder getRenderOrder() const=0;
    virtual int getRenderOrderNum() const=0;

    // �Ƿ�Ϊ��Ⱦ�����������ָ����һ������
    virtual bool isRenderToTextureCamera() const=0;

    enum RenderTargetImplementation
    {
        FRAME_BUFFER_OBJECT, // ֡�������Frame Buffer Object������������ʵ��������Ⱦ����Ⱦ�������������ͼ�δ�����
        PIXEL_BUFFER_RTT,    // ����決��Render To Texture��RTT��
        PIXEL_BUFFER,        // ���ػ��棨Pixel Buffer��
        FRAME_BUFFER,        // ֡���棨Frame Buffer�������������ڽϹ㷺��Ӳ��ƽ̨��
        SEPERATE_WINDOW
    };

    // ����/��ȡ��ȾĿ��ʵ�ַ�ʽ
    virtual void setRenderTargetImplementation(RenderTargetImplementation impl)=0;
    virtual RenderTargetImplementation getRenderTargetImplementation() const=0;
	// ������ȾĿ��ʵ�ַ�ʽ��and fall-back that's used if the former isn't available
    virtual void setRenderTargetImplementation(RenderTargetImplementation impl, RenderTargetImplementation fallback)=0;
    // Get the render target fallback.
    virtual RenderTargetImplementation getRenderTargetFallback() const=0;


	// ����/��ȡdraw buffer����ÿ֡���ƿ�ʼʱ���á�GL_NONE��ʾѡ������ʵ�buffer
    virtual void setDrawBuffer(GLenum buffer)=0;
    virtual GLenum getDrawBuffer() const=0;

	// ����/��ȡread buffer����ÿ֡���ƿ�ʼʱ���á�GL_NONE��ʾѡ������ʵ�buffer
    virtual void setReadBuffer(GLenum buffer)=0;
    virtual GLenum getReadBuffer() const =0;


	    enum BufferComponent
        {
            DEPTH_BUFFER,                       // ��Ȼ��棨DEPTH_BUFFER��
            STENCIL_BUFFER,
            PACKED_DEPTH_STENCIL_BUFFER,
            COLOR_BUFFER,                       // ��ɫ���棨COLOR_BUFFER��
            COLOR_BUFFER0,                      // OpenGLΪ������ȾĿ�꣨MRT����֧���ṩ�˶��ʮ������ɫ���棬0-15
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
	��Ҫ�ر�ע����ǣ����ϣ��ʹ�� FBO��ʵ������決���߳�����ͼ�Ļ��������Խ��������������setRenderTargetImplementationֱ������Ϊ��Ӧ��ö�������������޷�����
	�ؿ�����������Ϊ���������Ӧ����Ⱦ̨�Ѿ����������ƵĽ���󶨵�FBO ���ˣ�����ȷ���������ڳ�����������һ��Camera �ڵ㣬���á���ȾĿ��ʵ�ַ�ʽ��ΪFBO ��ʽ����ͨ
	��Camera::setRenderOrder �趨������Ⱦ˳������ΪPRE_RENDER ���Ա�֤����������������֮ǰִ�л��ƣ���������һ����ǰ����Ⱦ̨��������RenderStage::_preRenderList
	�б����Ӷ�ʵ�֡���Ⱦ��������Ч����
	*/

        // ����һ�����棨��ָ����OpenGL�ڲ���ʽ��
        virtual void attach(BufferComponent buffer, GLenum internalFormat)=0;

        // ��һ�����������ָ���Ļ��档level���ƹ��������MipMap����
        // face����Cube�����face��3D�����z level��mipMapGeneration�����Ƿ�Ϊ��������MipMap
        virtual void attach(BufferComponent buffer, osg::Texture* texture, unsigned int level = 0, unsigned int face=0, bool mipMapGeneration=false,
            unsigned int multisampleSamples = 0, unsigned int multisampleColorSamples = 0)=0;

        // ��һ��ͼ�������ָ���Ļ��档
        virtual void attach(BufferComponent buffer, osg::Image* image, unsigned int multisampleSamples = 0, unsigned int multisampleColorSamples = 0)=0;

        // �������
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


    // Ϊ�����/ָ������һ��������operation���߳�
    virtual void createCameraThread()=0;
    virtual void setCameraThread(OperationThread* gt)=0;

    // ��ȡ����Ĳ����߳�
    virtual OperationThread* getCameraThread()=0;
    virtual const OperationThread* getCameraThread() const =0;

    // ����/��ȡͼ�λ���
    virtual void setGraphicsContext(GraphicsContext* context)=0;
    virtual GraphicsContext* getGraphicsContext()=0;
    virtual const GraphicsContext* getGraphicsContext() const=0;

    // ����Rendering object������ʵ����ͼ��Ⱦ
    virtual void setRenderer(osg::GraphicsOperation* rc)=0;
    virtual osg::GraphicsOperation* getRenderer()=0;
    virtual const osg::GraphicsOperation* getRenderer() const=0;
		
    /** Set the Rendering cache that is used for cached objects associated with rendering of subgraphs.*/
    virtual void setRenderingCache(osg::CVBF_Object* rc)=0;
    virtual osg::CVBF_Object* getRenderingCache()=0;
    virtual const osg::CVBF_Object* getRenderingCache() const =0;



    // �Զ���Ļ��ƻص�
	struct OSG_EXPORT DrawCallback : virtual public CVBF_Object
	{
		DrawCallback() {}
		DrawCallback(const DrawCallback&,const CopyOp&) {}
		META_Object(osg, DrawCallback);

        // ��Ⱦ�̵߳��õķ��������ظú�����ʵ��ץ���Ȳ���
		virtual void operator () (osg::RenderInfo& renderInfo) const;
        // ͬ�ϣ�����������
		virtual void operator () (const osg::IVBF_Camera& /*camera*/) const {}
	};

    // ����/��ȡ�Զ���Ļ�ͼ��ʼ����initial draw�������ڻ��������������ÿһ����Ⱦ̨֮ǰ���г�ʼ����
	virtual void setInitialDrawCallback(DrawCallback* cb)  =0;
	virtual DrawCallback* getInitialDrawCallback() =0;
	virtual const DrawCallback* getInitialDrawCallback() const =0;

    // ������Ⱦǰ�ص����Ա�����Ⱦ����֮ǰ����ʱ��Ҫ����Ⱦ̨�Ѿ�׼���ã������Զ���Ĳ���
    virtual void setPreDrawCallback(DrawCallback* cb) =0;
	virtual DrawCallback* getPreDrawCallback()  =0;
	virtual const DrawCallback* getPreDrawCallback() const  =0;

    // ������Ⱦ��ص����Ա��ڻ��Ƴ����󣨴�ʱ��Ҫ����Ⱦ̨�Ѿ�׼���ã������Զ���Ĳ���
	virtual void setPostDrawCallback(DrawCallback* cb)  =0;
	virtual DrawCallback* getPostDrawCallback() =0;
	virtual const DrawCallback* getPostDrawCallback() const  =0;

    // ���û�ͼ���Ļص�����ʱ�������ͼ�����йص����й�����������
	virtual void setFinalDrawCallback(DrawCallback* cb)  =0;
	virtual DrawCallback* getFinalDrawCallback()  =0;
	virtual const DrawCallback* getFinalDrawCallback() const =0;

	virtual OpenThreads::Mutex* getDataChangeMutex() const =0;

};

OSG_EXPORT osg::IVBF_Camera* VBF_CreateCamera() ;
OSG_EXPORT osg::IVBF_Camera* VBF_CreateCamera(const osg::IVBF_Camera& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;
}
#endif
