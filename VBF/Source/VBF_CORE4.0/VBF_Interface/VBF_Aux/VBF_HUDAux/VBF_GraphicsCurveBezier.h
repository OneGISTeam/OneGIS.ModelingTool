//*******************************************************************
// FileName：VBF_GraphicsCurveBezier.h
// Function：二维图形：贝塞尔曲线
// Author:   杜莹
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_CURVE_BEZIER_H__
#define __VBF_GRAPHICS_CURVE_BEZIER_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsCurve.h>



class VBF_HUDAUX_EXPORT CVBF_GraphicsCurveBezier : public CVBF_GraphicsCurve
{
public:
	CVBF_GraphicsCurveBezier(const std::string& strName="");
	virtual ~CVBF_GraphicsCurveBezier();

	// 设置贝塞尔曲线的坐标串及参数，点数必须满足：3n+1 (n>=1)
	bool SetOrignPoints(const std::vector<osg::Vec2f>& vPoints, int nStep=2);

protected:

    // 曲线光滑
    virtual void Smooth();

private:
    int     m_nStep;    // 光滑参数
};


#endif 
