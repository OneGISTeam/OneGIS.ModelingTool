//*******************************************************************
// FileName��VBF_GraphicsAppearance.h
// Function�������Զ���ͼ�ε��������
// Author:   ��Ө
// Date:     2013-11-11
//*******************************************************************

#ifndef __VBF_GRAPHICS_APPEARANCE_H__
#define __VBF_GRAPHICS_APPEARANCE_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>
#include <Types/VBF_Optional.h>

#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <VBF_Common/VBF_XML/tinyxml.h>

class CVBF_Config;

//---------------------------------------------------------------
// �����ࣺVBF_PART_INFO
// ���������Զ���ͼ����۵�ĳ������
//---------------------------------------------------------------
class VBF_GLAUX_EXPORT CVBF_PartInfo
{
public:
	CVBF_PartInfo();
	virtual ~CVBF_PartInfo();

	// ���ظ�ֵ������
	CVBF_PartInfo& operator=(const CVBF_PartInfo& src);

	// ���ø�����۲���������ֵΪtrue��ʾ���óɹ�
	bool SetVisible(bool bVisible);
	bool SetGeometryStyle(EVBF_GEOMETRY_STYLE nStyle);
	bool SetShadeStyle(EVBF_SHADE_STYLE nStyle);
	bool SetColor(const osg::Vec4f& color);
	bool SetColor(const osg::Vec4f& color0, const osg::Vec4f& color1);
    bool SetLineStyle(const VBF_LINESTYLE& ls);
	void SetNumTexRepeats(int nNumRows, int nNumCols);

	// �жϸò����Ƿ�����ʹ�þ�̬/��̬����
	bool IsUsingStaticTexture();
	bool IsUsingDynamicTexture();

public:
	EVBF_GEOMETRY_STYLE			m_nStyleGeom;		// ���λ��Ʒ�ʽ��ʵ��/����
	EVBF_SHADE_STYLE			m_nStyleShade;		// ��ɫ��ʽ����ɫ/����

	bool						m_bExist;			// �Ƿ���ڣ���ֵ��ϵͳ�Զ����㣬�û������޸ģ�
	bool						m_bVisible;			// �Ƿ�ɼ�
	osg::Vec4f					m_color0;			// ����ɫ����ʼɫ��Ҳ��Ϊ��һɫ��
	CVBF_Optional<osg::Vec4f>	m_color1;			// ����ɫ�Ľ���ɫ
    VBF_LINESTYLE				m_LineStyle;		// �����ߵĴֶ�

	// �����ظ�����
	int							m_nNumTexRows;		// �����ں�����ظ�����
	int							m_nNumTexCols;		// ������������ظ�����

	// ����
	bool						m_bEnableTex;		// �Ƿ�����������
	bool						m_bTexToCache;		// �Ƿ���Ҫ��������������뻺��
	ref_ptr<osg::Image>			m_piImage;			// ����ͼ��ָ��
	ref_ptr<osg::Texture2D>		m_piTexture;		// ����ָ��

    // ����ͼ����
    ref_ptr<osg::Drawable>      m_ipDrawableSolid;      // ��䲿��
    ref_ptr<osg::Drawable>      m_ipDrawableWireframe;  // �����߲���
};



//---------------------------------------------------------------
// �����ࣺCVBF_GraphicsAppearance
// ���������Զ���ͼ�ε����
//---------------------------------------------------------------
class VBF_GLAUX_EXPORT CVBF_GraphicsAppearance : public IVBF_GraphicsAppearance
{
public:
	CVBF_GraphicsAppearance();
	virtual ~CVBF_GraphicsAppearance();

	// ����/��ȡ�Զ���ͼ��ĳ�������Ƿ�ɼ���Ĭ��ֵΪtrue
	virtual void SetVisible(int nPart, bool bVisible);
	virtual bool IsVisible(int nPart);

