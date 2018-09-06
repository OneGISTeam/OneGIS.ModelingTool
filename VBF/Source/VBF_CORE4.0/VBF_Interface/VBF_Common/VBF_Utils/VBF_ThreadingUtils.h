//**********************************************************************************
// 文件名：  VBF_ThreadingUtils.h
// 描述：    与多线程有关的工具函数
// 作者:     杜莹
// 日期:     2013-06-24
//**********************************************************************************

#ifndef __VBF_THREADING_UTILS_H__
#define __VBF_THREADING_UTILS_H__


#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>
#include <OpenThreads/Condition>
#include <OpenThreads/Mutex>
#include <OpenThreads/ReentrantMutex>
#include <VBF_Base/ref_ptr>
#include <set>
#include <map>

#define USE_CUSTOM_READ_WRITE_LOCK 1

  
typedef OpenThreads::Mutex		CVBF_Mutex;
typedef OpenThreads::Thread		CVBF_Thread;
typedef OpenThreads::ScopedLock<OpenThreads::Mutex> CVBF_ScopedMutexLock;

/**
    * Gets the unique ID of the running thread. Use this instead of
    * OpenThreads::Thread::CurrentThread, which only works reliably on
    * threads created with the OpenThreads framework
    */
extern VBF_UTILS_EXPORT unsigned VBF_GetCurrentThreadId();


#ifdef USE_CUSTOM_READ_WRITE_LOCK

/**
    * CVBF_Event with a toggled signal state.
    */
class VBF_UTILS_EXPORT CVBF_Event 
{
public:
    CVBF_Event();
    ~CVBF_Event();

    bool wait();

    /** waits on a signal, and then automatically resets it before returning. */
    bool waitAndReset(); 
    void set();
    void reset();
    bool isSet() const;

protected:
    OpenThreads::Mutex			_m;
    OpenThreads::Condition		_cond;
    bool						_set;
};

/** Same as an CVBF_Event, but waits on multiple notifications before releasing its wait. */
class VBF_UTILS_EXPORT CVBF_MultiEvent 
{
public:
    CVBF_MultiEvent(int num =1);
    ~CVBF_MultiEvent();

    bool wait();
    bool waitAndReset();
    void notify();
    void reset(int num =0);

protected:
    OpenThreads::Mutex			_m;
    OpenThreads::Condition		_cond;
    int							_set;
	int							_num;
};

/**
* Custom read/write lock. The read/write lock in OSG can unlock mutexes from a different
* thread than the one that locked them - this can hang the thread in Windows.
*
* Adapted from:
* http://www.codeproject.com/KB/threads/ReadWriteLock.aspx
*/
class VBF_UTILS_EXPORT CVBF_ReadWriteMutex
{
#if TRACE_THREADS
    typedef std::set<unsigned> TracedThreads;
    TracedThreads _trace;
    OpenThreads::Mutex _traceMutex;
#endif

public:
    CVBF_ReadWriteMutex();

    void readLock();
    void readUnlock();

    void writeLock();
    void writeUnlock();

protected:

    void incrementReaderCount();
    void decrementReaderCount();

private:
    int				_readerCount;
    CVBF_Mutex		_lockWriterMutex;
    CVBF_Mutex		_readerCountMutex;
    CVBF_Event		_noWriterEvent;
    CVBF_Event		_noReadersEvent;
};


struct VBF_UTILS_EXPORT CVBF_ScopedWriteLock
{
    CVBF_ScopedWriteLock(CVBF_ReadWriteMutex& lock);
    ~CVBF_ScopedWriteLock();

protected:
    CVBF_ReadWriteMutex&	_lock;
};

struct VBF_UTILS_EXPORT CVBF_ScopedReadLock
{
    CVBF_ScopedReadLock(CVBF_ReadWriteMutex& lock);
    ~CVBF_ScopedReadLock();

protected:
    CVBF_ReadWriteMutex&	_lock;
};

#else

typedef OpenThreads::ReadWriteMutex			CVBF_ReadWriteMutex;
typedef OpenThreads::CVBF_ScopedWriteLock	CVBF_ScopedWriteLock;
typedef OpenThreads::CVBF_ScopedReadLock	CVBF_ScopedReadLock;

#endif

/** Template for per-thread data storage */
template<typename T>
struct CVBF_PerThread
{
public:
    T& get()
	{
        CVBF_ScopedMutexLock lock(_mutex);
        return _data[VBF_GetCurrentThreadId()];
    }
   
private:
    std::map<unsigned,T>	_data;
    CVBF_Mutex				_mutex;
};

/** Template for thread safe per-object data storage */
template<typename KEY, typename DATA>
struct CVBF_PerObjectMap
{
public:
    DATA& get(KEY k)
    {
        {
            CVBF_ScopedReadLock readLock(_mutex);
            typename std::map<KEY,DATA>::iterator i = _data.find(k);
            if ( i != _data.end() )
                return i->second;
        }
        {
            CVBF_ScopedWriteLock lock(_mutex);
            typename std::map<KEY,DATA>::iterator i = _data.find(k);
            if ( i != _data.end() )
                return i->second;
            else
                return _data[k];
        }
    }

