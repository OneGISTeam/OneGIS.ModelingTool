//*******************************************************************
// FileName��VBF_GraphicsCurveCubicSpline.h
// Function����άͼ�Σ�������������
// Author:   ��Ө
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

	// ���������������ߵ����괮������
	bool SetOrignPoints(const std::vector<osg::Vec2f>& vPoints, int nNumInter=20);

protected:

    // ���߹⻬
    virtual void Smooth();

private:
    int     m_nNumInterPoints;  // ��Ҫ����ĵ���
};


#endif 
