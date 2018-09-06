#ifndef OSGVIEWER_Viewer
#define OSGVIEWER_Viewer 1

#include <VBF_Base/VBF_ArgumentParser.h>
//#include <VBF_Display/VBF_Manipulator/VBF_EventVisitor.h>
//#include <VBF_Engine/VBF_SGUtil/UpdateVisitor>
//#include <VBF_Display/VBF_Viewer/VBF_GraphicsWindow.h>
#include <VBF_Display/VBF_Viewer/VBF_View.h>
#include <VBF_Display/VBF_Viewer/VBF_Viewer.h>

using namespace osgViewer;

// 单一视景器：单视图、单场景
class CVBF_ViewerSimple : public CVBF_Viewer
{
public:

	CVBF_ViewerSimple();
	CVBF_ViewerSimple(::ArgumentParser& arguments);
	CVBF_ViewerSimple(const CVBF_ViewerSimple& viewer, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
	virtual ~CVBF_ViewerSimple();

	META_Object(osgViewer,CVBF_ViewerSimple);

	/** 从传入的View中获取所有的设置、相机/子相机，到后View会被销毁  */
	virtual void take(osg::IVBF_ViewBrief& rhs);


	/** 设置/获取统计对象，用于统计帧相关的时间和场景图数据 */
	virtual void setViewerStats(CVBF_Stats* stats) { m_ipView->setStats(stats); }
	virtual CVBF_Stats* getViewerStats() { return m_ipView->getStats(); }
	virtual const CVBF_Stats* getViewerStats() const { return m_ipView->getStats(); }


	/** 从配置文件读取视景器的设置 */
	virtual bool readConfiguration(const std::string& filename);

	IVBF_View* GetView() { return m_ipView.get(); }
	const IVBF_View* GetView() const { return m_ipView.get(); }

	/** 是否已经执行了Realize操作，是否有窗口 */
	virtual bool IsRealized() const;
	/** 该操作会使对Viewer之前的设置都使之生效，并设置窗口和相关线程 */
	virtual void Realize();

	// 设置开始时钟（Tick）和参考时间
	virtual void setStartTick(CVBF_Timer_t tick);
	void setReferenceTime(double time=0.0);

	// 设置场景中的数据，为场景中渲染的实际数据
	virtual void setSceneData(osg::IVBF_SGNode* node);


	// 该函数的功能是以嵌入式窗口的形式来设置该Viewer的渲染面。返回指向嵌入式界面指针。嵌入到外部管理的窗口中
	virtual GraphicsWindowEmbedded* setUpViewerAsEmbeddedInWindow(int x, int y, int width, int height);


	// 获取时间（过去的），程序执行的时间
	virtual double GetElapsedTime();

	// 获取帧戳
	virtual ::CVBF_FrameStamp* getViewerFrameStamp() { return m_ipView->getFrameStamp(); }

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
	void setCameraWithFocus(osg::IVBF_Camera* camera) { _cameraWithFocus = camera; }
	osg::IVBF_Camera* getCameraWithFocus() { return _cameraWithFocus.get(); }
	const osg::IVBF_Camera* getCameraWithFocus() const { return _cameraWithFocus.get(); }

    // 设置/获取焦点视图
    IVBF_View* getViewWithFocus() { return m_ipView.get(); }
    const IVBF_View* getViewWithFocus() const { return m_ipView.get(); }


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


	// 5、与视图相关的内容，为了统一

	virtual void addView(IVBF_View* view) {}	// 添加视图
    virtual void removeView(IVBF_View* view) {}	// 移除视图
		
	virtual IVBF_View* getView(unsigned i=0) { return m_ipView.get(); }	// 获取视图
    virtual const IVBF_View* getView(unsigned i=0) const { return m_ipView.get(); } 
    virtual unsigned int getNumViews() const { return 1; } // 获取视图数量

protected:

	void constructorInit();

	virtual void viewerInit() { m_ipView->init(); }


	observer_ptr<osg::IVBF_Camera>  _cameraWithFocus; //焦点相机：鼠标移动（而非拖动）时进入相机视口范围、允许接收事件且"渲染目标实现方式"为FRAME_BUFFER       
	ref_ptr<CVBF_View>              m_ipView;         // 视图
};



#endif
