//*******************************************************************
// FileName：  VBF_STObjectSRS.h
// Function：  多粒度时空对象时空参考定义
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_SRS_H__
#define __VBF_ST_OBJECT_SRS_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_STObject/AttributeValue.h>
#include <VBF_Common/VBF_XML/tinyxml.h>
#include <string>
#include <vector>

// 对象时空参考
class VBF_STOBJECT_EXPORT CVBF_STObjectSRS
{
public:
	CVBF_STObjectSRS();
    CVBF_STObjectSRS(const std::string& sID);

    void SetType(const std::string& sType)	{ m_sType = sType; }
    void SetVS(const std::string& sVS)		{ m_sVS = sVS; }

	const std::string& GetID()		{ return m_sID; }
	const std::string& GetType()	{ return m_sType; }
    const std::string& GetVS()		{ return m_sVS; }

    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemSRS, bool& bSimpleFormat);

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "SRS"; }


    bool IsSameType(CVBF_STObjectSRS* pSRS);
    CVBF_STObjectSRS* Clone();
    void FilledByTemplate(CVBF_STObjectSRS* pSRS);

private:
    std::string		m_sVS;   // 描述空间参考的字符串
    std::string		m_sType; // 类型：自定义、PROJ4、WKT、epsg等
    std::string		m_sID;   // ID
};

// 对象时空参考的集合
#include <VBF_Common/VBF_STObject/VBF_STOCollection.h>
typedef CVBF_STOVector<CVBF_STObjectSRS> CVBF_STObjectSRSes;



#endif
