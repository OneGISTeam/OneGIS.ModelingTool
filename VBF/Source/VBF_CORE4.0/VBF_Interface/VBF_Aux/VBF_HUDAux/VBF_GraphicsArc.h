//*******************************************************************
// FileName��VBF_GraphicsArc.h
// Function����άͼ�Σ�����
// Author:   ��Ө
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_ARC_H__
#define __VBF_GRAPHICS_ARC_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsShape.h>



class VBF_HUDAUX_EXPORT CVBF_GraphicsArc : public CVBF_GraphicsShape
{
public:
	CVBF_GraphicsArc(const std::string& strName="");
	virtual ~CVBF_GraphicsArc();

	// ����/��ȡ���ε���״����
	void SetTess(const osg::Vec2f& ptCenter, float a, float b, float fAngle0, float fAngle1);
	void GetTess(osg::Vec2f& ptCenter, float& a, float& b, float& fAngle0, float& fAngle1)
	{
		ptCenter = m_ptOffset;
		a		 = m_fScaleX;
		b		 = m_fScaleY;
		fAngle0  = m_fAngle0;
		fAngle1  = m_fAngle1;
	}

    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    // ������Ⱦ״̬
    virtual void SetStateSet();

protected:

    // �������ε�ʵ��ͱ��߲���
    osg::Geometry* CreateSolid();
    osg::Geometry* CreateLine();

protected:

	// Բ�ļ��뾶
	float					m_fAngle0;			// ��ʼ��
	float					m_fAngle1;			// ��ֹ��

	// Բ�ָܷ���
	int						m_nNumSplit;
	float					m_fDeltaTheta;		// Բ������������֮��ĽǶȼ��

	// �볡��ͼ�йص�����
	ref_ptr<osg::Geometry>	m_piGeomSolid;
	ref_ptr<osg::Geometry>	m_piGeomLine;
};


#endif 
