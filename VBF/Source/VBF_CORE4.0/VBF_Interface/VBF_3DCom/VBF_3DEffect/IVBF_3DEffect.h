//*******************************************************************
// FileName��IVBF_3DEffect.h
// Function����ά��Ч�ӿ�
// Author:   SunC
// Date:     2012-04-12
//*******************************************************************

#ifndef __IVBF_3DEFFECT_H__
#define __IVBF_3DEFFECT_H__


// ������Ч����
const char VBF_3DEFFECT_UNKNOWN[]		= "Unknown";
const char VBF_3DEFFECT_IMAGE2D[]		= "Image2D";
const char VBF_3DEFFECT_IMAGE3D[]		= "Image3D";
const char VBF_3DEFFECT_MASK[]			= "Mask";
const char VBF_3DEFFECT_MASKIMAGE[]		= "MaskImage";
const char VBF_3DEFFECT_VIDEO[]			= "Video";
const char VBF_3DEFFECT_AUDIO[]			= "Audio";

// ���������Ч����

// ��������
const char VBF_3DEFFECT_ACTION_NULL[]		= "��������";

// ���붯��
const char VBF_3DEFFECT_ACTION_FADEIN[]		= "����";
const char VBF_3DEFFECT_ACTION_LEFTIN[]		= "����";
const char VBF_3DEFFECT_ACTION_RIGHTIN[]	= "����";
const char VBF_3DEFFECT_ACTION_UPIN[]		= "����";
const char VBF_3DEFFECT_ACTION_DOWNIN[]		= "����";
const char VBF_3DEFFECT_ACTION_SCALEIN[]	= "����";
const char VBF_3DEFFECT_ACTION_EXPANDOUT[]	= "��չ����";

// �˳�����
const char VBF_3DEFFECT_ACTION_FADEOUT[]	= "����";
const char VBF_3DEFFECT_ACTION_LEFTOUT[]	= "���";
const char VBF_3DEFFECT_ACTION_RIGHTOUT[]	= "�ҳ�";
const char VBF_3DEFFECT_ACTION_UPOUT[]		= "�ϳ�";
const char VBF_3DEFFECT_ACTION_DOWNOUT[]	= "�³�";
const char VBF_3DEFFECT_ACTION_SCALEOUT[]	= "����";
const char VBF_3DEFFECT_ACTION_EXPANDIN[]	= "��С����";

// ��������
const char VBF_3DEFFECT_ACTION_SCALE[]		= "����";
const char VBF_3DEFFECT_ACTION_TRANS[]		= "λ��";
const char VBF_3DEFFECT_ACTION_FLICKER[]	= "��˸";


// �����ַ�������󳤶�
#define VBF_MAX_LENGTH_3DEFFECTTYPE		64		// ��Ч���͵���󳤶�
#define VBF_MAX_LENGTH_3DEFFECTID		64		// ��ЧID�ŵ���󳤶�


class TiXmlElement;

class IVBF_3DEffect
{
public:	
	virtual ~IVBF_3DEffect() {}	

	// ��ȡ��Ч����
	virtual const char* GetType()=0;

	// ����/��ȡ��Ч��ȫ��ΨһID��
	virtual void        SetID(const char* szID)=0;
	virtual const char* GetID()=0;

	// ����/��ȡ��Чͼ��/��Ƶ�ļ��ĸ�·��
	virtual void		SetFilePath(const char* szPath)=0;
	virtual const char*	GetFilePath()=0;

	// �������ļ���װ����Ч�������Ϣ
	virtual bool LoadFromXML(TiXmlElement* pElemEffect)=0;

	// ִ����Ч����Ķ��������������Ӵ������ļ�Ԫ���л�ȡ
	virtual bool StartFromXML(TiXmlElement* pElemAction)=0;
};

#endif 
