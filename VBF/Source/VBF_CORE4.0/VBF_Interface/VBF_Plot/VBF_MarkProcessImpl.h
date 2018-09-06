//*******************************************************************
// FileName��CVBF_MarkProcessImpl.h
// Function����ͼʵ��ģ�͹��̽ӿ�ʵ��
// Author:
// Date:     
//*******************************************************************

#ifndef __VBF_MARK_PROCESS_IMPL_H__
#define __VBF_MARK_PROCESS_IMPL_H__

#include <VBF_Base/observer_ptr>
#include "VBF_Plot/IVBF_MarkModel.h"
#include <VBF_Plot/IVBF_MarkProcess.h>
#include <VBF_Aux/VBF_GLAux/VBF_ReadWriteUtils.h>
#include <VBF_Aux/VBF_GLAux/VBF_JsonReader.h>


//--------------------------------------------------------------------
// ����ӿڣ�CVBF_MarkProcessImpl
// �ӿ���������ͼ���̵�ʵ��
//--------------------------------------------------------------------
template<class T>
class CVBF_MarkProcessImpl : public T
{
public:
    CVBF_MarkProcessImpl(const std::string& strType);
    CVBF_MarkProcessImpl(const CVBF_MarkProcessImpl& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}

    virtual ~CVBF_MarkProcessImpl();

public:
    virtual void ReSet() { m_bExecuted = false; }

    // ����
    virtual IVBF_MarkProcess* Clone() { return NULL; }

    // ��ȡ���̵�����
    virtual const std::string& GetType()	{ return m_strType; }

    // ��ȡ���̵���������
    virtual const std::string& GetTypeDesc()	{ return m_strTypeDesc; }

    // ���ù������󶨵�ʵ��ģ��
    virtual void SetMarkModel(IVBF_MarkModel* pIMarkModel) { m_opIMarkModel = pIMarkModel; }

    // �������ݵı������ȡ (�����Ƹ�ʽ)���Ա�ʵ�ֳ����ļ�¼�벥��
    virtual void ProcessSimulate(IVBF_SimulationTimer* pSimulationTimer)=0; // ����ģ��
    virtual void StatStartTime(double& dStartTime) { }

    // ���л�
    virtual bool WriteToXML(TiXmlElement* pElemProc);
    virtual bool ReadFromXML(TiXmlElement* pElemProc);

	// ִ��json�ű�
    virtual void ExecuteScript(const CVBF_Config& conf);

protected:
    std::string  	m_strType;            // �ù��̵�����
    std::string     m_strTypeDesc;      // �ù��̵���������
    bool            m_bExecuted;		// �Ƿ��ѱ�ִ��

    // �ù��̶�Ӧ�ľ���ʵ��ģ��
    observer_ptr<IVBF_MarkModel> m_opIMarkModel;
};


//-----------------------------------------------------------------------------
// ������CVBF_MarkProcessImpl()
// ���������캯��
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkProcessImpl<T>::CVBF_MarkProcessImpl(const std::string& strType)
{
    m_strType       = strType;
    m_strTypeDesc   = "";
    m_bExecuted     = false;
}


//-----------------------------------------------------------------------------
// ������~CVBF_MarkProcessImpl()
// ��������������
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkProcessImpl<T>::~CVBF_MarkProcessImpl()
{
}

//-----------------------------------------------------------------------------
// ������WriteToXML()
// ���������л�����������Ϣд��ָ����xml�ڵ�
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkProcessImpl<T>::WriteToXML(TiXmlElement* pElemProc)
{
    if(NULL==pElemProc) return false;

    // д�룺���
    ::VBF_SetAttribute(pElemProc, "Type",     m_strType);
    ::VBF_SetAttribute(pElemProc, "TypeDesc", m_strTypeDesc);

    return true;
}

//----------------------------------------------------------------------------
// ������ReadFromXML()
// ���������л�����ָ����xml�ڵ��ȡ������Ϣ
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkProcessImpl<T>::ReadFromXML(TiXmlElement* pElemProc)
{
    if(NULL==pElemProc) return false;

    return true;
}

//----------------------------------------------------------------------------
// ������ExecuteScript()
// ������ִ��json�ű�
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkProcessImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
}

#endif 
