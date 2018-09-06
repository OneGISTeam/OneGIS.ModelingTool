//*******************************************************************
// FileName：IVBF_3DAction.h
// Function：三维特效动作
// Author:   杜莹
// Date:     2012-05-12
//*******************************************************************

#ifndef __IVBF_3DACTION_H__
#define __IVBF_3DACTION_H__


// 定义各种特效动作

// 不做动作
const char VBF_3D_ACTION_NULL[]			= "不做动作";

// 进入动作
const char VBF_3D_ACTION_FADEIN[]		= "淡入";
const char VBF_3D_ACTION_LEFTIN[]		= "左入";
const char VBF_3D_ACTION_RIGHTIN[]		= "右入";
const char VBF_3D_ACTION_UPIN[]			= "上入";
const char VBF_3D_ACTION_DOWNIN[]		= "下入";
const char VBF_3D_ACTION_SCALEIN[]		= "扩入";
const char VBF_3D_ACTION_EXPANDOUT[]	= "扩展拉伸";

// 退出动作
const char VBF_3D_ACTION_FADEOUT[]		= "淡出";
const char VBF_3D_ACTION_LEFTOUT[]		= "左出";
const char VBF_3D_ACTION_RIGHTOUT[]		= "右出";
const char VBF_3D_ACTION_UPOUT[]		= "上出";
const char VBF_3D_ACTION_DOWNOUT[]		= "下出";
const char VBF_3D_ACTION_SCALEOUT[]		= "缩出";
const char VBF_3D_ACTION_EXPANDIN[]		= "缩小拉伸";

// 动画动作
const char VBF_3D_ACTION_SCALE[]		= "缩放";
const char VBF_3D_ACTION_TRANS[]		= "位移";
const char VBF_3D_ACTION_FLICKER[]		= "闪烁";


// 定义字符串的最大长度
#define VBF_MAX_LENGTH_3DACTIONTYPE		64		// 动作类型的最大长度
#define VBF_MAX_LENGTH_3DACTIONTID		64		// 动作ID号的最大长度


class TiXmlElement;

class IVBF_3DAction
{
public:	
	virtual ~IVBF_3DAction() {}	

	// 获取特效类型
	virtual const char* GetType()=0;

	// 设置/获取特效的全局唯一ID号
	virtual void        SetID(const char* szID)=0;
	virtual const char* GetID()=0;
	
	// 从配置文件中装载信息
	virtual bool LoadFromXML(TiXmlElement* pElem)=0;
};

#endif 
