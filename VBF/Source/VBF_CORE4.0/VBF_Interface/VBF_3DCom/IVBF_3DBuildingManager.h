//*******************************************************************
// FileName：IVBF_3DBuildingManager.h
// Function：地面建筑物管理接口
// Author:   杜莹
// Date:     2012-04-10
//*******************************************************************

#ifndef __IVBF_3DBUILDING_MANAGER_H__
#define __IVBF_3DBUILDING_MANAGER_H__

#include <vector>
#include <VBF_Base/VBF_Referenced.h>

namespace osg
{
	class Group;
	class UserDataContainer;
}

// 定义该组件的ID号
const char VBF_COMPONENT_3DBUILDINGMANAGER[]	= "Component: 3DBuildingManager";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DBUILDINGMANAGER[]	= "三维地面建筑物管理";	


// 建筑物被选中的消息
const char VBF_MESSAGE_3DBUIDING_SELECTED[]		= "Message: 3DBuilding Selected";	
const char VBF_MESSAGE_3DBUIDING_UNSELECTED[]	= "Message: 3DBuilding UnSelected";


// 定义工具ID号
const char VBF_TOOL_3DBUILDING_SELECT[]			= "Tool: Select One Building";			// 选择建筑物
const char VBF_TOOL_3DBUILDING_EDIT[]			= "Tool: Edit One Building";			// 编辑建筑物
const char VBF_TOOL_3DBUILDING_ADD[]			= "Tool: Add One Building";				// 添加建筑物

// 定义命令ID号
const char VBF_COMMAND_3DBUILDING_ADD[]			= "Command: 3DBuilding AddMesh";		// 添加建筑物
const char VBF_COMMAND_3DBUILDING_UPDATE[]		= "Command: 3DBuilding UpdateMesh";		// 修改建筑物
const char VBF_COMMAND_3DBUILDING_DELETE[]		= "Command: 3DBuilding DeleteMesh";		// 删除建筑物
const char VBF_COMMAND_3DBUILDING_TOGGLE[]		= "Command: 3DBuilding Toggle";			// 开/关建筑物

const char VBF_COMMAND_BUILDING_HIGHLIGHT_BOX[]	= "Command: Building Highlight Box";//使用包围盒进行高亮显示
const char VBF_COMMAND_BUILDING_HIGHLIGHT_MODULATE[]	= "Command: Building Highlight Modulate";//使用混色进行高亮显示


// 定义模型类型，该类型在xml配置文件中体现
const char VBF_MODELTYPE_TILE[]					= "Tile";		// 地块
const char VBF_MODELTYPE_BUILDING[]				= "Building";	// 建筑物
const char VBF_MODELTYPE_TREE[]					= "Tree";		// 树木


//---------------------------------------------------------------------------
// 定义结构体：VBF_MODELRESOURCEINFO
// 结构体描述：模型的素材信息，即ive文件的信息
//---------------------------------------------------------------------------
typedef struct _tagVBFModelResourceInfo
{
	_tagVBFModelResourceInfo() : strID(""), strFileName("*.ive") 
	{
		fDistIn = 2000.0f;
	}

	_tagVBFModelResourceInfo(const std::string& id, const std::string& type, const std::string& fn) : 
		strID(id), strType(type), strFileName(fn) 
	{
		fDistIn = 2000.0f;
	}

	_tagVBFModelResourceInfo& operator=(const _tagVBFModelResourceInfo& src)
	{
		// 防止src=src这样的操作
		if( this==&src )  return *this;	

		this->strID       = src.strID;
		this->strType	  = src.strType;
		this->strFileName = src.strFileName;
		this->fDistIn     = src.fDistIn;

		return *this;
	}
	
	std::string		strID;			// 素材的全局唯一ID号
	std::string		strType;		// 素材的模型类型：Building/Tree/Tile等
	std::string		strFileName;	// 素材对应的ive文件的绝对路径
	float			fDistIn;		// 素材实例最早出现的距离 (单位：米)

} VBF_MODELRESOURCEINFO;


class IVBF_3DBuildingManager:public CVBF_Referenced
{
public:	
	virtual ~IVBF_3DBuildingManager() {}

	// 设置/获取建筑物组件的xml配置文件名，不含路径，不允许与缺省文件名重复
	// 缺省为\\Lib\\SysSet\\3DMap\\VBF_3DBuildingConfig\\VBF_3DBuilding.xml
	// 如果该路径下没有该文件，返回false
	virtual bool        SetConfigFileName(const char* szFn)=0;
	virtual const char* GetConfigFileName()=0;

