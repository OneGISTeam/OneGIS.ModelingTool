//*******************************************************************
// FileName：IVBF_MarkAction.h
// Function：标图实体模型动作接口
// Author:
// Date:     2017-12-28
//*******************************************************************

#ifndef __IVBF_MARK_ACTION_H__
#define __IVBF_MARK_ACTION_H__

#include <vector>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Plot/IVBF_MarkStyleManager.h>



#define VBF_MARK_ACTION_ROTATEAXIS	"RotateAxis"	// 在某个支点处绕轴旋转（如：飞机螺旋桨的转动）
#define VBF_MARK_ACTION_TEXANIM		"TexAnim"       // 纹理矩阵变换（如：坦克履带的转动）


class IVBF_MarkModel;
class TiXmlElement;
class IVBF_PropertySet;
class IVBF_MarkContext;
class CVBF_Config;


class IVBF_MarkAction : public osg::CVBF_Object
{
public:
    virtual ~IVBF_MarkAction() {}

public:

    // 获取动作类型
    virtual const std::string& GetType()=0;

    // 获取动作名称
    virtual void SetName(const std::string& sName)=0;
    virtual const std::string& GetName()=0;


    // 获取动作类型的描述，以便用户理解
	virtual const std::string& GetTypeDesc()=0;

    // 设置/获取是否执行
    virtual void Enable(bool bEnable)=0;
    virtual bool IsEnable()=0;

    // 设置/获取动作所绑定的实体模型
	virtual void SetMarkModel(IVBF_MarkModel* pIMark)=0;
	virtual IVBF_MarkModel* GetMarkModel()=0;

	// 复制
    virtual IVBF_MarkAction* Clone()=0;

    // 串行化
    virtual bool WriteToXML(TiXmlElement* pElemAction)=0;    // 写入：将模型动作信息写入指定的xml节点
    virtual bool ReadFromXML(TiXmlElement* pElemAction)=0;   // 读取：从指定的xml节点读取模型动作信息

	// 初始化 (在构造函数之后由系统调用)
    virtual bool Init(IVBF_MarkContext* pIContext)=0;

	// 更新 (在每帧绘制前由系统调用)，返回值为false表示未做更新处理（如模型不可见时）
	virtual bool Update()=0;

	// 执行json脚本
    virtual void ExecuteScript(const CVBF_Config& conf)=0;
};


#endif 
