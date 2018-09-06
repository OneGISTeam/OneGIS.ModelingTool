//*******************************************************************
// FileName：  VBF_OS_QT.h
// Function：  与QT平台相关的内容
// Author:     杜莹
// Date:       2012-11-01
//*******************************************************************

#ifndef __VBF_OS_QT_H__
#define __VBF_OS_QT_H__

/*
inline void Sleep(unsigned int dwMilliseconds)
{
	// ???
}
*/

#ifndef VK_TAB
	#define VK_TAB            0x09
	#define VK_SHIFT          0x10
	#define VK_CONTROL        0x11

	#define VK_SPACE          0x20
	#define VK_PRIOR          0x21
	#define VK_NEXT           0x22
	#define VK_END            0x23
	#define VK_HOME           0x24
	#define VK_LEFT           0x25
	#define VK_UP             0x26
	#define VK_RIGHT          0x27
	#define VK_DOWN           0x28
	#define VK_PRINT          0x2A
	#define VK_INSERT         0x2D
	#define VK_DELETE         0x2E
	#define VK_HELP           0x2F

	#define VK_F1             0x70
	#define VK_F2             0x71
	#define VK_F3             0x72
	#define VK_F4             0x73
	#define VK_F5             0x74
	#define VK_F6             0x75
	#define VK_F7             0x76
	#define VK_F8             0x77
	#define VK_F9             0x78
	#define VK_F10            0x79
	#define VK_F11            0x7A
	#define VK_F12            0x7B
#endif

#endif
