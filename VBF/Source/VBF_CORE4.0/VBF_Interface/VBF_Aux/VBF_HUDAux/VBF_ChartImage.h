//*******************************************************************
// FileName��VBF_ChartImage.h
// Function��ͼ��
// Author:
// Date:
//*******************************************************************

#ifndef __VBF_CHART_IMAGE_H__
#define __VBF_CHART_IMAGE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>


class VBF_HUDAUX_EXPORT CVBF_ChartImage : public CVBF_Chart
{
public:
    CVBF_ChartImage(const std::string& strName="");
    virtual ~CVBF_ChartImage();


	// ����/��ȡ����ͼ��ָ��
    void		SetTexImage(osg::Image* pImage);
	osg::Image* GetTexImage() { return m_piImage.get(); }

	// ����/��ȡ����͸���ȣ�Ĭ��ֵΪ1.0��
    void  SetColor(osg::Vec4f color);
    osg::Vec4f GetColor() { return m_vColor; }


    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);
    virtual void Update();// ����


private:
    // ������Ⱦ״̬
    virtual void SetStateSet();

    // �������ε�ʵ�岿��
    osg::Geometry* CreateSolid();

private:
	// ����
	ref_ptr<osg::Image>		m_piImage;
    ref_ptr<osg::Vec3Array>	m_ipVerts;

    osg::Vec4f				m_vColor;	// ����͸����

	// �볡��ͼ�йص�����
    ref_ptr<osg::Geometry>	m_piGeomSolid;
};


#endif 
