//*******************************************************************
// FileName��VBF_GraphicsText.h
// Function����άͼ�Σ��ı�
// Author:   ��Ө
// Date:     2015-12-30
//*******************************************************************

#ifndef __VBF_GRAPHICS_TEXT_H__
#define __VBF_GRAPHICS_TEXT_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>
#include <VBF_Engine/VBF_Text/Text>


//--------------------------------------------------------------------
// ����ö�٣��ı����뷽ʽ������λ�����ı���Χ�е�λ�ù�ϵ
// ö��������EVBF_TEXT_ALIGN
//--------------------------------------------------------------------
enum EVBF_TEXT_ALIGN
{
	VBF_TEXT_ALIGN_LEFT_TOP,		// ���ϣ�Ĭ��ֵ��
	VBF_TEXT_ALIGN_LEFT_CENTER,		// ����
	VBF_TEXT_ALIGN_LEFT_BOTTOM,		// ����

    VBF_TEXT_ALIGN_CENTER_TOP,		// ����
    VBF_TEXT_ALIGN_CENTER_CENTER,	// ����
    VBF_TEXT_ALIGN_CENTER_BOTTOM,	// ����

    VBF_TEXT_ALIGN_RIGHT_TOP,		// ����
    VBF_TEXT_ALIGN_RIGHT_CENTER,	// ����
    VBF_TEXT_ALIGN_RIGHT_BOTTOM     // ����
};


class VBF_HUDAUX_EXPORT CVBF_GraphicsText : public CVBF_Graphics
{
public:
	CVBF_GraphicsText(const std::string& strName="");
	virtual ~CVBF_GraphicsText();

	// ����/��ȡ�ı�����
	void               SetText(const std::string& strText);
	const std::string& GetText() { return m_strText; }

	// ����/��ȡ�ı�����Ļ���꣨��λ�����أ�Ĭ��ֵΪ(0,0,-1)��
	void       SetPos(const osg::Vec2f& ptText);
	osg::Vec2f GetPos() { return m_ptText; }

	// ����/��ȡ�ı���ʽ
	void                 SetTextStyle(const VBF_TEXTSTYLE& style);
	const VBF_TEXTSTYLE& GetTextStyle() { return m_TextStyle; }

	// ����/��ȡ�ı����뷽ʽ��Ĭ��ֵΪVBF_TEXT_ALIGN_LEFT_TOP��
	void            SetTextAlign(EVBF_TEXT_ALIGN nAlign);
	EVBF_TEXT_ALIGN GetTextAlign() { return m_nTextAlign; }

	// ����/��ȡ�ı�������Ŀɼ���
	void SetFrameVisible(bool bVisible);
	bool IsFrameVisible() { return m_bFrameVisible; }

	// ����/��ȡ�ı����������ʽ
	void                      SetFrameStyle(const VBF_POLYGON2DSTYLE& style);
	const VBF_POLYGON2DSTYLE& GetFrameStyle()	{ return m_FrameStyle; }

    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

protected:

	// �����ı�
    virtual void CreateText();

	// ����������
	void CreateFrame();

	osg::Geometry* CreateFrame_Solid();
	osg::Geometry* CreateFrame_Wireframe();
	osg::Geometry* CreateFrame_Shadow();

	// �����ı����ݺ���ʽ���㱳����ߴ�
	void UpdateFrameSize(bool bForceUpdate=false);
	void UpdateFrameVerts();
	void UpdateFrameShadowVerts();

	// ��ӳ����л�ȡһ������
	osgText::Font* GetFont(const std::string& strFont);

	// �����ı����뷽ʽ����ƽ��
    virtual void Translate();

protected:

	// �ı�����Ļ����
	osg::Vec2f					m_ptText;

	// �ı����뷽ʽ
	EVBF_TEXT_ALIGN				m_nTextAlign;

	// �ı�
	std::string					m_strText;		// �ı�����
	VBF_TEXTSTYLE				m_TextStyle;	// �ı���ʽ

	// ���������ʽ
	bool						m_bFrameVisible;	// �������Ƿ�ɼ�
	int							m_nFrameSizeX;		// ��ȣ���λ�����أ�
	int							m_nFrameSizeY;		// �߶ȣ���λ�����أ�
	VBF_POLYGON2DSTYLE			m_FrameStyle;

	// ����������Ļ���½ǵ�Ϊԭ�㣬���������ΪС�����Σ����������ұ�Ϊ�ı�����
	ref_ptr<osg::Vec3Array>		m_piFrameVerts;			// �������7������
	ref_ptr<osg::Vec3Array>		m_piFrameShadowVerts;	// ��������Ӱ��8������

	// ��¼����Drawable���Ա��޸�ʱʹ��
	ref_ptr<osgText::Text>		m_piText;				// �ı�
	ref_ptr<osg::Geometry>		m_piGeomFrameShadow;	// ��������Ӱ
	ref_ptr<osg::Geometry>		m_piGeomFrameSolid;		// ������ʵ�岿��
	ref_ptr<osg::Geometry>		m_piGeomFrameWireframe;	// ���������񲿷�
};


#endif 
