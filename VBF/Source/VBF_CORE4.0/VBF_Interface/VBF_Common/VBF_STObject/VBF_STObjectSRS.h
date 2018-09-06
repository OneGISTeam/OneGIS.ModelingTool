//*******************************************************************
// FileName��  VBF_STObjectSRS.h
// Function��  ������ʱ�ն���ʱ�ղο�����
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

// ����ʱ�ղο�
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

	// ��̬��������ȡ�����xml��ʶ
	static std::string GetTag() { return "SRS"; }


    bool IsSameType(CVBF_STObjectSRS* pSRS);
    CVBF_STObjectSRS* Clone();
    void FilledByTemplate(CVBF_STObjectSRS* pSRS);

private:
    std::string		m_sVS;   // �����ռ�ο����ַ���
    std::string		m_sType; // ���ͣ��Զ��塢PROJ4��WKT��epsg��
    std::string		m_sID;   // ID
};

// ����ʱ�ղο��ļ���
#include <VBF_Common/VBF_STObject/VBF_STOCollection.h>
typedef CVBF_STOVector<CVBF_STObjectSRS> CVBF_STObjectSRSes;



#endif
