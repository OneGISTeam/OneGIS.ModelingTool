//***************************************************************************************
// FileName��IVBF_3DDBProviderMeta.h
// Function�����������ṩ��Ԫ���ݽӿ�
//           ÿ�����������ṩ�߶�Ҫʵ�ָýӿڣ�������ѡ��URL�Ĺ���
// Author:   κ��
// Date:     2011-10-19
//***************************************************************************************

#ifndef __IVBF_3DDBPROVDIER_META_H__
#define __IVBF_3DDBPROVDIER_META_H__

#include "VBF_3DTransModel/VBF_3DTransBlkDataTypes.h"

class IVBF_3DDBProviderMeta
{
public:
	virtual ~IVBF_3DDBProviderMeta() {}

public:	

 	// ��ʼ��/�ͷŲ��
 	virtual void Init()=0;
 	virtual void Release()=0;	
	
	// ���ܣ���ȡ��Meta����Ӧ��ProviderID
	virtual const char* GetProviderID()=0;

	// ���ܣ���ȡ��Meta����Ӧ��Provider��������Ϣ
	virtual const char* GetDesc()=0;

	// ���ܣ���URL����Ի���
	// ������pParentHWnd -- ����Ի��򸸴��ڵľ�������ΪNULL����û�и�����
	//		 nType       -- ��Ҫ�������������
	//       szURL       -- ���ص�URL
	// ���أ�����û�����ȷ�ϼ�������ֵΪtrue������Ϊfalse
	virtual bool  BrowseURL(HWND pParentHWnd, VBF_BLK_TYPE nType, char* szURL)=0;
};


#endif

