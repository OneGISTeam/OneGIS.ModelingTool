//***************************************************************************************
// FileName：IVBF_3DMainCtrl.h
// Function：图形集成框架接口。
//           该接口完成系统3D主控接口内容，负责控件注册、命令分发、事件处理等任务。
// Author:   杜莹
// Date:     2012-03-22
//***************************************************************************************

#ifndef __IVBF_3DMAIN_CTRL_H__
#define __IVBF_3DMAIN_CTRL_H__

#include "VBF_Macros.h"
#include <VBF_MainCtrl/IVBF_MainCtrl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <string>

// 定义该组件的ID号
const char VBF_COMPONENT_3DMAIN[]	= "Component: 3DMain";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DMAIN[]	    =	"三维主控";
const char VBF_INTERFACE_3D_MAIN_MAP[]	=	"三维主图";
// 定义消息
const char VBF_MESSAGE_VIEW_ADDED[]	      = "Message: A View Added";	   // 添加了一个osgView, nValue=ViewCount, pValue=CVBF_View*
const char VBF_MESSAGE_3DCAMERA_CHANGED[] = "Message: 3DCamera Changed";   // 相机的位置和姿态发生了变化
const char VBF_MESSAGE_ACTIVEMAP_CHANGED[]= "Message: Active Map Changed"; // 激活的地图（星球）发生了变化
const char VBF_MESSAGE_EARTHMAP_CHANGED[]= "Message: Earth Map Changed"; // 地球的地图发生了变化

class IVBF_View;
class IVBF_Viewer;
class IVBF_Log;
class IVBF_Map;

//----------------------------------------------------
// 定义接口：IVBF_3DMainCtrl
// 接口描述：3D图形集成框架接口
//----------------------------------------------------
class IVBF_3DMainCtrl : public IVBF_MainCtrl
{
public:
	virtual ~IVBF_3DMainCtrl() {}

	// 获取主Viewer
	virtual IVBF_Viewer* GetViewer()=0;

	// 添加/获取3D视图指针
	virtual bool	   AddView(IVBF_View* pView)=0;
    virtual void	   RemoveView(IVBF_View* pView)=0;
	virtual int		   GetNumViews()=0;
	virtual IVBF_View* GetView(int nIndex)=0;
    virtual osg::IVBF_SGNodeGroup* GetSceneGraph()=0;
    virtual osg::IVBF_SGNodeGroup* GetEarthNode()=0;
    virtual IVBF_Map* GetMainMap()=0;
    virtual void LoadMap(std::string strMapFileName)=0;
	// 开始执行主循环
	virtual int Start()=0;

	// 获取日志接口的指针，以便各个组件向其中写入日志信息 (如出错信息)
	virtual IVBF_Log* GetLogPtr()=0;

};



#endif
