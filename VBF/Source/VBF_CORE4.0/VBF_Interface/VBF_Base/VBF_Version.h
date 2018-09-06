//**********************************************************************************
// �ļ�����  VBF_Version.h
// ������    �������汾
// ����:     ��Ө
// ����:     2013-06-24
//**********************************************************************************

#ifndef __VBF_VERSION_H__
#define __VBF_VERSION_H__

#include <VBF_Base/VBF_BaseExport.h>

extern "C" {

#define VBF_VERSION_MAJOR		3
#define VBF_VERSION_MINOR		0
#define VBF_VERSION_PATCH		1
#define VBF_VERSION_SO			80


#define VBF_MIN_VERSION_REQUIRED(MAJOR, MINOR, PATCH)		((VBF_VERSION_MAJOR>MAJOR) || (VBF_VERSION_MAJOR==MAJOR && (VBF_VERSION_MINOR>MINOR || (VBF_VERSION_MINOR==MINOR && VBF_VERSION_PATCH>=PATCH))))
#define VBF_VERSION_LESS_THAN(MAJOR, MINOR, PATCH)			((VBF_VERSION_MAJOR<MAJOR) || (VBF_VERSION_MAJOR==MAJOR && (VBF_VERSION_MINOR<MINOR || (VBF_VERSION_MINOR==MINOR && VBF_VERSION_PATCH<PATCH))))
#define VBF_VERSION_LESS_OR_EQUAL(MAJOR, MINOR, PATCH)		((VBF_VERSION_MAJOR<MAJOR) || (VBF_VERSION_MAJOR==MAJOR && (VBF_VERSION_MINOR<MINOR || (VBF_VERSION_MINOR==MINOR && VBF_VERSION_PATCH<=PATCH))))
#define VBF_VERSION_GREATER_THAN(MAJOR, MINOR, PATCH)		((VBF_VERSION_MAJOR>MAJOR) || (VBF_VERSION_MAJOR==MAJOR && (VBF_VERSION_MINOR>MINOR || (VBF_VERSION_MINOR==MINOR && VBF_VERSION_PATCH>PATCH))))
#define VBF_VERSION_GREATER_OR_EQUAL(MAJOR, MINOR, PATCH)	((VBF_VERSION_MAJOR>MAJOR) || (VBF_VERSION_MAJOR==MAJOR && (VBF_VERSION_MINOR>MINOR || (VBF_VERSION_MINOR==MINOR && VBF_VERSION_PATCH>=PATCH))))


// ��ȡ�汾��
extern VBF_BASE_EXPORT const char* VBF_GetVersion();

/** The VBF_GetVersionSO() method returns the OpenSceneGraph shared object version number. */
extern VBF_BASE_EXPORT const char* VBF_GetVersionSO();

/** The VBF_GetLibraryName() method returns the library name in human-friendly form. */
extern VBF_BASE_EXPORT const char* VBF_GetLibraryName();


#define VBF_VERSION_RELEASE		VBF_VERSION_PATCH
#define VBF_VERSION_REVISION	0
}

#endif
