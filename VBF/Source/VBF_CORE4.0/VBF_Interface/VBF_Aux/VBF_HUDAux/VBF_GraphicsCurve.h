//*******************************************************************
// FileName��VBF_GraphicsCurve.h
// Function����άͼ�Σ��⻬����
// Author:   ��Ө
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_CURVE_H__
#define __VBF_GRAPHICS_CURVE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>


class VBF_HUDAUX_EXPORT CVBF_GraphicsCurve : public CVBF_Graphics
{
public:
	CVBF_GraphicsCurve(const std::string& strName="");
	virtual ~CVBF_GraphicsCurve();

	// ��ȡ���ߵ�ԭʼ���괮
	const std::vector<osg::Vec2f>& GetOrignPoints() { return m_vPointsOrign; }

	// ����/��ȡ������ʽ
	void                 SetLineStyle(const VBF_LINESTYLE& style);
	const VBF_LINESTYLE& GetLineStyle() { return m_LineStyle; }

	// ����/��ȡԭʼ������Ƿ�ɼ���Ĭ��ֵΪtrue��
	void SetOrignPointVisible(bool bVisible);
	bool IsOrignPointVisible()	{ return m_bOrignPointVisible; }

    // ����/��ȡԭʼ��������ʽ
    void                  SetOrignPointStyle(const VBF_POINTSTYLE& style);
    const VBF_POINTSTYLE& GetOrignPointStyle()	{ return m_PointStyle; }

    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    // ������Ⱦ״̬
    virtual void SetStateSet();

protected:

    // ���߹⻬
    virtual void Smooth()=0;

    // �������ߺ������
    osg::Geometry* CreateLine();
    osg::Geometry* CreatePoints();

protected:

	// ���괮
	std::vector<osg::Vec2f>		m_vPointsOrign;			// ���ߵ�ԭʼ���괮
	std::vector<osg::Vec2f>		m_vPointsSmooth;			// ���ߵĲ�ֵ���괮

	// ����㣨��GL_POINTS��ʽ���ƣ�
	bool						m_bOrignPointVisible;	// �Ƿ���ʾԭʼ�����
	VBF_POINTSTYLE				m_PointStyle;			// ��������ʽ

	// ���ߵ���ʽ
	VBF_LINESTYLE				m_LineStyle;

	// �볡��ͼ�йص�����
	ref_ptr<osg::Geometry>		m_piGeomLine;
	ref_ptr<osg::Geometry>		m_piGeomPoints;
};


#endif 
