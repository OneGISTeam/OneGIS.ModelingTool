#ifndef OSGVIEWER_CompositeViewer
#define OSGVIEWER_CompositeViewer 1

#include <VBF_Base/VBF_ArgumentParser.h>
#include <VBF_Display/VBF_Viewer/VBF_Viewer.h>
#include <VBF_Display/VBF_Viewer/VBF_View.h>
using namespace osgViewer;

// �����Ӿ���������ͼ���ೡ��
class CVBF_ViewerComposite : public CVBF_Viewer
{
    public:

        CVBF_ViewerComposite();
        CVBF_ViewerComposite(const CVBF_ViewerComposite&,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
        CVBF_ViewerComposite(::ArgumentParser& arguments);
		virtual ~CVBF_ViewerComposite();

        META_Object(osgViewer,CVBF_ViewerComposite);


        /** ����/��ȡͳ�ƶ�������ͳ��֡��ص�ʱ��ͳ���ͼ���� */
        virtual void setViewerStats(CVBF_Stats* stats) { _stats = stats; }
        virtual CVBF_Stats* getViewerStats() { return _stats.get(); }
        virtual const CVBF_Stats* getViewerStats() const { return _stats.get(); }

         /** �������ļ���ȡ�Ӿ��������� */
        bool readConfiguration(const std::string& filename);

		// ���/�Ƴ���ͼ
        void addView(IVBF_View* view);
        void removeView(IVBF_View* view);
		
		// ��ȡ��ͼ����ͼ����
        IVBF_View* getView(unsigned i=0) { return (IVBF_View*)(CVBF_ViewBrief*)_views[i].get(); }
        const IVBF_View* getView(unsigned i=0) const { return (IVBF_View*)(CVBF_ViewBrief*)_views[i].get(); }
        unsigned int getNumViews() const { return _views.size(); }



        /** �Ƿ��д��� */
        virtual bool IsRealized() const;
        /** ���ô��ں�����߳� */
        virtual void Realize();


		// ���ÿ�ʼʱ�ӣ�Tick���Ͳο�ʱ��
        virtual void setStartTick(CVBF_Timer_t tick);
        void setReferenceTime(double time=0.0);

		// ��ȡ֡��
        ::CVBF_FrameStamp* getFrameStamp() { return _frameStamp.get(); }
        const ::CVBF_FrameStamp* getFrameStamp() const { return _frameStamp.get(); }
        virtual ::CVBF_FrameStamp* getViewerFrameStamp() { return getFrameStamp(); }

		// ��ȡʱ�䣨��ȥ�ģ�
        virtual double GetElapsedTime();

 

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
        void setCameraWithFocus(osg::IVBF_Camera* camera);
        osg::IVBF_Camera* getCameraWithFocus() { return _cameraWithFocus.get(); }
        const osg::IVBF_Camera* getCameraWithFocus() const { return _cameraWithFocus.get(); }

		// ����/��ȡ������ͼ
        IVBF_View* getViewWithFocus() { return _viewWithFocus.get(); }
        const IVBF_View* getViewWithFocus() const { return _viewWithFocus.get(); }

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

    protected:

        void constructorInit();

        virtual void viewerInit();

        typedef std::vector< ref_ptr<CVBF_View> > RefViews;
        RefViews _views;

        bool m_bFirstFrame;                               // �Ƿ��һ֡

        ref_ptr<CVBF_Stats>            _stats;     // ͳ�ƹ���

        CVBF_Timer_t                        _startTick; // ��ʼʱ��
        ref_ptr< ::CVBF_FrameStamp >       _frameStamp;// ֡��

        observer_ptr<osg::IVBF_Camera> _cameraWithFocus;  // �������
        observer_ptr<CVBF_View>        _viewWithFocus;    // ������ͼ

};



#endif
