//*******************************************************************
// FileName：VBF_MarkPopupMenu.h
// Function：实体模型的弹出式菜单
// Author:   杜莹
// Date:     2015-01-30
//*******************************************************************

#ifndef __VBF_MARK_POPUP_MENU_H__
#define __VBF_MARK_POPUP_MENU_H__


// 右键弹出式菜单项的样式，表示不同类型的菜单项（不能组合使用）
#define IDM_ITEM_STYLE_COMMON						1  // 普通样式：仅有文字
#define IDM_ITEM_STYLE_POPUP						2  // 弹出式：文字 + 小三角形（指示有弹出式子菜单）
#define IDM_ITEM_STYLE_SEPARATOR					3  // 分隔线
#define IDM_ITEM_STYLE_CHECK						4  // 复选框 + 文字（通过对勾勾选）
#define IDM_ITEM_STYLE_RADIO_BEGIN					5  // 单选组的起始（单选框 + 文字）
#define IDM_ITEM_STYLE_RADIO						6  // 单选组的成员（单选框 + 文字）
#define IDM_ITEM_STYLE_RADIO_END					7  // 单选组的结束（单选框 + 文字）



// 右键弹出式菜单项的ID号，对应不同的操作
#define IDM_MARK_OPERATE_BASE						80000

#define IDM_MARK_OPERATE_DEPTHTEST					(IDM_MARK_OPERATE_BASE+1) // 深度测试
#define IDM_MARK_OPERATE_DEPTHWRITE					(IDM_MARK_OPERATE_BASE+2) // 深度写入

#define IDM_MARK_OPERATE_FILLMODE_SOLID				(IDM_MARK_OPERATE_BASE+3) // 填充模式：填充
#define IDM_MARK_OPERATE_FILLMODE_WIREFRAME			(IDM_MARK_OPERATE_BASE+4) // 填充模式：网格
#define IDM_MARK_OPERATE_FILLMODE_POINT				(IDM_MARK_OPERATE_BASE+5) // 填充模式：点
#define IDM_MARK_OPERATE_FILLMODE_SOLIDWIREFRAME	(IDM_MARK_OPERATE_BASE+6) // 填充模式：填充+网格线

#define IDM_MARK_OPERATE_ASSIGNIFF					(IDM_MARK_OPERATE_BASE+10) // 指定敌我类别（预留出10种类型）

#define IDM_MARK_OPERATE_TAILFLAME_SHOW				(IDM_MARK_OPERATE_BASE+20) // 尾焰是否可见
#define IDM_MARK_OPERATE_TRAIL_SHOW					(IDM_MARK_OPERATE_BASE+21) // 轨迹线是否可见
#define IDM_MARK_OPERATE_LABEL_SHOW					(IDM_MARK_OPERATE_BASE+22) // 标注是否可见
#define IDM_MARK_OPERATE_LABEL_DETAIL				(IDM_MARK_OPERATE_BASE+23) // 详细标注是否可见
#define IDM_MARK_OPERATE_HINTLINE_SHOW				(IDM_MARK_OPERATE_BASE+24) // 高度线是否可见
#define IDM_MARK_OPERATE_IFF_SHOW					(IDM_MARK_OPERATE_BASE+25) // 敌我类别是否可见
#define IDM_MARK_OPERATE_INTERSECT_SHOW				(IDM_MARK_OPERATE_BASE+26) // 与地面交线是否可见
#define IDM_MARK_OPERATE_TRAILSMOKE_SHOW			(IDM_MARK_OPERATE_BASE+27) // 模型的尾烟是否可见
#define IDM_MARK_OPERATE_COORDSYS_SHOW              (IDM_MARK_OPERATE_BASE+28) // 点状模型的局部坐标系是否可见

#define IDM_MARK_OPERATE_ASSIGNTASK					(IDM_MARK_OPERATE_BASE+30) // 分配作战任务
#define IDM_MARK_OPERATE_TASK_SHOW					(IDM_MARK_OPERATE_BASE+31) // 显示作战任务
#define IDM_MARK_OPERATE_ASSIGNWAEPON				(IDM_MARK_OPERATE_BASE+32) // 武器配置

#define IDM_MARK_OPERATE_POWERMAP_SHOW				(IDM_MARK_OPERATE_BASE+50) // 威力图是否可见
#define IDM_MARK_OPERATE_POWERMAP_SOLID				(IDM_MARK_OPERATE_BASE+51) // 威力图填充模式
#define IDM_MARK_OPERATE_POWERMAP_WIREFRAME			(IDM_MARK_OPERATE_BASE+52) // 网格模式
#define IDM_MARK_OPERATE_POWERMAP_POINT				(IDM_MARK_OPERATE_BASE+53) // 威力图点模式
#define IDM_MARK_OPERATE_POWERMAP_SOLIDWIREFRAME	(IDM_MARK_OPERATE_BASE+54) // 威力图填充+网格线模式
#define IDM_MARK_OPERATE_POWERMAP_COLOR				(IDM_MARK_OPERATE_BASE+55) // 威力图颜色设置

