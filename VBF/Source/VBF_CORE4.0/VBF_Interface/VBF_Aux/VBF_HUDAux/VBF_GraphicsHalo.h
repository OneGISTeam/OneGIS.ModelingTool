//*******************************************************************
// FileName��VBF_GraphicsHalo.h
// Function������ȦЧ��
// Author:
// Date:
//*******************************************************************

#ifndef __VBF_GRAPHICS_HALO_H__
#define __VBF_GRAPHICS_HALO_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>


class VBF_HUDAUX_EXPORT CVBF_GraphicsHalo : public CVBF_Graphics
{
public:
    CVBF_GraphicsHalo(const std::string& strName="");
    virtual ~CVBF_GraphicsHalo();

    // ����/��ȡ��λ�����Ļ���꣨��λ�����أ�Ĭ��ֵΪ(0,0,-1)��
    void SetPos(const osg::Vec2f& pt)
    {
        m_pt = pt;
        DirtyModel();// ʹģ�ͽڵ�ʧЧ
    }
    osg::Vec2f GetPos() { return m_pt; }

	// ����/��ȡ����ͼ��ָ��
    void		SetTexImage(osg::Image* pImage);
    osg::Image* GetTexImage() { return m_ipImage.get(); }

    void SetColor(osg::Vec4 vColor0,osg::Vec4 vColor1);// ʵ����ɫ����
    void SetSize(double dMinR,double dMaxR) { m_dMaxR = dMaxR; m_dMinR = dMinR; } // ʵ�ִ�С����

    // ����ÿ��ѭ����֡��
    void SetFramePerCycle(int numFrame) { m_numFrame = numFrame; }

    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    // ������Ⱦ״̬
    virtual void SetStateSet();
private:
    // �������ε�ʵ�岿��
    osg::Geometry* CreateSolid();


private:
    osg::Vec2f	m_pt;// ��λ����Ļ����
    osg::Vec4f m_vColor0;
    osg::Vec4f m_vColor1;

    ref_ptr<osg::Image>		m_ipImage;// ����

	// �볡��ͼ�йص�����
    ref_ptr<osg::Geometry>	m_ipGeomSolid;

    double m_dMinR; // ��С�뾶
    double m_dMaxR; // ���뾶

    int m_numFrame;
};


#endif 
