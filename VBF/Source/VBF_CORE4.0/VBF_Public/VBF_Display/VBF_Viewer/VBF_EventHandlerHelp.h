#ifndef VBF_EVENT_HANDLER_HELP
#define VBF_EVENT_HANDLER_HELP 1


#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>
#include <VBF_Display/VBF_Viewer/IVBF_Viewer.h>


namespace osgViewer {

/** 帮助事件处理器：按下帮助键（'h'，可重新设置），弹出屏幕帮助 */
class OSGVIEWER_EXPORT HelpHandler : public osgGA::GUIEventHandler
{
    public:

        HelpHandler(ApplicationUsage* au=0);

        void setApplicationUsage(ApplicationUsage* au) { _applicationUsage = au; }
        ApplicationUsage* getApplicationUsage() { return _applicationUsage.get(); }
        const ApplicationUsage* getApplicationUsage() const { return _applicationUsage.get(); }

		// 
        void setKeyEventTogglesOnScreenHelp(int key) { _keyEventTogglesOnScreenHelp = key; }
        int getKeyEventTogglesOnScreenHelp() const { return _keyEventTogglesOnScreenHelp; }

        void reset();

        osg::IVBF_Camera* getCamera() { return _camera.get(); }
        const osg::IVBF_Camera* getCamera() const { return _camera.get(); }

        bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

        // 获取鼠标和键盘的用法
        virtual void GetUsage(ApplicationUsage& usage) const;

    protected:

        void setUpHUDCamera(IVBF_Viewer* pIViewer);

        void setUpScene(IVBF_Viewer* pIViewer);

        ref_ptr<ApplicationUsage> _applicationUsage;

        int                                 _keyEventTogglesOnScreenHelp;

        bool                                _helpEnabled;

        bool                                _initialized;
        ref_ptr<osg::IVBF_Camera>           _camera;
        ref_ptr<osg::IVBF_SGNodeGroupSwitch>           _switch;

};


}

#endif
