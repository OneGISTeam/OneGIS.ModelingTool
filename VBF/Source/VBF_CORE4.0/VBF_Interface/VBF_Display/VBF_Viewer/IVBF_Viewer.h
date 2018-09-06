#ifndef IVBF_VIEWER_H
#define IVBF_VIEWER_H 1

#include <VBF_Base/VBF_Stats.h>

#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Engine/VBF_SGUtil/IncrementalCompileOperation>
#include <VBF_Display/VBF_Viewer/VBF_GraphicsWindow.h>

class IVBF_View;
enum EVBF_ThreadingModel // 线程模型
{
    enumSingleThreaded,           // 单线程模型。不创建任何新线程来完成场景的筛选和渲染，也不对渲染效率的提高有任何助益。它适合任何配置下使用。
    enumCullDrawThreadPerContext, // 为每个GC创建图形线程，并分配到不同的CPU上，实现并行渲染。每帧结束前都会强制同步所有的线程。
    enumThreadPerContext = enumCullDrawThreadPerContext,
    enumDrawThreadPerContext,     // 为每个GC创建线程，并分配到不同的CPU上。这种模式会在当前帧的所有线程完成工作之前，开始下一帧。
    enumCullThreadPerCameraDrawThreadPerContext, // 为每个GC和每个像机创建线程，不会等待前一次的渲染结束，而是返回仿真循环并再
								                 // 次开始执行frame 函数。如果使用四核甚至更高的系统配置，那么使用这一线程模型将最大限度地发挥多CPU 的处理能力。
    enumThreadPerCamera = enumCullThreadPerCameraDrawThreadPerContext,
    enumAutomaticSelection
};
    
enum EVBF_EndBarrierPosition // "结束栅栏"的位置
{
    enumBeforeSwapBuffers, // 可能轻微的降低帧速率 ，但可保证窗口间的一致性。
    enumAfterSwapBuffers   // 可以轻微的提高帧速率， 但可能导致窗口之间不一致的Swap
};


typedef std::vector<IVBF_View*>						CVBF_Views;
typedef std::vector<osgViewer::GraphicsWindow*>		CVBF_Windows;
typedef std::vector<osg::GraphicsContext*>			CVBF_Contexts;
typedef std::vector<osg::IVBF_Camera*>				CVBF_Cameras;


#define USE_REFERENCE_TIME DBL_MAX

class IVBF_Viewer : virtual public osg::CVBF_Object
{
public:

	// 0、配置与初始化

	virtual bool readConfiguration(const std::string& filename) = 0; // 从配置文件读取数据配置视景器	
	virtual bool IsRealized() const = 0;// 是否有窗口
	virtual void Realize() = 0;// 设置窗口和相关线程


	// 1、与视图相关的内容

    virtual void addView(IVBF_View* pIView)=0;	// 添加视图
    virtual void removeView(IVBF_View* pIView)=0; // 移除视图
		
    virtual IVBF_View* getView(unsigned i=0) =0;	// 获取视图
    virtual const IVBF_View* getView(unsigned i=0) const =0; 
    virtual unsigned int getNumViews() const =0; // 获取视图数量


	// 2、与仿真循环相关的内容
	
	virtual int run()=0;  // 运行
	
	virtual void SetDone(bool done)=0; // 设置完成标志，以通知视景器的工作完成并将退出帧循环（frame loop）	
	virtual bool IsDone() const = 0;    // 是否完成并将退出出帧循环
    virtual bool IsPaused() = 0;
    virtual void SetPaused(bool bPaused) = 0;

	virtual void frame(double simulationTime=USE_REFERENCE_TIME)=0; // 运行一帧
	virtual void advance(double simulationTime=USE_REFERENCE_TIME) = 0; // 仿真时钟向前一帧
//	virtual void eventTraversal() = 0;      // 事件响应
//	virtual void updateTraversal() = 0;	    // 更新
//	virtual void renderingTraversals() =0;  // 渲染

	virtual bool checkNeedToDoFrame() = 0;	// 检测是否需要运行下一帧，与按需求运行ON_DEMAND相关

	virtual void setRunMaxFrameRate(double frameRate)=0;// 设置最大帧速率
	virtual double getRunMaxFrameRate() const=0;		// 获取最大帧速率