    void remove(KEY k)
    {
        CVBF_ScopedWriteLock exclusive(_mutex);
        _data.erase( k );
        }
   
private:
    std::map<KEY,DATA>		_data;
    CVBF_ReadWriteMutex		_mutex;
};

/** Template for thread safe per-object data storage */
template<typename KEY, typename DATA>
struct CVBF_PerObjectRefMap
{
public:
    DATA* get(KEY k)
    {
        CVBF_ScopedReadLock lock(_mutex);
        typename std::map<KEY,ref_ptr<DATA > >::const_iterator i = _data.find(k);
        if ( i != _data.end() )
            return i->second.get();

        return 0L;
    }

    DATA* getOrCreate(KEY k, DATA* newDataIfNeeded)
    {
        ref_ptr<DATA> _refReleaser = newDataIfNeeded;
        {
            CVBF_ScopedReadLock lock(_mutex);
            typename std::map<KEY,ref_ptr<DATA> >::const_iterator i = _data.find(k);
            if ( i != _data.end() )
                return i->second.get();
        }

        {
            CVBF_ScopedWriteLock lock(_mutex);
            typename std::map<KEY,ref_ptr<DATA> >::iterator i = _data.find(k);
            if ( i != _data.end() )
                return i->second.get();

            _data[k] = newDataIfNeeded;
            return newDataIfNeeded;
        }
    }

    void remove(KEY k)
    {
        CVBF_ScopedWriteLock exclusive(_mutex);
        _data.erase( k );
    }

    void remove(DATA* data)
    {
        CVBF_ScopedWriteLock exclusive(_mutex);
        for( typename std::map<KEY,ref_ptr<DATA> >::iterator i = _data.begin(); i != _data.end(); ++i )
        {
            if ( i->second.get() == data )
            {
                _data.erase( i );
                break;
            }
        }
    }

private:
    std::map<KEY,ref_ptr<DATA> >    _data;
    CVBF_ReadWriteMutex					_mutex;
};

/** Template for thread safe per-object data storage */
template<typename KEY, typename DATA>
struct CVBF_PerObjectObsMap
{
public:
    DATA* get(KEY k)
    {
        CVBF_ScopedReadLock lock(_mutex);
        typename std::map<KEY, observer_ptr<DATA> >::const_iterator i = _data.find(k);
        if ( i != _data.end() )
            return i->second.get();

        return 0L;
    }

    DATA* getOrCreate(KEY k, DATA* newDataIfNeeded)
    {
        ref_ptr<DATA> _refReleaser = newDataIfNeeded;
        {
            CVBF_ScopedReadLock lock(_mutex);
            typename std::map<KEY,observer_ptr<DATA> >::const_iterator i = _data.find(k);
            if ( i != _data.end() )
                return i->second.get();
        }

        {
            CVBF_ScopedWriteLock lock(_mutex);
            typename std::map<KEY,observer_ptr<DATA> >::iterator i = _data.find(k);
            if ( i != _data.end() )
                return i->second.get();

            _data[k] = newDataIfNeeded;
            return newDataIfNeeded;
        }
    }

    void remove(KEY k)
    {
        CVBF_ScopedWriteLock exclusive(_mutex);
        _data.erase( k );
    }

    void remove(DATA* data)
    {
        CVBF_ScopedWriteLock exclusive(_mutex);
        for( typename std::map<KEY,observer_ptr<DATA> >::iterator i = _data.begin(); i != _data.end(); ++i )
        {
            if ( i->second.get() == data )
            {
                _data.erase( i );
                break;
            }
        }
        }

private:
    std::map<KEY,observer_ptr<DATA> >	_data;
    CVBF_ReadWriteMutex						_mutex;
};


/** Template for thread safe observer set */
template<typename T>
struct CVBF_ThreadSafeObserverSet
{
    typedef void (*Functor)(T*);
    typedef void (*ConstFunctor)(const T*);

public:
    void iterate( const Functor& f )
    {
        CVBF_ScopedWriteLock lock(_mutex);
        for( typename std::set<T>::iterator i = _data.begin(); i != _data.end(); )
        {
            if ( i->valid() )
            {
                f( i->get() );
                ++i;
            }
            else
            {
                i = _data.erase( i );
            }
        }
    }

    void iterate( const ConstFunctor& f )
    {
        CVBF_ScopedReadLock lock(_mutex);
        for( typename std::set<T>::iterator i = _data.begin(); i != _data.end(); )
        {
            if ( i->valid() )
            {
                f( i->get() );
                ++i;
            }
            else
            {
                i = _data.erase( i );
            }
        }
    }

    void insert(T* obj)
    {
        CVBF_ScopedWriteLock lock(_mutex);
        _data.insert( obj );
    }

    void remove(T* obj)
    {
        CVBF_ScopedWriteLock lock(_mutex);
        _data.erase( obj );
    }

private:
    std::set<observer_ptr<T> >		_data;
    CVBF_ReadWriteMutex					_mutex;
};


#endif

