//*******************************************************************
// FileName��VBF_GraphicsCurveTensionSpline.h
// Function����άͼ�Σ�������������
// Author:   ��Ө
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_CURVE_TENSION_SPLINE_H__
#define __VBF_GRAPHICS_CURVE_TENSION_SPLINE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsCurve.h>



class VBF_HUDAUX_EXPORT CVBF_GraphicsCurveTensionSpline : public CVBF_GraphicsCurve
{
public:
	CVBF_GraphicsCurveTensionSpline(const std::string& strName="");
	virtual ~CVBF_GraphicsCurveTensionSpline();

	// ���������������ߵ����괮������
	bool SetOrignPoints(const std::vector<osg::Vec2f>& vPoints, double dStep=4, double dCoef=0.01);

protected:

    // ���߹⻬
    virtual void Smooth();

private:
    double      m_dStep;
    double      m_dCoef;
};


#endif 
