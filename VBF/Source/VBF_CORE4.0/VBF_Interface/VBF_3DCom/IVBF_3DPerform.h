//***************************************************************************************
// FileName��IVBF_3DPerform.h
// Function����ά�ݲ����ƽӿڣ���Ҫ����
// Author:   
// Date:     2012-4-16
//***************************************************************************************
#ifndef __IVBF_3DPERFORM_H__
#define __IVBF_3DPERFORM_H__

// ����������ID��
const char VBF_COMPONENT_3DPERFORM[]			= "Component: 3DPerform";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DPERFORM[]			= "��ά�ݲ�����";

// ��������ID��
const char VBF_COMMAND_3DPERFORM_NEXT[]			= "Command: 3DPerform Next";			// ��һ��
const char VBF_COMMAND_3DPERFORM_PREV[]			= "Command: 3DPerform Prev";			// ��һ��
const char VBF_COMMAND_3DPERFORM_PLAY[]			= "Command: 3DPerform Play";			// ����
const char VBF_COMMAND_3DPERFORM_STOP[]		    = "Command: 3DPerform Stop";			// ֹͣ


class CVBF_Config;
class IVBF_3DPerform
{
public: 	
	virtual ~IVBF_3DPerform() {}

public:
	//��ȡҳ��
	virtual int GetPageCount()=0;

	//��ȡĳҳ������
	virtual	char* GetPageName(int nID)=0;
	
	//����ĳҳ
	virtual	void JumpToPage(int nPage)=0;

    virtual	bool SetConfigFileName(const char* szFn)=0;

    // ִ�нű�����
    virtual void ExecuteScript(const CVBF_Config&)=0;

    virtual void PPTControlSwitch()=0;

};

#endif





















