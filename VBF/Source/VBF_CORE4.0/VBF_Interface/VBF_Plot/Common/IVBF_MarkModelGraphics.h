//*******************************************************************
// FileName：IVBF_MarkModelGraphics.h
// Function：各种自定义图形的军标实体模型，区别于Mesh和Raster等
// Author:   杜莹
// Date:     2013-11-11
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_GRAPHICS_H__
#define __IVBF_MARK_MODEL_GRAPHICS_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>


class IVBF_GraphicsObserver;

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelGraphics
// 接口描述：各种自定义图形的军标实体模型
//--------------------------------------------------------------------
class IVBF_MarkModelGraphics : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelGraphics() {}

public:

	// 设置/获取图形的外观
	virtual void SetAppearance(IVBF_GraphicsAppearance* pAppearance)=0;
	virtual IVBF_GraphicsAppearance* GetAppearance()=0;  // 该函数必定成功

	// 添加/移除图形的观察者
	virtual void AddObserver(IVBF_GraphicsObserver* pIObserver)=0;
	virtual void RemoveObserver(IVBF_GraphicsObserver* pIObserver)=0;

	// 获取/遍历图形的观察者
	virtual int GetNumObservers()=0;
	virtual IVBF_GraphicsObserver* GetObserver(int nIndex)=0;
};


// 定义观察者可以接收到的各种消息
const char VBF_GRAPHICS_MESSAGE_MODEL_CHANGED[]			= "Message: Graphics Model Changed";		// 图形的模型改变了
const char VBF_GRAPHICS_MESSAGE_STATESET_CHANGED[]		= "Message: Graphics StateSet Changed";		// 图形的渲染状态改变了
const char VBF_GRAPHICS_MESSAGE_APPEARANCE_CHANGED[]	= "Message: Graphics Appearance Changed";	// 图形的外观改变了


//--------------------------------------------------------------------
// 定义接口：IVBF_GraphicsObserver
// 接口描述：形状观察者，以便响应形状变化消息
//--------------------------------------------------------------------
class IVBF_GraphicsObserver : public CVBF_Referenced
{
public:
	virtual ~IVBF_GraphicsObserver() {}

public:

	// 响应各种消息，消息的内容参见上面的定义（如VBF_GRAPHICS_MESSAGE_MODEL_CHANGED）
	virtual void OnGraphicsMessage(IVBF_MarkModelGraphics* pISender, const char* szMessage)=0;
};


#endif 
