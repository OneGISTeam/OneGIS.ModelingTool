#ifndef OSGVIEWER_VIEWEREVENTHANDLERS
#define OSGVIEWER_VIEWEREVENTHANDLERS 1

#include <VBF_Engine/VBF_SceneGraph/AnimationPath.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>
#include <VBF_Display/VBF_Manipulator/VBF_ManipulatorAnimationPath.h>

#include <VBF_Display/VBF_Viewer/VBF_GraphicsWindow.h>
#include <VBF_Display/VBF_Viewer/IVBF_Viewer.h>

#include <VBF_Common/VBF_Utils/VBF_FStream.h>
#include <VBF_Engine/VBF_SGUtil/LineSegmentIntersector>
namespace osgViewer {




// 窗口大小事件处理器，可以在窗口和全屏之间切换
class OSGVIEWER_EXPORT WindowSizeHandler : public osgGA::GUIEventHandler
{
public:
        WindowSizeHandler();

        // 获取鼠标和键盘的用法
        virtual void GetUsage(ApplicationUsage &usage) const;

        void setKeyEventToggleFullscreen(int key) { _keyEventToggleFullscreen = key; }
        int getKeyEventToggleFullscreen() const { return _keyEventToggleFullscreen; }

        void setToggleFullscreen(bool flag) { _toggleFullscreen = flag; }
        bool getToggleFullscreen() const { return _toggleFullscreen; }

        void setKeyEventWindowedResolutionUp(int key) { _keyEventWindowedResolutionUp = key; }
        int getKeyEventWindowedResolutionUp() const { return _keyEventWindowedResolutionUp; }
        void setKeyEventWindowedResolutionDown(int key) { _keyEventWindowedResolutionDown = key; }
        int getKeyEventWindowedResolutionDown() const { return _keyEventWindowedResolutionUp; }

        void setChangeWindowedResolution(bool flag) { _changeWindowedResolution = flag; }
        bool getChangeWindowedResolution() const { return _changeWindowedResolution; }

        virtual bool handle(const osgGA::GUIEventAdapter &ea, ::IVBF_GUIActionAdapter &aa);

protected:

        void toggleFullscreen(osgViewer::GraphicsWindow *window);
        void changeWindowedResolution(osgViewer::GraphicsWindow *window, bool increase);

        unsigned int getNearestResolution(int screenWidth, int screenHeight, int width, int height) const;

        int                     _keyEventToggleFullscreen;
        bool                    _toggleFullscreen;

        int                     _keyEventWindowedResolutionUp;
        int                     _keyEventWindowedResolutionDown;
        bool                    _changeWindowedResolution;
        std::vector<osg::Vec2>  _resolutionList;
        int                     _currentResolutionIndex;
};

// 线程模型设置事件处理器
class OSGVIEWER_EXPORT ThreadingHandler : public osgGA::GUIEventHandler
{
public:

        ThreadingHandler();

        // 获取鼠标和键盘的用法
        virtual void GetUsage(ApplicationUsage &usage) const;

        void setKeyEventChangeThreadingModel(int key) { _keyEventChangeThreadingModel = key; }
        int getKeyEventChangeThreadingModel() const { return _keyEventChangeThreadingModel; }

        void setChangeThreadingModel(bool flag) { _changeThreadingModel = flag; }
        bool getChangeThreadingModel() const { return _changeThreadingModel; }

        void setKeyEventChangeEndBarrierPosition(int key) { _keyEventChangeEndBarrierPosition = key; }
        int getKeyEventChangeEndBarrierPosition() const { return _keyEventChangeEndBarrierPosition; }

        void setChangeEndBarrierPosition(bool flag) { _changeEndBarrierPosition = flag; }
        bool getChangeEndBarrierPosition() const { return _changeEndBarrierPosition; }

        bool handle(const osgGA::GUIEventAdapter &ea, ::IVBF_GUIActionAdapter &aa);

protected:

        int             _keyEventChangeThreadingModel;
        bool            _changeThreadingModel;

        int             _keyEventChangeEndBarrierPosition;
        bool            _changeEndBarrierPosition;

        CVBF_Timer_t    _tickOrLastKeyPress;
        bool            m_bDone;
};

/**
 * Event handler allowing the user to record the animation "path" of a camera. In it's current
 * implementation, this handler cannot guarantee the final view matrix is correct; it is
 * conceivable that the matrix may be one frame off. Eh--not a big deal! :)
 * TODO: Write the file as we go, not when it's all done.
 * TODO: Create an osgviewer on-screen indication that animation is taking place.
*/

// 动画记录事件处理器
class OSGVIEWER_EXPORT RecordCameraPathHandler : public osgGA::GUIEventHandler
{
public:

        RecordCameraPathHandler(const std::string &filename = "saved_animation.path", float fps = 25.0f);

        void setKeyEventToggleRecord(int key) { _keyEventToggleRecord = key; }
        int getKeyEventToggleRecord() const { return _keyEventToggleRecord; }

