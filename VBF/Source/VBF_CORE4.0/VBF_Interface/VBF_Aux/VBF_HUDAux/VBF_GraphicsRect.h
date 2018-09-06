//*******************************************************************
// FileName��VBF_GraphicsRect.h
// Function����άͼ�Σ�����
// Author:   ��Ө
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_RECT_H__
#define __VBF_GRAPHICS_RECT_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsShape.h>



class VBF_HUDAUX_EXPORT CVBF_GraphicsRect : public CVBF_GraphicsShape
{
public:
	CVBF_GraphicsRect(const std::string& strName="");
	virtual ~CVBF_GraphicsRect();

	// ����/��ȡ���ε���Ļ����
	void SetPos(float x0, float x1, float y0, float y1);
	void GetPos(float& x0, float& x1, float& y0, float& y1) { x0 = m_x0; y0 = m_y0; x1 = m_x1; y1 = m_y1; }

    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    // ������Ⱦ״̬
    virtual void SetStateSet();

private:

    // �������ε�ʵ��ͱ��߲���
    osg::Geometry* CreateSolid();
    osg::Geometry* CreateLine();

    // ���¾����ĸ����������
    void UpdateVerts(osg::Geometry* pGeom);

private:

	// ��Ļ����
	float					m_x0, m_x1, m_y0, m_y1;

	// �볡��ͼ�йص�����
	ref_ptr<osg::Geometry>	m_piGeomSolid;
	ref_ptr<osg::Geometry>	m_piGeomLine;
};


#endif 
