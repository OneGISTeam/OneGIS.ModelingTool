//*******************************************************************
// FileName��  VBF_STObjectCognitive.h
// Function��  ������ʱ�ն������֪����
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_COGNITIVE_H__
#define __VBF_ST_OBJECT_COGNITIVE_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_STObject/VBF_STObjectAction.h>

// ��֪��Ϊ
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

	// ��̬��������ȡ�����xml��ʶ
	static std::string GetTag() { return "CognitiveBehavior"; }
protected:
    virtual CVBF_STObjectAction* NewOne()
    {
        return new CVBF_STOCognitiveBehavior(m_sName,m_sType);
    }
};


// ��֪����
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

	// ��̬��������ȡ�����xml��ʶ
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
