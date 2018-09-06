//***************************************************************************************
// FileName��IVBF_3DDBProvider.h
// Function�����������ṩ�߽ӿ�
//           ÿ����Ҫע�ᵽ��������ĵ��������ṩ�߶�Ҫʵ�ָýӿ�
// Author:   ������
// Date:     2010-7-23
//***************************************************************************************

#ifndef __IVBF_3DDB_PROVIDER_H__
#define __IVBF_3DDB_PROVIDER_H__

#include "VBF_DB\\VBF_3DTransModel\\VBF_3DTransBlkDem.h"
#include "VBF_DB\\VBF_3DTransModel\\VBF_3DTransBlkTex.h"
#include "VBF_DB\\VBF_3DTransModel\\VBF_3DTransBlkNote.h"
#include "VBF_DB\\VBF_3DTransModel\\VBF_3DDataSetTypes.h"

class IVBF_3DDBProvider
{
public:
	virtual ~IVBF_3DDBProvider() {}

public:	

 	// ��ʼ��/�ͷŲ��
 	virtual void Init(void* pParam=NULL)=0;
 	virtual void Release()=0;	
	
	/* ���ܣ�װ�ص������ݽ���ģ��
       ������bFromLowerΪ�Ƿ���ϲ�����ǿ������
       ���أ��ɹ�����true�����򷵻�false
	*/
	virtual bool  LoadBlkDem(VBF_3DDATASETDEM* pDS,   CVBF_TransBlkDem* pTransBlkDem, bool bFromLower=false)=0;
	virtual bool  LoadBlkTex(VBF_3DDATASETTEX* pDS,   CVBF_TransBlkTex* pTransBlkTex, bool bFromLower=false )=0;
	virtual bool  LoadBlkNote(VBF_3DDATASETNOTE* pDS, CVBF_TransBlkNote* pTransBlkNote, bool bFromLower=false)=0;

	// ���ݵ������꣬���Ҵ������ݵ���󼶱�
	virtual int   GetMaxLodOfDataSetTex(VBF_3DDATASETTEX* pDS, double L, double B)=0;
};


#endif

