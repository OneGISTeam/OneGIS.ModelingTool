//*******************************************************************
// FileName：  VBF_STObject.h
// Function：  多粒度时空对象定义
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_H__
#define __VBF_ST_OBJECT_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>

#include <VBF_Common/VBF_STObject/VBF_STOParameter.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectRef.h>

#include <VBF_Common/VBF_STObject/VBF_STObjectSRS.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectAttr.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectPosition.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectForm.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectPart.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectAction.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectCognitive.h>

#include <VBF_Common/VBF_STObject/IVBF_STObjectDisplayModel.h>

#include <VBF_Common/VBF_Utils/VBF_XmlUtils.h>

// 多粒度时空对象
class VBF_STOBJECT_EXPORT CVBF_STObject
{
public:
	CVBF_STObject();
    CVBF_STObject(const std::string& sID, const std::string& sType);

    void SetType(const std::string& sType)				{ m_sType = sType; }
    void SetName(const std::string& sName)				{ m_sName = sName; }
    void SetID(const std::string& sID)				{ m_sID = sID; }
    void SetTemplateID(const std::string& sTemplateID)	{ m_sTemplateID = sTemplateID; }
    void SetSRSID(const std::string& sSRSID)			{ m_sSRSID = sSRSID; }
    void SetTRSID(const std::string& sTRSID)			{ m_sTRSID = sTRSID; }
    void SetTimeFormat(const std::string& sTimeFormat)	{ m_sTimeFormat = sTimeFormat; }
    void SetBeginTime(double dBeginTime)	{ m_dBeginTime = dBeginTime; }
    void SetEndTime(double dEndTime)		{ m_dEndTime = dEndTime; }
    void SetLifeTime(double dLifeTime)		{ m_dLifeTime = dLifeTime; }

	const std::string& GetID()			{ return m_sID; }
	const std::string& GetType()		{ return m_sType; }
	const std::string& GetName()		{ return m_sName; }
    const std::string& GetTemplateID()	{ return m_sTemplateID; }
    const std::string& GetSRSID()		{ return m_sSRSID; }
    const std::string& GetTRSID()		{ return m_sTRSID; }
    const std::string& GetTimeFormat()	{ return m_sTimeFormat; }

    double GetBeginTime()	{ return m_dBeginTime; }
    double GetEndTime()		{ return m_dEndTime; }
    double GetLifeTime()	{ return m_dLifeTime; }

    CVBF_STObjectSRSes&			SRSes()				{ return m_SRSes; }
    CVBF_STObjectAttrs&			Attrs()				{ return m_Attrs; }
    CVBF_STObjectParameters&	Parameters()		{ return m_Parameters; }
    CVBF_STObjectPosition&		Position()			{ return m_Position; }
    CVBF_STObjectForms&			Forms()				{ return m_Forms; }
    CVBF_STObjectParts&			Parts()				{ return m_Parts; }
    CVBF_STOActiveAbilitys&		ActiveAbilitys()	{ return m_ActiveAbilitys; }
    CVBF_STObjectActions&		Actions()			{ return m_Actions; }
    CVBF_STOCognitiveAbilitys&	CognitiveAbilitys()	{ return m_CognitiveAbilitys; }
    CVBF_STOCognitiveBehaviors& CognitiveBehaviors(){ return m_CognitiveBehaviors; }

    virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	virtual void ReadFromXML(TiXmlElement* pElemObject, bool& bSimpleFormat);

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "Object"; }

    void ReadFromTemplate(std::string& sTemplateID);

    // 使用同类别的模板填充
    bool IsSameType(CVBF_STObject* pObject);
    CVBF_STObject* Clone();
    void FilledByTemplate(CVBF_STObject* pTemplate);

    CVBF_STObject* FindObject(const std::string& strID);
    bool RemoveObject(CVBF_STObject* pObject);

    void SetDisplayModel(IVBF_STObjectDisplayModel* pIDisplayModel) { m_ipDisplayModel = pIDisplayModel; }
    IVBF_STObjectDisplayModel* GetDisplayModel() { return m_ipDisplayModel.get() ; }
    void UpdateDisplayModel();
private:

	//  初始化（在构造函数中调用）
	void Init();

private:
    std::string m_sType;    // 类别
    std::string m_sID;      // ID
    std::string m_sName;    // 名称
    std::string m_sSRSID;   // 空间参考ID

    std::string m_sTRSID;   // 时间参考ID
    std::string m_sTimeFormat;  // 时间格式，仅为数据记录时的格式，在内存中绝对时间为JD，相对时间为秒

    // 生命期
    double m_dBeginTime;// 起始时间，绝对时间为JD，相对时间为秒，是否绝对时间隐含在时间格式中
    double m_dEndTime;  // 终止时间
    double m_dLifeTime; // 持续时间，秒

    std::string					m_sTemplateID; // 对象模板的ID
    CVBF_STObjectParameters		m_Parameters;   // 构造参数
    CVBF_STObjectSRSes			m_SRSes;
    CVBF_STObjectAttrs			m_Attrs;          // 属性
    CVBF_STObjectPosition		m_Position;       // 位置
    CVBF_STObjectForms			m_Forms;          // 形态
    CVBF_STObjectParts			m_Parts;          // 组成结构
    CVBF_STOActiveAbilitys		m_ActiveAbilitys; // 行为能力
    CVBF_STObjectActions		m_Actions;        // 行为
    CVBF_STOCognitiveAbilitys	m_CognitiveAbilitys;// 认知能力
    CVBF_STOCognitiveBehaviors  m_CognitiveBehaviors; // 认知行为

protected:
    std::string		m_sTag; // 区分对象还是对象模板Object、ObjectTemplate

    ref_ptr<IVBF_STObjectDisplayModel> m_ipDisplayModel; // 显示模型
};



typedef CVBF_STOVector<CVBF_STObject> CVBF_STObjects;


#endif
