//*******************************************************************
// FileName：  VBF_STOParameter.h
// Function：  多粒度时空对象的参数定义
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

// 对象参数
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

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "Parameter"; }

    bool IsSameType(CVBF_STObjectParameter* pParameter);
    CVBF_STObjectParameter* Clone();
    void FilledByTemplate(CVBF_STObjectParameter* pParameter);
protected:
    std::string				m_sName;    // 名称
    std::string				m_sType;    // 类型：static
    CVBF_AttributeValue		m_Value;	// 含类型和具体的值
};

// 对象参数集合
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

// 为了能重载函数ReadFromXML()，改用如下方法定义该类（杜莹修改：2017-11-09）
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
