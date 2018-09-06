//*******************************************************************
// FileName：IVBF_3DEffect.h
// Function：三维特效接口
// Author:   SunC
// Date:     2012-04-12
//*******************************************************************

#ifndef __IVBF_3DEFFECT_H__
#define __IVBF_3DEFFECT_H__


// 定义特效类型
const char VBF_3DEFFECT_UNKNOWN[]		= "Unknown";
const char VBF_3DEFFECT_IMAGE2D[]		= "Image2D";
const char VBF_3DEFFECT_IMAGE3D[]		= "Image3D";
const char VBF_3DEFFECT_MASK[]			= "Mask";
const char VBF_3DEFFECT_MASKIMAGE[]		= "MaskImage";
const char VBF_3DEFFECT_VIDEO[]			= "Video";
const char VBF_3DEFFECT_AUDIO[]			= "Audio";

// 定义各种特效动作

// 不做动作
const char VBF_3DEFFECT_ACTION_NULL[]		= "不做动作";

// 进入动作
const char VBF_3DEFFECT_ACTION_FADEIN[]		= "淡入";
const char VBF_3DEFFECT_ACTION_LEFTIN[]		= "左入";
const char VBF_3DEFFECT_ACTION_RIGHTIN[]	= "右入";
const char VBF_3DEFFECT_ACTION_UPIN[]		= "上入";
const char VBF_3DEFFECT_ACTION_DOWNIN[]		= "下入";
const char VBF_3DEFFECT_ACTION_SCALEIN[]	= "扩入";
const char VBF_3DEFFECT_ACTION_EXPANDOUT[]	= "扩展拉伸";

// 退出动作
const char VBF_3DEFFECT_ACTION_FADEOUT[]	= "淡出";
const char VBF_3DEFFECT_ACTION_LEFTOUT[]	= "左出";
const char VBF_3DEFFECT_ACTION_RIGHTOUT[]	= "右出";
const char VBF_3DEFFECT_ACTION_UPOUT[]		= "上出";
const char VBF_3DEFFECT_ACTION_DOWNOUT[]	= "下出";
const char VBF_3DEFFECT_ACTION_SCALEOUT[]	= "缩出";
const char VBF_3DEFFECT_ACTION_EXPANDIN[]	= "缩小拉伸";

// 动画动作
const char VBF_3DEFFECT_ACTION_SCALE[]		= "缩放";
const char VBF_3DEFFECT_ACTION_TRANS[]		= "位移";
const char VBF_3DEFFECT_ACTION_FLICKER[]	= "闪烁";


// 定义字符串的最大长度
#define VBF_MAX_LENGTH_3DEFFECTTYPE		64		// 特效类型的最大长度
#define VBF_MAX_LENGTH_3DEFFECTID		64		// 特效ID号的最大长度


class TiXmlElement;

class IVBF_3DEffect
{
public:	
	virtual ~IVBF_3DEffect() {}	

	// 获取特效类型
	virtual const char* GetType()=0;

	// 设置/获取特效的全局唯一ID号
	virtual void        SetID(const char* szID)=0;
	virtual const char* GetID()=0;

	// 设置/获取特效图像/视频文件的根路径
	virtual void		SetFilePath(const char* szPath)=0;
	virtual const char*	GetFilePath()=0;

	// 从配置文件中装载特效对象的信息
	virtual bool LoadFromXML(TiXmlElement* pElemEffect)=0;

	// 执行特效对象的动作，动作参数从从配置文件元素中获取
	virtual bool StartFromXML(TiXmlElement* pElemAction)=0;
};

#endif 
