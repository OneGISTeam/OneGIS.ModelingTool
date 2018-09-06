//*******************************************************************
// FileName��  VBF_STObjectGroup.h
// Function��  ������ʱ�ն����鶨��
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_GROUP_H__
#define __VBF_ST_OBJECT_GROUP_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_XML/tinyxml.h>
#include <VBF_Common/VBF_STObject/VBF_STObject.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectRef.h>
#include <string>


#include <VBF_Common/VBF_STObject/VBF_STOCollection.h>

class CVBF_STObjectGroup;

typedef CVBF_STOVector<CVBF_STObjectGroup> CVBF_STObjectGroups;


// ������
class VBF_STOBJECT_EXPORT CVBF_STObjectGroup
{
public:
	CVBF_STObjectGroup();
    CVBF_STObjectGroup(const std::string& sName);
    ~CVBF_STObjectGroup();

	const std::string& GetName()	{ return m_sName; }

    CVBF_STObjects&		 Objects()			{ return m_vObject; }
    CVBF_STObjectRefs&	 ObjectRefs()		{ return m_vObjectRef; }
    CVBF_STObjectGroups& ObjectGroups()		{ return m_vObjectGroup; }

    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemGroup, bool& bSimpleFormat);

	// ��̬��������ȡ�����xml��ʶ
	static std::string GetTag() { return "ObjectGroup"; }

    bool IsSameType(CVBF_STObjectGroup* pGroup);
    CVBF_STObjectGroup* Clone();
    void FilledByTemplate(CVBF_STObjectGroup* pGroup);

    CVBF_STObject* FindObject(const std::string& strID);
    bool RemoveObject(CVBF_STObject* pObject);
    bool RemoveGroup(CVBF_STObjectGroup* pGroup);

private:
    std::string				m_sName;    // ����
    CVBF_STObjects			m_vObject;
    CVBF_STObjectRefs		m_vObjectRef;
    CVBF_STObjectGroups		m_vObjectGroup;
};
#endif
