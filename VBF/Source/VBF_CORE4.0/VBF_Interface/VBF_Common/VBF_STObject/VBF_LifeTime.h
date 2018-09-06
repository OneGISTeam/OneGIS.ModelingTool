//*******************************************************************
// FileName��  VBF_LifeTime.h
// Function��  ������ʱ�ն������������
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_LIFETIME_H__
#define __VBF_ST_OBJECT_LIFETIME_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>

#include <VBF_Common/VBF_XML/tinyxml.h>
#include <string>


#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Base/ref_ptr>

// ������
class VBF_STOBJECT_EXPORT CVBF_LifeTime : public CVBF_Referenced
{
public:
    CVBF_LifeTime();
    void SetTRSID(const std::string& sTRSID)			{ m_sTRSID = sTRSID; }
    void SetTimeFormat(const std::string& sTimeFormat)	{ m_sTimeFormat = sTimeFormat; }
    void SetBeginTime(double dBeginTime)	{ m_dBeginTime = dBeginTime; }
    void SetEndTime(double dEndTime)		{ m_dEndTime = dEndTime; }
    void SetLifeTime(double dLifeTime)		{ m_dLifeTime = dLifeTime; }

	const std::string& GetTRSID()			{ return m_sTRSID; }
    const std::string& GetTimeFormat()		{ return m_sTimeFormat; }
    double GetBeginTime()		{ return m_dBeginTime; }
    double GetEndTime();
    double GetLifeTime()		{ return m_dLifeTime; }
    bool IsRelative();

    void WriteToXML(TiXmlElement* pElem);
    bool ReadFromXML(TiXmlElement* pElem);

    CVBF_LifeTime* Clone();

	bool operator==(const CVBF_LifeTime& right);

	CVBF_LifeTime& operator=(const CVBF_LifeTime& right);

	bool contains(double jd);

private:
    std::string		m_sTRSID;		// ʱ��ο�ID
    std::string		m_sTimeFormat;  // ʱ���ʽ

    // ������
    double m_dBeginTime;   // ��ʼʱ�䣨ʹ��������JD��ʾ��ʱ�䣬convertDTtoJD��
    double m_dEndTime;     // ��ֹʱ��
    double m_dLifeTime;    // ����ʱ�䣬��
};

#endif
