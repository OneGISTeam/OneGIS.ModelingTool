//*******************************************************************
// FileName��IVBF_MarkAttrLifeTime.h
// Function��ģ�����Խӿڣ�������
// Author:   ��Ө
// Date:     2015-04-14
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_LIFETIME_H__
#define __IVBF_MARK_ATTR_LIFETIME_H__


#include <VBF_Plot/IVBF_MarkAttr.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkAttrLifeTime
// �ӿ�������ģ�����Խӿڣ�������
//--------------------------------------------------------------------
class IVBF_MarkAttrLifeTime : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrLifeTime() {}

	// ���������ڣ���λ���룩
	virtual void   SetLifeTime(double dTime)=0;
	virtual double GetLifeTime()=0;
};



#endif 
