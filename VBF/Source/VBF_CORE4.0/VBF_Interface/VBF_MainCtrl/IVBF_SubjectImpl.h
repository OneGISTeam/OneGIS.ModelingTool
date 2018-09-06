//***************************************************************************************
// FileName：IVBF_SubjectImpl.h
// Function：被观察者实现
//           被观察者（Subject）接口。
// Author:   武玉国
// Date:     2018-2-22
//***************************************************************************************

#ifndef __IVBF_SUBJECT_IMPL_H__
#define __IVBF_SUBJECT_IMPL_H__

#include <VBF_MainCtrl/IVBF_Observer.h>
#include <VBF_MainCtrl/IVBF_Subject.h>
#include <vector>
#include <algorithm>
class IVBF_SubjectImpl : public IVBF_Subject
{
    typedef std::vector< IVBF_Observer*> CObserverList;
public:
    IVBF_SubjectImpl() { }
    virtual ~IVBF_SubjectImpl() {}

    //-----------------------------------------------------------------------------------
    // 函数：Attach()
    // 描述：添加一个事件观察者(IVBF_Subject中的纯虚函数)
    //-----------------------------------------------------------------------------------
    virtual void Attach(IVBF_Observer* pIObserver)
    {
        if(NULL==pIObserver) return;// 不允许添加空指针

        // 不允许重复添加
        CObserverList::iterator pIter = std::find(m_ObserverList.begin(), m_ObserverList.end(), pIObserver);
        if(pIter==m_ObserverList.end()) m_ObserverList.push_back(pIObserver);
    }

    //-----------------------------------------------------------------------------------
    // 函数：Detach()
    // 描述：释放一个事件观察者(IVBF_Subject中的纯虚函数)
    //-----------------------------------------------------------------------------------
    virtual void Detach(IVBF_Observer* pIObserver)
    {
        if(NULL==pIObserver) return;// 不允许空指针

        CObserverList::iterator pIter = std::find(m_ObserverList.begin(), m_ObserverList.end(), pIObserver);
        if(pIter!=m_ObserverList.end()) m_ObserverList.erase(pIter);
    }

    //-----------------------------------------------------------------------------------
    // 函数：DetachAll()
    // 描述：释放所有事件观察者(IVBF_Subject中的纯虚函数)
    //-----------------------------------------------------------------------------------
    virtual void DetachAll()
    {
        m_ObserverList.clear();
    }

    //-----------------------------------------------------------------------------------
    // 函数：Notify()
    // 描述：向所有事件观察者发送事件
    //-----------------------------------------------------------------------------------
    virtual void Notify(const char* szMessage, int nValue, void* pValue)
    {
        for(CObserverList::iterator pIter=m_ObserverList.begin(); pIter!=m_ObserverList.end(); pIter++)
        {
            IVBF_Observer* pIObserver = *pIter;
            if(pIObserver) pIObserver->OnEvent(szMessage, nValue, pValue);
        }
    }

private:
    CObserverList m_ObserverList; // 事件观察器列表
};

#endif
