//*******************************************************************
// FileName：IVBF_MarkActionTexAnim.h
// Function：模型行为接口，纹理矩阵变换（如：坦克履带的转动）
// Author:
// Date:     2017-12-28
//*******************************************************************

#ifndef __IVBF_MARK_ACTION_TEXANIM_H__
#define __IVBF_MARK_ACTION_TEXANIM_H__


#include <VBF_Plot/IVBF_MarkAction.h>
#include <Types/VBF_3DStyles.h>


class IVBF_MarkActionTexAnim : public IVBF_MarkAction
{
public:
    virtual ~IVBF_MarkActionTexAnim() {}
    virtual void SetSpeedU(float fSpeedU)=0; // 每秒变换的纹理坐标（纹理的水平方向）
    virtual void SetSpeedV(float fSpeedV)=0; // 每秒变换的纹理坐标（纹理的垂直方向）
};


#endif 
