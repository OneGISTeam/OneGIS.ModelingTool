//***************************************************************************************
// FileName：IVBF_MainCtrl.h
// Function：图形集成框架接口。
//           该接口完成系统3D主控接口内容，负责控件注册、命令分发、事件处理等任务。
// Author:   杜莹
// Date:     2012-03-22
//***************************************************************************************

#ifndef __IVBF_MAIN_CTRL_H__
#define __IVBF_MAIN_CTRL_H__

#include "VBF_Macros.h"
#include "IVBF_Observer.h"
#include "IVBF_Subject.h"
#include "IVBF_Component.h"

// 定义模块中专有接口的ID号
const char VBF_INTERFACE_MAIN[]				=	"主控";	

// 定义标准接口的ID号
const char VBF_INTERFACE_MAIN_COMMAND[]	    =	"主控命令响应接口";	
const char VBF_INTERFACE_MAIN_TOOL[]	    =	"主控交互工具响应接口";	
const char VBF_INTERFACE_MAIN_UIPROCESSOR[]	=	"主控用户界面处理接口";	
const char VBF_INTERFACE_MAIN_MESSAGE[]	    =	"主控消息响应接口";
const char VBF_INTERFACE_MAIN_EVENTHANDLER[]    =	"主控交互事件响应接口";

// 定义消息ID号
const char VBF_MESSAGE_VIEWPORTCHANGED[]		= "Message: Viewport Changed";			// 视口更改了
const char VBF_MESSAGE_ALLCOMPONENTS_INITED[]	= "Message: All Components Inited";		// 所有组件初始化完毕

const char VBF_MESSAGE_REGIST_COM[]		= "Message: Regist Component";	// 注册组件
const char VBF_MESSAGE_UNREGIST_COM[]	= "Message: UnRegist Component";	// 注册组件


// 定义命令ID号
const char VBF_COMMAND_CLEARSCREEN[]			= "Command: Clear Screen";

class IVBF_PropertySet;


//--------------------------------------------------------------------------------------------------
// 定义接口：IVBF_MainCtrl
// 接口描述：3D图形集成框架接口，完成系统主框接口内容，负责控件注册、命令分发、事件处理、绘图等任务。
//---------------------------------------------------------------
class IVBF_MainCtrl : public IVBF_Observer, public IVBF_Subject
{
public:
	virtual ~IVBF_MainCtrl() {}

public:

	// 为了兼容DTIS，临时使用？？？？？？？
	virtual char* GetType() = 0;

	//---------------------------------------------------------------
	// 获取/设置主控的ID值。
	//---------------------------------------------------------------
	virtual long GetID() = 0 ;
	virtual void SetID(long lID) = 0 ;

	//---------------------------------------------------------------
	// 获取/设置主控的用途。
	//---------------------------------------------------------------
	virtual void SetPurpose( const char* pPurpose )=0;
	virtual char* GetPurpose( ) = 0;



	//---------------------------------------------------------------
	// 删除系统主控对象。
	//---------------------------------------------------------------
	virtual void Release() = 0;

	//---------------------------------------------------------------
	// 从动态库文件注册组件。
	// 根据指定的组件动态库文件，注册组件。参数为组件动态库文件的全路径名。
	// szComponentFile:组件所在动态库的文件路径。
	// return 如果成功删除返回true，否则返回false。
	//---------------------------------------------------------------
    virtual bool RegisterComponentFile(const char* szComponentFile) = 0;

	//---------------------------------------------------------------
	// 从配置文件注册组件。
	// 根据指定的组件配置文件，注册组件。参数为组件配置文件的全路径名。
	// 组件配置文件中包含要注册的一组组件动态库名称。
	// szComponentCfgFile ：组件所在配置文件的路径。
	//---------------------------------------------------------------
	virtual bool RegisterComponentCfgFile(const char* szComponentCfgFile) = 0;

	//---------------------------------------------------------------
	// 注册/卸载已加入系统中的全部组件。
	//---------------------------------------------------------------
    virtual void RegisterComponentCfgFileDefault() = 0;	


	//---------------------------------------------------------------
	// 删除指定组件。
	// szComponentID:组件ID。
	// return 如果成功删除返回true，否则返回false。
        //---------------------------------------------------------------__declspec
	virtual bool RemoveComponent(const char* szComponentID) = 0;

    virtual void* PreRemoveComponent(const char* szComponentFile)=0;

	//---------------------------------------------------------------
	// 指定组件ID，获取组件接口指针。
	// szComponentID:组件ID。
	// return 组件指针，如果没有该组件返回NULL。
	//---------------------------------------------------------------
	virtual IVBF_Component* GetComponentPtr(const char* szComponentID) = 0;
	
	
	//---------------------------------------------------------------
	// 获取指定的接口指针。
	// 由于无法知道每个接口的类型，所以每个接口都以void*返回，
	// 调用者需要通过强制类型转换成需要的接口类型。
	// szInterfaceID:接口ID。
	// 接口指针。 szComponentID,排出的组件ID，防止反复查找，形成死循环
	//---------------------------------------------------------------
	virtual void* QueryInterface(const char* szInterfaceID,const char* szComponentID = NULL) = 0;
	
	
	//---------------------------------------------------------------
	// 执行指定命令。
	// szCommandID:命令ID。
	// pInParam:输入参数，其含义有命令本身决定。
	// pOutParam:输出参数，其含义有命令本身决定。
	// return 如果执行成功返回true，否则返回false。
	//---------------------------------------------------------------
	virtual bool ExecuteCommand(const char* szCommandID, IVBF_PropertySet* pInParam, IVBF_PropertySet* pOutParam) = 0;

