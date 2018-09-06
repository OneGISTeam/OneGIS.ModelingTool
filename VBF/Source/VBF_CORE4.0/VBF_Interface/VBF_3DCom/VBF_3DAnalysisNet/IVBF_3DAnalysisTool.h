//*******************************************************************
// FileName：IVBF_3DAnalysisTool.h
// Function：所有三维分析工具的基类
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_H__
#define __IVBF_3DANALYSIS_TOOL_H__


#include <VBF_OS.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventAdapter.h>
#include <VBF_Display/VBF_Manipulator/IVBF_GUIActionAdapter.h>
#include <Types/VBF_3DStyles.h>


class IVBF_3DAnalysisTool : public CVBF_Referenced
{
public:
	virtual ~IVBF_3DAnalysisTool() {}

	// 获取该分析工具的ID号
	virtual const char* GetToolID()=0;

	// 获取该工具当前是否被激活
	virtual bool IsActive()=0;

    // 设置/获取分析结果的文本样式
    virtual void                 SetTextStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetTextStyle()=0;

    // 设置/获取分析结果的背景框是否可见
    virtual void SetFrameVisible(bool bVisible)=0;
    virtual bool IsFrameVisible()=0;

    // 设置/获取分析结果的背景框样式
    virtual void                      SetFrameStyle(const VBF_POLYGON2DSTYLE& style)=0;
    virtual const VBF_POLYGON2DSTYLE& GetFrameStyle()=0;

    // 设置/获取分析过程的折线样式
    virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetLineStyle()=0;

    // 设置/获取量算分析过程中是否需要显示各类辅助信息
    virtual void SetTipCoordVisible(bool bVisible)=0;      // 鼠标所单击点的地理坐标（如果是坐标量算，始终显示）
    virtual bool IsTipCoordVisible()=0;

    virtual void SetTipDistVisible(bool bVisible)=0;       // 鼠标所单击相邻点的大圆线距离（如果是距离量算，始终显示）
    virtual bool IsTipDistVisible()=0;

    virtual void SetTipAzimuthVisible(bool bVisible)=0;    // 鼠标所单击点的方位角（如果是方位角量算，始终显示）
    virtual bool IsTipAzimuthVisible()=0;

    // 设置/获取是否使用度分秒方式显示地理坐标
    virtual void SetTipCoordTypeDMS(bool bDMS)=0;
    virtual bool IsTipCoordTypeDMS()=0;

    // 设置/获取次要点的辅助信息样式
    virtual void                 SetTipTextStyleMinor(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetTipTextStyleMinor()=0;

    virtual void                      SetTipFrameStyleMinor(const VBF_POLYGON2DSTYLE& style)=0;
    virtual const VBF_POLYGON2DSTYLE& GetTipFrameStyleMinor()=0;

    // 设置/获取主要点的辅助信息样式
    virtual void                 SetTipTextStyleMajor(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetTipTextStyleMajor()=0;

    virtual void                      SetTipFrameStyleMajor(const VBF_POLYGON2DSTYLE& style)=0;
    virtual const VBF_POLYGON2DSTYLE& GetTipFrameStyleMajor()=0;

    // 设置/获取方位角辅助信息中的线段样式(包括正北方向指示线和夹角线)
    virtual void                 SetTipAzimuthLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetTipAzimuthLineStyle()=0;

    // 设置/获取方位角辅助信息中的文本样式
    virtual void                 SetTipAzimuthTextStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetTipAzimuthTextStyle()=0;

    // 以下函数由系统内部调用，用户切勿调用
    virtual bool Init()=0;
    virtual void SetActive(bool bActive)=0;
    virtual void Clear()=0;
    virtual bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa)=0;
};

#endif
