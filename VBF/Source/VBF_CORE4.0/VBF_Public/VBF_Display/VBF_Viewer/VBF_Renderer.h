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
// 图形渲染器负责一切渲染有关的调度，是交互前台对渲染后台进行调度的入口
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
        
		// 在图形环境GC上渲染
        virtual void operator () (osg::GraphicsContext* context);

        virtual void release();
        
        void setCameraRequiresSetUp(bool flag); // 强制更新相关联的相机
        bool getCameraRequiresSetUp() const;

    protected:
        void initialize(osg::State* state);
        virtual ~Renderer();

        virtual void updateSceneView(osgUtil::SceneView* sceneView);        

        observer_ptr<osg::IVBF_Camera>                      _camera;
        
        bool                                                m_bDone;
        bool                                                _graphicsThreadDoesCull;
        bool                                                m_bCompileOnNextDraw;
        
		// 创建两个SceneView，支持渲染后台双缓存。SingleThreaded和CullDrawThreadPerContext只用到第一个。？？？
        ref_ptr<osgUtil::SceneView>                    _sceneView[2];

        class CVBF_SceneViewQueue//ThreadSafeQueue
        {
		public:
            CVBF_SceneViewQueue();
            ~CVBF_SceneViewQueue();

            void release(); // 放开等待该队列的所有线程，即使队列是空的

            osgUtil::SceneView* takeFront(); // 从队列中取出第一个，当队列为空时返回0
            void add(osgUtil::SceneView* sv); // 向队列尾部添加一个SceneView

		private:
            OpenThreads::Mutex _mutex;
            OpenThreads::Condition _cond;

            std::list<osgUtil::SceneView*> _queue;

            bool _isReleased;// 访问该队列的线程是否被放开（解除阻塞）
            
        };




        CVBF_SceneViewQueue _availableQueue;
        CVBF_SceneViewQueue _drawQueue;

        bool _initialized;
        ref_ptr<OpenGLQuerySupport> _querySupport;
        CVBF_Timer_t _startTick;
};

}

#endif
