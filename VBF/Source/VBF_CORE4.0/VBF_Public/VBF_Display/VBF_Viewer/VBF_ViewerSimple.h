#ifndef OSGVIEWER_Viewer
#define OSGVIEWER_Viewer 1

#include <VBF_Base/VBF_ArgumentParser.h>
//#include <VBF_Display/VBF_Manipulator/VBF_EventVisitor.h>
//#include <VBF_Engine/VBF_SGUtil/UpdateVisitor>
//#include <VBF_Display/VBF_Viewer/VBF_GraphicsWindow.h>
#include <VBF_Display/VBF_Viewer/VBF_View.h>
#include <VBF_Display/VBF_Viewer/VBF_Viewer.h>

using namespace osgViewer;

// ��һ�Ӿ���������ͼ��������
class CVBF_ViewerSimple : public CVBF_Viewer
{
public:

	CVBF_ViewerSimple();
	CVBF_ViewerSimple(::ArgumentParser& arguments);
	CVBF_ViewerSimple(const CVBF_ViewerSimple& viewer, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
	virtual ~CVBF_ViewerSimple();

	META_Object(osgViewer,CVBF_ViewerSimple);

	/** �Ӵ����View�л�ȡ���е����á����/�����������View�ᱻ����  */
	virtual void take(osg::IVBF_ViewBrief& rhs);


	/** ����/��ȡͳ�ƶ�������ͳ��֡��ص�ʱ��ͳ���ͼ���� */
	virtual void setViewerStats(CVBF_Stats* stats) { m_ipView->setStats(stats); }
	virtual CVBF_Stats* getViewerStats() { return m_ipView->getStats(); }
	virtual const CVBF_Stats* getViewerStats() const { return m_ipView->getStats(); }


	/** �������ļ���ȡ�Ӿ��������� */
	virtual bool readConfiguration(const std::string& filename);

	IVBF_View* GetView() { return m_ipView.get(); }
	const IVBF_View* GetView() const { return m_ipView.get(); }

	/** �Ƿ��Ѿ�ִ����Realize�������Ƿ��д��� */
	virtual bool IsRealized() const;
	/** �ò�����ʹ��Viewer֮ǰ�����ö�ʹ֮��Ч�������ô��ں�����߳� */
	virtual void Realize();

	// ���ÿ�ʼʱ�ӣ�Tick���Ͳο�ʱ��
	virtual void setStartTick(CVBF_Timer_t tick);
	void setReferenceTime(double time=0.0);

	// ���ó����е����ݣ�Ϊ��������Ⱦ��ʵ������
	virtual void setSceneData(osg::IVBF_SGNode* node);


	// �ú����Ĺ�������Ƕ��ʽ���ڵ���ʽ�����ø�Viewer����Ⱦ�档����ָ��Ƕ��ʽ����ָ�롣Ƕ�뵽�ⲿ����Ĵ�����
	virtual GraphicsWindowEmbedded* setUpViewerAsEmbeddedInWindow(int x, int y, int width, int height);


	// ��ȡʱ�䣨��ȥ�ģ�������ִ�е�ʱ��
	virtual double GetElapsedTime();

	// ��ȡ֡��
	virtual ::CVBF_FrameStamp* getViewerFrameStamp() { return m_ipView->getFrameStamp(); }

	/** ��֡ѭ������ͬ��while (!viewer.IsDone()) viewer.frame(); ��ѭ��ǰ���г�ʼ������ */
	virtual int run();

	/** ����Ƿ���Ҫ������һ֡���밴��������ON_DEMAND��� */
	virtual bool checkNeedToDoFrame();

	// ����ʱ����ǰһ֡
	virtual void advance(double simulationTime=USE_REFERENCE_TIME);

	// �¼���Ӧ
	virtual void eventTraversal();

	// ����
	virtual void updateTraversal();

	// ����/��ȡ�������
	void setCameraWithFocus(osg::IVBF_Camera* camera) { _cameraWithFocus = camera; }
	osg::IVBF_Camera* getCameraWithFocus() { return _cameraWithFocus.get(); }
	const osg::IVBF_Camera* getCameraWithFocus() const { return _cameraWithFocus.get(); }

    // ����/��ȡ������ͼ
    IVBF_View* getViewWithFocus() { return m_ipView.get(); }
    const IVBF_View* getViewWithFocus() const { return m_ipView.get(); }


	// ��ȡ�������
	virtual void getCameras(CVBF_Cameras& cameras, bool onlyActive=true);

	// ��ȡ���е�GC
	virtual void GetContexts(CVBF_Contexts& contexts, bool onlyValid=true);

	// ��ȡ���е��߳�
	virtual void GetAllThreads(Threads& threads, bool onlyActive=true);

	// ��ȡ�����߳�
	virtual void GetOperationThreads(OperationThreads& threads, bool onlyActive=true);

	// ��ȡ���еĳ�������
	virtual void getScenes(CVBF_Scenes& scenes, bool onlyValid=true);

	// ��ȡ���е���ͼ
	virtual void GetViews(CVBF_Views& views, bool onlyValid=true);

	// �õ���ǰViewer�����������������ͼ��̵��÷�
	virtual void GetUsage(ApplicationUsage& usage) const;


	// 5������ͼ��ص����ݣ�Ϊ��ͳһ

	virtual void addView(IVBF_View* view) {}	// �����ͼ
    virtual void removeView(IVBF_View* view) {}	// �Ƴ���ͼ
		
	virtual IVBF_View* getView(unsigned i=0) { return m_ipView.get(); }	// ��ȡ��ͼ
    virtual const IVBF_View* getView(unsigned i=0) const { return m_ipView.get(); } 
    virtual unsigned int getNumViews() const { return 1; } // ��ȡ��ͼ����

protected:

	void constructorInit();

	virtual void viewerInit() { m_ipView->init(); }


	observer_ptr<osg::IVBF_Camera>  _cameraWithFocus; //�������������ƶ��������϶���ʱ��������ӿڷ�Χ����������¼���"��ȾĿ��ʵ�ַ�ʽ"ΪFRAME_BUFFER       
	ref_ptr<CVBF_View>              m_ipView;         // ��ͼ
};



#endif
