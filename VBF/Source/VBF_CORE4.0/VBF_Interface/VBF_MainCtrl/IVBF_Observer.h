//***************************************************************************************
// FileName：IVBF_Observer.h
// Function：观察者接口
//           Observer模式中的观察者（Observer）接口。
// Author:   武玉国
// Date:     2006-4-22
//***************************************************************************************

#ifndef __IVBF_OBSERVER_H__
#define __IVBF_OBSERVER_H__


class IVBF_Observer
{
public:
	virtual ~IVBF_Observer() {}

public:

	//----------------------------------------------------------------
    // 消息响应函数
	// 响应消息，进行实际处理
	// szMessage：被发送的消息
	// nValue：消息的整数参数
	// pValue：消息的指针参数
	//----------------------------------------------------------------
    virtual void OnEvent(const char* szMessage, int nValue=0, void* pValue=NULL) = 0;
};


#endif
