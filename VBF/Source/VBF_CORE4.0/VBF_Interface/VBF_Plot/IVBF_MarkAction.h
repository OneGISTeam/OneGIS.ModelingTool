//*******************************************************************
// FileName��IVBF_MarkAction.h
// Function����ͼʵ��ģ�Ͷ����ӿ�
// Author:
// Date:     2017-12-28
//*******************************************************************

#ifndef __IVBF_MARK_ACTION_H__
#define __IVBF_MARK_ACTION_H__

#include <vector>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Plot/IVBF_MarkStyleManager.h>



#define VBF_MARK_ACTION_ROTATEAXIS	"RotateAxis"	// ��ĳ��֧�㴦������ת���磺�ɻ���������ת����
#define VBF_MARK_ACTION_TEXANIM		"TexAnim"       // �������任���磺̹���Ĵ���ת����


class IVBF_MarkModel;
class TiXmlElement;
class IVBF_PropertySet;
class IVBF_MarkContext;
class CVBF_Config;


class IVBF_MarkAction : public osg::CVBF_Object
{
public:
    virtual ~IVBF_MarkAction() {}

public:

    // ��ȡ��������
    virtual const std::string& GetType()=0;

    // ��ȡ��������
    virtual void SetName(const std::string& sName)=0;
    virtual const std::string& GetName()=0;


    // ��ȡ�������͵��������Ա��û����
	virtual const std::string& GetTypeDesc()=0;

    // ����/��ȡ�Ƿ�ִ��
    virtual void Enable(bool bEnable)=0;
    virtual bool IsEnable()=0;

    // ����/��ȡ�������󶨵�ʵ��ģ��
	virtual void SetMarkModel(IVBF_MarkModel* pIMark)=0;
	virtual IVBF_MarkModel* GetMarkModel()=0;

	// ����
    virtual IVBF_MarkAction* Clone()=0;

    // ���л�
    virtual bool WriteToXML(TiXmlElement* pElemAction)=0;    // д�룺��ģ�Ͷ�����Ϣд��ָ����xml�ڵ�
    virtual bool ReadFromXML(TiXmlElement* pElemAction)=0;   // ��ȡ����ָ����xml�ڵ��ȡģ�Ͷ�����Ϣ

	// ��ʼ�� (�ڹ��캯��֮����ϵͳ����)
    virtual bool Init(IVBF_MarkContext* pIContext)=0;

	// ���� (��ÿ֡����ǰ��ϵͳ����)������ֵΪfalse��ʾδ�����´�����ģ�Ͳ��ɼ�ʱ��
	virtual bool Update()=0;

	// ִ��json�ű�
    virtual void ExecuteScript(const CVBF_Config& conf)=0;
};


#endif 
