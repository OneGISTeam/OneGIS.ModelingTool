//*******************************************************************
// FileName：IVBF_MarkAttrWebView.h
// Function：模型属性接口：用于使用WebView显示模型信息
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_WEBVIEW_H__
#define __IVBF_MARK_ATTR_WEBVIEW_H__

#include <VBF_Plot/IVBF_MarkAttr.h>
class QWidget;
class IVBF_MarkAttrWebView : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrWebView() {}

    virtual void SetParentWidget(QWidget* pWidget)=0;
    // 设置/获取窗口在屏幕坐标系下的偏移量（单位：像素，默认值均为0）
	virtual void SetScreenOffset(float fOffsetX, float fOffsetY)=0;
	virtual void GetScreenOffset(float& fOffsetX, float& fOffsetY)=0;
    virtual void SetSize(int nWidth,int nHeight)=0;
    virtual void SetAlpha(float fAlpha)=0;
    virtual void SetURL(const std::string& sURL)=0;
};


#endif 
