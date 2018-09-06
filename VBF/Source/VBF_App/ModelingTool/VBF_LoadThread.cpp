//#include "stdafx.h"
#include "VBF_LoadThread.h"
#include <OpenThreads/ScopedLock>
#include <string>
#include "VBF_GlobalGIS_Plot.h"


CVBF_LoadThread::CVBF_LoadThread()
{
    m_bDone    = false;
    m_nSizeSub = 1000;

    // �������ļ�
    std::string strFn = g_sDataPath + "/Situation.data";
    m_fp = fopen(strFn.c_str(), "rb");

    if(NULL==m_fp) m_bDone = true;
}

void CVBF_LoadThread::run()
{
    while(!testCancel() && !m_bDone && m_fp!=NULL && !feof(m_fp))
    {
        LoadNextMark();
    }

    // ���ݶ�ȡ���
    if(m_fp!=NULL) fclose(m_fp);
    m_bDone = true;

    OpenThreads::Thread::YieldCurrentThread();
}

// ��ȡ̬���ļ��е���һ��ģ������
void CVBF_LoadThread::LoadNextMark()
{
    VBF_SITUDATA Data;
    Data.Read(m_fp);

    // �̱߳���
    OpenThreads::ScopedLock<OpenThreads::Mutex> lock(m_mutex);

    m_vDataCurr.push_back(Data);

    // �ж��Ƿ��γ�һ���µķֶΣ�����һ��list����
    if(m_vDataCurr.size() >= m_nSizeSub)
    {
        m_vDataPrev.push_back(m_vDataCurr);
        m_vDataCurr.clear();
    }
}

//-----------------------------------------------------------------------------
// ������GetNextData()
// ��������ȡ��һ����ȡ������
//-----------------------------------------------------------------------------
bool CVBF_LoadThread::GetNextData(VBF_SITUDATA& data)
{
    // ע�⣺�̱߳���
    OpenThreads::ScopedLock<OpenThreads::Mutex> lock(m_mutex);

    CSubList* pSubData = NULL;

    // �Ȳ�����ǰ��ȡ������
    if( m_vDataPrev.size() > 0 )
    {
        CSubList& sub = m_vDataPrev.front();
        pSubData = &sub;
    }
    else  // �ٲ��ҵ�ǰ���ڶ�ȡ������
    {
        pSubData = &m_vDataCurr;
    }

    if(pSubData!=NULL && pSubData->size()>0)
    {
        data = pSubData->front();
        pSubData->pop_front();
        return true;
    }

    // ɾ���Ѿ�Ϊ�յķֶ�list
    while( m_vDataPrev.size()>0 )
    {
        CSubList& sub = m_vDataPrev.front();
        if(sub.size()==0)
            m_vDataPrev.pop_front();
        else
            break;
    }

    return false;
}
