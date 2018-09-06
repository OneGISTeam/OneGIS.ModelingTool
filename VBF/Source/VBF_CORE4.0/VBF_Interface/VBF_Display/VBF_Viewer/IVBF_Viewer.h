#ifndef IVBF_VIEWER_H
#define IVBF_VIEWER_H 1

#include <VBF_Base/VBF_Stats.h>

#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Engine/VBF_SGUtil/IncrementalCompileOperation>
#include <VBF_Display/VBF_Viewer/VBF_GraphicsWindow.h>

class IVBF_View;
enum EVBF_ThreadingModel // �߳�ģ��
{
    enumSingleThreaded,           // ���߳�ģ�͡��������κ����߳�����ɳ�����ɸѡ����Ⱦ��Ҳ������ȾЧ�ʵ�������κ����档���ʺ��κ�������ʹ�á�
    enumCullDrawThreadPerContext, // Ϊÿ��GC����ͼ���̣߳������䵽��ͬ��CPU�ϣ�ʵ�ֲ�����Ⱦ��ÿ֡����ǰ����ǿ��ͬ�����е��̡߳�
    enumThreadPerContext = enumCullDrawThreadPerContext,
    enumDrawThreadPerContext,     // Ϊÿ��GC�����̣߳������䵽��ͬ��CPU�ϡ�����ģʽ���ڵ�ǰ֡�������߳���ɹ���֮ǰ����ʼ��һ֡��
    enumCullThreadPerCameraDrawThreadPerContext, // Ϊÿ��GC��ÿ����������̣߳�����ȴ�ǰһ�ε���Ⱦ���������Ƿ��ط���ѭ������
								                 // �ο�ʼִ��frame ���������ʹ���ĺ��������ߵ�ϵͳ���ã���ôʹ����һ�߳�ģ�ͽ�����޶ȵط��Ӷ�CPU �Ĵ���������
    enumThreadPerCamera = enumCullThreadPerCameraDrawThreadPerContext,
    enumAutomaticSelection
};
    
enum EVBF_EndBarrierPosition // "����դ��"��λ��
{
    enumBeforeSwapBuffers, // ������΢�Ľ���֡���� �����ɱ�֤���ڼ��һ���ԡ�
    enumAfterSwapBuffers   // ������΢�����֡���ʣ� �����ܵ��´���֮�䲻һ�µ�Swap
};


typedef std::vector<IVBF_View*>						CVBF_Views;
typedef std::vector<osgViewer::GraphicsWindow*>		CVBF_Windows;
typedef std::vector<osg::GraphicsContext*>			CVBF_Contexts;
typedef std::vector<osg::IVBF_Camera*>				CVBF_Cameras;


#define USE_REFERENCE_TIME DBL_MAX

class IVBF_Viewer : virtual public osg::CVBF_Object
{
public:

	// 0���������ʼ��

	virtual bool readConfiguration(const std::string& filename) = 0; // �������ļ���ȡ���������Ӿ���	
	virtual bool IsRealized() const = 0;// �Ƿ��д���
	virtual void Realize() = 0;// ���ô��ں�����߳�


	// 1������ͼ��ص�����

    virtual void addView(IVBF_View* pIView)=0;	// �����ͼ
    virtual void removeView(IVBF_View* pIView)=0; // �Ƴ���ͼ
		
    virtual IVBF_View* getView(unsigned i=0) =0;	// ��ȡ��ͼ
    virtual const IVBF_View* getView(unsigned i=0) const =0; 
    virtual unsigned int getNumViews() const =0; // ��ȡ��ͼ����


	// 2�������ѭ����ص�����
	
	virtual int run()=0;  // ����
	
	virtual void SetDone(bool done)=0; // ������ɱ�־����֪ͨ�Ӿ����Ĺ�����ɲ����˳�֡ѭ����frame loop��	
	virtual bool IsDone() const = 0;    // �Ƿ���ɲ����˳���֡ѭ��
    virtual bool IsPaused() = 0;
    virtual void SetPaused(bool bPaused) = 0;

	virtual void frame(double simulationTime=USE_REFERENCE_TIME)=0; // ����һ֡
	virtual void advance(double simulationTime=USE_REFERENCE_TIME) = 0; // ����ʱ����ǰһ֡
//	virtual void eventTraversal() = 0;      // �¼���Ӧ
//	virtual void updateTraversal() = 0;	    // ����
//	virtual void renderingTraversals() =0;  // ��Ⱦ

	virtual bool checkNeedToDoFrame() = 0;	// ����Ƿ���Ҫ������һ֡���밴��������ON_DEMAND���

	virtual void setRunMaxFrameRate(double frameRate)=0;// �������֡����
	virtual double getRunMaxFrameRate() const=0;		// ��ȡ���֡����


