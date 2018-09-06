#ifndef VBF_EVENT_HANDLER_SCREEN_CAPTURE
#define VBF_EVENT_HANDLER_SCREEN_CAPTURE 1

#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>
#include <VBF_Display/VBF_Viewer/VBF_ViewerSimple.h>

namespace osgViewer {

// 截屏事件处理器，通过按键截屏
class OSGVIEWER_EXPORT ScreenCaptureHandler : public osgGA::GUIEventHandler
{
    public:
        // 抽象基类，用于抓屏时的具体操作
        class CaptureOperation : public ::CVBF_Referenced
        {
            public:
                virtual void operator()(const osg::Image& image, const unsigned int context_id) = 0;
        };

        // 把抓取内容写到文件的具体CaptureOperation类
        class OSGVIEWER_EXPORT WriteToFile : public CaptureOperation
        {
            public:
                enum SavePolicy
                {
                    OVERWRITE,
                    SEQUENTIAL_NUMBER
                    // ... any others?
                };

                WriteToFile(const std::string& filename, const std::string& extension, SavePolicy savePolicy = SEQUENTIAL_NUMBER);
                virtual void operator()(const osg::Image& image, const unsigned int context_id);

                void setSavePolicy(SavePolicy savePolicy) { _savePolicy = savePolicy; }
                SavePolicy getSavePolicy() const { return _savePolicy; }

            protected:

                WriteToFile& operator = (const WriteToFile&) { return *this; }

                const std::string _filename;
                const std::string _extension;

                SavePolicy _savePolicy;

                std::vector<unsigned int> _contextSaveCounter;
        };

        /** @param numFrames >0: capture that number of frames. <0: capture all frames, call stopCapture() to stop it. */
        ScreenCaptureHandler(CaptureOperation* defaultOperation = 0, int numFrames = 1);

        void setKeyEventTakeScreenShot(int key) { _keyEventTakeScreenShot = key; }
        int getKeyEventTakeScreenShot() const { return _keyEventTakeScreenShot; }

        void setKeyEventToggleContinuousCapture(int key) { _keyEventToggleContinuousCapture = key; }
        int getKeyEventToggleContinuousCapture() const { return _keyEventToggleContinuousCapture; }

        void setCaptureOperation(CaptureOperation* operation);
        CaptureOperation* getCaptureOperation() const;

        // aa will point to an CVBF_View, so we will take a screenshot
        // of that view's graphics contexts.
        virtual bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

        /** Capture the given viewer's views on the next frame. */
        virtual void captureNextFrame(CVBF_Viewer& viewer);

        /** Set the number of frames to capture.
            @param numFrames >0: capture that number of frames. <0: capture all frames, call stopCapture() to stop it. */
        void setFramesToCapture(int numFrames);

        /** Get the number of frames to capture. */
        int getFramesToCapture() const;

        void startCapture();
        void stopCapture();

        // 获取鼠标和键盘的用法
        virtual void GetUsage(ApplicationUsage& usage) const;

    protected:
        bool _startCapture;
        bool _stopCapture;

        int _keyEventTakeScreenShot;
        int _keyEventToggleContinuousCapture;
        // there could be a key to start taking screenshots every new frame

        ref_ptr<CaptureOperation>          _operation;
        ref_ptr<osg::Camera::DrawCallback> _callback;

        void addCallbackToViewer(CVBF_Viewer& viewer);
        void removeCallbackFromViewer(CVBF_Viewer& viewer);
        osg::IVBF_Camera* findAppropriateCameraForCallback(CVBF_Viewer& viewer);
};



}

#endif
