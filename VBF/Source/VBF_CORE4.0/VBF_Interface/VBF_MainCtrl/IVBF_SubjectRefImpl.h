//***************************************************************************************
// FileName：IVBF_SubjectRefImpl.h
// Function：被观察者实现
//           Observer模式中的 被观察者（Subject）接口。
// Author:   武玉国
// Date:     2006-4-22
//***************************************************************************************

#ifndef __IVBF_SUBJECT_REF_IMPL_H__
#define __IVBF_SUBJECT_REF_IMPL_H__

#include <VBF_MainCtrl/IVBF_SubjectRef.h>
#include <VBF_MainCtrl/IVBF_ObserverRef.h>


class IVBF_SubjectRefImpl : public IVBF_SubjectRef
{
public:
    IVBF_SubjectRefImpl() { }
    virtual ~IVBF_SubjectRefImpl() {}

    virtual void Attach(IVBF_ObserverRef* pIObserver)
    {
        CVBF_ObserverVector::iterator itr;
        for(itr=m_vObservers.begin();itr!=m_vObservers.end();itr++)
        {
            observer_ptr<IVBF_ObserverRef>& opObserver = *itr;
            if(opObserver.valid()==false) continue;
            if(opObserver.get() == pIObserver) return;
        }

        m_vObservers.push_back(pIObserver);
    }
    virtual void Detach(IVBF_ObserverRef* pIObserver)
    {
        CVBF_ObserverVector::iterator itr;
        for(itr=m_vObservers.begin();itr!=m_vObservers.end();itr++)
        {
            observer_ptr<IVBF_ObserverRef>& opObserver = *itr;
            if(opObserver.valid()==false) continue;
            if(opObserver.get() == pIObserver)
            {
                m_vObservers.erase(itr);
                return;
            }
        }
    }
    virtual void DetachAll()
    {
        m_vObservers.clear();
    }

    virtual void Notify(const char* szMessage, int nValue=0, void* pValue=NULL)
    {
        CVBF_ObserverVector::iterator itr;
        for(itr=m_vObservers.begin();itr!=m_vObservers.end();itr++)
        {
            observer_ptr<IVBF_ObserverRef>& opObserver = *itr;
            if(opObserver.valid()==false) continue;
            opObserver->OnEvent(szMessage, nValue,pValue);
        }
    }

    typedef std::vector< observer_ptr<IVBF_ObserverRef> > CVBF_ObserverVector;
    CVBF_ObserverVector  m_vObservers;
};

#endif
