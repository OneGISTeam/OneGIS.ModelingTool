//*******************************************************************
// FileName：  VBF_STObjectCognitive.h
// Function：  多粒度时空对象的认知定义
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_COGNITIVE_H__
#define __VBF_ST_OBJECT_COGNITIVE_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectAction.h>

// 认知行为
class VBF_STOBJECT_EXPORT CVBF_STOCognitiveBehavior : public CVBF_STObjectAction
{
public:
    CVBF_STOCognitiveBehavior():CVBF_STObjectAction()
    {
    }
    CVBF_STOCognitiveBehavior(const std::string& sName,const std::string& sType):
        CVBF_STObjectAction(sName,sType)
    {
    }

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "CognitiveBehavior"; }
protected:
    virtual CVBF_STObjectAction* NewOne()
    {
        return new CVBF_STOCognitiveBehavior(m_sName,m_sType);
    }
};


// 认知能力
class VBF_STOBJECT_EXPORT CVBF_STOCognitiveAbility : public CVBF_STOActiveAbility
{
public:
    CVBF_STOCognitiveAbility():CVBF_STOActiveAbility()
    {
    }
    CVBF_STOCognitiveAbility(const std::string& sName, const std::string& sType):
        CVBF_STOActiveAbility(sName,sType)
    {
    }

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "CognitiveAbility"; }
protected:
    virtual CVBF_STOActiveAbility* NewOne()
    {
        return new CVBF_STOCognitiveAbility(m_sName,m_sType);
    }
};

#include <VBF_Common/VBF_STObject/VBF_STOCollection.h>
typedef CVBF_STOVector<CVBF_STOCognitiveBehavior> CVBF_STOCognitiveBehaviors;
typedef CVBF_STOVector<CVBF_STOCognitiveAbility> CVBF_STOCognitiveAbilitys;


#endif
