#ifndef OSGVIEWER_GRAPHICWINDOW
#define OSGVIEWER_GRAPHICWINDOW 1

#include <VBF_Engine/VBF_SceneGraph/GraphicsContext.h>
#include <VBF_Base/VBF_Notify.h>

#include <VBF_Display/VBF_Manipulator/VBF_EventQueue.h>
#include <VBF_Display/VBF_Manipulator/IVBF_GUIActionAdapter.h>

#include <VBF_Display/VBF_Viewer/Export>


class CVBF_View;

namespace osgViewer {

// 图形显示窗口，可以显示图形并接收窗口事件。继承自osg::GraphicsContext。
class OSGVIEWER_EXPORT GraphicsWindow : public osg::GraphicsContext, public ::IVBF_GUIActionAdapter
{
    public:

        GraphicsWindow() { _eventQueue = new osgGA::CVBF_EventQueue; _eventQueue->setGraphicsContext(this); }

        virtual bool isSameKindAs(const CVBF_Object* object) const { return dynamic_cast<const GraphicsWindow*>(object)!=0; }
        virtual const char* libraryName() const { return "osgViewer"; }
        virtual const char* className() const { return "GraphicsWindow"; }

		// 设置/获取事件队列
        void setEventQueue(osgGA::CVBF_EventQueue* eventQueue) { _eventQueue = eventQueue; }
        osgGA::CVBF_EventQueue* getEventQueue() { return _eventQueue.get(); }
        const osgGA::CVBF_EventQueue* getEventQueue() const { return _eventQueue.get(); }

        virtual void checkEvents() {}

        // 设置/获取窗口的位置和尺寸
        virtual void getWindowRectangle(int& x, int& y, int& width, int& height) { if (_traits.valid()) { x = _traits->x; y = _traits->y; width = _traits->width; height = _traits->height; }  }
       
		void setWindowRectangle(int x, int y, int width, int height)
        {
            if (setWindowRectangleImplementation(x ,y ,width, height) && _traits.valid())
            {
                resized(x,y,width,height);
            }
        }

        // setWindowRectangle的实现，被子类实现
        virtual bool setWindowRectangleImplementation(int /*x*/, int /*y*/, int /*width*/, int /*height*/) { osg::notify(osg::NOTICE)<<"GraphicsWindow::setWindowRectangleImplementation(..) not implemented."<<std::endl; return false; }

      
 
        // 设置是否需要窗口的装饰
        void setWindowDecoration(bool flag)
        {
            if (setWindowDecorationImplementation(flag) && _traits.valid())
            {
                _traits->windowDecoration = flag;
            }
        }

        /** implementation of setWindowDecoration, should be implemented by derived classes */
        virtual bool setWindowDecorationImplementation(bool /*flag*/) {  osg::notify(osg::NOTICE)<<"GraphicsWindow::setWindowDecorationImplementation(..) not implemented."<<std::endl; return false; }


        /** Set Window decoration.*/
        virtual bool getWindowDecoration() const { return _traits.valid() ? _traits->windowDecoration : false; }

        /** Get focus.*/
        virtual void grabFocus() { osg::notify(osg::NOTICE)<<"GraphicsWindow::grabFocus(..) not implemented."<<std::endl; }

        /** 把鼠标焦点转到当前窗口上 */
        virtual void grabFocusIfPointerInWindow() { osg::notify(osg::NOTICE)<<"GraphicsWindow::grabFocusIfPointerInWindow(..) not implemented."<<std::endl; }

        /** Raise the window to the top.*/
        virtual void raiseWindow() { osg::notify(osg::NOTICE)<<"GraphicsWindow::raiseWindow(..) not implemented."<<std::endl; }

