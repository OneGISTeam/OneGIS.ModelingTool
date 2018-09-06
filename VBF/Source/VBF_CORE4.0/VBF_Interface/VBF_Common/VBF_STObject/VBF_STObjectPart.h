//*******************************************************************
// FileName：  VBF_STObjectPart.h
// Function：  多粒度时空对象的组成定义
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_PART_H__
#define __VBF_ST_OBJECT_PART_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectRef.h>
#include <VBF_Common/VBF_STObject/VBF_STOParameter.h>
#include <VBF_Common/VBF_XML/tinyxml.h>
#include <string>
#include <vector>
#include <Types/Vec3f>
class CVBF_STObject;
// 对象组成
class VBF_STOBJECT_EXPORT CVBF_STObjectPart
{
public:
    CVBF_STObjectPart();
	CVBF_STObjectPart(const std::string& sName);

    void SetName(const std::string& sName)				{ m_sName = sName; }
    void SetID(const std::string& sID)					{ m_sID = sID; }
    void SetRefObjectID(const std::string& sRefObjectID){ m_sRefObjectID = sRefObjectID; }
    void SetTranslation(const osg::Vec3f& vTranslation)	{ m_vTranslation = vTranslation; }
    void SetRotate(const osg::Vec3f& vRotate)	{ m_vRotate = vRotate; }
    void SetScale(const osg::Vec3f& vScale)	 { m_vScale = vScale; }
    void SetRefObject(CVBF_STObject* pObject){ m_pObject= pObject; }

	const std::string& GetName()			{ return m_sName; }
	const std::string& GetID()				{ return m_sID; }
    const std::string& GetRefObjectID()		{ return m_sRefObjectID; }
    const osg::Vec3f& GetTranslation()	{ return m_vTranslation; }
    const osg::Vec3f& GetRotate()	{ return m_vRotate; }
    const osg::Vec3f& GetScale()	{ return m_vScale; }
    CVBF_STObject* GetRefObject()			{ return m_pObject; }

    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemPart, bool& bSimpleFormat);

    bool IsSameType(CVBF_STObjectPart* pPart);
    CVBF_STObjectPart* Clone();
    void FilledByTemplate(CVBF_STObjectPart* pPart);

private:
    std::string		m_sName;		// 名称
    std::string		m_sID;			// ID
    std::string		m_sRefObjectID;	// 引用对象的ID
    osg::Vec3f  m_vTranslation; // 平移
    osg::Vec3f  m_vScale;       // 缩放
    osg::Vec3f  m_vRotate;      // 旋转

    CVBF_STObject* m_pObject;
};

class VBF_STOBJECT_EXPORT CVBF_STObjectArrange
{
public:
	CVBF_STObjectArrange();
    CVBF_STObjectArrange(const std::string& sName, const std::string& sType);

	const std::string& GetName()			{ return m_sName; }
	const std::string& GetType()			{ return m_sType; }
	const std::string& GetTranslate()		{ return m_sTranslate; }

    CVBF_STObjectParameters& Parameters()	{ return m_Parameters; }
    CVBF_STObjectRef&		 ObjectRef()	{ return m_ObjectRef; }

    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemArrange, bool& bSimpleFormat);

    bool IsSameType(CVBF_STObjectArrange* pArrange);
    CVBF_STObjectArrange* Clone();
    void FilledByTemplate(CVBF_STObjectArrange* pArrange);
private:
    std::string					m_sName;		// 名称
    std::string					m_sType;		// 类别
    std::string					m_sTranslate;	// 位移
    CVBF_STObjectParameters		m_Parameters;   // 排列参数
    CVBF_STObjectRef			m_ObjectRef;	// 引用对象
};

class VBF_STOBJECT_EXPORT CVBF_STObjectParts
{
public:
	CVBF_STObjectParts() {}
    virtual ~CVBF_STObjectParts();

    void AddPart(CVBF_STObjectPart* pPart)			{ m_vPart.push_back(pPart); }
    void RemovePart(CVBF_STObjectPart* pPart);
    CVBF_STObjectPart* FindPart(const std::string& strName);

	CVBF_STObjectPart* FindPart(CVBF_STObject* pObject);

    void AddArrange(CVBF_STObjectArrange* pArrange) { m_vArrange.push_back(pArrange); }

    std::vector<CVBF_STObjectPart*>& Parts() { return m_vPart;}
    std::vector<CVBF_STObjectArrange*>& Arranges() { return m_vArrange;}

    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemParent, bool& bSimpleFormat);

    void Clone(CVBF_STObjectParts& Parts);
    void FilledByTemplate(CVBF_STObjectParts& Parts);


private:
    std::vector<CVBF_STObjectPart*>		m_vPart;
    std::vector<CVBF_STObjectArrange*>	m_vArrange;
};
#endif
