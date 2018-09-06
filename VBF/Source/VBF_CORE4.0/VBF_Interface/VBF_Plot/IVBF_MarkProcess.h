//*******************************************************************
// FileName��IVBF_MarkProcess.h
// Function����ͼʵ��ģ�͵Ĺ��̽ӿ�
// Author:
// Date:     2010-9-19
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_H__
#define __IVBF_MARK_PROCESS_H__

#include <VBF_Base/IVBF_SimulationTimer.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>

class IVBF_MarkModel;
class TiXmlElement;
class CVBF_Config;


class IVBF_MarkProcess : public osg::CVBF_Object
{
public:
	virtual ~IVBF_MarkProcess() {}

public:

    virtual void ReSet()=0;

    // ��ȡ��������
    virtual const std::string& GetType()=0;

    // ��ȡ���̵���������
    virtual const std::string& GetTypeDesc()=0;

    // ���ù������󶨵�ʵ��ģ��
    virtual void SetMarkModel(IVBF_MarkModel* pIMarkModel)=0;

    virtual void ProcessSimulate(IVBF_SimulationTimer* pSimulationTimer)=0; // ����ģ��

	//ͳ����ʼʱ��,Ϊ��ͳ������Ĺ��̵�ʱ�䣬��ͳ�ƾ���ʱ����ҽ�ͳ��ʱ�����Σ����ʱ��ʱ����0
	virtual void StatStartTime(double& dStartTime)=0;

    // ���л�
    virtual bool WriteToXML(TiXmlElement* pElemProc)=0;    // д�룺��ģ�͹�����Ϣд��ָ����xml�ڵ�
    virtual bool ReadFromXML(TiXmlElement* pElemProc)=0;   // ��ȡ����ָ����xml�ڵ��ȡģ�͹�����Ϣ

	// ִ��json�ű�
    virtual void ExecuteScript(const CVBF_Config& conf)=0;
};


#endif 
