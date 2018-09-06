#ifndef VBF_DELETE_OBSERVER_H
#define VBF_DELETE_OBSERVER_H 1

#include <VBF_Base/VBF_BaseExport.h>
#include <OpenThreads/Mutex>
#include <VBF_Base/VBF_Referenced.h>
#include <set>

// 对象被删除时（引用计数为0）的观察者的基类
class VBF_BASE_EXPORT DeleteObserver
{
public:
    DeleteObserver();
    virtual ~DeleteObserver();

    virtual void objectDeleted(void*);// 被观察的对象被删除时触发调用
};

// osg::Referenced用于管理（跟踪）所有关联的Observer的类
class VBF_BASE_EXPORT ObserverSet : public ::CVBF_Referenced
{
public:
    ObserverSet(const CVBF_Referenced* observedObject);

    CVBF_Referenced* getObserverdObject() { return _observedObject; }
    const CVBF_Referenced* getObserverdObject() const { return _observedObject; }

    // 通过增加引用计数给被观察对象加锁，以免被删除，如果对象不存在了返回null
    CVBF_Referenced* addRefLock();

    inline OpenThreads::Mutex* getObserverSetMutex() const { return &_mutex; }

    void addObserver(DeleteObserver* observer);
    void removeObserver(DeleteObserver* observer);

    void signalObjectDeleted(void* ptr);

    typedef std::set<DeleteObserver*> Observers;
    const Observers& getObservers() const;
protected:
    ObserverSet(const ObserverSet& rhs);
    ObserverSet& operator = (const ObserverSet& /*rhs*/);
    virtual ~ObserverSet();

    mutable OpenThreads::Mutex _mutex;
    CVBF_Referenced*           _observedObject;
    Observers                  _observers;
};

#endif
