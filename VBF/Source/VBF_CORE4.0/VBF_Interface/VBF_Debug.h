//*******************************************************************
// FileName��  VBF_Debug.h
// Function��  ������йص�����
// Author:     �����
// Date:       2013-09-10
//*******************************************************************

#ifndef __VBF_DEBUG_H__
#define __VBF_DEBUG_H__

#ifdef _DEBUG
/*
	#ifndef _WIN32_WINNT		// ����ʹ���ض��� Windows NT 4 ����߰汾�Ĺ��ܡ�
	#define _WIN32_WINNT 0x0501	// ����ֵ����Ϊ�ʵ���ֵ���������� Windows 2000 ����߰汾��
	#endif		

	#define _AFXDLL
	#include <afx.h>

	#define new DEBUG_NEW

	#define VBF_Max max
	#define VBF_Min min
*/
	#define VBF_Max std::max
	#define VBF_Min std::min
#else
#define VBF_Max std::max
#define VBF_Min std::min
#endif


#endif
