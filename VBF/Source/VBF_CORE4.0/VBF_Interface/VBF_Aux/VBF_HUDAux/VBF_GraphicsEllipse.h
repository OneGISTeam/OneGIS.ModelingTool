//*******************************************************************
// FileName��VBF_GraphicsEllipse.h
// Function����άͼ�Σ���Բ
// Author:   ��Ө
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_ELLIPSE_H__
#define __VBF_GRAPHICS_ELLIPSE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsArc.h>



class VBF_HUDAUX_EXPORT CVBF_GraphicsEllipse : public CVBF_GraphicsArc
{
public:
	CVBF_GraphicsEllipse(const std::string& strName="");
	virtual ~CVBF_GraphicsEllipse();

	// ����/��ȡ��Բ����״����
	void SetTess(const osg::Vec2f& ptCenter, float a, float b);
	void GetTess(osg::Vec2f& ptCenter, float& a, float& b)	{ ptCenter = m_ptOffset; a = m_fScaleX; b = m_fScaleY; }
};


#endif 
