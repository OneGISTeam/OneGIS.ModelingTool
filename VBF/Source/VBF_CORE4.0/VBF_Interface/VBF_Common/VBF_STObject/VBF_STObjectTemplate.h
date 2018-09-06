//*******************************************************************
// FileName：  VBF_STObjectTemplate.h
// Function：  多粒度时空对象模板定义
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_TEMPLATE_H__
#define __VBF_ST_OBJECT_TEMPLATE_H__

#include <VBF_Common/VBF_STObject/VBF_STObject.h>

// 对象模板
class VBF_STOBJECT_EXPORT CVBF_STObjectTemplate : public CVBF_STObject
{
public:
	CVBF_STObjectTemplate();
    CVBF_STObjectTemplate(const std::string& sID,const std::string& sType);

    virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	virtual void ReadFromXML(TiXmlElement* pElemObjectTempl, bool& bSimpleFormat);

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "ObjectTemplate"; }
};

#include <VBF_Common/VBF_STObject/VBF_STOCollection.h>
typedef CVBF_STOVector<CVBF_STObjectTemplate> CVBF_STObjectTemplates;

#endif
