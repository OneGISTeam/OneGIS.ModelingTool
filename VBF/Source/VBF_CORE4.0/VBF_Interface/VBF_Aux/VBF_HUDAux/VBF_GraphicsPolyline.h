//*******************************************************************
// FileName��VBF_GraphicsPolyline.h
// Function����άͼ�Σ�����
// Author:   ��Ө
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_POLYLINE_H__
#define __VBF_GRAPHICS_POLYLINE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>


class VBF_HUDAUX_EXPORT CVBF_GraphicsPolyline : public CVBF_Graphics
{
public:
	CVBF_GraphicsPolyline(const std::string& strName="");
	virtual ~CVBF_GraphicsPolyline();

	// ����/��ȡ���ߵ����괮
	void SetPoints(const std::vector<osg::Vec2f>& vPoints);
	const std::vector<osg::Vec2f>& GetPoints() { return m_vPoints; }

	// ����/��ȡ������ʽ
	void                 SetLineStyle(const VBF_LINESTYLE& style);
	const VBF_LINESTYLE& GetLineStyle() { return m_LineStyle; }

	// ����/��ȡ������Ƿ�ɼ���Ĭ��ֵΪtrue��
	void SetPointVisible(bool bVisible);
	bool IsPointVisible()	{ return m_bPointVisible; }

    // ����/��ȡ��������ʽ
    void                  SetPointStyle(const VBF_POINTSTYLE& style);
    const VBF_POINTSTYLE& GetPointStyle()	{ return m_PointStyle; }

    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    virtual void SetStateSet();

private:

    // �������ߺ������
    osg::Geometry* CreateLine();
    osg::Geometry* CreatePoints();

private:

	// ���괮
	std::vector<osg::Vec2f>		m_vPoints;	// �������괮

	// ����㣨��GL_POINTS��ʽ���ƣ�
	bool						m_bPointVisible;	// �Ƿ���ʾ�����
	VBF_POINTSTYLE				m_PointStyle;		// ��������ʽ

	// ���ߵ���ʽ
	VBF_LINESTYLE				m_LineStyle;

    ref_ptr<osg::Geometry>	m_ipGeomLine;
};


#endif 
