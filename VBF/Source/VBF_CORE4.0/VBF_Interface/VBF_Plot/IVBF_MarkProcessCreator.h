//*******************************************************************
// FileName��IVBF_MarkProcessCreator.h
// Function����ͼʵ��ģ�����Դ����ӿ�
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_ENTITY_MODEL_PROCESS_CREATOR_H__
#define __IVBF_MARK_ENTITY_MODEL_PROCESS_CREATOR_H__


// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DPLOT_PROCESS_CREATOR[]				= "��ά��ͼģ�͹��̴����ӿ�";	

#include <VBF_Plot/IVBF_MarkProcess.h>

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkEntityModelProcessCreator
// �ӿ�������ʵ��ģ������
//--------------------------------------------------------------------
class IVBF_MarkProcessCreator 
{
public:
	virtual ~IVBF_MarkProcessCreator() {}

public:
    virtual IVBF_MarkProcess* CreateMarkProcess(const std::string& strProcessType)=0;
};


#endif 
