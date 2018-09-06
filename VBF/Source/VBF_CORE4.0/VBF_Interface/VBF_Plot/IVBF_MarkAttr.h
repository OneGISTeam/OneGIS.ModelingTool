//*******************************************************************
// FileName：IVBF_MarkAttr.h
// Function：标图实体模型属性接口
// Author:
// Date:     2009-4-10
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_H__
#define __IVBF_MARK_ATTR_H__

#include <vector>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Plot/IVBF_MarkStyleManager.h>


const unsigned int VBF_MARK_ATTR_UNKNOWN			= 0;	// 未知类型
const unsigned int VBF_MARK_ATTR_HINTLINE			= 1;	// 高度线
const unsigned int VBF_MARK_ATTR_TRAILLINE			= 2;	// 轨迹线（折线形）
const unsigned int VBF_MARK_ATTR_TRAILSTRIP			= 3;	// 轨迹线（条带形）
const unsigned int VBF_MARK_ATTR_LABEL				= 4;	// 独立标签
const unsigned int VBF_MARK_ATTR_LABEL_CHAINED		= 5;	// 散列式标签
const unsigned int VBF_MARK_ATTR_INFO				= 6;	// 信息
const unsigned int VBF_MARK_ATTR_AUTOFLY			= 7;	// 自动飞行（导弹）
const unsigned int VBF_MARK_ATTR_LIFETIME			= 8;	// 生命期
const unsigned int VBF_MARK_ATTR_STATE				= 9;	// 状态
const unsigned int VBF_MARK_ATTR_TAILFLAME			= 10;	// 尾焰
const unsigned int VBF_MARK_ATTR_BATTLETASK			= 11;	// 作战任务
const unsigned int VBF_MARK_ATTR_POWERMAP			= 12;	// 威力图
const unsigned int VBF_MARK_ATTR_AIRLINE			= 13;	// 航线与航空管道
const unsigned int VBF_MARK_ATTR_SOUND				= 14;	// 音效
const unsigned int VBF_MARK_ATTR_EXPLOSION			= 15;	// 爆炸
const unsigned int VBF_MARK_ATTR_SMOKE				= 16;	// 特效：烟火
const unsigned int VBF_MARK_ATTR_MISSILEFIRE		= 17;	// 特效：导弹尾焰
const unsigned int VBF_MARK_ATTR_SHIPTRAIL			= 18;	// 特效：舰船航迹
const unsigned int VBF_MARK_ATTR_ROTATEX 		    = 19;	// 绕X轴旋转
const unsigned int VBF_MARK_ATTR_ROTATEY 		    = 20;	// 绕Y轴旋转
const unsigned int VBF_MARK_ATTR_ROTATEZ 		    = 21;	// 绕Z轴旋转
const unsigned int VBF_MARK_ATTR_DETECTED 		    = 22;	// 被探测
const unsigned int VBF_MARK_ATTR_IFF				= 23;	// 敌我类别，如“我方”、“敌方”等
const unsigned int VBF_MARK_ATTR_INTERSECT			= 24;	// 模型与地面的交线
const unsigned int VBF_MARK_ATTR_SPHEREATTITUDE		= 25;	// 模型的姿态球
const unsigned int VBF_MARK_ATTR_MISSILEFIRE_GROUP	= 26;	// 特效：导弹尾焰组
const unsigned int VBF_MARK_ATTR_TRAILSMOKE			= 27;	// 特效：轨迹线（烟雾状，使用粒子系统实现）
const unsigned int VBF_MARK_ATTR_COORDSYS			= 28;	// 局部坐标系（用于显示点状模型的局部坐标系）
const unsigned int VBF_MARK_ATTR_WEBVIEW            = 29;	// 窗口标签


class IVBF_MarkModel;
class TiXmlElement;
class IVBF_PropertySet;
class CVBF_PopupMenuItem;
class IVBF_MarkContext;
class CVBF_Config;


class IVBF_MarkAttr : public osg::CVBF_Object
{
public:
	virtual ~IVBF_MarkAttr() {}

public:

	// 获取属性类型
	virtual unsigned int GetType()=0;

	// 获取属性类型的描述，以便用户理解
	virtual const std::string& GetTypeDesc()=0;

	// 设置/获取可见性
	virtual void SetVisible(bool bVisible)=0;
	virtual bool IsVisible()=0;

	// 设置/获取属性所绑定的实体模型
	virtual void SetMarkModel(IVBF_MarkModel* pIMark)=0;
	virtual IVBF_MarkModel* GetMarkModel()=0;

	// 设置/获取属性最小最大可见距离，如果没有设置，默认使用属性所绑定的实体模型的可见距离
	// 如果获取的返回值为false，表示用户没有设置属性的最小最大可见距离
	virtual void SetDistMin(float fDistMin)=0;
	virtual bool GetDistMin(float& fDistMin)=0;

	virtual void SetDistMax(float fDistMax)=0;
	virtual bool GetDistMax(float& fDistMax)=0;

	// 复制
	virtual IVBF_MarkAttr* Clone()=0;

	// 设置属性参数列表
	virtual bool ExecuteCommand(const char* szCommandID, IVBF_PropertySet* pInParam, IVBF_PropertySet* pOutParam)=0;

    // 右键弹出菜单
    virtual void GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems)=0;
    virtual bool ProcessPopupMenuItem(unsigned int nID)=0;

    // 串行化
    virtual bool WriteToXML(TiXmlElement* pElemAttr)=0;    // 写入：将模型属性信息写入指定的xml节点
    virtual bool ReadFromXML(TiXmlElement* pElemAttr)=0;   // 读取：从指定的xml节点读取模型属性信息

	// 初始化 (在构造函数之后由系统调用)
    virtual bool Init(IVBF_MarkContext* pIContext)=0;

	// 更新 (在每帧绘制前由系统调用)，返回值为false表示未做更新处理（如模型不可见时）
	virtual bool Update()=0;

	// 执行json脚本
    virtual void ExecuteScript(const CVBF_Config& conf)=0;
};


#endif 
