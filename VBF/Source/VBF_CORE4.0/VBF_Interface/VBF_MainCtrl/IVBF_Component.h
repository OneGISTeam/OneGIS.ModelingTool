//***************************************************************************************
// FileName：IVBF_Component.h
// Function：组件接口
//           每个需要注册到组件容器的组件都要实现该接口，系统组件容器通过该接口完成对注册和专有接口的处理。
//           命令处理、绘图、交互工具、命令更新接口通过返回专有接口来完成。
//           每个组件只要完成需要实现的接口即可、不用实现全部接口。
// Author:   武玉国
// Date:     2006-4-22
//***************************************************************************************

#ifndef __IVBF_COMPONENT_H__
#define __IVBF_COMPONENT_H__

class IVBF_MainCtrl;


class IVBF_Component
{
public:
	virtual ~IVBF_Component() {}

public:

	//---------------------------------------------------------------
	// Release:释放组件对象。
	//---------------------------------------------------------------
	virtual void Release() = 0;
	
	//---------------------------------------------------------------
	// GetComponentID获取组件ID。
	// 每个组件有一个全局唯一的标识，用来和其他组件区分。该函数用于获取组件ID。
	//---------------------------------------------------------------
	virtual const char* GetComponentID() = 0;
	
	//---------------------------------------------------------------
	// Init:初始化组件对象。
	// 在系统注册所有组件后，调用每个组件的该函数。每个组件的初始化操作可以在该函数中完成。
	// 如果初始化成功返回true，否则返回false。
	//---------------------------------------------------------------
	virtual bool Init() = 0;

	//---------------------------------------------------------------
	// Finish:清理组件对象。
	// 在系统注销所有组件前，调用每个组件的该函数。每个组件的清理操作可以在该函数中完成。
	// 如果初始化成功返回true，否则返回false。
	//---------------------------------------------------------------
	virtual bool Finish() = 0;

	//---------------------------------------------------------------
	// GetInterfaceCount:获取组件支持的专有接口数目。
	// 获取组件支持的专有接口数目。不包括标准接口如 ：IVBF_Commad、IVBF_Message、
	// IVBF_Tool、IVBF_2DDrawer、IVBF_UIProcessor、IVBF_CVBF_Timer、IVBF_3DDrawer、IVBF_Status。
	// return 支持的专有接口数目。
	//---------------------------------------------------------------
	virtual int GetInterfaceCount() = 0;

	//---------------------------------------------------------------
	// GetInterfaceID:获取组件所支持的指定专有接口ID。
	// 只要依次返回每个专有接口的ID就可以，与顺序无关。
	// nIndex ：依次访问接口ID的索引号。
	// return 指定专有接口ID。
	//---------------------------------------------------------------
	virtual const char* GetInterfaceID(int nIndex) = 0;

	//---------------------------------------------------------------
	// QueryInterface:获取指定的接口指针。
	// szInterfaceID: 接口ID。
	// return 指定专有接口指针。
	//---------------------------------------------------------------
	virtual void* QueryInterface(const char* szInterfaceID) = 0;

	
	//---------------------------------------------------------------
	// GetComponentDesc:获取组件功能的描述信息。
	// return 组件功能的描述信息。
	//---------------------------------------------------------------
    virtual const char* GetComponentDesc()=0;


	//---------------------------------------------------------------
	// SetCopyRight:设置版权。
	// return 是否正确。
	//---------------------------------------------------------------
    virtual bool SetCopyRight(const char* szUser,const char* szPassword)=0;


};

#ifdef WIN32
    #ifndef COMPONENT_API
            #ifdef COMPONENT_EXPORTS
                    #define COMPONENT_API extern "C" __declspec(dllexport)
            #else
                    #define COMPONENT_API extern "C" __declspec(dllimport)
            #endif
    #endif
#else

    #ifndef COMPONENT_API
            #ifdef COMPONENT_EXPORTS
                    #define COMPONENT_API extern "C"
            #else
                    #define COMPONENT_API extern "C"
            #endif
    #endif

#endif




//---------------------------------------------------------------
// brief 创建组件函数。
// 创建组件函数，每个组件动态库对外只导出该函数。
// pMain ：组件所在主控指针。
// return 创建的组件指针。
//---------------------------------------------------------------
COMPONENT_API       IVBF_Component*  VBF_CreateComponentObject(IVBF_MainCtrl* pIMainCtrl);



#endif

