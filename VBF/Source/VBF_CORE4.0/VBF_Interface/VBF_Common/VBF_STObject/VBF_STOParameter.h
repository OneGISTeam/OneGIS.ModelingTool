//*******************************************************************
// FileName��  VBF_STOParameter.h
// Function��  ������ʱ�ն���Ĳ�������
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_PARAMETER_H__
#define __VBF_ST_OBJECT_PARAMETER_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_XML/tinyxml.h>
#include <VBF_Common/VBF_STObject/AttributeValue.h>
#include <string>
#include <vector>

// �������
class VBF_STOBJECT_EXPORT CVBF_STObjectParameter
{
public:
	CVBF_STObjectParameter();
    CVBF_STObjectParameter(const std::string& sName);

    void SetName(const std::string& sName) { m_sName = sName; }
    void SetType(const std::string& sType) { m_sType = sType; }
    void SetValue(const CVBF_AttributeValue& value) { m_Value = value; }
    void SetValue(const std::string& sValue);

	const CVBF_AttributeValue& GetValue()		{ return m_Value; }
    std::string				   GetValueString()	{ return m_Value.getString(); }
	const std::string&		   GetName()		{ return m_sName; }
    const std::string&		   GetType()		{ return m_sType; }

	std::string GetID()			{ return ""; }

    virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	virtual void ReadFromXML(TiXmlElement* pElemParameter, bool& bSimpleFormat);

	// ��̬��������ȡ�����xml��ʶ
	static std::string GetTag() { return "Parameter"; }

    bool IsSameType(CVBF_STObjectParameter* pParameter);
    CVBF_STObjectParameter* Clone();
    void FilledByTemplate(CVBF_STObjectParameter* pParameter);
protected:
    std::string				m_sName;    // ����
    std::string				m_sType;    // ���ͣ�static
    CVBF_AttributeValue		m_Value;	// �����ͺ;����ֵ
};

// �����������
#include <VBF_Common/VBF_STObject/VBF_STOCollection.h>
typedef CVBF_STOVector<CVBF_STObjectParameter> CVBF_STObjectParameters;

class VBF_STOBJECT_EXPORT CVBF_STOParameterValue : public CVBF_STObjectParameter
{
public:
	CVBF_STOParameterValue();
    CVBF_STOParameterValue(const std::string& sName);

    virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	virtual void ReadFromXML(TiXmlElement* pElemParent, bool& bSimpleFormat);
};

//typedef CVBF_STOVector<CVBF_STOParameterValue> CVBF_STOParameterValues;

// Ϊ�������غ���ReadFromXML()���������·���������ࣨ��Ө�޸ģ�2017-11-09��
class VBF_STOBJECT_EXPORT CVBF_STOParameterValues : public CVBF_STOVector<CVBF_STOParameterValue>
{
public:
    CVBF_STOParameterValues();
	virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	virtual void ReadFromXML(TiXmlElement* pElemParent, bool& bSimpleFormat);

    std::string GetParameterValue(const std::string& strName);
    void SetParameterValue(const std::string& strName,const std::string& strValue);
    void AddParameter(CVBF_STObjectParameter& Parameter);
private:
    CVBF_STObjectParameters* pParameters;
};

#endif