	// ����/��ȡĳ�����ֵļ�����ʽ��Ĭ��Ϊ��ʵ��+����
	virtual void                SetGeometryStyle(int nPart, EVBF_GEOMETRY_STYLE nStyle);
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle(int nPart);

	// ����/��ȡĳ�����ֵ���ɫ��ʽ��Ĭ��Ϊ��ֻʹ����ɫ
	virtual void             SetShadeStyle(int nPart, EVBF_SHADE_STYLE nStyle);
	virtual EVBF_SHADE_STYLE GetShadeStyle(int nPart);

	// ����ĳ�����ֵĵ�һɫ������ɫ�����������Զ���ͼ�Σ�
	virtual void       SetColor(int nPart, const osg::Vec4f& color);
	virtual osg::Vec4f GetColor(int nPart);

	// ����ĳ�����ֵĽ���ɫ������ɫ���Զ���ͼ�ζ���ƽ�����䵽�ײ���
	virtual void SetColor(int nPart, const osg::Vec4f& color0, const osg::Vec4f& color1);
	virtual bool GetColor(int nPart, osg::Vec4f& color0, osg::Vec4f& color1);

	// ���ĳ�����ֵ���ʽ�а����߿������ߵĴֶȣ��ߵ���ɫ���Զ���ͼ����ͬ��
    virtual void  SetLineStyle(int nPart, const VBF_LINESTYLE& ls);
    virtual VBF_LINESTYLE& GetLineStyle(int nPart);

	// ����/��ȡĳ�����ֵ��������ݺ᷽����ظ�������Ĭ��ֵ��Ϊ1
	virtual void SetNumTexRepeats(int nPart, int nNumRows, int nNumCols);
	virtual void GetNumTexRepeats(int nPart, int& nNumRows, int& nNumCols);

	// �ж�ĳ�������Ƿ�����ʹ�õ�һɫ/����ɫ/��̬����/��̬����
	virtual bool IsUsingSingleColor(int nPart);
	virtual bool IsUsingFadedColor(int nPart);
	virtual bool IsUsingStaticTexture(int nPart);
	virtual bool IsUsingDynamicTexture(int nPart);

	// ����/��ȡĳ�����ֵ�����ͼ��ָ��
	virtual void		SetTexImage(int nPart, osg::Image* pImage, bool bTexToCache);
	virtual osg::Image* GetTexImage(int nPart);

public:

	// ����/�������۵������ߣ�����������ʵ��ģ��
	void SetOwner(IVBF_GraphicsAppearanceOwner* pIOwner) { m_pIOwner = pIOwner; }

	// ���ظ�ֵ������
	CVBF_GraphicsAppearance& operator=(const CVBF_GraphicsAppearance& src);

    // ���л�
    virtual bool WriteToXML(TiXmlElement* pElemAppr);
    virtual bool ReadFromXML(TiXmlElement* pElemAppr);

	// ִ��json�ű�
	virtual void ExecuteScript(const CVBF_Config& conf);

private:

	// �жϸ������Զ���ͼ��ĳ�����ֵ��������Ƿ���Ч
	bool IsPartValid(int nPart) { return (nPart>=0 && nPart<(int)m_vPartInfos.size()); }

public:

	// �Զ���ͼ�θ������ֵ���Ϣ����������Ԫ�صĸ����ɸ���ģ���Լ����壩
	std::vector<CVBF_PartInfo>		m_vPartInfos;

	// �۲��ߣ�����������ʵ��ģ�ͣ�
	IVBF_GraphicsAppearanceOwner*	m_pIOwner;
};


//-----------------------------------------------------------------------------
// ȫ�ֺ�����VBF_SetPartTexture()
// �������������������ĳ�����ֵ�����
//-----------------------------------------------------------------------------
void VBF_GLAUX_EXPORT VBF_SetPartTexture(osg::StateSet* ss, CVBF_PartInfo& part);


#endif 
