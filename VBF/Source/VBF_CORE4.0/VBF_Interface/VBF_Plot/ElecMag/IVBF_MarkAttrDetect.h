//*******************************************************************
// FileName：IVBF_MarkAttrDetect.h
// Function：可被探测属性接口
//           用于接收探测结果的事件并根据探测结果更改模型的显示状态
//           利用其Visible属性表示是否被探测到
// Author:
// Date:     2013-10-23
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_DETECT_H__
#define __IVBF_MARK_ATTR_DETECT_H__

#include <VBF_Plot/IVBF_MarkAttr.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkAttrDetect
// 接口描述：
//--------------------------------------------------------------------
class IVBF_MarkAttrDetect : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrDetect() {}

	// 设置/获取模型被探测到后，包围盒是否可见（默认为true）
	virtual void SetBoundingBoxVisibleWhenDetected(bool bVisible)=0;
	virtual bool IsBoundingBoxVisibleWhenDetected()=0;
};


#endif 
