//*******************************************************************
// FileName：IVBF_MarkProcessDepart.h
// Function：飞行过程
// Author:   武玉国
// Date:     2010-9-20
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_DEPART_H__
#define __IVBF_MARK_PROCESS_DEPART_H__

#include <VBF_Plot/IVBF_MarkProTimerTrigger.h>

#define VBF_MARK_PROCESS_DEPART      "Depart"       // 分离

class IVBF_MarkProcessDepart : public IVBF_MarkProTimerTrigger
{
protected:
    virtual ~IVBF_MarkProcessDepart() {}

	// 设置/获取需要分离的子节点序号
	virtual void SetDepartChildNo(int nChildNo)=0;
	virtual int  GetDepartChildNo()=0;
};


#endif 
