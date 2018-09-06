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


// �Ӿ����Ļ���
class OSGVIEWER_EXPORT CVBF_Viewer : public IVBF_Viewer
{
public:

	CVBF_Viewer();
	CVBF_Viewer(const CVBF_Viewer& vb);


public:
	
	// 2�������ѭ����ص�����

	virtual int run();  // ��֡ѭ������ͬ��while (!viewer.IsDone()) viewer.frame(); ��ѭ��ǰ���г�ʼ������
	
	virtual void SetDone(bool done) { m_bDone = done; }	// ������ɱ�־����֪ͨ�Ӿ����Ĺ�����ɲ����˳�֡ѭ����frame loop��
	virtual bool IsDone() const { return m_bDone; }		// �Ƿ���ɲ����˳���֡ѭ��
	virtual void frame(double simulationTime=USE_REFERENCE_TIME); // ����һ֡
    virtual bool IsPaused() { return m_bPaused; }
    virtual void SetPaused(bool bPaused) { m_bPaused = bPaused; }
    virtual void eventTraversal() = 0;   // �¼���Ӧ
    virtual void updateTraversal() = 0;	 // ����
    virtual void renderingTraversals();// ��Ⱦ


	// ����/��ȡ֡���з���
	void setRunFrameScheme(FrameScheme fs) { _runFrameScheme = fs; }
	FrameScheme getRunFrameScheme() const { return _runFrameScheme; }

	virtual bool checkNeedToDoFrame() = 0; // ����Ƿ���Ҫ������һ֡���밴��������ON_DEMAND���
	
	void setRunMaxFrameRate(double frameRate) { _runMaxFrameRate = frameRate; }// ����/��ȡ���֡����
	double getRunMaxFrameRate() const { return _runMaxFrameRate; }


	// 3���߳���صĽӿ�
	virtual void SetThreadingModel(EVBF_ThreadingModel threadingModel);					// �����߳�ģ��������Ⱦ����
	virtual EVBF_ThreadingModel GetThreadingModel() const { return _threadingModel; }	// ��ȡ�߳�ģ��

	virtual bool areThreadsRunning() const { return _threadsRunning; } // �߳��Ƿ�������
	virtual void StartThreading();	// �����Ӿ����������߳�	
	virtual void StopThreading();	// ֹͣ�Ӿ����������߳�
    virtual bool IsFirstFrame() { return m_bFirstFrame; }


public:

	/** ����/��ȡ"����դ��"��λ�� */
	virtual void SetEndBarrierPosition(EVBF_EndBarrierPosition bp);
	virtual EVBF_EndBarrierPosition GetEndBarrierPosition() const { return _endBarrierPosition; }


	/** ����/��ȡEventVisitor */
	void setEventVisitor(osgGA::EventVisitor* eventVisitor) { _eventVisitor = eventVisitor; }
	osgGA::EventVisitor* getEventVisitor() { return _eventVisitor.get(); }
	const osgGA::EventVisitor* getEventVisitor() const { return _eventVisitor.get(); }

	/** ����/��ȡ�Զ�����˳�����Ĭ�ϼ���Escape (osgGA::GUIEVentAdapter::KEY_Escape)�� ����0��ص������� */
	void setKeyEventSetsDone(int key) { _keyEventSetsDone = key; }
	int getKeyEventSetsDone() const { return _keyEventSetsDone; }

	/** ����/��ȡ�Ƿ�������ĳ������QUIT_APPLICATION��֮��ֱ���˳����������� */
	void setQuitEventSetsDone(bool flag) { _quitEventSetsDone = flag; }
	bool getQuitEventSetsDone() const { return _quitEventSetsDone; }


	/** ����/��ȡ�Ƿ���ÿ֡��Ⱦ����֮��ر�RC�豸����renderingTraversals()�е���relaseContext()����
	* Ĭ��Ϊtrue����ÿ֡��Ⱦ����֮��ر�RC�豸����Ϊflase����������ܣ����ڶ��߳�ģ������ܴ���������� */
	void setReleaseContextAtEndOfFrameHint(bool hint) { _releaseContextAtEndOfFrameHint = hint; }
	bool getReleaseContextAtEndOfFrameHint() const { return _releaseContextAtEndOfFrameHint; }


	/** ����/��ȡUpdateVisitor */
	void setUpdateVisitor(osgUtil::UpdateVisitor* updateVisitor) { _updateVisitor = updateVisitor; }
	osgUtil::UpdateVisitor* getUpdateVisitor() { return _updateVisitor.get(); }
	const osgUtil::UpdateVisitor* getUpdateVisitor() const { return _updateVisitor.get(); }




