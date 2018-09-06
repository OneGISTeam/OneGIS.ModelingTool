//*******************************************************************
// FileName��  VBF_STObjectAttr.h
// Function��  ������ʱ�ն�������Զ���
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_ATTR_H__
#define __VBF_ST_OBJECT_ATTR_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_STObject/AttributeValue.h>
#include <VBF_Common/VBF_XML/tinyxml.h>
#include <string>
#include <vector>
#include <VBF_Macros.h>

// ��������
class VBF_STOBJECT_EXPORT CVBF_STObjectAttr
{
public:
	CVBF_STObjectAttr();
    CVBF_STObjectAttr(const std::string& sName, const std::string& sType);

    void SetName(const std::string& sName) { m_sName = sName; }
    void SetType(const std::string& sType) { m_sType = sType; }
    void SetTRSID(const std::string& sTRSID) { m_sTRSID = sTRSID; }
    void SetTimeFormat(const std::string& sTimeFormat) { m_sTimeFormat = sTimeFormat; }
    void SetValue(const CVBF_AttributeValue& value) { m_Value = value; }
	void SetTime(double dTime) {m_dTime = dTime;}

	const std::string& GetName()			{ return m_sName; }
    const std::string& GetType()			{ return m_sType; }
	const std::string& GetTRSID()			{ return m_sTRSID; }
    const std::string& GetTimeFormat()		{ return m_sTimeFormat; }
	double GetTime() {return m_dTime;} 

    const CVBF_AttributeValue& GetValue()		{ return m_Value; }
	std::string				   GetValueString()	{ return m_Value.getString(); }

    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemAttr, bool& bSimpleFormat);

	// ��̬��������ȡ�����xml��ʶ
	static std::string GetTag() { return "Attr"; }

    bool IsSameType(CVBF_STObjectAttr* pAttr);
    CVBF_STObjectAttr* Clone();
    void FilledByTemplate(CVBF_STObjectAttr* pAttr);

private:
    std::string				m_sName;		// ����
    std::string				m_sType;		// ���ͣ���̬/��̬/ʵʱ����ö��
    std::string				m_sTRSID;		// ʱ��ο�ID
    std::string				m_sTimeFormat;	// ʱ���ʽ

    CVBF_AttributeValue		m_Value;		// �����ͺ;����ֵ

	double m_dTime;  //��ǰ���Ե�ʱ��
};


// �������Լ���
#include <VBF_Common/VBF_STObject/VBF_STOCollection.h>
typedef CVBF_STOVector<CVBF_STObjectAttr> CVBF_STObjectAttrs;


#endif
