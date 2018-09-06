//*******************************************************************
// FileName：IVBF_3DEffectManager.h
// Function：三维特效管理器接口
// Author:   杜莹
// Date:     2012-04-12
//*******************************************************************

#ifndef __IVBF_3DEFFECT_MANAGER_H__
#define __IVBF_3DEFFECT_MANAGER_H__

#include "VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h"

// 定义该组件的ID号
const char VBF_COMPONENT_3DEFFECTMANAGER[]	= "Component: 3DEffectManager";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DEFFECTMANAGER[]	= "三维特效管理器接口";	

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

	// 函数：创建一个特效接口，该接口完全由用户管理
	// 参数：nEffectType -- 特效的类型，如HUD/Mask/MaskImage/Video等
	// 返回：特效接口，创建不成功返回NULL
	virtual IVBF_3DEffect* CreateEffect(const char* szType)=0;	
	
	// 函数：创建并添加一个特效接口，该接口由系统管理
	// 参数：szID          -- 特效的全局唯一ID号
	// 返回：特效接口，创建不成功返回NULL，如果该ID号已经存在，直接返回已经存在的接口
	virtual IVBF_3DEffect* AddEffect(const char* szEffectID, const char* szType)=0;

	// 函数：删除一个特效接口，该接口由系统管理
	// 参数：szID          -- 特效的全局唯一ID号
	// 返回：删除成功返回true，否则返回false
	virtual bool DeleteEffect(const char* szEffectID)=0;

	// 函数：查找指定的特效
	// 参数：szID		-- 特效的全局唯一ID号
	//       pIEffect	-- 查找到的特效接口指针
	// 返回：查找到返回true，否则返回false
	virtual bool LookupEffect(const char* szEffectID, IVBF_3DEffect*& pIEffect)=0;

	// 函数：启动配置文件中的特效	
	// 参数：szID		  -- 特效的全局唯一ID号
	// 返回：启动成功返回true，否则返回false
	virtual bool StartEffectConfiged(const char* szEffectID, const char* szActionID)=0;
    virtual bool StartEffectConfiged(TiXmlElement* pElem, const char* szActionID)=0;

	// 函数：实现一个闪烁效果
	// 参数：nFlickerTimes	  -- 闪烁的总次数
	//       nFlickerInterval -- 两次闪烁之间的间隔 (单位：帧)
	//       bNeverStop		  -- 是否一直闪烁，如果为true，参数nFlickerTimes将被忽略
	virtual void Flicker(osg::IVBF_SGNode* pNode, int nFlickerTimes, int nFlickerInterval, bool bNeverStop=false)=0;

    // 加载数据
    virtual bool SetConfigFileName(const char* szFn)=0;

	// 初始化
	virtual bool Init() = 0;
    virtual bool InsertEffectElem(const char* szEffectID, TiXmlElement* pElem)=0;
    virtual void SetFilePath(const char* szFilePath)=0;
};

#endif 