	// 设置/获取所有模型的可见性
	virtual void SetVisible(bool bVisible)=0;
	virtual bool IsVisible()=0;	
	
	// 说明：设置符合条件的模型的可见性
	// 参数：udc -- 查询条件，包含若干参数对
	// UserDataContainer的用法类似于：
	// ref_ptr<osg::DefaultUserDataContainer> udc = new osg::DefaultUserDataContainer;
	// udc->addUserObject( new osg::TemplateValueObject<float>("ModelType", "Building")  );	
	// 目前支持的数据类型包括：string/bool/char/unsigned char/short/unsigned short/int/unsigned int
	virtual void SetModelVisible(osg::UserDataContainer* udc, bool bVisible)=0;

	// 设置/获取模型标签文本的可见性
	virtual void SetLabelTextVisible(bool bVisible)=0;
	virtual void SetLabelTextVisible(osg::UserDataContainer* udc, bool bVisible)=0;
	virtual bool IsLabelTextVisible()=0;

	// 设置/获取模型标签图像的可见性
	virtual void SetLabelImageVisible(bool bVisible)=0;
	virtual bool IsLabelImageVisible()=0;

	// 设置/获取模型被选中时文本信息是否可见 (默认为可见)
	virtual void SetSelectedInfoVisible(bool bVisible)=0;
	virtual bool IsSelectedInfoVisible()=0;

	// 设置/获取模型被选中时多媒体信息是否可见
	virtual void SetSelectedMediaVisible(bool bVisible)=0;
	virtual bool IsSelectedMediaVisible()=0;

	// 设置/获取用哪个热键循环浏览被选模型的多媒体信息，该值由osg::KeySymbol定义 (默认为用Up/Down键)
	// 参数：bNext为true表示浏览下一个，false表示浏览上一个
	virtual void SetKeyToBrowseMedia(bool bNext, int nKey)=0;
	virtual int  GetKeyToBrowseMedia(bool bNext)=0;

	// 说明：按参数对选择并高亮显示模型 该参数由xml配置文件设定
	// 返回：如果选择到指定条件的模型，返回true；否则，返回false
	virtual bool SelectModel(osg::UserDataContainer* udc)=0;
	
	// 取消选择状态
	virtual void ClearSelected()=0;

	// 获取被选中建筑物的个数
	virtual int GetNumSelected()=0;

	// 获取被n个被选中的建筑物，仅用于遍历，与顺序无关
	virtual osg::IVBF_SGNodeGroup* GetSelected(int nIndex)=0;

	// 设置高亮显示时是否使用包围盒样式，默认为使用包围盒
	// 参数：bBox      -- 是否使用包围盒样式
	//       nTimes    -- 闪烁的次数
	//       nInterval -- 闪烁的间隔帧数
	virtual void SetHighlightStyleOfBox(bool bBox)=0;

	// 设置高亮显示的颜色，值域为[0, 1]，默认为[1,0,0,1]
	virtual void SetHighlightColor(float r, float g, float b, float a)=0;

	// 设置高亮显示的速度
	// 参数：nTimes    -- 闪烁的次数，默认为只闪烁3次
	//       nInterval -- 闪烁的间隔帧数，默认为间隔20帧
	// 参数：bAlways   -- 是否是否一直闪烁
	virtual void SetHighlightSpeed(int nTimes, int nInterval, bool bAlways)=0;

	// 说明：按查询条件对模型进行反向选择，并对选择结果进行透明淡化显示
	// 参数：udc -- 查询条件，包含若干参数对
	// 返回：如果反向选择到指定条件的模型，返回true；否则，返回false
	virtual bool SelectModelInverse(osg::UserDataContainer* udc)=0;

	// 取消反向选择结果
	virtual void ClearSelectedInverse()=0;

	// 设置反向选择到的建筑物的透明颜色
	virtual void SetTransparentColorAmbient(float r, float g, float b, float a)=0;  // 默认为(0.2, 0.2, 0.2, 1.0)
	virtual void SetTransparentColorDiffuse(float r, float g, float b, float a)=0;	// 默认为(1.0, 1.0, 0.97, 0.3)

	// 高亮显示/取消符合条件的模型
	virtual void HighlightModel(osg::UserDataContainer* udc, float r, float g, float b, float a, bool bModulate=true)=0;
	virtual void UnHighlightModel(osg::UserDataContainer* udc)=0;

	// 切换所有模型到指定状态
	virtual void SwitchAllModels(const char* szSwitchKey, const char* szSwitchValue)=0;
};

#endif 
