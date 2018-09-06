#ifndef VBF_REFERENCED_H
#define VBF_REFERENCED_H 1

#include <VBF_Base/VBF_BaseExport.h>

#include <OpenThreads/ScopedLock>
#include <OpenThreads/Mutex>
#include <OpenThreads/Atomic>

#if !defined(_OPENTHREADS_ATOMIC_USE_MUTEX)
# define _OSG_REFERENCED_USE_ATOMIC_OPERATIONS
#endif


class DeleteHandler;
class DeleteObserver;
class ObserverSet;

// 保证静态初始化顺序正确的辅助模板类
template <typename T, T M()>
struct depends_on
{
    depends_on() { M(); }
};

// 需要引用计数对象的基类，该类与线程紧密相关。
// 注：使用时，仅需从本类继承即可，基本不需要调用本类的函数，可使用智能指针自动处理引用计数的管理
class VBF_BASE_EXPORT CVBF_Referenced
{
    public:
	    CVBF_Referenced();        
        explicit CVBF_Referenced(bool threadSafeRefUnref); 
        CVBF_Referenced(const CVBF_Referenced&);
        CVBF_Referenced& operator = (const CVBF_Referenced&);

        // 设置/获取是否使用mutex确保ref()和unref()的线程安全性。
        virtual void setThreadSafeRefUnref(bool threadSafe);
		bool getThreadSafeRefUnref() const ;

        // 获取用于保证ref()/unref()线程安全性的mutex
        OpenThreads::Mutex* getRefMutex() const;

		// 获取可选的全局Referenced互斥量，该互斥量可以在所有的Referenced对象之间共享
        static OpenThreads::Mutex* getGlobalReferencedMutex();

        // 增加一次引用计数，表明存在指针正引用本对象。
        int ref() const;
        
        // 减少一次引用计数。如果引用计数降为0, 表明该对象不再被引用，自动删除该对象。
        int unref() const;
        
        // 减少一次引用计数。无论如何不删除（即使引用计数降为0）。
        //!!!最好使用unref()函数替代此函数，此函数可能导致内存泄漏。用时必须谨慎，明确知道谁负责删除
        int unref_nodelete() const;
        
        // 返回对象的被引用次数。
        int referenceCount() const;

		//---以下部分用于弱智能指针，当this被删除时，要通知弱引用了this的对象（this的观察者）。观察者可以是多个，即ObserverSet。

        // 获取观察者的集合，如果没有设置返回NULL
        ObserverSet* getObserverSet() const;

        // 获取观察者的集合，如果没有设置则创建一个
        ObserverSet* getOrCreateObserverSet() const;

        // 添加/移除一个观察者，并放入观察者集合中或从集合中移除
        void addObserver(DeleteObserver* observer) const;
        void removeObserver(DeleteObserver* observer) const;

        // 是否使用互斥量实现线程安全的引用计数
        static void setThreadSafeReferenceCounting(bool enableThreadSafeReferenceCounting);
        static bool getThreadSafeReferenceCounting();

        friend class DeleteHandler;

        // 设置/获取延迟删除处理器
        static void setDeleteHandler(DeleteHandler* handler);
        static DeleteHandler* getDeleteHandler();

    protected:
        virtual ~CVBF_Referenced();

		// 通知观察者this被删除并删除this，可以是仅通知，也可以是仅删除，或通知并删除。
        void signalObserversAndDelete(bool signalDelete, bool doDelete) const;
        void deleteUsingDeleteHandler() const; // 使用延迟删除处理器删除


#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
        mutable OpenThreads::AtomicPtr  _observerSet;	// 观察者的集合
        mutable OpenThreads::Atomic     _refCount;		// 引用的数量
#else
        
        mutable OpenThreads::Mutex*     _refMutex;    // 互斥量，用于保证线程安全
        mutable int                     _refCount;    // 引用的数量     
        mutable void*                   _observerSet; // 观察者的集合
#endif
};



// 以下函数是为了boost::intrusive_ptr使用Referenced
inline void intrusive_ptr_add_ref(CVBF_Referenced* p) { p->ref(); }
inline void intrusive_ptr_release(CVBF_Referenced* p) { p->unref(); }
	

#endif
