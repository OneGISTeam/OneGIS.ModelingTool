//*******************************************************************
// FileName��IVBF_MarkAttrCreator.h
// Function����ͼʵ��ģ�����Դ����ӿ�
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_CREATOR_H__
#define __IVBF_MARK_ATTR_CREATOR_H__


// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DPLOT_ATTR_CREATOR[]	= "��ά��ͼģ�����Դ����ӿ�";	

#include "IVBF_MarkAttr.h"

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkAttrCreator
// �ӿ�������ʵ��ģ�����Դ����ӿ�
//--------------------------------------------------------------------
class IVBF_MarkAttrCreator 
{
public:
	virtual ~IVBF_MarkAttrCreator() {}

public:
	virtual IVBF_MarkAttr* CreateMarkAttr(unsigned int nAttrType)=0;
};


#endif 