        /** Mouse cursor types, the same ones already present with ancient glut ... */
        enum MouseCursor {
            InheritCursor,
            NoCursor,
            RightArrowCursor,
            LeftArrowCursor,
            InfoCursor,
            DestroyCursor,
            HelpCursor,
            CycleCursor,
            SprayCursor,
            WaitCursor,
            TextCursor,
            CrosshairCursor,
            HandCursor,
            UpDownCursor,
            LeftRightCursor,
            TopSideCursor,
            BottomSideCursor,
            LeftSideCursor,
            RightSideCursor,
            TopLeftCorner,
            TopRightCorner,
            BottomRightCorner,
            BottomLeftCorner
        };

        /** Set the name of the window */
        virtual void setWindowName(const std::string& /*name*/) { osg::notify(osg::NOTICE)<<"GraphicsWindow::setWindowName(..) not implemented."<<std::endl; }

        /** Return the name of the window */
        virtual std::string getWindowName() { return _traits.valid() ? _traits->windowName : ""; }

        /** Switch on/off the cursor.*/
        virtual void useCursor(bool cursorOn) { setCursor(cursorOn ? InheritCursor : NoCursor); }

        /** Set mouse cursor to a specific shape.*/
        virtual void setCursor(MouseCursor /*mouseCursor*/) { osg::notify(osg::NOTICE)<<"GraphicsWindow::setCursor(..) not implemented."<<std::endl; }

        /** Create a new mouse cursor from the usual bitmap data.*/
        //virtual MouseCursor createCursor(const char *data, const char *mask, unsigned w, unsigned h, unsigned hotx, unsigned hoty) { osg::notify(osg::NOTICE)<<"GraphicsWindow::createCursor(..) not implemented."<<std::endl; }

        // 设置垂直同步
        virtual void setSyncToVBlank(bool on)
        {
            osg::notify(osg::NOTICE) << "GraphicsWindow::setSyncToVBlank(" << on << ") not implemented." << std::endl;
        }

        bool getSyncToVBlank() const { return _traits.valid() ? _traits->vsync : true; }

        /** Set swap group. */
        virtual void setSwapGroup(bool on, GLuint group, GLuint barrier)
        {
            osg::notify(osg::NOTICE) << "GraphicsWindow::setSwapGroup(" << on << " " << group << " " << barrier << ") not implemented." << std::endl;
        }

        void getSwapGroup(bool& on, GLuint& group, GLuint& barrier) const { on = _traits->swapGroupEnabled; group = _traits->swapGroup; barrier = _traits->swapBarrier; }

    public:

 		// 是否有效（创建了一个可用的GC）
        virtual bool valid() const { osg::notify(osg::NOTICE)<<"GraphicsWindow::valid() not implemented."<<std::endl; return false; }

 		// Realize（需要在子类中实现）
        virtual bool realizeImplementation() { osg::notify(osg::NOTICE)<<"GraphicsWindow::realizeImplementation() not implemented."<<std::endl; return false; }

 		// 是否Realize
        virtual bool isRealizedImplementation() const  { osg::notify(osg::NOTICE)<<"GraphicsWindow::isRealizedImplementation() not implemented."<<std::endl; return false; }

  		// 关闭GC
        virtual void closeImplementation()  { osg::notify(osg::NOTICE)<<"GraphicsWindow::closeImplementation() not implemented."<<std::endl; }

		// 把窗口的GC设置为当前GC（需要在子类中实现）
        virtual bool makeCurrentImplementation()  { osg::notify(osg::NOTICE)<<"GraphicsWindow::makeCurrentImplementation() not implemented."<<std::endl; return false;}

        /** Make this graphics context current with specified read context implementation.
          * Pure virtual - must be implemented by concrete implementations of GraphicsContext. */
        virtual bool makeContextCurrentImplementation(GraphicsContext* /*readContext*/)  { osg::notify(osg::NOTICE)<<"GraphicsWindow::makeContextCurrentImplementation(..) not implemented."<<std::endl; return false;}

		// 释放GC的实现（需要在子类中实现）
        virtual bool releaseContextImplementation() {  osg::notify(osg::NOTICE)<<"GraphicsWindow::releaseContextImplementation(..) not implemented."<<std::endl; return false; }

