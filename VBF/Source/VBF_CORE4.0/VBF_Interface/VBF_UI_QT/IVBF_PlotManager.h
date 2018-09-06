/**************************************************************************************************
* @file IVBF_PlotManager.h
* @note 图标管理接口
* @author w00040
* @data 2017-9-21
**************************************************************************************************/
#ifndef IVBF_PLOT_MANAGER_H
#define IVBF_PLOT_MANAGER_H

#include <VBF_Base/VBF_Referenced.h>

#include <string>
#include <QWidget>

// 定义图标界面模块中专有接口的ID号
const char VBF_INTERFACE_PLOTMANAGER[]	= "图标管理接口";

/**
  * @class IVBF_PlotManager
  * @brief 图标管理类接口
  * @note 实现图标管理接口
  * @author w00040
*/
class IVBF_PlotManager : public CVBF_Referenced
{
public:
	/**  
	  * @brief 构造函数
	*/
	IVBF_PlotManager(){};

	/**  
	  * @brief 析构函数
	*/
	virtual ~IVBF_PlotManager(){};

	/**  
	  * @brief 实例化图标管理界面
	*/
	virtual void InitWidgetPlotManager(QWidget *parent) = 0;

	/**  
	  * @brief 获取图标管理窗体
	*/
	virtual void* GetWidgetPlotManager() = 0;

	/**  
	  * @brief 设置图标管理窗体位置
	*/
	virtual void SetPlotManagePosition(int x, int y, int w, int h) = 0;
};

#endif