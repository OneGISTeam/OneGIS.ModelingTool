//*******************************************************************
// FileName：  VBF_STObjectAction.h
// Function：  多粒度时空对象行为和行为能力的定义
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_ACTION_H__
#define __VBF_ST_OBJECT_ACTION_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_STObject/VBF_STOParameter.h>
#include <VBF_Common/VBF_XML/tinyxml.h>
#include <VBF_Common/VBF_STObject/VBF_LifeTime.h>
#include <string>
#include <vector>

#include <list>
#include <Types/Vec3d>

// 时间参数
class VBF_STOBJECT_EXPORT CVBF_STOTimeParameter
{
public:
    void SetTRSID(const std::string& sTRSID)			{ m_sTRSID = sTRSID; }
    void SetTimeFormat(const std::string& sTimeFormat)	{ m_sTimeFormat = sTimeFormat; }
    void SetTime(const std::string& sTime)				{ m_sTime = sTime; }

	const std::string& GetTRSID()			{ return m_sTRSID; }
    const std::string& GetTimeFormat()		{ return m_sTimeFormat; }
    const std::string& GetTime()			{ return m_sTime; }

    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemTime, bool& bSimpleFormat);

private:
    std::string		m_sTRSID;       // 时间参考ID
    std::string		m_sTimeFormat;  // 时间格式
    std::string		m_sTime;        // 时间
};

// 路径参数
class VBF_STOBJECT_EXPORT CVBF_STOPathParameter
{
public:
    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemPath, bool& bSimpleFormat);
};


// 对象形态集合
#include <VBF_Common/VBF_STObject/VBF_STOCollection.h>
typedef CVBF_STOVector<CVBF_STObjectParameter> CVBF_STOActionParameters;

/*
class VBF_STOBJECT_EXPORT CVBF_STOActionParameters : public CVBF_STObjectParameters
{
public:
    CVBF_STOActionParameters();
    ~CVBF_STOActionParameters();
    virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);

    CVBF_STOTimeParameter* GetOrCreateTimeParameter();
    CVBF_STOPathParameter* GetOrCreatePathParameter();

 private:
    // 以下参数为特殊参数，可以没有，但如果有则强制为此格式
    CVBF_STOTimeParameter* m_pTimeParameter;
    CVBF_STOPathParameter* m_pPathParameter;

};
*/

// 路径
class VBF_STOBJECT_EXPORT CVBF_STOActionPath
{
public:
    CVBF_STOActionPath();

    virtual void WriteToXML(TiXmlElement* pElemParent);
    virtual void ReadFromXML(TiXmlElement* pElemAction);
    std::vector<osg::Vec3d>& Points() { return m_vPoints; }
    bool IsNeedSmooth() { return m_bNeedSmooth; }
    int  GetInterPointsNum() { return m_numInterPoints; }

private:
    std::vector<osg::Vec3d> m_vPoints;
    bool m_bNeedSmooth;
    int  m_numInterPoints;
};

// 行为
class VBF_STOBJECT_EXPORT CVBF_STObjectAction
{
public:
	CVBF_STObjectAction();
    CVBF_STObjectAction(const std::string& sName,const std::string& sType);

    void SetName(const std::string& strName){ m_sName = strName; }
    void SetType(const std::string& strType){ m_sType = strType; }

    void SetTrigger(const std::string& sTrigger)	{ m_sTrigger = sTrigger; }
    void SetTriggerParameter(const std::string& sTriggerParameter) { m_sTriggerParameter = sTriggerParameter; }
    void SetResult(const std::string& sResult)		{ m_sResult = sResult; }
    void SetObjectID(const std::string& sObjectID)	{ m_sObjectID = sObjectID; }

	const std::string& GetName()				{ return m_sName; }
	const std::string& GetObjectID()			{ return m_sObjectID; }
	const std::string& GetType()				{ return m_sType; }
	const std::string& GetTrigger()				{ return m_sTrigger; }
    const std::string& GetTriggerParameter()	{ return m_sTriggerParameter; }
    const std::string& GetResult()				{ return m_sResult; }
    CVBF_LifeTime& LifeTime() { return m_LifeTime; }

    CVBF_STOActionPath& Path() { return m_Path; }

	CVBF_STOActionParameters& Parameters() { return m_Parameters; }

    virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	virtual void ReadFromXML(TiXmlElement* pElemAction, bool& bSimpleFormat);

