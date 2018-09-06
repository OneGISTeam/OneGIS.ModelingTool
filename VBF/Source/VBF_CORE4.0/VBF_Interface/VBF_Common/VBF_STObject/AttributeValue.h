//*******************************************************************
// FileName：  AttributeValue.h
// Function：  属性值定义
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_ATTR_VALUE_H__
#define __VBF_ST_ATTR_VALUE_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <string>
#include <map>

struct CVBF_AttributeValueUnion
{
    std::string stringValue;
    double      doubleValue;
    int         intValue;
    bool        boolValue;

	bool        set;	// 是否设置了该值，false意味着值无效

	CVBF_AttributeValueUnion()
	{
		set			= false;
		stringValue = "";
		doubleValue = 0.0;
		intValue    = 0;
		boolValue   = false;
	}
};

enum CVBF_AttributeType
{
    VBF_ATTRTYPE_UNSPECIFIED,
    VBF_ATTRTYPE_STRING,
    VBF_ATTRTYPE_INT,
    VBF_ATTRTYPE_DOUBLE,
    VBF_ATTRTYPE_BOOL,
    VBF_ATTRTYPE_FLOAT,
    VBF_ATTRTYPE_VEC3D
};

struct VBF_STOBJECT_EXPORT CVBF_AttributeValue : public std::pair<CVBF_AttributeType,CVBF_AttributeValueUnion>
{
    std::string getString() const;
    std::string GetType() const;

    float   getFloat(float defaultValue=0.0) const;
    double  getDouble(double defaultValue=0.0) const;
    int     getInt(int defaultValue=0 ) const;
    bool    getBool(bool defaultValue=false) const;

    void SetString(const std::string& strValue);
};

typedef std::map<std::string, CVBF_AttributeValue> CVBF_AttributeTable;


class TiXmlElement;

// 全局函数：从xml中读/写属性类型和属性值
void VBF_QueryAttribute(TiXmlElement* pElem, CVBF_AttributeValue& value);
void VBF_SetAttribute(TiXmlElement* pElem, const CVBF_AttributeValue& value);

#endif
