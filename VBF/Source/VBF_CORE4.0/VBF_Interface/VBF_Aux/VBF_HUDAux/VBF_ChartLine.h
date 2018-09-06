#ifndef __VBF_CHART_LINE_H__
#define __VBF_CHART_LINE_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsText.h>
#include <VBF_Aux/VBF_HUDAux/VBF_ChartPartAxis.h>
#include <VBF_Aux/VBF_HUDAux/VBF_ChartPartGrid.h>

typedef struct _tagVBFPointStyleEx
{
    float			fSize;		// ��Ĵ�С
    osg::Vec4f		color;		// �����ɫ
    std::string     sTexFn;     // �����ļ���

    // ���캯��
    _tagVBFPointStyleEx()
    {
        fSize	= 1.0f;
        color	= osg::Vec4f(1.0f, 0.0f, 0.0f, 1.0f);
    }

    _tagVBFPointStyleEx& operator=(const _tagVBFPointStyleEx& src)
    {
        if(this==&src) return *this;

        fSize	= src.fSize;
        color	= src.color;
        sTexFn  = src.sTexFn;

        return *this;
    }

    bool operator==(const _tagVBFPointStyleEx& src)
    {
        if(this==&src) return true;

        if(!osg::equivalent(fSize, src.fSize)) return false;
        if(color!=src.color) return false;
        if(sTexFn!=src.sTexFn) return false;

        return true;
    }

} VBF_POINTSTYLEEX;

// ����ͼ

class VBF_HUDAUX_EXPORT CVBF_ChartLine : public CVBF_Chart
{
public:
    CVBF_ChartLine(const std::string& strName,int numSeries);
    virtual ~CVBF_ChartLine();

    virtual void Update(); // ����

    CVBF_ChartSeries& GetSeries(int idx) { return m_vSeries[idx]; }
    VBF_LINESTYLE&    GetLineStyle(int idx) { return m_vLineStyle[idx]; }
    VBF_POINTSTYLEEX& GetPointStyle(int idx) { return m_vPointStyle[idx]; }

    virtual void SetSize(unsigned int nWidth,unsigned int nHeight);
    virtual void SetPos(const osg::Vec2f& pt);

    // ��ȡ/���ò������ᡢ����
    CVBF_ChartAxisAttr&  GetAxisAttr()  { return m_AxisAttr;  } // ��ȡ�����ᣨ������
    CVBF_ChartAxisValue& GetAxisValue() { return m_AxisValue; } // ��ȡ�����ᣨֵ��
    CVBF_ChartPartGrid&  GetGrid() { return m_Grid; } // ����

    void SetAxisAtRight(bool bRight);
    void SetValueTextVisible(bool bVisible) { m_bVisibleValueText = bVisible;} // ֵע���Ƿ�ɼ�
    void SetFillVisible(bool bVisible) { m_bFillVisible = bVisible; }
private:
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    void CreateValueText(CVBF_DrawableList& vDrawables);// ��������ֵע��
    void CalLineVerts(osg::Vec3Array* pVerts,std::vector<float>& vData);
    void CalAreaVerts(osg::Vec3Array* pVerts,std::vector<float>& vData);

    void CalculateAxisPos();
    void UpdateText();

    std::vector<CVBF_ChartSeries> m_vSeries;
    std::vector<VBF_LINESTYLE>    m_vLineStyle;
    std::vector<VBF_POINTSTYLEEX> m_vPointStyle;

    std::vector< ref_ptr<osg::Vec3Array> > m_vVerts;// ��������(������)�����ڶ�̬���£���m_vSeries��Ӧ��ÿ��Series��Ӧһ��Vec3Array
    std::vector< ref_ptr<osg::Vec3Array> > m_vVertsArea;

    VBF_TEXTSTYLE m_TextStyleValue;	// �ı���ʽ
    std::vector< ref_ptr<osgText::Text> > m_vTextValue;    // ����ֵע��

    // ������
    CVBF_ChartAxisAttr  m_AxisAttr;
    CVBF_ChartAxisValue m_AxisValue;

    // ��������
    CVBF_ChartPartGrid m_Grid;

    bool m_bAxisAtRight;
    bool m_bVisibleValueText;// ֵע���Ƿ�ɼ�
    bool m_bFillVisible;// �Ƿ����
};


#endif
