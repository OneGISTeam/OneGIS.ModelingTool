//*******************************************************************
// FileName：IVBF_MarkModel2D.h
// Function：实体模型接口：2D，使用屏幕坐标
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_2D_H__
#define __IVBF_MARK_MODEL_2D_H__

#include <VBF_Plot/IVBF_MarkModel.h>

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModel2D
// 接口描述：2D，使用屏幕坐标
//--------------------------------------------------------------------
class IVBF_MarkModel2D : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModel2D() {}

    // 设置/获取图形占据的屏幕矩形
    virtual void SetClientRect(float x0, float x1, float y0, float y1)=0;
    virtual void GetClientRect(float& x0, float& x1, float& y0, float& y1)=0;

	// 设置/获取坐标原点是否位于屏幕左上角（默认为true）
	virtual void SetOriginTopLeft(bool bTopLeft)=0;
	virtual bool IsOriginTopLeft()=0;
};



#endif 
