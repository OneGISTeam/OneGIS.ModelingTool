//***************************************************************************************
// FileName��IVBF_SubjectImpl.h
// Function�����۲���ʵ��
//           ���۲��ߣ�Subject���ӿڡ�
// Author:   �����
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
    // ������Attach()
    // ���������һ���¼��۲���(IVBF_Subject�еĴ��麯��)
    //-----------------------------------------------------------------------------------
    virtual void Attach(IVBF_Observer* pIObserver)
    {
        if(NULL==pIObserver) return;// ��������ӿ�ָ��

        // �������ظ����
        CObserverList::iterator pIter = std::find(m_ObserverList.begin(), m_ObserverList.end(), pIObserver);
        if(pIter==m_ObserverList.end()) m_ObserverList.push_back(pIObserver);
    }

    //-----------------------------------------------------------------------------------
    // ������Detach()
    // �������ͷ�һ���¼��۲���(IVBF_Subject�еĴ��麯��)
    //-----------------------------------------------------------------------------------
    virtual void Detach(IVBF_Observer* pIObserver)
    {
        if(NULL==pIObserver) return;// �������ָ��

        CObserverList::iterator pIter = std::find(m_ObserverList.begin(), m_ObserverList.end(), pIObserver);
        if(pIter!=m_ObserverList.end()) m_ObserverList.erase(pIter);
    }

    //-----------------------------------------------------------------------------------
    // ������DetachAll()
    // �������ͷ������¼��۲���(IVBF_Subject�еĴ��麯��)
    //-----------------------------------------------------------------------------------
    virtual void DetachAll()
    {
        m_ObserverList.clear();
    }

    //-----------------------------------------------------------------------------------
    // ������Notify()
    // �������������¼��۲��߷����¼�
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
    CObserverList m_ObserverList; // �¼��۲����б�
};

#endif