	enum FrameScheme // ֡���з���
	{
		ON_DEMAND,   // ����������
		CONTINUOUS   // ��������
	};

	// ����/��ȡ֡���з���
	virtual void setRunFrameScheme(FrameScheme fs)=0;
	virtual FrameScheme getRunFrameScheme() const=0;



	// 3���߳���صĽӿ�

    virtual void SetThreadingModel(EVBF_ThreadingModel threadingModel) =0;	// �����߳�ģ��
    virtual EVBF_ThreadingModel GetThreadingModel() const =0;				// ��ȡ�߳�ģ��

	virtual bool areThreadsRunning() const =0; // �߳��Ƿ�������
	virtual void StopThreading() =0;	// ֹͣ�Ӿ����������߳�	
	virtual void StartThreading() =0;	// �����Ӿ����������߳�


	/**����/��ȡ��������������ɱ�����ش󣨶ࣩģ��ʱ��ɵ�֡���½�  */
	virtual void setIncrementalCompileOperation(osgUtil::IncrementalCompileOperation* ico)=0;
	virtual osgUtil::IncrementalCompileOperation* getIncrementalCompileOperation()=0;


	// 4���ص�����

	virtual void addUpdateOperation(osg::Operation* operation)=0;	// ���1�����´�����
	virtual void removeUpdateOperation(osg::Operation* operation)=0;// �Ƴ�1�����´�����

	virtual void setUpdateOperations(osg::OperationQueue* operations)=0;// ���ö�����´�����
	virtual osg::OperationQueue* getUpdateOperations()=0;				// ��ȡ������´�����
	virtual const osg::OperationQueue* getUpdateOperations() const=0;


	// 5����ȡ��ͼ�볡������
    	
    virtual IVBF_View* getViewWithFocus() = 0;// ��ȡ������ͼ
    virtual const IVBF_View* getViewWithFocus() const = 0;

    virtual void GetViews(CVBF_Views& views, bool onlyValid=true) = 0;	// ��ȡ���е���ͼ	
    virtual void GetWindows(CVBF_Windows& windows, bool onlyValid=true)=0;// ��ȡ���еĴ���
	virtual void GetContexts(CVBF_Contexts& contexts, bool onlyValid=true) = 0;// ��ȡ���е�GC	
	virtual CVBF_FrameStamp* getViewerFrameStamp() = 0; // ��ȡ֡��

	// ���ý���դ����λ��
    virtual void SetEndBarrierPosition(EVBF_EndBarrierPosition bp)=0;
    virtual EVBF_EndBarrierPosition GetEndBarrierPosition() const =0;

	// ��ȡ���ͼ��̵��÷�
	virtual void GetUsage(ApplicationUsage& usage) const = 0;

    virtual bool IsFirstFrame() = 0;


	//!!! �������ݿ����Ƿ��Ż��������ǿ����ڵײ����ӹ��ܣ������ǵ��û���Ӧ���ṩ��˸��ӵĽӿڣ�
public:
	// ����/��ȡͳ�ƶ�������ͳ��֡��ص�ʱ��ͳ���ͼ����
	virtual void setViewerStats(CVBF_Stats* stats) = 0;
	virtual CVBF_Stats* getViewerStats() = 0;
	virtual const CVBF_Stats* getViewerStats() const = 0;


	// ����/��ȡ����Ԥ������Զ������������Ԥ��������
	virtual void setRealizeOperation(osg::Operation* op) = 0;
	virtual osg::Operation* getRealizeOperation() = 0;

public:
    // ����/��ȡ�Զ�����˳�����Ĭ�ϼ���Escape (osgGA::GUIEVentAdapter::KEY_Escape)�� ����0��ص�������
    virtual void setKeyEventSetsDone(int key)=0;
    virtual int getKeyEventSetsDone() const=0;

    // ����/��ȡ�Ƿ�������ĳ������QUIT_APPLICATION��֮��ֱ���˳���������
    virtual void setQuitEventSetsDone(bool flag)=0;
    virtual bool getQuitEventSetsDone() const=0;
    virtual void setStartTick(CVBF_Timer_t tick)=0;


};

enum EVBF_VIEWER_TYPE
{
	EVBF_VIEWER_TYPE_SIMPLE    = 1,	// ����ͼ�Ӿ���
	EVBF_VIEWER_TYPE_COMPOSITE = 2	// ����ͼ�Ӿ���
};

OSGVIEWER_EXPORT IVBF_Viewer* VBF_CreateViewer(EVBF_VIEWER_TYPE type);
OSGVIEWER_EXPORT IVBF_Viewer* VBF_CreateViewer(EVBF_VIEWER_TYPE type,ArgumentParser& arguments);



#endif
