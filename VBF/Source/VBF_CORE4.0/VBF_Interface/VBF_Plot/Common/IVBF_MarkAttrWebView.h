//*******************************************************************
// FileName��IVBF_MarkAttrWebView.h
// Function��ģ�����Խӿڣ�����ʹ��WebView��ʾģ����Ϣ
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
    // ����/��ȡ��������Ļ����ϵ�µ�ƫ��������λ�����أ�Ĭ��ֵ��Ϊ0��
	virtual void SetScreenOffset(float fOffsetX, float fOffsetY)=0;
	virtual void GetScreenOffset(float& fOffsetX, float& fOffsetY)=0;
    virtual void SetSize(int nWidth,int nHeight)=0;
    virtual void SetAlpha(float fAlpha)=0;
    virtual void SetURL(const std::string& sURL)=0;
};


#endif 