 		// 把GC绑定到关联的纹理（需要在子类中实现）
        virtual void bindPBufferToTextureImplementation(GLenum /*buffer*/)  { osg::notify(osg::NOTICE)<<"GraphicsWindow::bindPBufferToTextureImplementation(..) not implemented."<<std::endl; }

 		// 交换前后缓存（需要在子类中实现）
        virtual void swapBuffersImplementation()  { osg::notify(osg::NOTICE)<<"GraphicsWindow:: swapBuffersImplementation() not implemented."<<std::endl; }

    public:

        typedef std::list<CVBF_View*> CVBF_ViewList;
	
		// 获取与该图形窗口关联的视口列表
         void GetViews(CVBF_ViewList& views);


		// 实现GUIActionAdapter接口
        virtual void requestRedraw();
        virtual void requestContinuousUpdate(bool /*needed*/=true) {}
        virtual void requestWarpPointer(float /*x*/,float /*y*/) {}


    protected:

        ref_ptr<osgGA::CVBF_EventQueue> _eventQueue;  // 事件队列

};


class GraphicsWindowEmbedded : public GraphicsWindow
{
public:

	GraphicsWindowEmbedded(osg::GraphicsContext::Traits* traits=0)
	{
		_traits = traits;

		init();

	}

	GraphicsWindowEmbedded(int x, int y, int width, int height)
	{
		_traits = new GraphicsContext::Traits;
		_traits->x = x;
		_traits->y = y;
		_traits->width = width;
		_traits->height = height;

		init();
	}

	virtual bool isSameKindAs(const CVBF_Object* object) const { return dynamic_cast<const GraphicsWindowEmbedded*>(object)!=0; }
	virtual const char* libraryName() const { return "osgViewer"; }
	virtual const char* className() const { return "GraphicsWindowEmbedded"; }

	void init()
	{
		if (valid())
		{
			setState( new osg::State );
			getState()->setGraphicsContext(this);

			if (_traits.valid() && _traits->sharedContext)
			{
				getState()->setContextID( _traits->sharedContext->getState()->getContextID() );
				incrementContextIDUsageCount( getState()->getContextID() );
			}
			else
			{
				getState()->setContextID( osg::GraphicsContext::createNewContextID() );
			}
		}
	}

	// dummy implementations, assume that graphics context is *always* current and valid.
	virtual bool valid() const { return true; }
	virtual bool realizeImplementation() { return true; }
	virtual bool isRealizedImplementation() const  { return true; }
	virtual void closeImplementation() {}
	virtual bool makeCurrentImplementation() { return true; }
	virtual bool releaseContextImplementation() { return true; }
	virtual void swapBuffersImplementation() {}
	virtual void grabFocus() {}
	virtual void grabFocusIfPointerInWindow() {}
	virtual void raiseWindow() {}
};


extern "C"
{
    typedef void (* CGraphicsWindowFunction) (void);
}

struct GraphicsWindowFunctionProxy
{
    GraphicsWindowFunctionProxy(CGraphicsWindowFunction function) { (function)(); }
};

#define USE_GRAPICSWINDOW_IMPLEMENTATION(ext) \
    extern "C" void graphicswindow_##ext(void); \
    static osgViewer::GraphicsWindowFunctionProxy graphicswindowproxy_##ext(graphicswindow_##ext);

#if defined(_WIN32)
    #define USE_GRAPHICSWINDOW()  USE_GRAPICSWINDOW_IMPLEMENTATION(Win32)
#elif defined(__APPLE__)
    #define USE_GRAPHICSWINDOW()  USE_GRAPICSWINDOW_IMPLEMENTATION(Carbon)
#else
    #define USE_GRAPHICSWINDOW()  USE_GRAPICSWINDOW_IMPLEMENTATION(X11)
#endif

}

#endif
