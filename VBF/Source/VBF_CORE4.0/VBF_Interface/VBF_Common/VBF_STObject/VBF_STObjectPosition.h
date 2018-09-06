//*******************************************************************
// FileName��  VBF_STObjectPosition.h
// Function��  ������ʱ�ն����λ�ö���
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_POSITION_H__
#define __VBF_ST_OBJECT_POSITION_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_STObject/VBF_STOGeometry.h>
#include <VBF_Common/VBF_XML/tinyxml.h>
#include <string>
#include <VBF_Common/VBF_STObject/VBF_STOParameter.h>
#include <Types/Vec3d>
// ����λ��
class VBF_STOBJECT_EXPORT CVBF_STObjectPosition
{
public:
    CVBF_STObjectPosition();

    void SetType(const std::string& sType)				{ m_sType = sType; }
    void SetShape(const std::string& sShape)			{ m_sShape = sShape; }
    void SetFormat(const std::string& sFormat)			{ m_sFormat = sFormat; }
    void SetSRSID(const std::string& sSRSID)			{ m_sSRSID = sSRSID; }
    void SetTRSID(const std::string& sTRSID)			{ m_sTRSID = sTRSID; }
    void SetTimeFormat(const std::string& sTimeFormat)	{ m_sTimeFormat = sTimeFormat; }
    void SetGeometry(CVBF_Geometry* pGeometry)			{ m_ipGeometry = pGeometry; }

	const std::string& GetType()			{ return m_sType; }
    const std::string& GetShape()			{ return m_sShape; }
    const std::string& GetFormat()			{ return m_sFormat; }
    const std::string& GetSRSID()			{ return m_sSRSID; }
    const std::string& GetTRSID()			{ return m_sTRSID; }
    const std::string& GetTimeFormat()		{ return m_sTimeFormat; }
    CVBF_Geometry*     GetGeometry()		{ return m_ipGeometry.get(); }
    CVBF_STObjectParameters& Parameters()	{ return m_Parameters; }

    osg::Vec3d GetLocation();
    void SetLocation(const osg::Vec3d& vGeo) ;

    const osg::Vec3d& GetRotation() { return m_vRotation; }
    void SetRotation(const osg::Vec3d& vRotation){ m_vRotation = vRotation; }

    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemParent, bool& bSimpleFormat);

    void FilledByTemplate(CVBF_STObjectPosition& Position);
    void Clone(CVBF_STObjectPosition& Position);

	// ��̬��������ȡ�����xml��ʶ
	static std::string GetTag() { return "Position"; }

private:
    void WriteGeometryToXML(TiXmlElement* pElemParent);
	void ReadGeometryFromXML(TiXmlElement* pElemParent);

private:
    std::string			m_sType;    // ���ͣ���̬����̬��ʵʱ��������
    std::string			m_sShape;   // ��״���㡢�ߡ���
    std::string			m_sFormat;  // ���ݸ�ʽ
    std::string			m_sSRSID;   // �ռ�ο�ID
    std::string			m_sTRSID;   // ʱ��ο�ID
    std::string			m_sTimeFormat;   // ʱ���ʽ

    ref_ptr<CVBF_Geometry> m_ipGeometry;
    osg::Vec3d m_vRotation;
    // ��һ�����飬ÿһ��ʱ����һ��CVBF_Geometry��Rotation

    CVBF_STObjectParameters	m_Parameters;   // �������

};
#endif
