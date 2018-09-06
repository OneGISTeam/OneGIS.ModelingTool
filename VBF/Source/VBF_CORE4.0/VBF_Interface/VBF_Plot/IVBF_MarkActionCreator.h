//*******************************************************************
// FileName��IVBF_MarkActionCreator.h
// Function����ͼʵ��ģ����Ϊ�����ӿ�
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_ACTION_CREATOR_H__
#define __IVBF_MARK_ACTION_CREATOR_H__


// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DPLOT_ACTION_CREATOR[]	= "��ά��ͼģ����Ϊ�����ӿ�";

#include "IVBF_MarkAction.h"
#include <string>
//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkActionCreator
// �ӿ�������ʵ��ģ����Ϊ�����ӿ�
//--------------------------------------------------------------------
class IVBF_MarkActionCreator
{
public:
    virtual ~IVBF_MarkActionCreator() {}

public:
    virtual IVBF_MarkAction* CreateMarkAction(const std::string& strActionType)=0;
};


#endif 
