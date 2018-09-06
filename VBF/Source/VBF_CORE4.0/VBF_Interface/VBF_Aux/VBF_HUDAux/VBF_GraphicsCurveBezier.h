//*******************************************************************
// FileName��VBF_GraphicsCurveBezier.h
// Function����άͼ�Σ�����������
// Author:   ��Ө
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

	// ���ñ��������ߵ����괮�������������������㣺3n+1 (n>=1)
	bool SetOrignPoints(const std::vector<osg::Vec2f>& vPoints, int nStep=2);

protected:

    // ���߹⻬
    virtual void Smooth();

private:
    int     m_nStep;    // �⻬����
};


#endif 
