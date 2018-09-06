//*******************************************************************
// FileName：  VBF_LifeTime.h
// Function：  多粒度时空对象的生命周期
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

// 生命期
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
    std::string		m_sTRSID;		// 时间参考ID
    std::string		m_sTimeFormat;  // 时间格式

    // 生命期
    double m_dBeginTime;   // 起始时间（使用儒略日JD表示的时间，convertDTtoJD）
    double m_dEndTime;     // 终止时间
    double m_dLifeTime;    // 持续时间，秒
};

#endif
