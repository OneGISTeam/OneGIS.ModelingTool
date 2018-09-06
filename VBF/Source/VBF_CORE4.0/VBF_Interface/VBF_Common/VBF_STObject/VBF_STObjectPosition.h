//*******************************************************************
// FileName：  VBF_STObjectPosition.h
// Function：  多粒度时空对象的位置定义
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
// 对象位置
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

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "Position"; }

private:
    void WriteGeometryToXML(TiXmlElement* pElemParent);
	void ReadGeometryFromXML(TiXmlElement* pElemParent);

private:
    std::string			m_sType;    // 类型：静态、动态、实时、函数等
    std::string			m_sShape;   // 形状：点、线、面
    std::string			m_sFormat;  // 数据格式
    std::string			m_sSRSID;   // 空间参考ID
    std::string			m_sTRSID;   // 时间参考ID
    std::string			m_sTimeFormat;   // 时间格式

    ref_ptr<CVBF_Geometry> m_ipGeometry;
    osg::Vec3d m_vRotation;
    // 是一个数组，每一个时间点记一个CVBF_Geometry和Rotation

    CVBF_STObjectParameters	m_Parameters;   // 轨道参数

};
#endif
