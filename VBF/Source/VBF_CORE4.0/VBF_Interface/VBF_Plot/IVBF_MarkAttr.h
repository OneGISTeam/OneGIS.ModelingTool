//*******************************************************************
// FileName��IVBF_MarkAttr.h
// Function����ͼʵ��ģ�����Խӿ�
// Author:
// Date:     2009-4-10
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_H__
#define __IVBF_MARK_ATTR_H__

#include <vector>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Plot/IVBF_MarkStyleManager.h>


const unsigned int VBF_MARK_ATTR_UNKNOWN			= 0;	// δ֪����
const unsigned int VBF_MARK_ATTR_HINTLINE			= 1;	// �߶���
const unsigned int VBF_MARK_ATTR_TRAILLINE			= 2;	// �켣�ߣ������Σ�
const unsigned int VBF_MARK_ATTR_TRAILSTRIP			= 3;	// �켣�ߣ������Σ�
const unsigned int VBF_MARK_ATTR_LABEL				= 4;	// ������ǩ
const unsigned int VBF_MARK_ATTR_LABEL_CHAINED		= 5;	// ɢ��ʽ��ǩ
const unsigned int VBF_MARK_ATTR_INFO				= 6;	// ��Ϣ
const unsigned int VBF_MARK_ATTR_AUTOFLY			= 7;	// �Զ����У�������
const unsigned int VBF_MARK_ATTR_LIFETIME			= 8;	// ������
const unsigned int VBF_MARK_ATTR_STATE				= 9;	// ״̬
const unsigned int VBF_MARK_ATTR_TAILFLAME			= 10;	// β��
const unsigned int VBF_MARK_ATTR_BATTLETASK			= 11;	// ��ս����
const unsigned int VBF_MARK_ATTR_POWERMAP			= 12;	// ����ͼ
const unsigned int VBF_MARK_ATTR_AIRLINE			= 13;	// �����뺽�չܵ�
const unsigned int VBF_MARK_ATTR_SOUND				= 14;	// ��Ч
const unsigned int VBF_MARK_ATTR_EXPLOSION			= 15;	// ��ը
const unsigned int VBF_MARK_ATTR_SMOKE				= 16;	// ��Ч���̻�
const unsigned int VBF_MARK_ATTR_MISSILEFIRE		= 17;	// ��Ч������β��
const unsigned int VBF_MARK_ATTR_SHIPTRAIL			= 18;	// ��Ч����������
const unsigned int VBF_MARK_ATTR_ROTATEX 		    = 19;	// ��X����ת
const unsigned int VBF_MARK_ATTR_ROTATEY 		    = 20;	// ��Y����ת
const unsigned int VBF_MARK_ATTR_ROTATEZ 		    = 21;	// ��Z����ת
const unsigned int VBF_MARK_ATTR_DETECTED 		    = 22;	// ��̽��
const unsigned int VBF_MARK_ATTR_IFF				= 23;	// ��������硰�ҷ��������з�����
const unsigned int VBF_MARK_ATTR_INTERSECT			= 24;	// ģ�������Ľ���
const unsigned int VBF_MARK_ATTR_SPHEREATTITUDE		= 25;	// ģ�͵���̬��
const unsigned int VBF_MARK_ATTR_MISSILEFIRE_GROUP	= 26;	// ��Ч������β����
const unsigned int VBF_MARK_ATTR_TRAILSMOKE			= 27;	// ��Ч���켣�ߣ�����״��ʹ������ϵͳʵ�֣�
const unsigned int VBF_MARK_ATTR_COORDSYS			= 28;	// �ֲ�����ϵ��������ʾ��״ģ�͵ľֲ�����ϵ��
const unsigned int VBF_MARK_ATTR_WEBVIEW            = 29;	// ���ڱ�ǩ


class IVBF_MarkModel;
class TiXmlElement;
class IVBF_PropertySet;
class CVBF_PopupMenuItem;
class IVBF_MarkContext;
class CVBF_Config;


class IVBF_MarkAttr : public osg::CVBF_Object
{
public:
	virtual ~IVBF_MarkAttr() {}

public:

	// ��ȡ��������
	virtual unsigned int GetType()=0;

	// ��ȡ�������͵��������Ա��û����
	virtual const std::string& GetTypeDesc()=0;

	// ����/��ȡ�ɼ���
	virtual void SetVisible(bool bVisible)=0;
	virtual bool IsVisible()=0;

	// ����/��ȡ�������󶨵�ʵ��ģ��
	virtual void SetMarkModel(IVBF_MarkModel* pIMark)=0;
	virtual IVBF_MarkModel* GetMarkModel()=0;

	// ����/��ȡ������С���ɼ����룬���û�����ã�Ĭ��ʹ���������󶨵�ʵ��ģ�͵Ŀɼ�����
	// �����ȡ�ķ���ֵΪfalse����ʾ�û�û���������Ե���С���ɼ�����
	virtual void SetDistMin(float fDistMin)=0;
	virtual bool GetDistMin(float& fDistMin)=0;

	virtual void SetDistMax(float fDistMax)=0;
	virtual bool GetDistMax(float& fDistMax)=0;

	// ����
	virtual IVBF_MarkAttr* Clone()=0;

	// �������Բ����б�
	virtual bool ExecuteCommand(const char* szCommandID, IVBF_PropertySet* pInParam, IVBF_PropertySet* pOutParam)=0;

    // �Ҽ������˵�
    virtual void GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems)=0;
    virtual bool ProcessPopupMenuItem(unsigned int nID)=0;

    // ���л�
    virtual bool WriteToXML(TiXmlElement* pElemAttr)=0;    // д�룺��ģ��������Ϣд��ָ����xml�ڵ�
    virtual bool ReadFromXML(TiXmlElement* pElemAttr)=0;   // ��ȡ����ָ����xml�ڵ��ȡģ��������Ϣ

	// ��ʼ�� (�ڹ��캯��֮����ϵͳ����)
    virtual bool Init(IVBF_MarkContext* pIContext)=0;

	// ���� (��ÿ֡����ǰ��ϵͳ����)������ֵΪfalse��ʾδ�����´�����ģ�Ͳ��ɼ�ʱ��
	virtual bool Update()=0;

	// ִ��json�ű�
    virtual void ExecuteScript(const CVBF_Config& conf)=0;
};


#endif 
