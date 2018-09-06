//*******************************************************************
// FileName��VBF_GraphicsPolygon.h
// Function����άͼ�Σ������
// Author:   ��Ө
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_POLYGON_H__
#define __VBF_GRAPHICS_POLYGON_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>
#include <VBF_Macros.h>


class VBF_HUDAUX_EXPORT CVBF_GraphicsPolygon : public CVBF_Graphics
{
public:
	CVBF_GraphicsPolygon(const std::string& strName="");
	virtual ~CVBF_GraphicsPolygon();

	// ����/��ȡ����ε����괮
	void SetPoints(const std::vector<osg::Vec2f>& vPoints);
	const std::vector<osg::Vec2f>& GetPoints() { return m_vPoints; }

	// ����/��ȡ����ε����괮���0���������꣨ע�⣺���������������������˳��һ�£�
	virtual void SetPointsAndTexCoords(const std::vector<osg::Vec2f>& vPoints, const std::vector<osg::Vec2f>& vTexCoords);
	virtual void GetPointsAndTexCoords(std::vector<osg::Vec2f>& vPoints, std::vector<osg::Vec2f>& vTexCoords)
	{
		vPoints    = m_vPoints;
		vTexCoords = m_vTexCoords;
	}

	// ����/��ȡ����εļ�����ʽ��Ĭ��Ϊ��ʵ��+����
	virtual void                SetGeometryStyle(EVBF_GEOMETRY_STYLE nStyle);
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle() { return m_nStyleGeom; }

	// ����/��ȡ����ε���ɫ��ʽ��Ĭ��Ϊ��ֻʹ����ɫ
	virtual void             SetShadeStyle(EVBF_SHADE_STYLE nStyle);
	virtual EVBF_SHADE_STYLE GetShadeStyle() { return m_nStyleShade; }

	// ����/��ȡ����ε�ʵ����ɫ
	void              SetSolidColor(const osg::Vec4f& color);
	const osg::Vec4f& GetSolidColor() { return m_colorSolid; }

	// ����/��ȡ����εı�����ʽ
	void                 SetLineStyle(const VBF_LINESTYLE& style);
	const VBF_LINESTYLE& GetLineStyle() { return m_LineStyle; }

	// ����/��ȡ����ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache);
	virtual osg::Image* GetTexImage() { return m_piImage.get(); }

	// ����/��ȡ�������ݺ᷽����ظ�������Ĭ��ֵ��Ϊ1
	virtual void SetNumTexRepeats(int nNumRows, int nNumCols);
	virtual void GetNumTexRepeats(int& nNumRows, int& nNumCols) { nNumRows = m_nNumTexRows; nNumCols = m_nNumTexCols; }

	// ����/��ȡͬʱ���ö�����ɫ������ʱ�����ߵĻ�Ϸ�ʽ
	virtual void SetTexEnvMode(EVBF_TEXENV_MODE	nMode);
	virtual EVBF_TEXENV_MODE GetTexEnvMode() { return m_nTexEnvMode; }

	// ����/��ȡ������Ƿ�ɼ���Ĭ��ֵΪfalse��
	void SetPointVisible(bool bVisible);
	bool IsPointVisible()	{ return m_bPointVisible; }

    // ����/��ȡ��������ʽ
    void                  SetPointStyle(const VBF_POINTSTYLE& style);
    const VBF_POINTSTYLE& GetPointStyle()	{ return m_PointStyle; }

    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    // ������Ⱦ״̬
    virtual void SetStateSet();

protected:

    // ������������/��������
    osg::Vec3Array* CreateVerts();
    osg::Vec2Array* CreateTexCoords();

    // ��������εĸ�������
    osg::Geometry* CreateSolid();
    osg::Geometry* CreateLine();
    osg::Geometry* CreatePoints();

protected:

	// ���괮
	std::vector<osg::Vec2f>		m_vPoints;			// �û����õ����괮
	std::vector<osg::Vec2f>		m_vTexCoords;		// �û����õ��������꣨����Ϊ�գ�

	EVBF_GEOMETRY_STYLE			m_nStyleGeom;		// ���λ��Ʒ�ʽ��ʵ��/����
	EVBF_SHADE_STYLE			m_nStyleShade;		// ��ɫ��ʽ����ɫ/����
	EVBF_TEXENV_MODE			m_nTexEnvMode;		// ͬʱ���ö�����ɫ������ʱ�����ߵĻ�Ϸ�ʽ

	// ��ʽ
	osg::Vec4f					m_colorSolid;
	VBF_LINESTYLE				m_LineStyle;

	// ����㣨��GL_POINTS��ʽ���ƣ�
	bool						m_bPointVisible;	// �Ƿ���ʾ�����
	VBF_POINTSTYLE				m_PointStyle;		// ��������ʽ

	// ����
	ref_ptr<osg::Image>			m_piImage;
	bool						m_bTexToCache;      // �����Ƿ���Ҫ���뻺�棬Ĭ��Ϊfalse
	int							m_nNumTexRows;		// �����ظ�����������
	int							m_nNumTexCols;		// �����ظ�����������

    // �ʷֵĽ��
    int                         m_nNumTriangles;
    WORD*                       m_pIndices;

	// �볡��ͼ�йص�����
	ref_ptr<osg::Vec3Array>		m_piVerts;		// ��������
	ref_ptr<osg::Geometry>		m_piGeomSolid;
	ref_ptr<osg::Geometry>		m_piGeomLine;
	ref_ptr<osg::Geometry>		m_piGeomPoints;
};


#endif 
