//*******************************************************************
// FileName��  VBF_OS.h
// Function��  �����ϵͳ��ƽ̨��ص�����
// Author:     ��Ө
// Date:       2012-11-01
//*******************************************************************

#ifndef __VBF_OS_H__
#define __VBF_OS_H__

// �������ϵͳ/ƽ̨��ֻ����ѡ��һ��
//#define VBF_OS_WINDOWS
//#define VBF_OS_LINUX
//#define VBF_OS_VXWORKS

// Windows����ϵͳ��ʹ�õĶ����뺯��
#ifdef VBF_OS_WINDOWS
	#include "VBF_OS_Windows.h"
#endif


// ����ΪLinux����ϵͳ��ʹ�õĶ����뺯��
#ifdef VBF_OS_LINUX
	#include "VBF_OS_Linux.h"
#endif


#ifdef VBF_OS_LINUX
    #define VBF_DLL_LOCAL   __attribute__((visibility("hidden")))
#else
     #define VBF_DLL_LOCAL
#endif


// ����ΪQT���뻷����ʹ�õĶ����뺯��
#ifdef VBF_QT
	#include "VBF_OS_QT.h"
#endif

#endif
