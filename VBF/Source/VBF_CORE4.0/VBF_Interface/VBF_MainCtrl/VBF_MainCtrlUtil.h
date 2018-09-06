//*************************************************************************************************************
// FileName：VBF_MainCtrlUtil.h
// Function：与主控有关的工具函数, 负责主控的初始化与释放
// Date:     2012-03-29
//*************************************************************************************************************

#ifndef __VBF_MAINCTRL_UTIL_H__
#define __VBF_MAINCTRL_UTIL_H__

#include "VBF_OS.h"
#include "VBF_STL.h"
#include "VBF_Macros.h"
#include "IVBF_MainCtrl.h"
#include <VBF_Common/VBF_Utils/VBF_DynamicLibrary.h>


#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#include <direct.h>
#define lumkdir(t) (_mkdir(t))
#else
#include <unistd.h>
#include <iostream>
#define lumkdir(t) (mkdir(t,0755))
#endif



#include <stdlib.h>

#ifdef WIN32
#include <Windows.h>
#endif

//----------------------------------------------------------------------------------------------------------
// 函数：VBF_CreateMainCtrl()
// 描述：创建主控接口，并注册主控中的所有组件
// 参数：szDllName    -- 主控所在动态库的名字，不包含Debug版的标识和.dll后缀，如“VBF_3DMainCtrl”，而不是"VBF_3DMainCtrlD.dll"
//      szAppPath    -- 应用程序的完整路径
//      szSysSetPath -- 配置文件夹的完整路径（如果为NULL，表示位于应用程序下的/SysSet/文件夹）
//----------------------------------------------------------------------------------------------------------
inline bool VBF_CreateMainCtrl(const char* szDllName, IVBF_MainCtrl*& pIMainCtrl, VBF_DynamicLibrary*& pLib,
	const char* szAppPath, const char* szSysSetPath=NULL)
{
	// 注册3D所有组件
#ifdef WIN32
	typedef IVBF_MainCtrl* (__cdecl *VBF_CreateMainObjectProc) ( void );
#else
	typedef IVBF_MainCtrl* ( *VBF_CreateMainObjectProc) ( void );
#endif

	char szDllNameFull[256];

#ifdef WIN32
#ifdef _DEBUG
	::VBF_sprintf(szDllNameFull, "%sd.dll", szDllName);
#else
	::VBF_sprintf(szDllNameFull, "%s.dll", szDllName);
#endif
#else
	::VBF_sprintf(szDllNameFull, "lib%s.so", szDllName);
#endif

	char *pathvar;
	pathvar = getenv("PATH");

	std::string strPath = pathvar;
	strPath.append(";").append(szAppPath);
	std::cout<<strPath<<std::endl;

#ifdef WIN32
	SetEnvironmentVariable("PATH", strPath.c_str());
//	std::cout<<getenv("PATH")<<std::endl;
	_chdir(szAppPath);
#else
	setenv("PATH", strPath.c_str(), 0);
	std::cout<<getenv("PATH")<<std::endl;
	chdir(szAppPath);
#endif

	pLib = VBF_DynamicLibrary::loadLibrary(szDllNameFull);
	if(NULL==pLib)
	{
		char szErr[256];
		::VBF_sprintf(szErr, "%s装载不成功!", szDllNameFull);
		std::cout << szErr << std::endl;
		return false;
	}

	VBF_CreateMainObjectProc CreateMainObject = (VBF_CreateMainObjectProc)pLib->getProcAddress("VBF_CreateMainObject");
	if(NULL==CreateMainObject)
	{
		char szErr[256];
		::VBF_sprintf(szErr, "%s没有导出VBF_CreateMainObject()函数!", szDllNameFull);
		std::cout << szErr << std::endl;
		return false;
	}

	// 创建主控接口
	pIMainCtrl = CreateMainObject();

	// 设置程序路径
	pIMainCtrl->SetAppPath(szAppPath);

	// 设置配置路径
	if(NULL==szSysSetPath || strlen(szSysSetPath)==0)
	{
		char szPathDef[MAX_PATH];
		::VBF_sprintf(szPathDef, "%s/SysSet", szAppPath);
		pIMainCtrl->SetSysSetPath(szPathDef);
	}
	else
	{
		pIMainCtrl->SetSysSetPath(szSysSetPath);
	}

	// 注册主控中的所有组件
	pIMainCtrl->RegisterComponentCfgFileDefault();

	// 选择默认工具
	pIMainCtrl->SelectTool("");
	return true;
}


//------------------------------------------------------------------------------------
// 函数：VBF_ReleaseMainCtrl()
// 描述：释放3D主控
//------------------------------------------------------------------------------------
inline void VBF_ReleaseMainCtrl(IVBF_MainCtrl*& pIMainCtrl, VBF_DynamicLibrary*& pLib)
{
	SAFE_RELEASE(pIMainCtrl);
	SAFE_DELETE(pLib);
}


#endif
