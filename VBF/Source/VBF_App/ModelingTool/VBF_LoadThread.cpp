//#include "stdafx.h"
#include "VBF_LoadThread.h"
#include <OpenThreads/ScopedLock>
#include <string>
#include "VBF_GlobalGIS_Plot.h"


CVBF_LoadThread::CVBF_LoadThread()
{
    m_bDone    = false;
    m_nSizeSub = 1000;

    // 打开数据文件
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

    // 数据读取完毕
    if(m_fp!=NULL) fclose(m_fp);
    m_bDone = true;

    OpenThreads::Thread::YieldCurrentThread();
}

// 读取态势文件中的下一个模型数据
void CVBF_LoadThread::LoadNextMark()
{
    VBF_SITUDATA Data;
    Data.Read(m_fp);

    // 线程保护
    OpenThreads::ScopedLock<OpenThreads::Mutex> lock(m_mutex);

    m_vDataCurr.push_back(Data);

    // 判断是否形成一个新的分段，避免一个list过大
    if(m_vDataCurr.size() >= m_nSizeSub)
    {
        m_vDataPrev.push_back(m_vDataCurr);
        m_vDataCurr.clear();
    }
}

//-----------------------------------------------------------------------------
// 函数：GetNextData()
// 描述：获取下一个读取的数据
//-----------------------------------------------------------------------------
bool CVBF_LoadThread::GetNextData(VBF_SITUDATA& data)
{
    // 注意：线程保护
    OpenThreads::ScopedLock<OpenThreads::Mutex> lock(m_mutex);

    CSubList* pSubData = NULL;

    // 先查找以前读取的数据
    if( m_vDataPrev.size() > 0 )
    {
        CSubList& sub = m_vDataPrev.front();
        pSubData = &sub;
    }
    else  // 再查找当前正在读取的数据
    {
        pSubData = &m_vDataCurr;
    }

    if(pSubData!=NULL && pSubData->size()>0)
    {
        data = pSubData->front();
        pSubData->pop_front();
        return true;
    }

    // 删除已经为空的分段list
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
