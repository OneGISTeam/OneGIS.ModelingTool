//*******************************************************************
// FileName��VBF_SGGeodeText.h
// Function��Ҷ�ڵ㣬�ɻ����ı����䱳���򣬲�����ı�����ȫ�����ơ��̶����ش�С����λ������
// Author:   ��Ө
// Date:     2015-12-03
//*******************************************************************

#ifndef __VBF_SGGEODE_TEXT_H__
#define __VBF_SGGEODE_TEXT_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGeometryBillboard.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Aux/VBF_GLAux/VBF_SGGeodeMatrixTransform.h>

class CVBF_SGDrawableSet;

// ��������ӳ���
typedef std::map< std::string, ref_ptr<osgText::Font> > CVBF_FontMap;


class VBF_GLAUX_EXPORT CVBF_SGGeodeText : public CVBF_SGGeodeMatrixTransform
{
private:
	typedef CVBF_SGGeodeMatrixTransform BaseClass;

public:
	CVBF_SGGeodeText();
	CVBF_SGGeodeText(const CVBF_SGGeodeText& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
	virtual ~CVBF_SGGeodeText();

	META_Node(VBF, CVBF_SGGeodeText)

	// ��ʼ������ͼ
	void Init();

	// ����/��ȡ�ı�����
	void               SetText(const std::string& strText);
	const std::string& GetText() { return m_strText; }

	// ����/��ȡ�ı���ʽ
	void                 SetTextStyle(const VBF_TEXTSTYLE& style) { m_TextStyle = style; }
	const VBF_TEXTSTYLE& GetTextStyle() { return m_TextStyle; }

	// ����/��ȡ�ı�������Ŀɼ���
	void SetFrameVisible(bool bVisible) { m_bFrameVisible = bVisible; }
	bool IsFrameVisible() { return m_bFrameVisible; }

	// ����/��ȡ�ı����������ʽ
	void                      SetFrameStyle(const VBF_POLYGON2DSTYLE& style) { m_FrameStyle = style; }
	const VBF_POLYGON2DSTYLE& GetFrameStyle()	{ return m_FrameStyle; }

	// ����/��ȡ�Ƿ���Ʊ������еĶ�λ��ʶ�������ı�������ߵ�С�����Σ�Ĭ��Ϊtrue��
	void SetIndicatorVisible(bool bVisible);
	bool IsIndicatorVisible() { return (m_nTriSpace > 0); }

	// ����/��ȡ��Ļ����ϵ�µ����꣨��λ�����أ�Ĭ��ֵΪ(0,0,-1)��
	void       SetScreenPos(const osg::Vec3d& vPos);
	const osg::Vec3d& GetScreenPos() { return m_vScreenPos; }

    // �ж�ĳ����Ļ���Ƿ����ı���Χ��
    bool Contains(float x, float y);

private:

	// �����ı�Ҷ�ڵ�
	void CreateText();

	// ����������Ҷ�ڵ�
	void CreateFrame();

	osg::Geometry* CreateFrame_Solid();
	osg::Geometry* CreateFrame_Wireframe();
	osg::Geometry* CreateFrame_Shadow();

	// �����ı����ݺ���ʽ���㱳����ߴ�
	void UpdateFrameSize(bool bForceUpdate=false);
	void UpdateFrameVerts();
	void UpdateFrameShadowVerts();

	// �����ı���ʽ
	void UpdateTextStyle();

	// ��ӳ����л�ȡһ������
	osgText::Font* GetFont(const std::string& strFont);

    // �ı����������ı�ʱ��������Ӧ�ĳ���ͼ�ڵ㣨ÿ֡����ǰ���ã�
    void UpdateSG();
    void UpdateText();
    void OnUpdateTextStyle();
    void UpdateFrameStyle();

private:

	// �ı�
	std::string						m_strText;		// �ı�����
	VBF_TEXTSTYLE					m_TextStyle;	// �ı���ʽ

	// ���������ʽ
	bool							m_bFrameVisible;	// �������Ƿ�ɼ�
	int								m_nFrameSizeX;		// ��ȣ���λ�����أ�
	int								m_nFrameSizeY;		// �߶ȣ���λ�����أ�
	VBF_POLYGON2DSTYLE				m_FrameStyle;

	// С���������ı�����֮��ļ������λ�����أ������������εĸߣ���ֵΪ0��ʾ�����������Σ�
	int								m_nTriSpace;

	// ����������Ļ���½ǵ�Ϊԭ�㣬���������ΪС�����Σ����������ұ�Ϊ�ı�����
	ref_ptr<osg::Vec3Array>			m_piFrameVerts;			// �������7������
	ref_ptr<osg::Vec3Array>			m_piFrameShadowVerts;	// ��������Ӱ��8������

	// ��¼����Drawable���Ա��޸�ʱʹ��
	ref_ptr<osg::Geometry>			m_piGeomFrameShadow;	// ��������Ӱ
	ref_ptr<osg::Geometry>			m_piGeomFrameSolid;		// ������ʵ�岿��
	ref_ptr<osg::Geometry>			m_piGeomFrameWireframe;	// ���������񲿷�
	ref_ptr<osgText::Text>			m_piText;				// �ı�

	// �ı����䱳��������Ļ����ϵ�µ�����/ƫ��������λ�����أ�Ĭ��ֵΪ(0,0)��
	osg::Vec3d                      m_vScreenPos;		// �û����õ���Ļ����

	ref_ptr<CVBF_SGDrawableSet>		m_ipDrawableSet;
};

#endif 
