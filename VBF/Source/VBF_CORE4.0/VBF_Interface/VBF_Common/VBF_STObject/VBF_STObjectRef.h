//*******************************************************************
// FileName��  VBF_STObjectRef.h
// Function��  ������ʱ�ն������ö���
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_REF_H__
#define __VBF_ST_OBJECT_REF_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_STObject/VBF_STOCollection.h>

#include <VBF_Common/VBF_XML/tinyxml.h>
#include <string>

// ��������
class VBF_STOBJECT_EXPORT CVBF_STObjectRef
{
public:
    CVBF_STObjectRef();
    CVBF_STObjectRef(const std::string& sID,const std::string& sURL);

    void SetID(const std::string& sID)		{ m_sID = sID; }
    void SetURL(const std::string& sURL)	{ m_sURL = sURL; }

	const std::string& GetID()		{ return m_sID; }
    const std::string& GetURL()		{ return m_sURL; }

    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemObjectRef, bool& bSimpleFormat);

	// ��̬��������ȡ�����xml��ʶ
	static std::string GetTag() { return "ObjectRef"; }

    bool IsSameType(CVBF_STObjectRef* pRef);
    CVBF_STObjectRef* Clone();
    void FilledByTemplate(CVBF_STObjectRef* pRef);

private:
    std::string		m_sID;   // ID
    std::string		m_sURL;  // ͳһ��Դ��λ��
};

typedef CVBF_STOVector<CVBF_STObjectRef> CVBF_STObjectRefs;


#endif
