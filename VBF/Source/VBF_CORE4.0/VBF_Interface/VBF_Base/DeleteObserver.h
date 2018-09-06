#ifndef VBF_DELETE_OBSERVER_H
#define VBF_DELETE_OBSERVER_H 1

#include <VBF_Base/VBF_BaseExport.h>
#include <OpenThreads/Mutex>
#include <VBF_Base/VBF_Referenced.h>
#include <set>

// ����ɾ��ʱ�����ü���Ϊ0���Ĺ۲��ߵĻ���
class VBF_BASE_EXPORT DeleteObserver
{
public:
    DeleteObserver();
    virtual ~DeleteObserver();

    virtual void objectDeleted(void*);// ���۲�Ķ���ɾ��ʱ��������
};

// osg::Referenced���ڹ������٣����й�����Observer����
class VBF_BASE_EXPORT ObserverSet : public ::CVBF_Referenced
{
public:
    ObserverSet(const CVBF_Referenced* observedObject);

    CVBF_Referenced* getObserverdObject() { return _observedObject; }
    const CVBF_Referenced* getObserverdObject() const { return _observedObject; }

    // ͨ���������ü��������۲������������ⱻɾ����������󲻴����˷���null
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