        void setKeyEventTogglePlayback(int key) { _keyEventTogglePlayback = key; }
        int getKeyEventTogglePlayback() const { return _keyEventTogglePlayback; }

        void setAutoIncrementFilename( bool autoinc = true ) { _autoinc = autoinc?0:-1; }

        virtual void GetUsage(ApplicationUsage &usage) const;

        bool handle(const osgGA::GUIEventAdapter &ea, ::IVBF_GUIActionAdapter &aa);

protected:

        std::string                                     _filename;
        int                                             _autoinc;
        CVBF_FStreamOut                                 _fout;

        int                                             _keyEventToggleRecord;
        int                                             _keyEventTogglePlayback;


        bool                                            _currentlyRecording;
        bool                                            _currentlyPlaying;
        double                                          _interval;
        double                                          _delta;
        CVBF_Timer_t                                    _animStartTime;
        CVBF_Timer_t                                    _lastFrameTime;
        ref_ptr<osg::AnimationPath>                _animPath;
        ref_ptr<osgGA::AnimationPathManipulator>   _animPathManipulator;
        ref_ptr<IVBF_CameraManipulator>          m_ipOldManipulator;
};


// LOD缩放事件处理器：增加/减少LOD的比例
class OSGVIEWER_EXPORT LODScaleHandler : public osgGA::GUIEventHandler
{
    public:

        LODScaleHandler();

        void setKeyEventIncreaseLODScale(int key) { _keyEventIncreaseLODScale = key; }
        int getKeyEventIncreaseLODScale() const { return _keyEventIncreaseLODScale; }

        void setKeyEventDecreaseLODScale(int key) { _keyEventDecreaseLODScale = key; }
        int getKeyEventDecreaseLODScale() const { return _keyEventDecreaseLODScale; }

        bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

        // 获取鼠标和键盘的用法
        virtual void GetUsage(ApplicationUsage& usage) const;

    protected:


        int _keyEventIncreaseLODScale;
        int _keyEventDecreaseLODScale;


};

// 切换处置同步
class OSGVIEWER_EXPORT ToggleSyncToVBlankHandler : public osgGA::GUIEventHandler
{
    public:
        ToggleSyncToVBlankHandler();

        void setKeyEventToggleSyncToVBlankHandler(int key) { _keyEventToggleSyncToVBlank = key; }
        int getKeyEventToggleSyncToVBlankHandler() const { return _keyEventToggleSyncToVBlank; }

        bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

        // 获取鼠标和键盘的用法
        virtual void GetUsage(ApplicationUsage& usage) const;
    protected:
        int _keyEventToggleSyncToVBlank;
};



/** InteractiveImage is an event handler that computes the mouse coordinates in an images coordinate frame
  * and then passes keyboard and mouse events to it.  This event handler is useful for vnc or browser
  * surfaces in the 3D scene.*/

class OSGVIEWER_EXPORT InteractiveImageHandler : public osgGA::GUIEventHandler, public osg::Drawable::CullCallback
{
public:

    // Constructor to use when the InteractiveImage is in the 3D scene (i.e. not in a fullscreen HUD overlay).
    InteractiveImageHandler(osg::Image* image);
    // Constructor to use when the InteractiveImage is in a fullscreen HUD overlay.
    InteractiveImageHandler(osg::Image* image, osg::Texture2D* texture, osg::IVBF_Camera* camera);

    META_Object(osgViewer, InteractiveImageHandler);

    virtual bool handle(const osgGA::GUIEventAdapter& ea,::IVBF_GUIActionAdapter& aa, osg::CVBF_Object*, osg::NodeVisitor* nv);
    virtual bool cull(osg::NodeVisitor* nv, osg::Drawable* drawable, osg::RenderInfo* renderInfo) const;
 

protected:

	friend class CVBF_InteractiveImageHandlerCullCallback;
    virtual ~InteractiveImageHandler() {}

    InteractiveImageHandler() {}

    InteractiveImageHandler(const InteractiveImageHandler&,const osg::CopyOp& = osg::CopyOp::SHALLOW_COPY):
 //       osg::CVBF_Object(), 
		osgGA::GUIEventHandler(), 
		osg::Drawable::CullCallback(), 
		_fullscreen(false) 
	{
	}

    bool mousePosition(CVBF_View* view, osg::NodeVisitor* nv, const osgGA::GUIEventAdapter& ea, int& x, int &y) const;
    bool computeIntersections(CVBF_View* view, float x,float y, const osg::CVBF_SGNodePath& nodePath, osgUtil::LineSegmentIntersector::Intersections& intersections,osg::IVBF_SGNode::NodeMask traversalMask = 0xffffffff) const;

    void resize(int width, int height);

    observer_ptr<osg::Image>   _image;
    observer_ptr<osg::Texture2D> _texture;

    bool                            _fullscreen;
    observer_ptr<osg::IVBF_Camera>  _camera;


};

}

#endif
