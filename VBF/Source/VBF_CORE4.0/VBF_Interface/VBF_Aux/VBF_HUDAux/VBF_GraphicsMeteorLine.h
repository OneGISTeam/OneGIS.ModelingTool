//*******************************************************************
// FileName��VBF_GraphicsMeteorLine.h
// Function����άͼ�Σ�������
// Author:
// Date:
//*******************************************************************

#ifndef __VBF_GRAPHICS_METEORLINE_H__
#define __VBF_GRAPHICS_METEORLINE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>

class CVBF_GraphicsImage;

class VBF_HUDAUX_EXPORT CVBF_GraphicsMeteorLine : public CVBF_Graphics
{
public:
    CVBF_GraphicsMeteorLine(const std::string& strName="");
    virtual ~CVBF_GraphicsMeteorLine();

    // ����/��ȡ������ʽ
    void                 SetLineStyle(const VBF_LINESTYLE& style);
    const VBF_LINESTYLE& GetLineStyle() { return m_LineStyle; }

    void SetPath(const std::vector<osg::Vec3f>& vPoints);

    void SetTexImage(osg::Image* pImage, bool bTexToCache);

    osg::Vec3& GetImagePos(){ return m_vImagePos; }

    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

private:

    void CreateLine();
    void CreateImage();
private:

    std::vector<osg::Vec3f>	m_vPoints;	// �������괮
    VBF_LINESTYLE			m_LineStyle;// ���ߵ���ʽ


    ref_ptr<osg::Vec3Array>	m_ipVerts;	// ����
    ref_ptr<osg::Geometry>  m_ipGeomLine;

    ref_ptr<osg::Image>		m_piImage;
    bool					m_bTexToCache;	// �����Ƿ���Ҫ���뻺�棬Ĭ��Ϊfalse

    ref_ptr<osg::Geometry> m_ipGraphicsImage;

    osg::Vec3 m_vImagePos;

};


#endif 
