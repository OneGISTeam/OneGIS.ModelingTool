#ifndef OSGVIEWER_CompositeViewer
#define OSGVIEWER_CompositeViewer 1

#include <VBF_Base/VBF_ArgumentParser.h>
#include <VBF_Display/VBF_Viewer/VBF_Viewer.h>
#include <VBF_Display/VBF_Viewer/VBF_View.h>
using namespace osgViewer;

// 复合视景器：多视图、多场景
class CVBF_ViewerComposite : public CVBF_Viewer
{
    public:

        CVBF_ViewerComposite();
        CVBF_ViewerComposite(const CVBF_ViewerComposite&,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
        CVBF_ViewerComposite(::ArgumentParser& arguments);
		virtual ~CVBF_ViewerComposite();

        META_Object(osgViewer,CVBF_ViewerComposite);


        /** 设置/获取统计对象，用于统计帧相关的时间和场景图数据 */
        virtual void setViewerStats(CVBF_Stats* stats) { _stats = stats; }
        virtual CVBF_Stats* getViewerStats() { return _stats.get(); }
        virtual const CVBF_Stats* getViewerStats() const { return _stats.get(); }

         /** 从配置文件读取视景器的设置 */
        bool readConfiguration(const std::string& filename);

		// 添加/移除视图
        void addView(IVBF_View* view);
        void removeView(IVBF_View* view);
		
		// 获取视图及视图数量
        IVBF_View* getView(unsigned i=0) { return (IVBF_View*)(CVBF_ViewBrief*)_views[i].get(); }
        const IVBF_View* getView(unsigned i=0) const { return (IVBF_View*)(CVBF_ViewBrief*)_views[i].get(); }
        unsigned int getNumViews() const { return _views.size(); }



        /** 是否有窗口 */
        virtual bool IsRealized() const;
        /** 设置窗口和相关线程 */
        virtual void Realize();


		// 设置开始时钟（Tick）和参考时间
        virtual void setStartTick(CVBF_Timer_t tick);
        void setReferenceTime(double time=0.0);

		// 获取帧戳
        ::CVBF_FrameStamp* getFrameStamp() { return _frameStamp.get(); }
        const ::CVBF_FrameStamp* getFrameStamp() const { return _frameStamp.get(); }
        virtual ::CVBF_FrameStamp* getViewerFrameStamp() { return getFrameStamp(); }

		// 获取时间（过去的）
        virtual double GetElapsedTime();

 

        /** 主帧循环。等同于while (!viewer.IsDone()) viewer.frame(); 在循环前进行初始化工作 */
        virtual int run();

        /** 检测是否需要运行下一帧，与按需求运行ON_DEMAND相关 */
        virtual bool checkNeedToDoFrame();

		// 仿真时钟向前一帧
        virtual void advance(double simulationTime=USE_REFERENCE_TIME);

		// 事件响应
        virtual void eventTraversal();

		// 更新
        virtual void updateTraversal();

		// 设置/获取焦点相机
        void setCameraWithFocus(osg::IVBF_Camera* camera);
        osg::IVBF_Camera* getCameraWithFocus() { return _cameraWithFocus.get(); }
        const osg::IVBF_Camera* getCameraWithFocus() const { return _cameraWithFocus.get(); }

		// 设置/获取焦点视图
        IVBF_View* getViewWithFocus() { return _viewWithFocus.get(); }
        const IVBF_View* getViewWithFocus() const { return _viewWithFocus.get(); }

		// 获取所有相机
        virtual void getCameras(CVBF_Cameras& cameras, bool onlyActive=true);

		// 获取所有的GC
        virtual void GetContexts(CVBF_Contexts& contexts, bool onlyValid=true);

		// 获取所有的线程
        virtual void GetAllThreads(Threads& threads, bool onlyActive=true);

		// 获取操作线程
        virtual void GetOperationThreads(OperationThreads& threads, bool onlyActive=true);

		// 获取所有的场景数据
        virtual void getScenes(CVBF_Scenes& scenes, bool onlyValid=true);

		// 获取所有的视图
        virtual void GetViews(CVBF_Views& views, bool onlyValid=true);


        // 得到当前Viewer的命令行描述，鼠标和键盘的用法
        virtual void GetUsage(ApplicationUsage& usage) const;

    protected:

        void constructorInit();

        virtual void viewerInit();

        typedef std::vector< ref_ptr<CVBF_View> > RefViews;
        RefViews _views;

        bool m_bFirstFrame;                               // 是否第一帧

        ref_ptr<CVBF_Stats>            _stats;     // 统计工具

        CVBF_Timer_t                        _startTick; // 起始时钟
        ref_ptr< ::CVBF_FrameStamp >       _frameStamp;// 帧戳

        observer_ptr<osg::IVBF_Camera> _cameraWithFocus;  // 焦点相机
        observer_ptr<CVBF_View>        _viewWithFocus;    // 焦点视图

};



#endif
