//***************************************************************************************
// FileName��IVBF_Observer.h
// Function���۲��߽ӿ�
//           Observerģʽ�еĹ۲��ߣ�Observer���ӿڡ�
// Author:   �����
// Date:     2006-4-22
//***************************************************************************************

#ifndef __IVBF_OBSERVER_REF_H__
#define __IVBF_OBSERVER_REF_H__

#include <VBF_Base/VBF_Referenced.h>
class IVBF_ObserverRef : public CVBF_Referenced
{
public:
    virtual ~IVBF_ObserverRef() {}

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
