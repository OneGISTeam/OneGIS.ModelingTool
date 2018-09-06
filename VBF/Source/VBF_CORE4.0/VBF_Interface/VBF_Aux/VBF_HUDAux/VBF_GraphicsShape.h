//*******************************************************************
// FileName��VBF_GraphicsShape.h
// Function�������Զ���2D����ͼ�Σ��̳���CVBF_Graphics
// Author:   ��Ө
// Date:     2015-12-29
//*******************************************************************

#ifndef __VBF_GRAPHICS_SHAPE_H__
#define __VBF_GRAPHICS_SHAPE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>



//=============================================================================
// �����ࣺCVBF_GraphicsShape
// ������������2D����ͼ�εĻ���
//=============================================================================
class VBF_HUDAUX_EXPORT CVBF_GraphicsShape : public CVBF_Graphics
{
public:
    CVBF_GraphicsShape(const std::string& strName="");
    virtual ~CVBF_GraphicsShape();

	// ����/��ȡͼ�εļ�����ʽ��Ĭ��Ϊ��ʵ��+����
	virtual void                SetGeometryStyle(EVBF_GEOMETRY_STYLE nStyle);
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle() { return m_nStyleGeom; }

	// ����/��ȡͼ�ε���ɫ��ʽ��Ĭ��Ϊ��ֻʹ����ɫ
	virtual void             SetShadeStyle(EVBF_SHADE_STYLE nStyle);
	virtual EVBF_SHADE_STYLE GetShadeStyle() { return m_nStyleShade; }

	// ����/��ȡͼ�ε�ʵ����ɫ
	void              SetSolidColor(const osg::Vec4f& color);
	const osg::Vec4f& GetSolidColor() { return m_colorSolid; }

	// ����/��ȡͼ�εı�����ʽ
	void                 SetLineStyle(const VBF_LINESTYLE& style);
	const VBF_LINESTYLE& GetLineStyle() { return m_LineStyle; }

	// ����/��ȡ����ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache);
	virtual osg::Image* GetTexImage() { return m_piImage.get(); }

	// ����/��ȡĳ�����ֵ��������ݺ᷽����ظ�������Ĭ��ֵ��Ϊ1
	virtual void SetNumTexRepeats(int nNumRows, int nNumCols);
	virtual void GetNumTexRepeats(int& nNumRows, int& nNumCols) { nNumRows = m_nNumTexRows; nNumCols = m_nNumTexCols; }

	// ����/��ȡͬʱ���ö�����ɫ������ʱ�����ߵĻ�Ϸ�ʽ
	virtual void SetTexEnvMode(EVBF_TEXENV_MODE	nMode);
	virtual EVBF_TEXENV_MODE GetTexEnvMode() { return m_nTexEnvMode; }

	// ����/��ȡ��ͼ�����ĵ����ת�ǣ�Ĭ��ֵΪ0.0����ʱ��Ϊ������λ���Ƕȣ�
	virtual void  SetRotate(float fRotate)	{ m_fRotate = fRotate; DirtyModel(); }
	virtual float GetRotate()				{ return m_fRotate; }

protected:

	// �Զ���������š���ת��ƽ��
	void Transform(osg::Vec3Array* pVerts);

protected:

	EVBF_GEOMETRY_STYLE		m_nStyleGeom;		// ���λ��Ʒ�ʽ��ʵ��/����
	EVBF_SHADE_STYLE		m_nStyleShade;		// ��ɫ��ʽ����ɫ/����

	// ��ʽ
	osg::Vec4f				m_colorSolid;
	VBF_LINESTYLE			m_LineStyle;

	// ����
	ref_ptr<osg::Image>		m_piImage;
	bool					m_bTexToCache;      // �����Ƿ���Ҫ���뻺�棬Ĭ��Ϊfalse
	int						m_nNumTexRows;		// �����ظ�����������
	int						m_nNumTexCols;		// �����ظ�����������

	// ͬʱ���ö�����ɫ������ʱ�����ߵĻ�Ϸ�ʽ
	EVBF_TEXENV_MODE		m_nTexEnvMode;

	// ͼ�α任
	float					m_fScaleX;		// ���ţ�����ڵ�λͼ�Σ�
	float					m_fScaleY;
	float					m_fRotate;		// ��ͼ�����ĵ����ת��
	osg::Vec2				m_ptOffset;		// ƽ�ƣ�����ڵ�λͼ�ε�ԭ�㣩
};



#endif
