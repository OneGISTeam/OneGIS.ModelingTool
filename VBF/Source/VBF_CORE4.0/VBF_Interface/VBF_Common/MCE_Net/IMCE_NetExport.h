#ifndef __IMCE_NET_EXPORT_H__
#define __IMCE_NET_EXPORT_H__

#include <afxsock.h>
#include "IMCE_Net.h"

class CSocket;

// ����ĺ궨�壬��Ϊ�˵�����dll�����������
#ifndef MCE_NET
    #define MCE_NET_EXPORT _declspec(dllimport)



	#if _MSC_VER == 1200
	
		#ifdef _DEBUG
			#pragma comment(lib,"..\\..\\Lib6D\\MCE_NetD.lib") 
			#pragma message("�Զ����� MCE_NetD.dll") 
		#else 
			#pragma comment(lib,"..\\..\\Lib6R\\MCE_Net.lib") 
			#pragma message("�Զ����� MCE_Net.dll") 
		#endif 

	#else if _MSC_VER == 2000

		#ifdef _DEBUG
			#pragma comment(lib,"..\\..\\Lib10D\\MCE_NetD.lib") 
			#pragma message("�Զ����� MCE_NetD.dll") 
		#else 
			#pragma comment(lib,"..\\..\\Lib10R\\MCE_Net.lib") 
			#pragma message("�Զ����� MCE_Net.dll") 
		#endif 

	#endif 

#else 
    #define MCE_NET_EXPORT _declspec(dllexport) 
#endif 

// ȫ�ֺ�����
MCE_NET_EXPORT  IMCE_Net* MCE_CreateNet(bool bAsync);
MCE_NET_EXPORT  void      MCE_ReleaseNet(IMCE_Net*& pINet);

// ȫ�ֹ��ߺ�����
MCE_NET_EXPORT  bool MCE_GetHostName(char* szHostName);
MCE_NET_EXPORT  bool MCE_GetIP(char* szIP);
MCE_NET_EXPORT  bool MCE_GetUserName(char* szUserName);
MCE_NET_EXPORT  void MCE_GetSocketIP(CSocket* pSocket, char* szstrIP);

#endif