//*******************************************************************
// FileName��IVBF_3DEffectManager.h
// Function����ά��Ч�������ӿ�
// Author:   ��Ө
// Date:     2012-04-12
//*******************************************************************

#ifndef __IVBF_3DEFFECT_MANAGER_H__
#define __IVBF_3DEFFECT_MANAGER_H__

#include "VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h"

// ����������ID��
const char VBF_COMPONENT_3DEFFECTMANAGER[]	= "Component: 3DEffectManager";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DEFFECTMANAGER[]	= "��ά��Ч�������ӿ�";	

//MESSAGE
const char VBF_MESSAGE_3DEFFECT_CREATE[]	= "Message: 3DEffect Created";

class IVBF_3DEffect;
class TiXmlElement;
namespace osg
{
	class Node;
}

class IVBF_3DEffectManager : public CVBF_Referenced
{
public:	
	virtual ~IVBF_3DEffectManager() {}

	// ����������һ����Ч�ӿڣ��ýӿ���ȫ���û�����
	// ������nEffectType -- ��Ч�����ͣ���HUD/Mask/MaskImage/Video��
	// ���أ���Ч�ӿڣ��������ɹ�����NULL
	virtual IVBF_3DEffect* CreateEffect(const char* szType)=0;	
	
	// ���������������һ����Ч�ӿڣ��ýӿ���ϵͳ����
	// ������szID          -- ��Ч��ȫ��ΨһID��
	// ���أ���Ч�ӿڣ��������ɹ�����NULL�������ID���Ѿ����ڣ�ֱ�ӷ����Ѿ����ڵĽӿ�
	virtual IVBF_3DEffect* AddEffect(const char* szEffectID, const char* szType)=0;

	// ������ɾ��һ����Ч�ӿڣ��ýӿ���ϵͳ����
	// ������szID          -- ��Ч��ȫ��ΨһID��
	// ���أ�ɾ���ɹ�����true�����򷵻�false
	virtual bool DeleteEffect(const char* szEffectID)=0;

	// ����������ָ������Ч
	// ������szID		-- ��Ч��ȫ��ΨһID��
	//       pIEffect	-- ���ҵ�����Ч�ӿ�ָ��
	// ���أ����ҵ�����true�����򷵻�false
	virtual bool LookupEffect(const char* szEffectID, IVBF_3DEffect*& pIEffect)=0;

	// ���������������ļ��е���Ч	
	// ������szID		  -- ��Ч��ȫ��ΨһID��
	// ���أ������ɹ�����true�����򷵻�false
	virtual bool StartEffectConfiged(const char* szEffectID, const char* szActionID)=0;
    virtual bool StartEffectConfiged(TiXmlElement* pElem, const char* szActionID)=0;

	// ������ʵ��һ����˸Ч��
	// ������nFlickerTimes	  -- ��˸���ܴ���
	//       nFlickerInterval -- ������˸֮��ļ�� (��λ��֡)
	//       bNeverStop		  -- �Ƿ�һֱ��˸�����Ϊtrue������nFlickerTimes��������
	virtual void Flicker(osg::IVBF_SGNode* pNode, int nFlickerTimes, int nFlickerInterval, bool bNeverStop=false)=0;

    // ��������
    virtual bool SetConfigFileName(const char* szFn)=0;

	// ��ʼ��
	virtual bool Init() = 0;
    virtual bool InsertEffectElem(const char* szEffectID, TiXmlElement* pElem)=0;
    virtual void SetFilePath(const char* szFilePath)=0;
};

#endif 
