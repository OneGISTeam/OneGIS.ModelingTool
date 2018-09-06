//*******************************************************************
// FileName��VBF_GraphicsCircle.h
// Function����άͼ�Σ�Բ��
// Author:   ��Ө
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_CIRCLE_H__
#define __VBF_GRAPHICS_CIRCLE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsArc.h>



class VBF_HUDAUX_EXPORT CVBF_GraphicsCircle : public CVBF_GraphicsArc
{
public:
	CVBF_GraphicsCircle(const std::string& strName="");
	virtual ~CVBF_GraphicsCircle();

	// ����/��ȡԲ�ε���״����
	void SetTess(const osg::Vec2f& ptCenter, float r);
	void GetTess(osg::Vec2f& ptCenter, float& r) { ptCenter = m_ptOffset; r = m_fScaleX; }
};


#endif 
