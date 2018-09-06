#ifndef OSGVIEWER_VIEWERBASE
#define OSGVIEWER_VIEWERBASE 1

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SGUtil/UpdateVisitor>
#include <VBF_Display/VBF_Viewer/IVBF_Viewer.h>
#include <VBF_Display/VBF_Manipulator/VBF_EventVisitor.h>
#include <VBF_Display/VBF_Manipulator/VBF_EventQueue.h>
#include <VBF_Display/VBF_Viewer/VBF_Scene.h>
#include <VBF_Display/VBF_Viewer/VBF_GraphicsWindow.h>


class View;


typedef std::vector<osgViewer::Scene*> CVBF_Scenes;


// 视景器的基类
class OSGVIEWER_EXPORT CVBF_Viewer : public IVBF_Viewer
{
public:

	CVBF_Viewer();
	CVBF_Viewer(const CVBF_Viewer& vb);


public:
	
	// 2、与仿真循环相关的内容

	virtual int run();  // 主帧循环。等同于while (!viewer.IsDone()) viewer.frame(); 在循环前进行初始化工作
	
	virtual void SetDone(bool done) { m_bDone = done; }	// 设置完成标志，以通知视景器的工作完成并将退出帧循环（frame loop）
	virtual bool IsDone() const { return m_bDone; }		// 是否完成并将退出出帧循环
	virtual void frame(double simulationTime=USE_REFERENCE_TIME); // 运行一帧
    virtual bool IsPaused() { return m_bPaused; }
    virtual void SetPaused(bool bPaused) { m_bPaused = bPaused; }
    virtual void eventTraversal() = 0;   // 事件响应
    virtual void updateTraversal() = 0;	 // 更新
    virtual void renderingTraversals();// 渲染


	// 设置/获取帧运行方案
	void setRunFrameScheme(FrameScheme fs) { _runFrameScheme = fs; }
	FrameScheme getRunFrameScheme() const { return _runFrameScheme; }

	virtual bool checkNeedToDoFrame() = 0; // 检测是否需要运行下一帧，与按需求运行ON_DEMAND相关
	
	void setRunMaxFrameRate(double frameRate) { _runMaxFrameRate = frameRate; }// 设置/获取最大帧速率
	double getRunMaxFrameRate() const { return _runMaxFrameRate; }


	// 3、线程相关的接口
	virtual void SetThreadingModel(EVBF_ThreadingModel threadingModel);					// 设置线程模型用于渲染遍历
	virtual EVBF_ThreadingModel GetThreadingModel() const { return _threadingModel; }	// 获取线程模型

	virtual bool areThreadsRunning() const { return _threadsRunning; } // 线程是否在运行
	virtual void StartThreading();	// 启动视景器的所有线程	
	virtual void StopThreading();	// 停止视景器的所有线程
    virtual bool IsFirstFrame() { return m_bFirstFrame; }


public:

	/** 设置/获取"结束栅栏"的位置 */
	virtual void SetEndBarrierPosition(EVBF_EndBarrierPosition bp);
	virtual EVBF_EndBarrierPosition GetEndBarrierPosition() const { return _endBarrierPosition; }


	/** 设置/获取EventVisitor */
	void setEventVisitor(osgGA::EventVisitor* eventVisitor) { _eventVisitor = eventVisitor; }
	osgGA::EventVisitor* getEventVisitor() { return _eventVisitor.get(); }
	const osgGA::EventVisitor* getEventVisitor() const { return _eventVisitor.get(); }

	/** 设置/获取自定义的退出键。默认键是Escape (osgGA::GUIEVentAdapter::KEY_Escape)。 设置0则关掉此特性 */
	void setKeyEventSetsDone(int key) { _keyEventSetsDone = key; }
	int getKeyEventSetsDone() const { return _keyEventSetsDone; }

	/** 设置/获取是否允许按下某个键（QUIT_APPLICATION）之后直接退出这种做法。 */
	void setQuitEventSetsDone(bool flag) { _quitEventSetsDone = flag; }
	bool getQuitEventSetsDone() const { return _quitEventSetsDone; }


	/** 设置/获取是否在每帧渲染结束之后关闭RC设备（在renderingTraversals()中调用relaseContext()）。
	* 默认为true，即每帧渲染结束之后关闭RC设备。设为flase可以提高性能，对于多线程模型这可能带来别的问题 */
	void setReleaseContextAtEndOfFrameHint(bool hint) { _releaseContextAtEndOfFrameHint = hint; }
	bool getReleaseContextAtEndOfFrameHint() const { return _releaseContextAtEndOfFrameHint; }


	/** 设置/获取UpdateVisitor */
	void setUpdateVisitor(osgUtil::UpdateVisitor* updateVisitor) { _updateVisitor = updateVisitor; }
	osgUtil::UpdateVisitor* getUpdateVisitor() { return _updateVisitor.get(); }
	const osgUtil::UpdateVisitor* getUpdateVisitor() const { return _updateVisitor.get(); }




	/** 设置/获取场景预处理的自定义操作（场景预处理器） */
	void setRealizeOperation(osg::Operation* op) { _realizeOperation = op; }
	osg::Operation* getRealizeOperation() { return _realizeOperation.get(); }


	/**设置/获取增量编译操作，可避免加载大（多）模型时造成的帧率下降  */
	void setIncrementalCompileOperation(osgUtil::IncrementalCompileOperation* ico);
	osgUtil::IncrementalCompileOperation* getIncrementalCompileOperation() { return _incrementalCompileOperation.get(); }



	// 4、回调函数

	virtual void addUpdateOperation(osg::Operation* operation);		// 添加1个场景更新的自定操作（更新处理器）
	virtual void removeUpdateOperation(osg::Operation* operation);	// 移除1个更新处理器

