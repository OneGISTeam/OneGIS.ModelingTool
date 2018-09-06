//*******************************************************************
// FileName��VBF_GraphicsPolyPolygon.h
// Function����άͼ�Σ�һ������
// Author:   ��Ө
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_POLY_POLYGON_H__
#define __VBF_GRAPHICS_POLY_POLYGON_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>
#include <VBF_Macros.h>


// ���������
typedef std::vector<osg::Vec2f>  CVBF_Point2DList;


// ����ṹ�壺��ά����ε���Ϣ
struct VBF_POLYGON2D : public ::CVBF_Referenced
{
public:
	std::string					m_strID;		// �û����õĶ����ID�ţ�������Ψһ��

	// ���괮
	std::vector<osg::Vec2f>		m_vPoints;		// �û����õ����괮
	std::vector<osg::Vec2f>		m_vTexCoords;	// �û����õ��������꣨����Ϊ�գ�

	// �����ظ�����
	int							m_nNumTexRows;		// �����ظ�����������
	int							m_nNumTexCols;		// �����ظ�����������

	// ��ʽ
	osg::Vec4f					m_colorSolid;
	VBF_LINESTYLE				m_LineStyle;

	// �ʷֵĽ��
	int                         m_nNumTriangles;
	WORD*                       m_pIndices;

	// �볡��ͼ�йص�����
	ref_ptr<osg::Vec3Array>		m_piVerts;		// ��������
	ref_ptr<osg::Geometry>		m_piGeomSolid;
	ref_ptr<osg::Geometry>		m_piGeomLine;

	VBF_POLYGON2D(const std::string& strID)
	{
		m_strID				= strID;
		m_nNumTexRows		= 1;
		m_nNumTexCols		= 1;
		m_nNumTriangles		= 0;
		m_pIndices			= NULL;

		m_colorSolid		= osg::Vec4f(0, 1, 1, 0.6);
		m_LineStyle.fWidth  = 2.0f;
		m_LineStyle.color	= osg::Vec4f(0, 1, 1, 1.0);
	}

	virtual ~VBF_POLYGON2D()
	{
		SAFE_DELETE(m_pIndices);
	}
};

// ���������б�
typedef std::vector< ref_ptr<VBF_POLYGON2D> >  CVBF_PolygonList;

class VBF_HUDAUX_EXPORT CVBF_GraphicsPolyPolygon : public CVBF_Graphics
{
public:
	CVBF_GraphicsPolyPolygon(const std::string& strName="");
	virtual ~CVBF_GraphicsPolyPolygon();

	// ���һ������Σ�����strID��ʾ����������е�ΨһID�ţ��������ظ��������ID���Ѿ����ڷ���false
	bool AddPolygon(const std::string& strID, const CVBF_Point2DList& vPoints);
	bool AddPolygonAndTexCoords(const std::string& strID, const CVBF_Point2DList& vPoints, const std::vector<osg::Vec2f>& vTexCoords);

	// ��ȡĳ������ε����괮���������ε�ID�Ų����ڷ���false
	bool GetPolygon(const std::string& strID, CVBF_Point2DList& vPoints);

	// ɾ��һ������Σ��������ε�ID�Ų����ڷ���false
	bool RemovePolygon(const std::string& strID);


	// ����/��ȡ���ж���εļ�����ʽ��Ĭ��Ϊ��ʵ��+����
	virtual void                SetGeometryStyle(EVBF_GEOMETRY_STYLE nStyle);
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle() { return m_nStyleGeom; }

	// ����/��ȡ���ж���ε���ɫ��ʽ��Ĭ��Ϊ��ֻʹ����ɫ
	virtual void             SetShadeStyle(EVBF_SHADE_STYLE nStyle);
	virtual EVBF_SHADE_STYLE GetShadeStyle() { return m_nStyleShade; }

	// ����/��ȡĳ������ε�ʵ����ɫ
	bool SetSolidColor(const std::string& strID, const osg::Vec4f& color);
	bool GetSolidColor(const std::string& strID, osg::Vec4f& color);

	// ����/��ȡĳ������εı�����ʽ
	bool SetLineStyle(const std::string& strID, const VBF_LINESTYLE& style);
	bool GetLineStyle(const std::string& strID, VBF_LINESTYLE& style);

	// ����/��ȡ���ж���ε�����ͼ��ָ�루���ж����ʹ��ͬһ������
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache);
	virtual osg::Image* GetTexImage() { return m_piImage.get(); }

	// ����/��ȡĳ������ε��������ݺ᷽����ظ�������Ĭ��ֵ��Ϊ1���������ε�ID�Ų����ڷ���false
	virtual bool SetNumTexRepeats(const std::string& strID, int nNumRows, int nNumCols);
	virtual bool GetNumTexRepeats(const std::string& strID, int& nNumRows, int& nNumCols);

	// ����/��ȡ���ж����ͬʱ���ö�����ɫ������ʱ�����ߵĻ�Ϸ�ʽ
	virtual void SetTexEnvMode(EVBF_TEXENV_MODE	nMode);
	virtual EVBF_TEXENV_MODE GetTexEnvMode() { return m_nTexEnvMode; }

	// ����/��ȡ���ж���ε�������Ƿ�ɼ���Ĭ��ֵΪfalse��
	void SetPointVisible(bool bVisible);
	bool IsPointVisible()	{ return m_bPointVisible; }

    // ����/��ȡ���ж���ε���������ʽ
    void                  SetPointStyle(const VBF_POINTSTYLE& style);
    const VBF_POINTSTYLE& GetPointStyle()	{ return m_PointStyle; }

    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    // ������Ⱦ״̬
    virtual void SetStateSet();

private:

	// ���б��в���ĳһ�������
	VBF_POLYGON2D* FindPolygon(const std::string& strID);

    // ������������/��������
    osg::Vec3Array* CreateVerts(VBF_POLYGON2D* pPolygon);
    osg::Vec2Array* CreateTexCoords(VBF_POLYGON2D* pPolygon);

    // ��������εĸ�������
    osg::Geometry* CreateSolid(VBF_POLYGON2D* pPolygon);
    osg::Geometry* CreateLine(VBF_POLYGON2D* pPolygon);
    osg::Geometry* CreatePoints();

private:

	// ������б�������Ҫ�����û�����AddPolygon()��˳���������˳�����Դ˴�����ʹ��std::map��
	CVBF_PolygonList			m_vPolygons;

	EVBF_GEOMETRY_STYLE			m_nStyleGeom;		// ���λ��Ʒ�ʽ��ʵ��/����
	EVBF_SHADE_STYLE			m_nStyleShade;		// ��ɫ��ʽ����ɫ/����
	EVBF_TEXENV_MODE			m_nTexEnvMode;		// ͬʱ���ö�����ɫ������ʱ�����ߵĻ�Ϸ�ʽ

	// ����㣨��GL_POINTS��ʽ���ƣ�
	bool						m_bPointVisible;	// �Ƿ���ʾ�����
	VBF_POINTSTYLE				m_PointStyle;		// ��������ʽ

	// �������ж���ι���һ������
	ref_ptr<osg::Image>			m_piImage;
	bool						m_bTexToCache;      // �����Ƿ���Ҫ���뻺�棬Ĭ��Ϊfalse

	// ��������㹲��һ��Drawable
	ref_ptr<osg::Geometry>		m_piGeomPoints;
};


#endif 
