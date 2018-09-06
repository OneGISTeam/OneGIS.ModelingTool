//*******************************************************************
// FileName��IVBF_MarkModelCreator.h
// Function����ͼʵ��ģ�ʹ����ӿ�
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_CREATOR_H__
#define __IVBF_MARK_MODEL_CREATOR_H__

#include <VBF_Plot/IVBF_MarkModel.h>
#include <string>


// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DPLOT_MODEL_CREATOR[]	 = "��ά��ͼģ�ʹ����ӿ�";


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelCreator
// �ӿ�������ʵ��ģ�ʹ�����
//--------------------------------------------------------------------
class IVBF_MarkModelCreator
{
public:
	virtual ~IVBF_MarkModelCreator() {}

public:
	virtual IVBF_MarkModel* CreateMarkModel(unsigned int nMarkType, const std::string& strMarkID)=0;
};


#endif 
