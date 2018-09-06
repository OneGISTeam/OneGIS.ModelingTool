//*******************************************************************
// FileName：  VBF_STObjectAttr.h
// Function：  多粒度时空对象的属性定义
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

// 对象属性
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

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "Attr"; }

    bool IsSameType(CVBF_STObjectAttr* pAttr);
    CVBF_STObjectAttr* Clone();
    void FilledByTemplate(CVBF_STObjectAttr* pAttr);

private:
    std::string				m_sName;		// 名称
    std::string				m_sType;		// 类型：静态/动态/实时，用枚举
    std::string				m_sTRSID;		// 时间参考ID
    std::string				m_sTimeFormat;	// 时间格式

    CVBF_AttributeValue		m_Value;		// 含类型和具体的值

	double m_dTime;  //当前属性的时间
};


// 对象属性集合
#include <VBF_Common/VBF_STObject/VBF_STOCollection.h>
typedef CVBF_STOVector<CVBF_STObjectAttr> CVBF_STObjectAttrs;


#endif
