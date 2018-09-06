//*******************************************************************
// FileName��IVBF_MarkProcessDepart.h
// Function�����й���
// Author:   �����
// Date:     2010-9-20
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_DEPART_H__
#define __IVBF_MARK_PROCESS_DEPART_H__

#include <VBF_Plot/IVBF_MarkProTimerTrigger.h>

#define VBF_MARK_PROCESS_DEPART      "Depart"       // ����

class IVBF_MarkProcessDepart : public IVBF_MarkProTimerTrigger
{
protected:
    virtual ~IVBF_MarkProcessDepart() {}

	// ����/��ȡ��Ҫ������ӽڵ����
	virtual void SetDepartChildNo(int nChildNo)=0;
	virtual int  GetDepartChildNo()=0;
};


#endif 