	/** ����/��ȡ����Ԥ������Զ������������Ԥ�������� */
	void setRealizeOperation(osg::Operation* op) { _realizeOperation = op; }
	osg::Operation* getRealizeOperation() { return _realizeOperation.get(); }


	/**����/��ȡ��������������ɱ�����ش󣨶ࣩģ��ʱ��ɵ�֡���½�  */
	void setIncrementalCompileOperation(osgUtil::IncrementalCompileOperation* ico);
	osgUtil::IncrementalCompileOperation* getIncrementalCompileOperation() { return _incrementalCompileOperation.get(); }



	// 4���ص�����

	virtual void addUpdateOperation(osg::Operation* operation);		// ���1���������µ��Զ����������´�������
	virtual void removeUpdateOperation(osg::Operation* operation);	// �Ƴ�1�����´�����

	void setUpdateOperations(osg::OperationQueue* operations) { _updateOperations = operations; } // ���ö�����´�����
	osg::OperationQueue* getUpdateOperations() { return _updateOperations.get(); }				  // ��ȡ������´�����
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

	

	// 5����ȡ��ͼ�볡������

    virtual IVBF_View* getViewWithFocus() = 0;// ��ȡ������ͼ
    virtual const IVBF_View* getViewWithFocus() const = 0;

	
	virtual void getCameras(CVBF_Cameras& cameras, bool onlyActive=true) = 0; // ��ȡ���е����
	virtual void GetContexts(CVBF_Contexts& contexts, bool onlyValid=true) = 0;// ��ȡ���е�GC	
	virtual void GetWindows(CVBF_Windows& windows, bool onlyValid=true);// ��ȡ���еĴ���	
	virtual void getScenes(CVBF_Scenes& scenes, bool onlyValid=true) = 0;// ��ȡ���еĳ�������

	// ����Ƿ��д��ڴ򿪣����û����ֹ����ѭ��
	void checkWindowStatus();

	/** Check to see if windows are still open using the list of contexts given as a parameter.
	*  If no windows are open, stop rendering threads and set viewer done to true.
	*  This function is more effective than checkWindowStatus() as it does not query
	*  the context list and should be used whenever context list is already available in your code.*/
	void checkWindowStatus(const CVBF_Contexts& contexts);




protected:


	// �Զ��������ŵ��߳�ģ�ͣ��������/���ڵ����ú�Ӳ��������
	virtual EVBF_ThreadingModel suggestBestThreadingModel();

	// �����̺߳�CPU���ã����ݲ�ͬ���߳�ģ�ͣ�
	virtual void setUpThreading();

	// ��ȡ���е��߳�
	typedef std::vector<OpenThreads::Thread*> Threads;
	virtual void GetAllThreads(Threads& threads, bool onlyActive=true) = 0;

	// ��ȡ�����߳�
	typedef std::vector<osg::OperationThread*> OperationThreads;
	virtual void GetOperationThreads(OperationThreads& threads, bool onlyActive=true) = 0;


	// ��ȡʱ�䣨��ȥ�ģ�
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

    bool          m_bFirstFrame;			// �Ƿ�ĵ�һ֡�����⴦����ʼ����
    bool          m_bDone;					// �Ƿ������
    bool          m_bPaused;
    int           _keyEventSetsDone;
    bool          _quitEventSetsDone;
	bool                                                _releaseContextAtEndOfFrameHint;

	EVBF_ThreadingModel                                 _threadingModel;		// �߳�ģ��
	bool                                                _threadsRunning;		// �߳��Ƿ�������

	bool                                                _requestRedraw;
	bool                                                _requestContinousUpdate;

	FrameScheme                                         _runFrameScheme;
	double                                              _runMaxFrameRate;


	EVBF_EndBarrierPosition                             _endBarrierPosition;

	ref_ptr<osg::BarrierOperation>                 _startRenderingBarrier;//��Ⱦ������һ��դ����־������ͬ����ʼ���е�ͼ���豸���̲߳�����
	ref_ptr<osg::BarrierOperation>                 _endRenderingDispatchBarrier;//��Ⱦ������һ��դ����־������ͬ���������е�ͼ���豸���̲߳�����
	ref_ptr<osg::EndOfDynamicDrawBlock>            _endDynamicDrawBlock;  //����ͬ���������еĶ�̬������Ʋ���

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
