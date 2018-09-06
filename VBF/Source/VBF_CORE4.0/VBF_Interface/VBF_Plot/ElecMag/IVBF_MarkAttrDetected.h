//*******************************************************************
// FileName：IVBF_MarkAttrDetected.h
// Function：可被探测属性接口
//           用于接收探测结果的事件并根据探测结果更改模型的显示状态
//           利用其Visible属性表示是否被探测到
// Author:   武玉国
// Date:     2013-10-23
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_DETECTED_H__
#define __IVBF_MARK_ATTR_DETECTED_H__

#include <VBF_plot/IVBF_MarkAttr.h>

// 
//--------------------------------------------------------------------
// 定义接口：IVBF_MarkAttrDetected
// 接口描述：
//--------------------------------------------------------------------
class IVBF_MarkAttrDetected : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrDetected() {}
};


#endif 
