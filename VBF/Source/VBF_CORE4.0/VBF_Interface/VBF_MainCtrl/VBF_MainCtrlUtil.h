//*************************************************************************************************************
// FileName��VBF_MainCtrlUtil.h
// Function���������йصĹ��ߺ���, �������صĳ�ʼ�����ͷ�
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
// ������VBF_CreateMainCtrl()
// �������������ؽӿڣ���ע�������е��������
// ������szDllName    -- �������ڶ�̬������֣�������Debug��ı�ʶ��.dll��׺���硰VBF_3DMainCtrl����������"VBF_3DMainCtrlD.dll"
//      szAppPath    -- Ӧ�ó��������·��
//      szSysSetPath -- �����ļ��е�����·�������ΪNULL����ʾλ��Ӧ�ó����µ�/SysSet/�ļ��У�
//----------------------------------------------------------------------------------------------------------
inline bool VBF_CreateMainCtrl(const char* szDllName, IVBF_MainCtrl*& pIMainCtrl, VBF_DynamicLibrary*& pLib,
	const char* szAppPath, const char* szSysSetPath=NULL)
{
	// ע��3D�������
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
		::VBF_sprintf(szErr, "%sװ�ز��ɹ�!", szDllNameFull);
		std::cout << szErr << std::endl;
		return false;
	}

	VBF_CreateMainObjectProc CreateMainObject = (VBF_CreateMainObjectProc)pLib->getProcAddress("VBF_CreateMainObject");
	if(NULL==CreateMainObject)
	{
		char szErr[256];
		::VBF_sprintf(szErr, "%sû�е���VBF_CreateMainObject()����!", szDllNameFull);
		std::cout << szErr << std::endl;
		return false;
	}

	// �������ؽӿ�
	pIMainCtrl = CreateMainObject();

	// ���ó���·��
	pIMainCtrl->SetAppPath(szAppPath);

	// ��������·��
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

	// ע�������е��������
	pIMainCtrl->RegisterComponentCfgFileDefault();

	// ѡ��Ĭ�Ϲ���
	pIMainCtrl->SelectTool("");
	return true;
}


//------------------------------------------------------------------------------------
// ������VBF_ReleaseMainCtrl()
// �������ͷ�3D����
//------------------------------------------------------------------------------------
inline void VBF_ReleaseMainCtrl(IVBF_MainCtrl*& pIMainCtrl, VBF_DynamicLibrary*& pLib)
{
	SAFE_RELEASE(pIMainCtrl);
	SAFE_DELETE(pLib);
}


#endif
