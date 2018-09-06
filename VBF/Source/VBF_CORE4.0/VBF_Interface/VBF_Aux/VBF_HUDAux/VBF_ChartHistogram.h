#ifndef __VBF_CHART_HISTOGRAM_H__
#define __VBF_CHART_HISTOGRAM_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Engine/VBF_Text/Text>
#include <VBF_Aux/VBF_HUDAux/VBF_GraphicsText.h>
#include <VBF_Aux/VBF_HUDAux/VBF_ChartPartAxis.h>
#include <VBF_Aux/VBF_HUDAux/VBF_ChartPartGrid.h>

// ��״ͼ
// ���Bar�����Եĸ���ȷ��
class VBF_HUDAUX_EXPORT CVBF_ChartHistogram : public CVBF_Chart
{
public:
    enum Mode
    {
        ACCUMULATION, // �ۼ�
        APPOSITION    // ���У�����

    };
    CVBF_ChartHistogram(const std::string& strName,int numAttr,int numSeries);
    virtual ~CVBF_ChartHistogram();

    // ��������
    int  GetValue(int nSeries, int nAttr) { return m_vSeries[nSeries].Data()[nAttr]; }
    void SetValue(int nSeries,int nAttr,double dValue) { m_vSeries[nSeries].Data()[nAttr] = dValue; }
    CVBF_ChartSeries& GetSeries(int idx) { return m_vSeries[idx]; }

    // ����ģʽ
    void SetMode(Mode eMode) { m_eMode = eMode; }

    // ������ʽ
    void                SetSeriesStyle(int idx,const VBF_POLYGON2DSTYLE& style);
    VBF_POLYGON2DSTYLE& GetSeriesStyle(int idx){ return m_vSeriesStyles[idx]; }

    void                SetAttrStyle(int idx,const VBF_POLYGON2DSTYLE& style);
    VBF_POLYGON2DSTYLE& GetAttrStyle(int idx){ return m_vAttrStyles[idx]; }

    void SetMaxValue(int nMaxLength,double dMaxValue);
    void SetBarWidth(int nWidth,int nSpace);  // ���,���

    // ��ȡ/���ò������ᡢ����
    CVBF_ChartAxisAttr&  GetAxisAttr()  { return m_AxisAttr;  } // ��ȡ�����ᣨ������
    CVBF_ChartAxisValue& GetAxisValue() { return m_AxisValue; } // ��ȡ�����ᣨֵ��
    CVBF_ChartPartGrid&  GetGrid() { return m_Grid; } // ����

    void SeAttrValueVisible( bool bVisible) { m_bVisibleAttrValue = bVisible;}
    VBF_TEXTSTYLE& GetValueTextStyle(){ return m_TextStyleValue; }// ��ȡ����ֵע������

    virtual void SetPos(const osg::Vec2f& pt);
    void SetSpaceToAxis(float fDis) { m_fSpaceToAxis = fDis; }

    virtual void Update(); // ����

    // �������ɸ�ͼ�ε�����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

private:

    void CreateSolid(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables);
    void CreateWireframe(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables);
    void CreateShadow(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables);
    void CreateValueText(const CVBF_GraphicsContext& context,CVBF_DrawableList& vDrawables);// ��������ֵע��


    void UpdateVerts();
    void UpdateShadowVerts();


    float m_fSpaceToAxis; // �������ϵ�һ��������֮��Ŀհ׾���

protected:
    Mode m_eMode;
    // ���ʾ1980��1990��2000��2010��2020�����ݵ��˾�GDP���˾����룬��������ϵ�����������˾�GDP���˾����룩�������������1980��1990��2000��2010��2020��
    int m_numSeries;// ����ϵ�еĸ���
    int m_numAttr;  // ��ʾ�����Եĸ���

    int         m_nMaxLength; // ��󳤶�
    double      m_dMaxValue;  // ����ֵ

    int			m_nBarWidth;    // ÿ���ĸ߶ȣ���λ�����أ�
    int         m_nBarSpace;    // ÿ��֮��ļ��

    std::vector<CVBF_ChartSeries> m_vSeries;

    // ����ѡ��һ
    std::vector<VBF_POLYGON2DSTYLE>	m_vSeriesStyles; // ÿһ������ʹ�õ���ʽ
    std::vector<VBF_POLYGON2DSTYLE>	m_vAttrStyles;   // ÿһ������ʹ�õ���ʽ

    // ��¼���㼰Drawable���Ա��޸�ʱʹ��
    ref_ptr<osg::Vec3Array>		m_ipVerts;			// ���Ķ���
    ref_ptr<osg::Vec3Array>		m_ipVertsShadow;	// ��Ӱ�Ķ���

    ref_ptr<osg::Geometry>		m_ipDrawableShadow;     // ��Ӱ
    ref_ptr<osg::Geometry>		m_ipDrawableSolid;      // ʵ��
    ref_ptr<osg::Geometry>		m_ipDrawableWireframe;	// ����



    bool m_bHorizontal;// �Ƿ�ˮƽ��

    // ����ֵע��
    bool m_bVisibleAttrValue;// ����ֵע���Ƿ���ʾ
    int           m_idxTextValue;   // ע��ϵ�е�������-1��ע�ǣ�
    VBF_TEXTSTYLE m_TextStyleValue;	// �ı���ʽ
    std::vector< ref_ptr<osgText::Text> > m_vTextValue;    // ����ֵע��


    // ������
    CVBF_ChartAxisAttr  m_AxisAttr;
    CVBF_ChartAxisValue m_AxisValue;


    // ��������
    CVBF_ChartPartGrid m_Grid;
};

class VBF_HUDAUX_EXPORT CVBF_ChartHistogramH: public CVBF_ChartHistogram
{
public:
    CVBF_ChartHistogramH(const std::string& strName,int numAttr,int numSeries);
};
class VBF_HUDAUX_EXPORT CVBF_ChartHistogramV: public CVBF_ChartHistogram
{
public:
    CVBF_ChartHistogramV(const std::string& strName,int numAttr,int numSeries);
};
#endif 
