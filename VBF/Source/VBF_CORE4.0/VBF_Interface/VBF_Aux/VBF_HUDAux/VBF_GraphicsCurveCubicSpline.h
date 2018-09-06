//*******************************************************************
// FileName：VBF_GraphicsCurveCubicSpline.h
// Function：二维图形：三次样条曲线
// Author:   杜莹
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_CURVE_CUBIC_SPLINE_H__
#define __VBF_GRAPHICS_CURVE_CUBIC_SPLINE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsCurve.h>



class VBF_HUDAUX_EXPORT CVBF_GraphicsCurveCubicSpline : public CVBF_GraphicsCurve
{
public:
	CVBF_GraphicsCurveCubicSpline(const std::string& strName="");
	virtual ~CVBF_GraphicsCurveCubicSpline();

	// 设置三次样条曲线的坐标串及参数
	bool SetOrignPoints(const std::vector<osg::Vec2f>& vPoints, int nNumInter=20);

protected:

    // 曲线光滑
    virtual void Smooth();

private:
    int     m_nNumInterPoints;  // 需要插入的点数
};


#endif 
