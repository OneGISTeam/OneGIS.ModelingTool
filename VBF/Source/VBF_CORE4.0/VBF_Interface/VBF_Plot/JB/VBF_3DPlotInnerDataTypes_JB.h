#ifndef __VBF_3DPLOT_INNER_DATATYPES_JB_H__
#define __VBF_3DPLOT_INNER_DATATYPES_JB_H__


#include <VBF_Base/ref_ptr>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>
//------------------------------------------------------------
// ����ṹ�壺VBF_JBCONTOUR
// �ṹ�����������������е�ͼԪ��ϣ������ÿ�ȣ��������
//------------------------------------------------------------
typedef struct _tagVBFJBContour : public ::CVBF_Referenced
{
    int						nIndexShape;	// ��Ӧ��m_vFillPolygons�е�������
    bool					bFill;			// �Ƿ����
    bool					bInner;			// �Ƿ�Ϊ������
    osg::Vec4f				colorFill;		// �����ɫ

    // ����������
    std::vector<osg::Vec3d>	vPoints;

    // ����ͼ�еļ�����
    ref_ptr<osg::Geometry>	piGeomSerifInner;	// �����ڲ�
    ref_ptr<osg::Geometry>	piGeomSerifOuter;	// �����ⲿ
    ref_ptr<osg::Geometry>	piGeomsFill[2];		// ��䲿�֣����飺��һ���zֵΪm_fThickness���ڶ����zֵΪ0.0��

    _tagVBFJBContour()
    {
        nIndexShape	= -1;
        bFill		= false;
        bInner		= true;
        colorFill	= osg::Vec4f(1.0f, 0.0f, 0.0f, 1.0f);

        vPoints.clear();
    }

    // ��ȡ����
    int GetNumPoints() const  { return (int)vPoints.size(); }

} VBF_JBCONTOUR;


//------------------------------------------------------------
// ��������Ҫ���ͼԪ��ԭʼ�������ݣ��������ж������Ƿ����
//------------------------------------------------------------
class CVBF_JbPolygon : public ::CVBF_Referenced
{
public:
    CVBF_Shape*         pShape;	// ��Ӧ������е�ͼ�Σ��ⲿָ�룩
    osg::Vec4f          color;
    vector<osg::Vec3d>  vPoints;

    // ��ɫ�Ƿ�ʧЧ
    bool                bDirtyColor;
    CVBF_JbPolygon()
    {
        pShape = NULL;
        color  = osg::Vec4f(1.0f, 0.0f, 0.0f, 1.0f);
        vPoints.clear();
        bDirtyColor = false;
    }

};

//------------------------------------------------------------
// ����ṹ�壺VBF_JBTEXTINFO
// �ṹ����������״��������и������ֵ��ı���Ϣ
//------------------------------------------------------------
typedef struct _tagVBFJBTextInfo : public ::CVBF_Referenced
{
    std::string				strText;		// �ı�����
    VBF_TEXTSTYLE			style;			// �ı���ʽ
    void*                   pShape;			// ��Ӧ������е�ͼ�Σ��ⲿָ�룩
    ref_ptr<osgText::Text>	piText;			// ����ͼ�е�Drawable

    // �����Ƿ�ʧЧ
    bool                    bDirtyText;     // �ı������Ƿ�ʧЧ
    bool                    bDirtyStyle;    // �ı���ʽ�Ƿ�ʧЧ

    _tagVBFJBTextInfo()
    {
        strText     = "";
        pShape      = NULL;

        bDirtyText  = false;
        bDirtyStyle = false;
        style.nFontResX = 120;
        style.nFontResY = 120;
    }

} VBF_JBTEXTINFO;




#endif
