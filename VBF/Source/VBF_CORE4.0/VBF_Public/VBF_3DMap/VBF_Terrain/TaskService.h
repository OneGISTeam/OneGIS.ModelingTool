#ifndef OSGEARTH_TASK_SERVICE
#define OSGEARTH_TASK_SERVICE 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/Progress.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Base/VBF_Timer.h>
#include <queue>
#include <list>
#include <string>
#include <map>

namespace osgEarth
{
	// 任务请求
    class OSGEARTH_EXPORT TaskRequest : public ::CVBF_Referenced
    {
    public:
        enum State 
		{
            STATE_IDLE,
            STATE_PENDING,
            STATE_IN_PROGRESS,
            STATE_COMPLETED
        };
    public:
        TaskRequest( float priority =0.0f );
        virtual ~TaskRequest() { }

 		// 实际执行任务的代码
        virtual void operator()( ProgressCallback* progress ) =0;

        void run();
        void cancel();

        bool isIdle() const { return _state == STATE_IDLE; }
        bool isPending() const { return _state == STATE_PENDING; }
        bool isCompleted() const { return _state == STATE_COMPLETED; }
        bool isInProgress() const { return _state == STATE_IN_PROGRESS; }
        bool isRunning() const { return isPending() || isInProgress(); }

        bool wasCanceled() const;

        void setPriority( float value ) { _priority = value; }
        float getPriority() const { return _priority; }
        State getState() const { return _state; }
        void setState(State s) { _state = s; }
        void setStamp(int stamp) { _stamp = stamp; }
        int getStamp() const { return _stamp; }
        CVBF_Referenced* getResult() const { return _result.get(); }
        ProgressCallback* getProgressCallback() { return _progress.get(); }
        void setProgressCallback(ProgressCallback* progress) { _progress = progress? progress : new ProgressCallback(); }
        const std::string& getName() const { return m_sName; }
        void setName( const std::string& name ) { m_sName = name; }
        void reset() { _result = 0L; }
        CVBF_Timer_t startTime() const { return _startTime; }
        CVBF_Timer_t endTime() const { return _endTime; }
        double runTime() const { return CVBF_Timer::instance()->delta_s(_startTime,_endTime); }

        void setCompletedEvent( CVBF_Event* value ) { _completedEvent = value; }
        CVBF_Event* getCompletedEvent() const { return _completedEvent; }

    protected:
        float _priority;
        volatile State _state;
        volatile int _stamp;
        ref_ptr<CVBF_Referenced> _result;
        ref_ptr< ProgressCallback > _progress;
        std::string m_sName;
        CVBF_Timer_t _startTime;
        CVBF_Timer_t _endTime;
        CVBF_Event* _completedEvent;
    };

    typedef std::list< ref_ptr<TaskRequest> > TaskRequestList;

    typedef std::vector< ref_ptr<TaskRequest> > TaskRequestVector;

    typedef std::multimap< float, ref_ptr<TaskRequest> > TaskRequestPriorityMap;
    
    /**
     * Convenience template for creating a task that synchronized with an event.
     * Initialze multiple ParallelTask's with a common MultiEvent (semaphore) to
     * run them in parallel and wait for them all to complete.
     */
    template<typename T>
    struct ParallelTask : public TaskRequest, T
    {
        ParallelTask() : _mev(0L), _sev(0L) { }
        ParallelTask( CVBF_MultiEvent* ev ) : _mev(ev), _sev(0L) { }
        ParallelTask( CVBF_Event* ev ) : _sev(ev), _mev(0L) { }

        void operator()( ProgressCallback* pc ) 
        {
            this->execute();
            if ( _mev )
                _mev->notify();
            else if ( _sev )
                _sev->set();
        }

        CVBF_MultiEvent* _mev;
        CVBF_Event*      _sev;
    };

	// 任务请求队列
    class TaskRequestQueue : public ::CVBF_Referenced
    {
    public:
        TaskRequestQueue();

        void add( TaskRequest* request );
        TaskRequest* get();
        void clear();

        void SetDone();

        void setStamp( int value ) { _stamp = value; }
        int getStamp() const { return _stamp; }

        unsigned int getNumRequests() const;

    private:
        TaskRequestPriorityMap _requests;
        OpenThreads::Mutex _mutex;
        OpenThreads::Condition _cond;
        volatile bool m_bDone;

        int _stamp;
    };
    
	// 任务线程
    struct TaskThread : public OpenThreads::Thread
    {
        TaskThread( TaskRequestQueue* queue );
        bool IsDone() { return m_bDone;}
        void SetDone( bool done) { m_bDone = done; }
        void run();
        int cancel();

    private:
        ref_ptr<TaskRequestQueue> _queue;
        ref_ptr<TaskRequest> _request;
        volatile bool m_bDone;
    };

	// 任务服务，管理一个具有优先次序的任务队列及关联的线程池（多个线程）
    class OSGEARTH_EXPORT TaskService : public ::CVBF_Referenced
    {
    public:
        TaskService( const std::string& name ="", int numThreads =4 );

        void add( TaskRequest* request );

        void setName( const std::string& value ) { m_sName = value; }
        const std::string& getName() const { return m_sName; }

        int getStamp() const;
        void setStamp( int stamp );

        int getNumThreads() const;
        void setNumThreads( int numThreads );

        /**
         *Gets the number of requets left in the queue
         */
        unsigned int getNumRequests() const;

    private:
        virtual ~TaskService();        
		
		void adjustThreadCount();
        void removeFinishedThreads();

        OpenThreads::ReentrantMutex _threadMutex;
        typedef std::list<TaskThread*> TaskThreads;
        TaskThreads _threads;

        ref_ptr<TaskRequestQueue> _queue;

        int _numThreads;
        int _lastRemoveFinishedThreadsStamp;
        std::string m_sName;

    };

    /**
     * Manages a pool of TaskService objects, automatically allocating
     * threads among them based on a weighting metric.
     */
    class OSGEARTH_EXPORT TaskServiceManager : public ::CVBF_Referenced
    {
    public:
        /**
         * Creates a new manager, and sets the target number of threads to 
         * allocate across all managed task services.
         */
        TaskServiceManager( int numThreads =4 );

        /**
         * Sets a new total target thread count to allocate across all task
         * services under management. (The actual thread count may be higher since
         * each service is guaranteed at least one thread.)
         */
        void setNumThreads( int numThreads );

		// 获取所管理的任务服务的所有线程数
        int getNumThreads() const { return _numThreads; }

		// 添加一个新的任务服务，并重新分配线程池
        TaskService* add( UID uid, float weight =1.0f );

		// 获取任务服务
        TaskService* get( UID uid ) const;

 		// 通过UID获取一个任务服务，如果不存在则创建一个
        TaskService* getOrAdd( UID uid, float weight =1.0f );

        // 移除一个任务服务，并重新分配线程池
        void remove( TaskService* service );
        void remove( UID uid );

        /**
         * Assigned a weight value to a particular task service. The manager will
         * re-distribute available threads for all registered task services.
         */
        void setWeight( TaskService* service, float weight );

    private:
        typedef std::pair< ref_ptr<TaskService>, float > WeightedTaskService;
        typedef std::map< UID, WeightedTaskService > TaskServiceMap;
        TaskServiceMap _services;
        int _numThreads, _targetNumThreads;
        OpenThreads::Mutex _taskServiceMgrMutex;

        void reallocate( int targetNumThreads );
    };
}

#endif // OSGEARTH_TASK_SERVICE

