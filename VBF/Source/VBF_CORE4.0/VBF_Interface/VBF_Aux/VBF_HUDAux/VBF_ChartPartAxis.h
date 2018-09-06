#ifndef __VBF_CHART_PART_AXIS_H__
#define __VBF_CHART_PART_AXIS_H__

#include <VBF_Aux/VBF_HUDAux/VBF_Chart.h>


// ͼ������������
#include <VBF_Engine/VBF_Text/Text>
class VBF_HUDAUX_EXPORT CVBF_ChartAxis
{
public:
    CVBF_ChartAxis();
    void SetVisible(bool bVisible) { m_bVisible = bVisible;}
    void SetPos(const osg::Vec2f& pt)    { m_pt = pt;                   m_bDirty = true;}

    void SetLength(float fAxisLen);
    float GetLength(){ return m_dLength; }

    void SetLabelRotateAngle(int nAngle) { m_nLabelRotateAngle = nAngle;m_bDirty = true;}
    void SetOrignPointLB(bool bLB)       { m_bOrignPointLB = bLB;       m_bDirty = true; }// ԭ���Ƿ������·�λ��Ӱ��ע�ǵ�λ��


    // ��ȡ����ʽ��ע����ʽ
    VBF_TEXTSTYLE& GetTextStyle(){ return m_TextStyle; }
    VBF_LINESTYLE& GetLineStyle(){ return m_lsAxis; }

    virtual void Update();
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);
    void SetHorizontal(bool bHorizontal) { m_bHorizontal = bHorizontal; m_bDirty = true;}

protected:
    void UpdateVerts();

    bool m_bVisible;
    osg::Vec2f	m_pt;// ��λ����Ļ����

    ref_ptr<osg::Geometry>		m_ipDrawable;
    ref_ptr<osg::Vec3Array>		m_ipVertsAxis;		// ������Ķ���

    bool m_bHorizontal;
    bool m_bOrignPointLB;// ԭ���Ƿ������·�λ

    double m_dLength;
    int    m_nLabelRotateAngle; // ע�ǵ���ת�ǣ��ȣ�

    VBF_LINESTYLE  m_lsAxis;    // �������ʽ
    VBF_TEXTSTYLE  m_TextStyle;	// ע�ǵ��ı���ʽ

    bool m_bDirty;

};

class VBF_HUDAUX_EXPORT CVBF_ChartAxisAttr : public CVBF_ChartAxis
{
public:
    CVBF_ChartAxisAttr();

    void SetAttrsName(std::vector<std::string>& vAttrName);
    const std::vector<std::string>& GetAttrsName() {return m_vStringAttr; }

    void SetBarWidth(int nBarWidth,int nBarSpace);// ���ڼ���ע�ǵ�λ��
    void SetHeadSapce(float fSpace) { m_fHeadfSpace = fSpace; m_bDirty = true;}

    virtual void Update();
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);
private:
    std::vector<std::string> m_vStringAttr; //�����ı�
    std::vector< ref_ptr<osgText::Text> > m_vTextAxisAttr; // ������ע��
    int m_nBarWidth;
    int m_nBarSpace;
    float m_fHeadfSpace;

};
// ������
class VBF_HUDAUX_EXPORT CVBF_ChartAxisValue : public CVBF_ChartAxis
{
public:
    CVBF_ChartAxisValue();

    void SetMaxValue(double dMaxValue);// �������ֵ
    void SetTickMarkNum(int num);      // ���ÿ̶��ߵĸ���
    int  GetTickMarkNum() { return m_numTickMark; }
    double GetMaxValue() { return m_dMaxValue; }

    virtual void Update();
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true);

    float ValueToLength( float fValue)
    {
        return m_dLength* fValue/m_dMaxValue;
    }
private:
    std::vector< ref_ptr<osgText::Text> > m_vTextAxisData; // ������ע��

    int m_numTickMark;
    double m_dMaxValue;


};


#endif 