	//---------------------------------------------------------------
	// 选中交互工具。
	// szToolID:交互工具ID。
	// return 如果选择成功返回true，否则返回false。
	//---------------------------------------------------------------
	virtual bool SelectTool(const char* szToolID) = 0;
	
	//---------------------------------------------------------------
	// 获取当前工具。
	// return 当前工具ID。
	//---------------------------------------------------------------
	virtual const char* GetCurrentTool() = 0;

	//---------------------------------------------------------------
	// 鼠标事件入口，为了兼容DTIS，临时使用？？？？？？？
	// nMouseEvent:鼠标事件类型，可以是如下值之一:
	// DTIS_MOUSE_LBUTTONDOWN、DTIS_MOUSE_LBUTTONUP、 DTIS_MOUSE_LBUTTONDBLCLK、DTIS_MOUSE_RBUTTONDOWN、
	// DTIS_MOUSE_RBUTTONUP、DTIS_MOUSE_MOVE、DTIS_MOUSE_WHEEL、DTIS_MOUSE_CANCEL。
	// nKeyStatus: 键盘状态，可以是如下值的任意个:
	// DTIS_MOUSE_LBUTTON、DTIS_MOUSE_RBUTTON、DTIS_MOUSE_SHIFT、DTIS_MOUSE_CONTROL、DTIS_MOUSE_MBUTTON。
	// nX，nY:鼠标的当前位置。
	// nDelta:鼠标滚轮的滚动尺寸。
	// return 0表示鼠标事件不成功，其它值表示成功，每个值的含义由具体组件决定。
	//---------------------------------------------------------------
	virtual bool OnMouseEvent(int nMouseEvent, int nKeyStatus, int nX, int nY, int nDelta) = 0;

	//---------------------------------------------------------------
	// 键盘事件入口，为了兼容DTIS，临时使用？？？？？？？
	// nKeyEvent:键盘事件类型:可以是如下值之一
	// DTIS_KEY_DOWN、DTIS_KEY_UP、DTIS_KEY_CHAR。	
	// nChar:键盘按下的字符。
	// nRepCount:重复按下次数。
	// nFlag:状态参数，具体含义参见msdn中OnKeyDown,OnKeyUp中nFlags的说明。
	// return 0表示鼠标事件不成功，其它值表示成功，每个值的含义由具体组件决定。
	//---------------------------------------------------------------
	virtual bool OnKeyEvent(int nKeyEvent, int nChar, int nRepCount, int nFlag) = 0;


	//---------------------------------------------------------------
	// 命令更新。
	// 设置工具条或菜单中响应的命令的更新信息，该函数由系统调用。
	// szCommandID:命令id。
	// pEnable:是否可用。
	// pCheck:是否选中。
	// pRadio:是否单选。
	// szText:文字内容。
	// return 如果已经处理命令返回true，否则返回false。
	//---------------------------------------------------------------
	virtual bool UpdateUI(const char* szCommandID, int* pEnable, int* pCheck, int* pRadio, char* szText) = 0;
	

	//---------------------------------------------------------------
	// 订购/取消订购指定的消息。
	// 该函数实现消息的“订购-发布”模式，系统主控会把消息发到订购了该消息的组件。
	// szMessage: 消息ID。
	// pIMessage: 消息订购者
	//---------------------------------------------------------------
	virtual void SubscribeMessage(const char* szMessage, IVBF_Component* pIComponent) = 0;
	virtual void UnSubscribeMessage(const char* szMessage, IVBF_Component* pIComponent) = 0;

	//---------------------------------------------------------------
	// 发送消息。
	// 该函数用于向其它组件发送消息，系统主控会把消息发到所有响应该消息的组件。
	// szMessage:消息ID。
	// nValue, pValue:消息参数，具体含义有消息本身决定。
	//---------------------------------------------------------------
    virtual void SendMessage(void* pSender,const char* szMessage, int nValue, void* pValue) = 0;

	
	//---------------------------------------------------------------
	// 激活。
	// 在多文档窗口中，每次切换当前文档时，都要把当前文档设置为活动状态。主控会向每个组件发送消息，
	// 每个组件可以在此时做一些切换动作（如工具条上的对话框可以在此时设置与其关联的主控，一些非模态对话框可以在此时切换其关联的主控）。
	//---------------------------------------------------------------
	virtual void SetActive(bool bActive) = 0;

	virtual void  SetAppPath(const char* szPath)=0;
	virtual char* GetAppPath()=0;
	virtual void  SetSysSetPath(const char* szPath)=0;
	virtual char* GetSysSetPath()=0;
};


#ifdef WIN32
    #ifdef MAIN_EXPORTS
            #define MAIN_API extern "C" __declspec(dllexport)
    #else
            #define MAIN_API extern "C" __declspec(dllimport)
    #endif
#else

    #ifdef MAIN_EXPORTS
            #define MAIN_API extern "C"
    #else
            #define MAIN_API  extern "C"
    #endif
#endif


//----------------------------------------------------------------------
// 创建主控接口函数，返回3D主控指针。
//----------------------------------------------------------------------
MAIN_API IVBF_MainCtrl*  VBF_CreateMainObject();


#endif