	enum FrameScheme // 帧运行方案
	{
		ON_DEMAND,   // 按需求运行
		CONTINUOUS   // 连续运行
	};

	// 设置/获取帧运行方案
	virtual void setRunFrameScheme(FrameScheme fs)=0;
	virtual FrameScheme getRunFrameScheme() const=0;



	// 3、线程相关的接口

    virtual void SetThreadingModel(EVBF_ThreadingModel threadingModel) =0;	// 设置线程模型
    virtual EVBF_ThreadingModel GetThreadingModel() const =0;				// 获取线程模型

	virtual bool areThreadsRunning() const =0; // 线程是否在运行
	virtual void StopThreading() =0;	// 停止视景器的所有线程	
	virtual void StartThreading() =0;	// 启动视景器的所有线程


	/**设置/获取增量编译操作，可避免加载大（多）模型时造成的帧率下降  */
	virtual void setIncrementalCompileOperation(osgUtil::IncrementalCompileOperation* ico)=0;
	virtual osgUtil::IncrementalCompileOperation* getIncrementalCompileOperation()=0;


	// 4、回调函数

	virtual void addUpdateOperation(osg::Operation* operation)=0;	// 添加1个更新处理器
	virtual void removeUpdateOperation(osg::Operation* operation)=0;// 移除1个更新处理器

	virtual void setUpdateOperations(osg::OperationQueue* operations)=0;// 设置多组更新处理器
	virtual osg::OperationQueue* getUpdateOperations()=0;				// 获取多组更新处理器
	virtual const osg::OperationQueue* getUpdateOperations() const=0;


	// 5、获取视图与场景数据
    	
    virtual IVBF_View* getViewWithFocus() = 0;// 获取焦点视图
    virtual const IVBF_View* getViewWithFocus() const = 0;

    virtual void GetViews(CVBF_Views& views, bool onlyValid=true) = 0;	// 获取所有的视图	
    virtual void GetWindows(CVBF_Windows& windows, bool onlyValid=true)=0;// 获取所有的窗口
	virtual void GetContexts(CVBF_Contexts& contexts, bool onlyValid=true) = 0;// 获取所有的GC	
	virtual CVBF_FrameStamp* getViewerFrameStamp() = 0; // 获取帧戳

	// 设置结束栅栏的位置
    virtual void SetEndBarrierPosition(EVBF_EndBarrierPosition bp)=0;
    virtual EVBF_EndBarrierPosition GetEndBarrierPosition() const =0;

	// 获取鼠标和键盘的用法
	virtual void GetUsage(ApplicationUsage& usage) const = 0;

    virtual bool IsFirstFrame() = 0;


	//!!! 以下内容考虑是否优化掉（我们可以在底层增加功能，给我们的用户不应该提供如此复杂的接口）
public:
	// 设置/获取统计对象，用于统计帧相关的时间和场景图数据
	virtual void setViewerStats(CVBF_Stats* stats) = 0;
	virtual CVBF_Stats* getViewerStats() = 0;
	virtual const CVBF_Stats* getViewerStats() const = 0;


	// 设置/获取场景预处理的自定义操作（场景预处理器）
	virtual void setRealizeOperation(osg::Operation* op) = 0;
	virtual osg::Operation* getRealizeOperation() = 0;

public:
    // 设置/获取自定义的退出键。默认键是Escape (osgGA::GUIEVentAdapter::KEY_Escape)。 设置0则关掉此特性
    virtual void setKeyEventSetsDone(int key)=0;
    virtual int getKeyEventSetsDone() const=0;

    // 设置/获取是否允许按下某个键（QUIT_APPLICATION）之后直接退出这种做法
    virtual void setQuitEventSetsDone(bool flag)=0;
    virtual bool getQuitEventSetsDone() const=0;
    virtual void setStartTick(CVBF_Timer_t tick)=0;


};

enum EVBF_VIEWER_TYPE
{
	EVBF_VIEWER_TYPE_SIMPLE    = 1,	// 单视图视景器
	EVBF_VIEWER_TYPE_COMPOSITE = 2	// 多视图视景器
};

OSGVIEWER_EXPORT IVBF_Viewer* VBF_CreateViewer(EVBF_VIEWER_TYPE type);
OSGVIEWER_EXPORT IVBF_Viewer* VBF_CreateViewer(EVBF_VIEWER_TYPE type,ArgumentParser& arguments);



#endif
