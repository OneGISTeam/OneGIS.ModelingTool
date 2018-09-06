//*******************************************************************
// FileName��IVBF_3DAction.h
// Function����ά��Ч����
// Author:   ��Ө
// Date:     2012-05-12
//*******************************************************************

#ifndef __IVBF_3DACTION_H__
#define __IVBF_3DACTION_H__


// ���������Ч����

// ��������
const char VBF_3D_ACTION_NULL[]			= "��������";

// ���붯��
const char VBF_3D_ACTION_FADEIN[]		= "����";
const char VBF_3D_ACTION_LEFTIN[]		= "����";
const char VBF_3D_ACTION_RIGHTIN[]		= "����";
const char VBF_3D_ACTION_UPIN[]			= "����";
const char VBF_3D_ACTION_DOWNIN[]		= "����";
const char VBF_3D_ACTION_SCALEIN[]		= "����";
const char VBF_3D_ACTION_EXPANDOUT[]	= "��չ����";

// �˳�����
const char VBF_3D_ACTION_FADEOUT[]		= "����";
const char VBF_3D_ACTION_LEFTOUT[]		= "���";
const char VBF_3D_ACTION_RIGHTOUT[]		= "�ҳ�";
const char VBF_3D_ACTION_UPOUT[]		= "�ϳ�";
const char VBF_3D_ACTION_DOWNOUT[]		= "�³�";
const char VBF_3D_ACTION_SCALEOUT[]		= "����";
const char VBF_3D_ACTION_EXPANDIN[]		= "��С����";

// ��������
const char VBF_3D_ACTION_SCALE[]		= "����";
const char VBF_3D_ACTION_TRANS[]		= "λ��";
const char VBF_3D_ACTION_FLICKER[]		= "��˸";


// �����ַ�������󳤶�
#define VBF_MAX_LENGTH_3DACTIONTYPE		64		// �������͵���󳤶�
#define VBF_MAX_LENGTH_3DACTIONTID		64		// ����ID�ŵ���󳤶�


class TiXmlElement;

class IVBF_3DAction
{
public:	
	virtual ~IVBF_3DAction() {}	

	// ��ȡ��Ч����
	virtual const char* GetType()=0;

	// ����/��ȡ��Ч��ȫ��ΨһID��
	virtual void        SetID(const char* szID)=0;
	virtual const char* GetID()=0;
	
	// �������ļ���װ����Ϣ
	virtual bool LoadFromXML(TiXmlElement* pElem)=0;
};

#endif 
