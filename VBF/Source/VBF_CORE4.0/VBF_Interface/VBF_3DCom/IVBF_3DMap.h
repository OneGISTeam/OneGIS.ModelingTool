#ifndef __IVBF_3DMAP_H__
#define __IVBF_3DMAP_H__


#include <VBF_MainCtrl/IVBF_PropertySet.h>
#include <VBF_3DMap/VBF_EarthUtil/VBF_ColorFilterRGB.h>
#include <VBF_3DMap/VBF_EarthUtil/VBF_ColorFilterHSL.h>
#include <VBF_3DMap/VBF_Terrain/IVBF_Map.h>


// 定义该组件的ID号
const char VBF_COMPONENT_3DMAP[]	= "Component: 3DMap";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DMAP[]	= "三维地图";

// 定义命令ID号
const char VBF_COMMAND_SHOWDIALOG_FILTERRGB[]       = "Command: Show Dialog FilterRGB";     // 显示地图调色对话框：RGB模式
const char VBF_COMMAND_SHOWDIALOG_FILTERHSL[]       = "Command: Show Dialog FilterHSL";     // 显示地图调色对话框：HSL模式
const char VBF_COMMAND_SHOWDIALOG_LAYERCONTROL[]    = "Command: Show Dialog LayerControl";  // 显示地图图层控制对话框
const char VBF_COMMAND_SHOWDIALOG_NATUREOPTIONS[]   = "Command: Show Dialog NatureOptions"; // 显示自然环境选项对话框
const char VBF_COMMAND_SHOWDIALOG_TIMER[]   = "Command: Show Dialog Set Time"; // 显示设置时间对话框
const char VBF_COMMAND_SHOWDIALOG_MAP_ADDIMAGELAYER[]    = "Command: Show Dialog Map AddImageLayer";  // 显示添加影像图层对话框


//-------------------------------------------------------------------
// 定义接口：IVBF_3DMap
// 接口描述：三维地图组件的接口
//-------------------------------------------------------------------
class IVBF_3DMap
{
public:	
	virtual ~IVBF_3DMap() {}
};

#endif 
