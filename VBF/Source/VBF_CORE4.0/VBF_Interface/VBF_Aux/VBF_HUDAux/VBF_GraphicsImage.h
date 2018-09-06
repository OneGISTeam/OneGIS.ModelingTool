//*******************************************************************
// FileName��VBF_GraphicsImage.h
// Function����άͼ�Σ�ͼ��
// Author:   ��Ө
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_IMAGE_H__
#define __VBF_GRAPHICS_IMAGE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>


class VBF_HUDAUX_EXPORT CVBF_GraphicsImage : public CVBF_Graphics
{
public:
	CVBF_GraphicsImage(const std::string& strName="");
	virtual ~CVBF_GraphicsImage();

	// ����/��ȡͼ�����Ļ����
	void SetPos(float x0, float x1, float y0, float y1);
	void GetPos(float& x0, float& x1, float& y0, float& y1) { x0 = m_x0; y0 = m_y0; x1 = m_x1; y1 = m_y1; }

	// ����/��ȡ����ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	void		SetTexImage(osg::Image* pImage, bool bTexToCache);
	osg::Image* GetTexImage() { return m_piImage.get(); }

	// ����/��ȡ����͸���ȣ�Ĭ��ֵΪ1.0��
    void  SetColor(osg::Vec4f color);
    osg::Vec4f GetColor() { return m_vColor; }

	// ����/��ȡ��ͼ�����ĵ����ת�ǣ�Ĭ��ֵΪ0.0����ʱ��Ϊ������λ���Ƕȣ�
	void  SetRotate(float fRotate)	{ m_fRotate = fRotate; DirtyModel(); }
	float GetRotate()				{ return m_fRotate; }

    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);


    // ������Ⱦ״̬
    virtual void SetStateSet();

private:

    // �������ε�ʵ�岿��
    osg::Geometry* CreateSolid();

	// �Զ���������š���ת��ƽ��
	void Transform(osg::Vec3Array* pVerts);

private:

	// ��Ļ����
	float					m_x0, m_x1, m_y0, m_y1;

	// ͼ��任
	float					m_fRotate;		// ��ͼ�����ĵ����ת��

	// ����
	ref_ptr<osg::Image>		m_piImage;
	bool					m_bTexToCache;	// �����Ƿ���Ҫ���뻺�棬Ĭ��Ϊfalse
    osg::Vec4f				m_vColor;	// ����͸����

	// �볡��ͼ�йص�����
    ref_ptr<osg::Geometry>	m_piGeomSolid;
};


#endif 
