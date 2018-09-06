//*******************************************************************
// FileName：IVBF_3DLayout.h
// Function：三维界面上布局要素管理接口，如指北针等
// Author:   杜莹
// Date:     2012-04-23
//*******************************************************************

#ifndef __IVBF_3DLAYOUT_H__
#define __IVBF_3DLAYOUT_H__

#include <VBF_Base/VBF_Referenced.h>

// 定义该组件的ID号
const char VBF_COMPONENT_3DLAYOUT[]	= "Component: 3DLayout";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DLAYOUT[]	= "三维界面布局要素管理";


class IVBF_3DLayout : public CVBF_Referenced
{
public:	
	virtual ~IVBF_3DLayout() {}

    // 设置/获取指北针的可见性
	virtual void SetCompassVisible(bool bVisible)=0;
	virtual bool IsCompassVisible()=0;		

	// 设置/获取背景框文字提示信息是否可见，默认为不可见
	virtual void SetFramedTextVisible(bool bVisible)=0;
	virtual bool IsFramedTextVisible()=0;

	// 设置背景框文字的样式
	virtual void SetFramedTextSize(float fSize)=0;					// 文字大小，默认为56.0
	virtual void SetFramedTextFont(const char* szFontFile)=0;		// 字体文件名，不含路径，如"simhei.ttf"
	virtual void SetFramedTextColor(float r, float g, float b)=0;	// 文字颜色，默认为(1,1,1)

	// 设置背景框文字是否循环显示，默认为不循环,显示完毕后立即关闭
	virtual void SetFramedTextLooping(bool bLooping)=0;				

	// 在屏幕底部绘制具有背景框的文字提示信息，单行，可滚动，同时自动使背景框可见
	virtual void ShowFramedText(const char* szText)=0;

	//设置/获取导航器的可见性
	virtual void SetNavigatorVisible(bool bVisible)=0;
	virtual bool IsNavigatorVisible()=0;

	// 设置/获取鸟瞰图的可见性
	virtual void SetAirViewVisible(bool bVisible)=0;
	virtual bool IsAirViewVisible()=0;

    // 设置/获取仿真时间的可见性
    virtual void SetTimerVisible(bool bVisible)=0;
    virtual bool IsTimerVisible()=0;
};

#endif 
