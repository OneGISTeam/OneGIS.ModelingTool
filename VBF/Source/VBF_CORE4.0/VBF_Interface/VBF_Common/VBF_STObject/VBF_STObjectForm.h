//*******************************************************************
// FileName��  VBF_STObjectForm.h
// Function��  ������ʱ�ն������̬����
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
// ������̬��һ����
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

    std::string m_sName;		// ����
    std::string m_sType;		// ����
    std::string m_sDataFormat;	// ���ݸ�ʽ
    std::string m_sURL;			// ͳһ��Դ��λ��

    osg::Vec3f  m_vTranslation; // ƽ��
    osg::Vec3f  m_vScale;       // ����
    osg::Vec3f  m_vRotate;      // ��ת
    bool m_bTransparent; // �Ƿ�͸������͸�����֣�
    std::string			m_sShape;   // ��״���㡢�ߡ���


    CVBF_STObjectParameters		m_Parameters;


    ref_ptr<CVBF_Geometry> m_ipGeometry;

//    std::string		m_sTranslation;
};

// ������̬
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

	// �Ƿ�λ������
	bool IsLocationDependence()		{ return (m_bsLocationDependence=="true"); }
    void SetLocationDependence(bool bLocationDependence) { m_bsLocationDependence = bLocationDependence?"true":"false" ;}

	void AddPart(CVBF_STOFormPart* pPart)		{ m_vPart.push_back(pPart); }
	std::vector<CVBF_STOFormPart*>& Parts()		{ return m_vPart; }
    CVBF_STOFormPart* FindPart(const std::string& strName);
    void DeletePart(const std::string& strName);

    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemForm, bool& bSimpleFormat);

	// ��̬��������ȡ�����xml��ʶ
	static std::string GetTag() { return "Form"; }

    bool IsSameType(CVBF_STObjectForm* pForm);
    CVBF_STObjectForm* Clone();
    void FilledByTemplate(CVBF_STObjectForm* pForm);

private:
    std::string		m_sName;    // ����
    double		m_dTime;    // ʱ��
    std::string		m_sState;   // ̬
    std::string		m_sScale;   // �߶�
    std::string		m_sSRSID;   // �ռ�ο�ID
    std::string		m_bsLocationDependence;// λ������

    std::vector<CVBF_STOFormPart*> m_vPart;
};

// ������̬����
#include <VBF_Common/VBF_STObject/VBF_STOCollection.h>
typedef CVBF_STOVector<CVBF_STObjectForm> CVBF_STObjectForms;


#endif
