//*******************************************************************
// FileName��IVBF_MarkInputHandlerCreator.h
// Function����ͼʵ��ģ�����봦���������ӿ�
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_INPUTHANDLERCREATOR_H__
#define __IVBF_MARK_INPUTHANDLERCREATOR_H__


// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DPLOT_INPUTHANDLER_CREATOR[]	= "��ά��ͼ���봦���������ӿ�";

#include "IVBF_MarkInputHandler.h"

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkInputHandlerCreator
// �ӿ�������ʵ��ģ�����봦���������ӿ�
//--------------------------------------------------------------------
class IVBF_MarkInputHandlerCreator
{
public:
    virtual ~IVBF_MarkInputHandlerCreator() {}

public:
    virtual IVBF_MarkInputHandler* CreateMarkInputHandler(unsigned int nType,const std::string& strCode)=0;
};


#endif 
