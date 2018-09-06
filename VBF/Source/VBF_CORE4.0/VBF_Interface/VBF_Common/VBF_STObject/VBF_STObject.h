//*******************************************************************
// FileName��  VBF_STObject.h
// Function��  ������ʱ�ն�����
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_H__
#define __VBF_ST_OBJECT_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>

#include <VBF_Common/VBF_STObject/VBF_STOParameter.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectRef.h>

#include <VBF_Common/VBF_STObject/VBF_STObjectSRS.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectAttr.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectPosition.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectForm.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectPart.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectAction.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectCognitive.h>

#include <VBF_Common/VBF_STObject/IVBF_STObjectDisplayModel.h>

#include <VBF_Common/VBF_Utils/VBF_XmlUtils.h>

// ������ʱ�ն���
class VBF_STOBJECT_EXPORT CVBF_STObject
{
public:
	CVBF_STObject();
    CVBF_STObject(const std::string& sID, const std::string& sType);

    void SetType(const std::string& sType)				{ m_sType = sType; }
    void SetName(const std::string& sName)				{ m_sName = sName; }
    void SetID(const std::string& sID)				{ m_sID = sID; }
    void SetTemplateID(const std::string& sTemplateID)	{ m_sTemplateID = sTemplateID; }
    void SetSRSID(const std::string& sSRSID)			{ m_sSRSID = sSRSID; }
    void SetTRSID(const std::string& sTRSID)			{ m_sTRSID = sTRSID; }
    void SetTimeFormat(const std::string& sTimeFormat)	{ m_sTimeFormat = sTimeFormat; }
    void SetBeginTime(double dBeginTime)	{ m_dBeginTime = dBeginTime; }
    void SetEndTime(double dEndTime)		{ m_dEndTime = dEndTime; }
    void SetLifeTime(double dLifeTime)		{ m_dLifeTime = dLifeTime; }

	const std::string& GetID()			{ return m_sID; }
	const std::string& GetType()		{ return m_sType; }
	const std::string& GetName()		{ return m_sName; }
    const std::string& GetTemplateID()	{ return m_sTemplateID; }
    const std::string& GetSRSID()		{ return m_sSRSID; }
    const std::string& GetTRSID()		{ return m_sTRSID; }
    const std::string& GetTimeFormat()	{ return m_sTimeFormat; }

    double GetBeginTime()	{ return m_dBeginTime; }
    double GetEndTime()		{ return m_dEndTime; }
    double GetLifeTime()	{ return m_dLifeTime; }

    CVBF_STObjectSRSes&			SRSes()				{ return m_SRSes; }
    CVBF_STObjectAttrs&			Attrs()				{ return m_Attrs; }
    CVBF_STObjectParameters&	Parameters()		{ return m_Parameters; }
    CVBF_STObjectPosition&		Position()			{ return m_Position; }
    CVBF_STObjectForms&			Forms()				{ return m_Forms; }
    CVBF_STObjectParts&			Parts()				{ return m_Parts; }
    CVBF_STOActiveAbilitys&		ActiveAbilitys()	{ return m_ActiveAbilitys; }
    CVBF_STObjectActions&		Actions()			{ return m_Actions; }
    CVBF_STOCognitiveAbilitys&	CognitiveAbilitys()	{ return m_CognitiveAbilitys; }
    CVBF_STOCognitiveBehaviors& CognitiveBehaviors(){ return m_CognitiveBehaviors; }

    virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	virtual void ReadFromXML(TiXmlElement* pElemObject, bool& bSimpleFormat);

	// ��̬��������ȡ�����xml��ʶ
	static std::string GetTag() { return "Object"; }

    void ReadFromTemplate(std::string& sTemplateID);

    // ʹ��ͬ����ģ�����
    bool IsSameType(CVBF_STObject* pObject);
    CVBF_STObject* Clone();
    void FilledByTemplate(CVBF_STObject* pTemplate);

    CVBF_STObject* FindObject(const std::string& strID);
    bool RemoveObject(CVBF_STObject* pObject);

    void SetDisplayModel(IVBF_STObjectDisplayModel* pIDisplayModel) { m_ipDisplayModel = pIDisplayModel; }
    IVBF_STObjectDisplayModel* GetDisplayModel() { return m_ipDisplayModel.get() ; }
    void UpdateDisplayModel();
private:

	//  ��ʼ�����ڹ��캯���е��ã�
	void Init();

private:
    std::string m_sType;    // ���
    std::string m_sID;      // ID
    std::string m_sName;    // ����
    std::string m_sSRSID;   // �ռ�ο�ID

    std::string m_sTRSID;   // ʱ��ο�ID
    std::string m_sTimeFormat;  // ʱ���ʽ����Ϊ���ݼ�¼ʱ�ĸ�ʽ�����ڴ��о���ʱ��ΪJD�����ʱ��Ϊ��

    // ������
    double m_dBeginTime;// ��ʼʱ�䣬����ʱ��ΪJD�����ʱ��Ϊ�룬�Ƿ����ʱ��������ʱ���ʽ��
    double m_dEndTime;  // ��ֹʱ��
    double m_dLifeTime; // ����ʱ�䣬��

    std::string					m_sTemplateID; // ����ģ���ID
    CVBF_STObjectParameters		m_Parameters;   // �������
    CVBF_STObjectSRSes			m_SRSes;
    CVBF_STObjectAttrs			m_Attrs;          // ����
    CVBF_STObjectPosition		m_Position;       // λ��
    CVBF_STObjectForms			m_Forms;          // ��̬
    CVBF_STObjectParts			m_Parts;          // ��ɽṹ
    CVBF_STOActiveAbilitys		m_ActiveAbilitys; // ��Ϊ����
    CVBF_STObjectActions		m_Actions;        // ��Ϊ
    CVBF_STOCognitiveAbilitys	m_CognitiveAbilitys;// ��֪����
    CVBF_STOCognitiveBehaviors  m_CognitiveBehaviors; // ��֪��Ϊ

protected:
    std::string		m_sTag; // ���ֶ����Ƕ���ģ��Object��ObjectTemplate

    ref_ptr<IVBF_STObjectDisplayModel> m_ipDisplayModel; // ��ʾģ��
};



typedef CVBF_STOVector<CVBF_STObject> CVBF_STObjects;


#endif