    bool IsSameType(CVBF_STObjectAction* pAction);
    CVBF_STObjectAction* Clone();
    void FilledByTemplate(CVBF_STObjectAction* pAction);


	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "Action"; }
protected:
    virtual CVBF_STObjectAction* NewOne();

    std::string		m_sName;   // 名称
	std::string		m_sObjectID;   // 执行动作的对象ID 

    std::string		m_sType;   // 类别
    std::string		m_sTrigger;   // 触发方式
    std::string		m_sTriggerParameter; // 触发参数
    std::string		m_sResult; // 行为结果

    CVBF_STOActionParameters m_Parameters;

    CVBF_LifeTime m_LifeTime;

    // 行为的路径，特殊的参数
    CVBF_STOActionPath m_Path;

};

typedef CVBF_STOVector<CVBF_STObjectAction> CVBF_STObjectActions;

/*
class VBF_STOBJECT_EXPORT CVBF_STObjectActions
{
public:
    ~CVBF_STObjectActions();
    void AddAction(CVBF_STObjectAction* pAction) { m_vAction.push_back(pAction); }
    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
private:
    std::vector<CVBF_STObjectAction*> m_vAction;

};
*/

// 对象行为能力
class VBF_STOBJECT_EXPORT CVBF_STOCondition // 环境
{
public:
    CVBF_STOCondition();
    CVBF_STOCondition(const std::string& ClassID,const std::string& sParameterName);

    void SetValue(const std::string& sValue) { m_sValue = sValue; }

	const std::string& GetClassID()			{ return m_sClassID; }
	const std::string& GetParameterName()	{ return m_sParameterName; }
	const std::string& GetValue()			{ return m_sValue; }

    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemCondition, bool& bSimpleFormat);

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "Condition"; }

    bool IsSameType(CVBF_STOCondition* pCondition);
    CVBF_STOCondition* Clone();
    void FilledByTemplate(CVBF_STOCondition* pCondition);

private:
    std::string		m_sClassID;			// 环境类别的ID，把所有的环境分为若干类，每类一个ID
    std::string		m_sParameterName;	// 环境影响的参数名，对应于前面的参数名
    std::string		m_sValue;
};

typedef CVBF_STOVector<CVBF_STOCondition> CVBF_STOConditions;


/*
class VBF_STOBJECT_EXPORT CVBF_STOConditions
{
public:
    ~CVBF_STOConditions();
    void Reserve(int nSize) { m_vCondition.reserve(nSize); }
    void AddCondition(CVBF_STOCondition* pCondition) { m_vCondition.push_back(pCondition); }
    void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
private:
    std::vector<CVBF_STOCondition*> m_vCondition;

};
*/
class VBF_STOBJECT_EXPORT CVBF_STOActiveAbility
{
public:
    CVBF_STOActiveAbility();
    CVBF_STOActiveAbility(const std::string& sName, const std::string& sType);

    void SetName(const std::string& strName){ m_sName = strName; }
    void SetType(const std::string& strType){ m_sType = strType; }

    const std::string& GetName() { return m_sName; }
    const std::string& GetType() { return m_sType; }
    CVBF_STObjectParameters& Parameters(){ return m_Parameters; }
    CVBF_STOConditions&      Conditions(){ return m_Conditions; }

	virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	virtual void ReadFromXML(TiXmlElement* pElemAbility, bool& bSimpleFormat);

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "ActiveAbility"; }


    bool IsSameType(CVBF_STOActiveAbility* pActiveAbility);
    CVBF_STOActiveAbility* Clone();
    void FilledByTemplate(CVBF_STOActiveAbility* pActiveAbility);

protected:
    virtual CVBF_STOActiveAbility* NewOne();

    std::string		m_sType;    // 类别
    std::string		m_sName;    // 名称
    CVBF_STObjectParameters		m_Parameters;   // 参数
    CVBF_STOConditions			m_Conditions;   // 环境
};

//typedef CVBF_STOVector<CVBF_STOActiveAbility> CVBF_STOActiveAbilitys;
class CVBF_STOActiveAbilitys : public CVBF_STOVector<CVBF_STOActiveAbility>
{
public:
    std::vector<std::string> GetAllType()
    {
        std::vector<std::string> vType;
        for(int i=0;i<Size();i++)
        {
            CVBF_STOActiveAbility* pActiveAbility = GetAt(i);
            vType.push_back(pActiveAbility->GetType());
        }
        return vType;
    }


};
#endif
