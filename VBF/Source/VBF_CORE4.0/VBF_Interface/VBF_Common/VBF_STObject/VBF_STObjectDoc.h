//*******************************************************************
// FileName��  VBF_STObjectDoc.h
// Function��  ������ʱ�ն����ĵ�����
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_DOC_H__
#define __VBF_ST_OBJECT_DOC_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_STObject/VBF_STObject.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectGroup.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectRelation.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectTemplate.h>

#include <VBF_Common/VBF_XML/tinyxml.h>
#include <string>

// �����ĵ�
class VBF_STOBJECT_EXPORT CVBF_STObjectDoc
{
public:
    CVBF_STObjectDoc();
    CVBF_STObjectDoc(const std::string& sFileName);
    virtual ~CVBF_STObjectDoc();

    void SetFileName(const std::string& sFileName) { m_sFileName = sFileName; }
    void SetDesc(const std::string& sDesc)		{ m_sDesc = sDesc; }
    void SetDate(const std::string& sDate)		{ m_sDate = sDate; }
    void SetPath(const std::string& sPath)		{ m_sPath = sPath; }
    void SetAuthor(const std::string& sAuthor)	{ m_sAuthor = sAuthor; }

	const std::string& GetFileName()			{ return m_sFileName; }
	const std::string& GetVersion()				{ return m_sVersion; }
	const std::string& GetDesc()				{ return m_sDesc; }
    const std::string& GetDate()				{ return m_sDate; }
    const std::string& GetPath()				{ return m_sPath; }
    const std::string& GetAuthor()				{ return m_sAuthor; }

	CVBF_STObjects&			Objects()			{ return m_vObject; }
    CVBF_STObjectRefs&		ObjectRefs()		{ return m_vObjectRef; }
    CVBF_STObjectGroups&	ObjectGroups()		{ return m_vObjectGroup; }
    CVBF_STObjectRelations& ObjectRelations()	{ return m_vObjectRelation; }
    CVBF_STObjectTemplates& ObjectTemplates()	{ return m_vObjectTemplate; }

	// д��/��ȡ
    bool ReadFromXML(bool bSimpleFormat);
    void WriteToXML(bool bSimpleFormat=false);
    void WriteToXML(const std::string& sFileName);

    void ReadDocRef(const std::string& sURL);
    void Clear();

    CVBF_STObject* FindObject(const std::string& strID);
    void RemoveObject(CVBF_STObject* pObject);
    void RemoveGroup(CVBF_STObjectGroup* pGroup);

private:
    std::string				m_sFileName;	// �ĵ��ļ���
    std::string				m_sDesc;		// �ĵ�����
	std::string				m_sVersion;		// �汾
    std::string				m_sDate;		// ��������
    std::string				m_sPath;		// Ĭ������·��
    std::string				m_sAuthor;		// ����

    CVBF_STObjects			m_vObject;
    CVBF_STObjectRefs		m_vObjectRef;
    CVBF_STObjectGroups		m_vObjectGroup;
    CVBF_STObjectRelations	m_vObjectRelation;
    CVBF_STObjectTemplates	m_vObjectTemplate;
};
#endif
