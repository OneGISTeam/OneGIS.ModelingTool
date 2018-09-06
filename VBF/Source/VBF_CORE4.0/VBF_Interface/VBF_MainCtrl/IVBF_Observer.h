//***************************************************************************************
// FileName��IVBF_Observer.h
// Function���۲��߽ӿ�
//           Observerģʽ�еĹ۲��ߣ�Observer���ӿڡ�
// Author:   �����
// Date:     2006-4-22
//***************************************************************************************

#ifndef __IVBF_OBSERVER_H__
#define __IVBF_OBSERVER_H__


class IVBF_Observer
{
public:
	virtual ~IVBF_Observer() {}

public:

	//----------------------------------------------------------------
    // ��Ϣ��Ӧ����
	// ��Ӧ��Ϣ������ʵ�ʴ���
	// szMessage�������͵���Ϣ
	// nValue����Ϣ����������
	// pValue����Ϣ��ָ�����
	//----------------------------------------------------------------
    virtual void OnEvent(const char* szMessage, int nValue=0, void* pValue=NULL) = 0;
};


#endif
