//*******************************************************************
// FileName：  VBF_STObjectForm.h
// Function：  多粒度时空对象的形态定义
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_FORM_H__
#define __VBF_ST_OBJECT_FORM_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_XML/tinyxml.h>
#include <string>
#include <vector>
#include <Types/Vec3f>
#include <VBF_Common/VBF_STObject/VBF_STOParameter.h>
#include <VBF_Common/VBF_STObject/VBF_STOGeometry.h>
// 对象形态的一部分
class VBF_STOBJECT_EXPORT CVBF_STOFormPart
{
public:
	CVBF_STOFormPart();
    CVBF_STOFormPart(const std::string& sName, const std::string& sType);

    void SetName(const std::string& sName)	{ m_sName = sName; }
    void SetType(const std::string& sType)	{ m_sType = sType; }
    void SetDataFormat(const std::string& sDataFormat)		{ m_sDataFormat = sDataFormat; }
    void SetURL(const std::string& sURL)					{ m_sURL = sURL; }
    void SetTranslation(const osg::Vec3f& vTranslation)	{ m_vTranslation = vTranslation; }
    void SetRotate(const osg::Vec3f& vRotate)	{ m_vRotate = vRotate; }
    void SetScale(const osg::Vec3f& vScale)	{ m_vScale = vScale; }
    void SetShape(const std::string& sShape)			{ m_sShape = sShape; }
    void SetGeometry(CVBF_Geometry* pGeometry)			{ m_ipGeometry = pGeometry; }

	const std::string& GetName()		{ return m_sName; }
    const std::string& GetType()		{ return m_sType; }
    const std::string& GetDataFormat()	{ return m_sDataFormat; }
    const std::string& GetURL()			{ return m_sURL; }
    const osg::Vec3f& GetTranslation()	{ return m_vTranslation; }
    const osg::Vec3f& GetRotate()	{ return m_vRotate; }
    const osg::Vec3f& GetScale()	{ return m_vScale; }
    const std::string& GetShape()			{ return m_sShape; }
    CVBF_Geometry*     GetGeometry()		{ return m_ipGeometry.get(); }

    CVBF_STObjectParameters& Parameters() { return m_Parameters; }

	void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemPart, bool& bSimpleFormat);

    CVBF_STOFormPart* Clone();

private:

    std::string m_sName;		// 名称
    std::string m_sType;		// 类型
    std::string m_sDataFormat;	// 数据格式
    std::string m_sURL;			// 统一资源定位符

    osg::Vec3f  m_vTranslation; // 平移
    osg::Vec3f  m_vScale;       // 缩放
    osg::Vec3f  m_vRotate;      // 旋转
    bool m_bTransparent; // 是否透明（含透明部分）
    std::string			m_sShape;   // 形状：点、线、面


    CVBF_STObjectParameters		m_Parameters;


    ref_ptr<CVBF_Geometry> m_ipGeometry;

//    std::string		m_sTranslation;
};

// 对象形态
class VBF_STOBJECT_EXPORT CVBF_STObjectForm
{
public:
	CVBF_STObjectForm();
    CVBF_STObjectForm(const std::string& sName);
    virtual ~CVBF_STObjectForm();

    void SetName(const std::string& sName)	{ m_sName = sName; }
    void SetState(const std::string& sState)	{ m_sState = sState; }
    void SetScale(const std::string& sScale)	{ m_sScale = sScale; }
    void SetTime(double dTime)		{ m_dTime = dTime; }
    void SetSRSID(const std::string& sSRSID)	{ m_sSRSID = sSRSID; }

	const std::string& GetName()	{ return m_sName; }
	const std::string& GetState()	{ return m_sState; }
    const std::string& GetScale()	{ return m_sScale; }
    double GetTime()	{ return m_dTime; }
    const std::string& GetSRSID()	{ return m_sSRSID; }

	// 是否位置依赖
	bool IsLocationDependence()		{ return (m_bsLocationDependence=="true"); }
    void SetLocationDependence(bool bLocationDependence) { m_bsLocationDependence = bLocationDependence?"true":"false" ;}

	void AddPart(CVBF_STOFormPart* pPart)		{ m_vPart.push_back(pPart); }
	std::vector<CVBF_STOFormPart*>& Parts()		{ return m_vPart; }
    CVBF_STOFormPart* FindPart(const std::string& strName);
    void DeletePart(const std::string& strName);

    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemForm, bool& bSimpleFormat);

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "Form"; }

    bool IsSameType(CVBF_STObjectForm* pForm);
    CVBF_STObjectForm* Clone();
    void FilledByTemplate(CVBF_STObjectForm* pForm);

private:
    std::string		m_sName;    // 名称
    double		m_dTime;    // 时间
    std::string		m_sState;   // 态
    std::string		m_sScale;   // 尺度
    std::string		m_sSRSID;   // 空间参考ID
    std::string		m_bsLocationDependence;// 位置依赖

    std::vector<CVBF_STOFormPart*> m_vPart;
};

// 对象形态集合
#include <VBF_Common/VBF_STObject/VBF_STOCollection.h>
typedef CVBF_STOVector<CVBF_STObjectForm> CVBF_STObjectForms;


#endif