	void setUpdateOperations(osg::OperationQueue* operations) { _updateOperations = operations; } // 设置多组更新处理器
	osg::OperationQueue* getUpdateOperations() { return _updateOperations.get(); }				  // 获取多组更新处理器
	const osg::OperationQueue* getUpdateOperations() const { return _updateOperations.get(); }


	//h00017
	struct UpdateCallback : public CVBF_Referenced
	{
		UpdateCallback() {}

		virtual void customOperator(const IVBF_Viewer* pViewer) {}
	};

	void addPreUpdateCallback(UpdateCallback* cb)
	{
		_preUpdateCallbackList.push_back(cb);
	}

	void addPostUpdateCallback(UpdateCallback* cb)
	{
		_postUpdateCallbackList.push_back(cb);
	}

	void removePreUpdateCallback(UpdateCallback* cb)
	{
		UpdateCallbackList::iterator it = _preUpdateCallbackList.begin();
		while (it != _preUpdateCallbackList.end())
		{
			if (cb == (*it).get())
			{
				_preUpdateCallbackList.erase(it);
				break;
			}

			it++;
		}
	}

	void removePostUpdateCallback(UpdateCallback* cb)
	{
		UpdateCallbackList::iterator it = _postUpdateCallbackList.begin();
		while (it != _postUpdateCallbackList.end())
		{
			if (cb == (*it).get())
			{
				_postUpdateCallbackList.erase(it);
				break;
			}

			it++;
		}
	}
	//h00017

	

	// 5、获取视图与场景数据

    virtual IVBF_View* getViewWithFocus() = 0;// 获取焦点视图
    virtual const IVBF_View* getViewWithFocus() const = 0;

	
	virtual void getCameras(CVBF_Cameras& cameras, bool onlyActive=true) = 0; // 获取所有的相机
	virtual void GetContexts(CVBF_Contexts& contexts, bool onlyValid=true) = 0;// 获取所有的GC	
	virtual void GetWindows(CVBF_Windows& windows, bool onlyValid=true);// 获取所有的窗口	
	virtual void getScenes(CVBF_Scenes& scenes, bool onlyValid=true) = 0;// 获取所有的场景数据

	// 检测是否还有窗口打开，如果没有终止仿真循环
	void checkWindowStatus();

	/** Check to see if windows are still open using the list of contexts given as a parameter.
	*  If no windows are open, stop rendering threads and set viewer done to true.
	*  This function is more effective than checkWindowStatus() as it does not query
	*  the context list and should be used whenever context list is already available in your code.*/
	void checkWindowStatus(const CVBF_Contexts& contexts);




protected:


	// 自动设置最优的线程模型（根据相机/窗口的设置和硬件能力）
	virtual EVBF_ThreadingModel suggestBestThreadingModel();

	// 设置线程和CPU配置（根据不同的线程模型）
	virtual void setUpThreading();

	// 获取所有的线程
	typedef std::vector<OpenThreads::Thread*> Threads;
	virtual void GetAllThreads(Threads& threads, bool onlyActive=true) = 0;

	// 获取操作线程
	typedef std::vector<osg::OperationThread*> OperationThreads;
	virtual void GetOperationThreads(OperationThreads& threads, bool onlyActive=true) = 0;


	// 获取时间（过去的）
	virtual double GetElapsedTime() = 0;



protected:

	void viewerBaseInit();

	friend class CVBF_View;

	inline void makeCurrent(osg::GraphicsContext* gc)
	{
		if (_currentContext==gc) return;

		releaseContext();

		if (gc && gc->valid() && gc->makeCurrent()) _currentContext = gc;
	}

	inline void releaseContext()
	{
		if (_currentContext.valid() && _currentContext->valid())
		{
			_currentContext->releaseContext();
		}
		_currentContext = 0;
	}

	virtual void viewerInit() = 0;

    bool          m_bFirstFrame;			// 是否的第一帧（特殊处理，初始化）
    bool          m_bDone;					// 是否已完成
    bool          m_bPaused;
    int           _keyEventSetsDone;
    bool          _quitEventSetsDone;
	bool                                                _releaseContextAtEndOfFrameHint;

	EVBF_ThreadingModel                                 _threadingModel;		// 线程模型
	bool                                                _threadsRunning;		// 线程是否在运行

	bool                                                _requestRedraw;
	bool                                                _requestContinousUpdate;

	FrameScheme                                         _runFrameScheme;
	double                                              _runMaxFrameRate;


	EVBF_EndBarrierPosition                             _endBarrierPosition;

	ref_ptr<osg::BarrierOperation>                 _startRenderingBarrier;//渲染启动的一个栅栏标志，用于同步开始所有的图形设备的线程操作。
	ref_ptr<osg::BarrierOperation>                 _endRenderingDispatchBarrier;//渲染结束的一个栅栏标志，用于同步结束所有的图形设备的线程操作。
	ref_ptr<osg::EndOfDynamicDrawBlock>            _endDynamicDrawBlock;  //用于同步结束所有的动态对象绘制操作

	ref_ptr<osgGA::EventVisitor>                   _eventVisitor;

	ref_ptr<osg::OperationQueue>                   _updateOperations;
	ref_ptr<osgUtil::UpdateVisitor>                _updateVisitor;

	ref_ptr<osg::Operation>                        _realizeOperation;
	ref_ptr<osgUtil::IncrementalCompileOperation>  _incrementalCompileOperation;

	observer_ptr<osg::GraphicsContext>             _currentContext;


protected:
	//h00017
	typedef std::vector< observer_ptr<UpdateCallback> > UpdateCallbackList;
	UpdateCallbackList                                  _preUpdateCallbackList;
	UpdateCallbackList                                  _postUpdateCallbackList;
	//h00017
};


#endif
