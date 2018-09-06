//***************************************************************************************
// FileName��IVBF_3DNet.h
// Function����ά��ʾ���ƽӿڣ���Ҫ���ڻ�ȡ����ʾ�����йص���Ϣ�ͶԳ������п���
// Author: 
// Date:     2006-4-22
//***************************************************************************************

#ifndef __IVBF_3DNET_H__
#define __IVBF_3DNET_H__


// ����������ID��
const char VBF_COMPONENT_3DNET[]			= "Component: 3DNet";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DNET[]			= "��ά����ӿ�";

// ������ϢID��

// ��������ID��
const char VBF_COMMAND_3DNET_CLIENTINFO[]	= "�ͻ�����Ϣ";

class IVBF_3DNet
{
public: 	
	virtual ~IVBF_3DNet() {}

public:

	// ����������Ϣ
	virtual void   SetNumClientRows(int nRows)=0;
	virtual void   SetNumClientCols(int nCols)=0;	
	virtual void   SetClientResH(int nResH)=0;
	virtual void   SetClientResV(int nResV)=0;

	// ��ȡ������Ϣ
	virtual int   GetNumClientRows()=0;
	virtual int   GetNumClientCols()=0;
	virtual int   GetClientResH()=0;
	virtual int	  GetClientResV()=0;
	virtual int   GetClientRowNo()=0;
	virtual int   GetClientColNo()=0;

	// �Ƿ��ڵȴ��ͻ��˽�����Ⱦ
	virtual bool  IsWaitingForClient()=0;
};

#endif





















