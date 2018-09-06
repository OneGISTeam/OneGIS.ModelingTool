//*******************************************************************
// FileName：IVBF_MarkAttrLabel.h
// Function：模型属性接口：标签，用于显示模型当前的某些信息（如编号、坐标等）
// Author:   杜莹
// Date:     2013-12-16
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_LABEL_H__
#define __IVBF_MARK_ATTR_LABEL_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <VBF_Plot/Common/IVBF_MarkModelText.h>


// 定义工具ID号
const char VBF_TOOL_MARKATTR_TOGGLE_LABEL[]	 = "Tool: Toggle Label Between Simple and Detail";	// 通过鼠标双击在简标和详标之间切换


//--------------------------------------------------------------------
// 定义枚举：EVBF_LABELPOS_TYPE
// 枚举描述：标签的定位方式
//--------------------------------------------------------------------
enum EVBF_LABELPOS_TYPE
{
	VBF_LABELPOS_ORIGIN			= 0,	// 模型原始定位点（默认值）
	VBF_LABELPOS_BOXCENTER		= 1,	// 模型包围盒中心
	VBF_LABELPOS_BOXCORNER		= 2,	// 模型包围盒角点
	VBF_LABELPOS_BOXTOPCENTER	= 3		// 模型包围盒顶部中心（注意：此时要求模型必须为Raster类）
};


// 定义标签中需要显示的内容项，用户可组合使用其中的一项或多项
#define VBF_LABELITEM_ID			0x00000001	// 模型的ID号
#define VBF_LABELITEM_CODE			0x00000002	// 模型的编码
#define VBF_LABELITEM_COORDGEO		0x00000004	// 模型的地理坐标
#define VBF_LABELITEM_COORDECI		0x00000008	// 模型的地惯坐标
#define VBF_LABELITEM_COORDECF		0x00000010	// 模型的地固坐标
#define VBF_LABELITEM_SIMPLE		0x00000020	// 用户自定义的简单文本
#define VBF_LABELITEM_DETAIL		0x00000040	// 用户自定义的详细文本


class IVBF_MarkAttrLabel : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrLabel() {}

	// 设置/获取标签的内容项（值参见该头文件中VBF_LABELITEM_ID等常量的定义）
	virtual void  SetTextItem(DWORD dwItem)=0;
	virtual DWORD GetTextItem()=0;

    // 设置/获取用户自定义的简单文本
    virtual void               SetSimpleText(const std::string& strText)=0;
    virtual const std::string& GetSimpleText()=0;

    // 设置/获取用户自定义的详细文本
    virtual void               SetDetailText(const std::string& strText)=0;
    virtual const std::string& GetDetailText()=0;

	// 获取当前显示的文本
	virtual const std::string& GetText()=0;

	// 设置/获取标签的定位方式（值参见该头文件中枚举VBF_LABELPOS_TYPE的定义）
    virtual void               SetPosType(EVBF_LABELPOS_TYPE nPosType)=0;
    virtual EVBF_LABELPOS_TYPE GetPosType()=0;

	// 设置/获取文本样式
	virtual void                 SetTextStyle(const VBF_TEXTSTYLE& style)=0;
	virtual const VBF_TEXTSTYLE& GetTextStyle()=0;

	// 设置/获取文本背景框的可见性
	virtual void SetFrameVisible(bool bVisible)=0;
	virtual bool IsFrameVisible()=0;

	// 设置/获取文本背景框的样式
	virtual void                      SetFrameStyle(const VBF_POLYGON2DSTYLE& style)=0;
	virtual const VBF_POLYGON2DSTYLE& GetFrameStyle()=0;

    // 设置/获取是否绘制背景框中的定位标识符（即文本矩形左边的小三角形，默认为true）
    virtual void SetIndicatorVisible(bool bVisible)=0;
    virtual bool IsIndicatorVisible()=0;

	// 设置/获取文本及其背景框在屏幕坐标系下的偏移量（单位：像素，默认值均为0）
	virtual void SetScreenOffset(float fOffsetX, float fOffsetY)=0;
	virtual void GetScreenOffset(float& fOffsetX, float& fOffsetY)=0;

    // 判断是否包含指定的鼠标位置（切换简标和详标时使用）
    virtual bool Contains(float x, float y)=0;
};


#endif 
