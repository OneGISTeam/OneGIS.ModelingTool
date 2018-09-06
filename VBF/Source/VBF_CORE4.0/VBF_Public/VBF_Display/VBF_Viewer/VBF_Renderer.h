#ifndef OSGVIEWER_RENDERER
#define OSGVIEWER_RENDERER 1

#include <OpenThreads/Condition>
#include <VBF_Base/VBF_Timer.h>
#include <VBF_Engine/VBF_SGDB/DatabasePager>
#include <VBF_Engine/VBF_SGUtil/SceneView>
#include <VBF_Display/VBF_Viewer/Export>

namespace osgViewer {

class OSGVIEWER_EXPORT OpenGLQuerySupport : public ::CVBF_Referenced
{
    public:
        OpenGLQuerySupport();

        virtual void checkQuery(CVBF_Stats* stats, osg::State* state, CVBF_Timer_t startTick) = 0;
        
        virtual void beginQuery(unsigned int frameNumber, osg::State* state) = 0;
        virtual void endQuery(osg::State* state) = 0;
        virtual void initialize(osg::State* state, CVBF_Timer_t startTick);
    protected:

        const osg::Drawable::Extensions*            _extensions;
};
// ͼ����Ⱦ������һ����Ⱦ�йصĵ��ȣ��ǽ���ǰ̨����Ⱦ��̨���е��ȵ����
class OSGVIEWER_EXPORT Renderer : public osg::GraphicsOperation
{
    public:
        Renderer(osg::IVBF_Camera* camera);

        osgUtil::SceneView* getSceneView(unsigned int i) { return _sceneView[i].get(); }
        const osgUtil::SceneView* getSceneView(unsigned int i) const { return _sceneView[i].get(); }

        void SetDone(bool done) { m_bDone = done; }
        bool IsDone() { return m_bDone; }

        void setGraphicsThreadDoesCull(bool flag);
        bool getGraphicsThreadDoesCull() const { return _graphicsThreadDoesCull; }


        virtual void cull();
        virtual void draw();
        virtual void cull_draw();

        virtual void compile();
        
        void setCompileOnNextDraw(bool flag) { m_bCompileOnNextDraw = flag; }
        bool IsCompileOnNextDraw() const { return m_bCompileOnNextDraw; }

        virtual void operator () (osg::CVBF_Object* object);
        
		// ��ͼ�λ���GC����Ⱦ
        virtual void operator () (osg::GraphicsContext* context);

        virtual void release();
        
        void setCameraRequiresSetUp(bool flag); // ǿ�Ƹ�������������
        bool getCameraRequiresSetUp() const;

    protected:
        void initialize(osg::State* state);
        virtual ~Renderer();

        virtual void updateSceneView(osgUtil::SceneView* sceneView);        

        observer_ptr<osg::IVBF_Camera>                      _camera;
        
        bool                                                m_bDone;
        bool                                                _graphicsThreadDoesCull;
        bool                                                m_bCompileOnNextDraw;
        
		// ��������SceneView��֧����Ⱦ��̨˫���档SingleThreaded��CullDrawThreadPerContextֻ�õ���һ����������
        ref_ptr<osgUtil::SceneView>                    _sceneView[2];

        class CVBF_SceneViewQueue//ThreadSafeQueue
        {
		public:
            CVBF_SceneViewQueue();
            ~CVBF_SceneViewQueue();

            void release(); // �ſ��ȴ��ö��е������̣߳���ʹ�����ǿյ�

            osgUtil::SceneView* takeFront(); // �Ӷ�����ȡ����һ����������Ϊ��ʱ����0
            void add(osgUtil::SceneView* sv); // �����β�����һ��SceneView

		private:
            OpenThreads::Mutex _mutex;
            OpenThreads::Condition _cond;

            std::list<osgUtil::SceneView*> _queue;

            bool _isReleased;// ���ʸö��е��߳��Ƿ񱻷ſ������������
            
        };




        CVBF_SceneViewQueue _availableQueue;
        CVBF_SceneViewQueue _drawQueue;

        bool _initialized;
        ref_ptr<OpenGLQuerySupport> _querySupport;
        CVBF_Timer_t _startTick;
};

}

#endif
