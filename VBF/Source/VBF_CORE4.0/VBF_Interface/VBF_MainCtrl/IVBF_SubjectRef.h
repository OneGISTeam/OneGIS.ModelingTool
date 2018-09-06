//***************************************************************************************
// FileName：IVBF_SubjectRef.h
// Function：被观察者接口
//           Observer模式中的 被观察者（Subject）接口。
// Author:   武玉国
// Date:     2006-4-22
//***************************************************************************************

#ifndef __IVBF_SUBJECT_REF_H__
#define __IVBF_SUBJECT_REF_H__

#include <VBF_Base/VBF_Referenced.h>
class IVBF_ObserverRef;


class IVBF_SubjectRef : public CVBF_Referenced
{
public:
    virtual ~IVBF_SubjectRef() {}

public:

	//---------------------------------------------------------------
	//  Attach:添加观察者
	//  将指定的观察者对象添加到相应的消息相应列表中。
	//  pObserver：被添加的观察者对象指针
	//---------------------------------------------------------------
    virtual void Attach(IVBF_ObserverRef* pIObserver) = 0;

	//---------------------------------------------------------------
	// Detach:取消观察者
	// 将指定的观察者对象从指定消息响应列表中删除。
	// pObserver：被删除的观察者对象指针
	//---------------------------------------------------------------
    virtual void Detach(IVBF_ObserverRef* pIObserver) = 0;

 	//---------------------------------------------------------------
    // DetachAll:取消所有观察者
	// 将所有观察者从所有消息相应列表中。
 	//---------------------------------------------------------------
    virtual void DetachAll() = 0;

 	//---------------------------------------------------------------
	// Notify:发送消息 
	// 将指定消息发送给相应的观察者。
	// szMessage：要发送的消息。
	// iValue：消息的整数参数；
	// pValue：消息的指针参数。
 	//---------------------------------------------------------------
    virtual void Notify(const char* szMessage, int nValue=0, void* pValue=NULL) = 0;
};

#endif