#define IDM_MARK_OPERATE_AIRLINE_NEW				(IDM_MARK_OPERATE_BASE+70) // 新建航线
#define IDM_MARK_OPERATE_AIRLINE_ASSIGN				(IDM_MARK_OPERATE_BASE+71) // 指定航线
#define IDM_MARK_OPERATE_AIRLINE_SHOW_PRIMARY		(IDM_MARK_OPERATE_BASE+72) // 显示原始航线
#define IDM_MARK_OPERATE_AIRLINE_SHOW_SMOOTH		(IDM_MARK_OPERATE_BASE+73) // 显示光滑后的航线
#define IDM_MARK_OPERATE_AIRLINE_SHOW_PIPELINE		(IDM_MARK_OPERATE_BASE+74) // 显示航空管线
#define IDM_MARK_OPERATE_AIRLINE_SHOW_HINTLINE		(IDM_MARK_OPERATE_BASE+75) // 显示航线高度指示线
#define IDM_MARK_OPERATE_AIRLINES_OUTPUT_COOR		(IDM_MARK_OPERATE_BASE+76) // 输出航线坐标

// 卫星模型的菜单
#define IDM_MARK_OPERATE_SATELLITE_INFO				(IDM_MARK_OPERATE_BASE+80) // 显示卫星信息
#define IDM_MARK_OPERATE_SATELLITE_ORBIT			(IDM_MARK_OPERATE_BASE+81) // 显示卫星轨道
#define IDM_MARK_OPERATE_SATELLITE_SPECIALPOINTS	(IDM_MARK_OPERATE_BASE+82) // 显示轨道上的特殊点（如近地点、远地点）
#define IDM_MARK_OPERATE_SATELLITE_VERTLINE			(IDM_MARK_OPERATE_BASE+83) // 显示卫星的垂线
#define IDM_MARK_OPERATE_SATELLITE_SPHEREATTITUDE	(IDM_MARK_OPERATE_BASE+84) // 显示卫星的姿态球
#define IDM_MARK_OPERATE_SATELLITE_GROUNDTRACK		(IDM_MARK_OPERATE_BASE+85) // 显示星下点轨迹
#define IDM_MARK_OPERATE_SATELLITE_SENSOR			(IDM_MARK_OPERATE_BASE+86) // 显示卫星的传感器


//---------------------------------------------------------------------
// 定义类：CVBF_PopupMenuItem
// 类描述：右键弹出式菜单中的子项
//---------------------------------------------------------------------
class CVBF_PopupMenuItem
{
public:
	unsigned int 	nStyle;		// 菜单项的样式，参见IDM_ITEM_STYLE_COMMON等的定义
	std::string		strLabel;	// 菜单项的文字标签
	unsigned int 	nID;		// 菜单项对应的操作，参见IDM_MARK_OPERATE_BASE等的定义
	bool			bCheck;		// 是否勾选（仅适用于IDM_ITEM_STYLE_CHECK和IDM_ITEM_STYLE_RADIO两种样式）

	CVBF_PopupMenuItem()
	{
		nStyle		= IDM_ITEM_STYLE_COMMON;
		strLabel	= "";
		nID			= 0;
		bCheck		= false;
	}

	CVBF_PopupMenuItem(unsigned int nStyle0)
	{
		nStyle		= nStyle0;
		strLabel	= "";
		nID			= 0;
		bCheck		= false;
	}

	CVBF_PopupMenuItem(unsigned int nStyle0, const std::string& sLabel0)
	{
		nStyle		= nStyle0;
		strLabel	= sLabel0;
		nID			= 0;
		bCheck		= false;
	}

	CVBF_PopupMenuItem(unsigned int nStyle0, const std::string& sLabel0, unsigned int nID0, bool bCheck0)
	{
		nStyle		= nStyle0;
		strLabel	= sLabel0;
		nID			= nID0;
		bCheck		= bCheck0;
	}

	CVBF_PopupMenuItem& operator=(const CVBF_PopupMenuItem& src)
	{
		if(this==&src) return *this;

		nStyle		= src.nStyle;
		strLabel	= src.strLabel;
		nID			= src.nID;
		bCheck		= src.bCheck;

		return *this;
	}

	bool operator==(const CVBF_PopupMenuItem& src)
	{
		return (nStyle==src.nStyle && strLabel==src.strLabel && nID==src.nID && bCheck==src.bCheck);
	}
};


#endif 
