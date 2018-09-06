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

// ��֤��̬��ʼ��˳����ȷ�ĸ���ģ����
template <typename T, T M()>
struct depends_on
{
    depends_on() { M(); }
};

// ��Ҫ���ü�������Ļ��࣬�������߳̽�����ء�
// ע��ʹ��ʱ������ӱ���̳м��ɣ���������Ҫ���ñ���ĺ�������ʹ������ָ���Զ��������ü����Ĺ���
class VBF_BASE_EXPORT CVBF_Referenced
{
    public:
	    CVBF_Referenced();        
        explicit CVBF_Referenced(bool threadSafeRefUnref); 
        CVBF_Referenced(const CVBF_Referenced&);
        CVBF_Referenced& operator = (const CVBF_Referenced&);

        // ����/��ȡ�Ƿ�ʹ��mutexȷ��ref()��unref()���̰߳�ȫ�ԡ�
        virtual void setThreadSafeRefUnref(bool threadSafe);
		bool getThreadSafeRefUnref() const ;

        // ��ȡ���ڱ�֤ref()/unref()�̰߳�ȫ�Ե�mutex
        OpenThreads::Mutex* getRefMutex() const;

		// ��ȡ��ѡ��ȫ��Referenced���������û��������������е�Referenced����֮�乲��
        static OpenThreads::Mutex* getGlobalReferencedMutex();

        // ����һ�����ü�������������ָ�������ñ�����
        int ref() const;
        
        // ����һ�����ü�����������ü�����Ϊ0, �����ö����ٱ����ã��Զ�ɾ���ö���
        int unref() const;
        
        // ����һ�����ü�����������β�ɾ������ʹ���ü�����Ϊ0����
        //!!!���ʹ��unref()��������˺������˺������ܵ����ڴ�й©����ʱ�����������ȷ֪��˭����ɾ��
        int unref_nodelete() const;
        
        // ���ض���ı����ô�����
        int referenceCount() const;

		//---���²�������������ָ�룬��this��ɾ��ʱ��Ҫ֪ͨ��������this�Ķ���this�Ĺ۲��ߣ����۲��߿����Ƕ������ObserverSet��

        // ��ȡ�۲��ߵļ��ϣ����û�����÷���NULL
        ObserverSet* getObserverSet() const;

        // ��ȡ�۲��ߵļ��ϣ����û�������򴴽�һ��
        ObserverSet* getOrCreateObserverSet() const;

        // ���/�Ƴ�һ���۲��ߣ�������۲��߼����л�Ӽ������Ƴ�
        void addObserver(DeleteObserver* observer) const;
        void removeObserver(DeleteObserver* observer) const;

        // �Ƿ�ʹ�û�����ʵ���̰߳�ȫ�����ü���
        static void setThreadSafeReferenceCounting(bool enableThreadSafeReferenceCounting);
        static bool getThreadSafeReferenceCounting();

        friend class DeleteHandler;

        // ����/��ȡ�ӳ�ɾ��������
        static void setDeleteHandler(DeleteHandler* handler);
        static DeleteHandler* getDeleteHandler();

    protected:
        virtual ~CVBF_Referenced();

		// ֪ͨ�۲���this��ɾ����ɾ��this�������ǽ�֪ͨ��Ҳ�����ǽ�ɾ������֪ͨ��ɾ����
        void signalObserversAndDelete(bool signalDelete, bool doDelete) const;
        void deleteUsingDeleteHandler() const; // ʹ���ӳ�ɾ��������ɾ��


#if defined(_OSG_REFERENCED_USE_ATOMIC_OPERATIONS)
        mutable OpenThreads::AtomicPtr  _observerSet;	// �۲��ߵļ���
        mutable OpenThreads::Atomic     _refCount;		// ���õ�����
#else
        
        mutable OpenThreads::Mutex*     _refMutex;    // �����������ڱ�֤�̰߳�ȫ
        mutable int                     _refCount;    // ���õ�����     
        mutable void*                   _observerSet; // �۲��ߵļ���
#endif
};



// ���º�����Ϊ��boost::intrusive_ptrʹ��Referenced
inline void intrusive_ptr_add_ref(CVBF_Referenced* p) { p->ref(); }
inline void intrusive_ptr_release(CVBF_Referenced* p) { p->unref(); }
	

#endif
