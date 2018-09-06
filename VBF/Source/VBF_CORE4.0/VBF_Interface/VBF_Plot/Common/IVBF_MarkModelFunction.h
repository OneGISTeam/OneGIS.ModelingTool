//*******************************************************************
// FileName：IVBF_MarkModelFunction.h
// Function：实体模型接口：函数曲面
// Author:   杜莹
// Date:     2017-04-01
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_FUNCTION_H__
#define __IVBF_MARK_MODEL_FUNCTION_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec3d>
#include <Types/Vec4f>
#include <vector>
#include <VBF_Plot/Common/VBF_SurfaceFunction.h>
#include <VBF_Plot/Common/VBF_ParamSurface.h>
#include <VBF_Plot/Common/VBF_ColorFunction.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_SURFACE_STYLE
// 接口描述：自定义表面绘制样式，可以是如下枚举值的单个
//--------------------------------------------------------------------
enum EVBF_SURFACE_STYLE
{
    EVBF_SURFACE_STYLE_POINT		= 0x01,		// 只绘制点
    EVBF_SURFACE_STYLE_LINE         = 0x02,		// 只绘制线
    EVBF_SURFACE_STYLE_FILL         = 0x04,		// 只绘制实体
    EVBF_SURFACE_STYLE_COMPOSITE	= (EVBF_SURFACE_STYLE_FILL | EVBF_SURFACE_STYLE_LINE)	// 同时绘制实体和网格线
};


class IVBF_MarkModelFunction : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkModelFunction() {}

    // 设置用户自定义的曲面函数和颜色函数，如果颜色函数为NULL，系统将使用标准颜色函数
    virtual void SetFunction(CVBF_SurfaceFunction* pSurfaceFunc, CVBF_ColorFunction* pColorFunc=NULL)=0;

    // 设置用户自定义的参数曲面和颜色函数，如果颜色函数为NULL，系统将使用标准颜色函数
    virtual void SetParamSurface(CVBF_ParamSurface* pParamSurface, CVBF_ColorFunction* pColorFunc=NULL)=0;

    // 设置/获取表面绘制样式（默认为EVBF_SURFACE_STYLE_COMPOSITE）
    virtual void                SetSurfaceStyle(EVBF_SURFACE_STYLE nStyle)=0;
    virtual EVBF_SURFACE_STYLE  GetSurfaceStyle()=0;

    // 设置/获取网格线的样式
    virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetLineStyle()=0;
};

#endif 
