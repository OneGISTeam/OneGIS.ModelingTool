//**********************************************************************************
// 文件名：  VBF_ValueToColor.h
// 描述：    数值到颜色的映射
// 作者:
// 日期:     2015-12-18
//**********************************************************************************

#ifndef __VBF_VALUE_TO_COLOR_H__
#define __VBF_VALUE_TO_COLOR_H__



#include <VBF_Common/VBF_Math/VBF_Export.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <Types/Vec4f>

#include <string>

class IVBF_ValueToColor
{
public:
    virtual osg::Vec4f& GetColor(float fValue)=0;

};

// 彩虹状映射方式
class CVBF_ValueToColorWind : public IVBF_ValueToColor
{
public:
    CVBF_ValueToColorWind()
    {
        m_fAlpha = 0.4f;
    }
    virtual osg::Vec4f& GetColor(float fValue)
    {
        fValue/=50.0;

        float rad = fValue*2*3.1415926*5/6 * 0.75;

        float s = sin(rad);
        float c = cos(rad);

        m_color = osg::Vec4f(maxValue(0,-c),maxValue(s,0), maxValue(maxValue(c,0),-s),m_fAlpha);

        return m_color;
    }
    float maxValue(float a,float b) { return a<b?b:a; }

private:
    float m_fAlpha;
    osg::Vec4f m_color;

};

// 颜色为最近采样
class CVBF_ValueToColorNearest: public IVBF_ValueToColor
{
public:
    CVBF_ValueToColorNearest()
    {
        m_dMinValue = 0;
        m_dMaxValue = 0;
        m_colorDefault = osg::Vec4f(1.0,1.0,1.0,0);
    }
    virtual void SetMinMaxValue(double dMinValue,double dMaxValue)
    {
        m_dMinValue = dMinValue;
        m_dMaxValue = dMaxValue;
    }
    std::vector<osg::Vec4f>& GetColorTable() { return m_vColors; }
protected:
    double m_dMinValue;
    double m_dMaxValue;
    std::vector<osg::Vec4f> m_vColors;
    osg::Vec4f m_colorDefault;
};

// 颜色为最近采样，值为线性插值
class CVBF_ValueToColorNearestLinear : public CVBF_ValueToColorNearest
{
public:
    virtual osg::Vec4f& GetColor(float fValue)
    {
        int num = m_vColors.size();
        if(num<2) return m_colorDefault;

        double dScale = (fValue - m_dMinValue) / (m_dMaxValue-m_dMinValue); // 计算分割比例
        int idx = std::max(0.0,std::min(dScale,1.0)) * (num-1);

        return m_vColors[idx];
    }
};
// 颜色为最近采样，值为LOG10
class CVBF_ValueToColorNearestLog10 : public CVBF_ValueToColorNearest
{
public:
    virtual osg::Vec4f& GetColor(float fValue)
    {
        int num = m_vColors.size();
        if(num<1) return m_colorDefault;

        if(fValue<1) fValue = 1;// 对数的特殊性要求

        int idx = log10(fValue)/log10(m_dMaxValue)*(num-1);

        return m_vColors[idx];
    }

};



class CVBF_ValueToColorPiecewiseLinear : public IVBF_ValueToColor // 分段线性差值（值与颜色都是分段线性插值）
{
public:
    CVBF_ValueToColorPiecewiseLinear()
    {
        m_colorDefault = osg::Vec4f(1.0,1.0,1.0,0);
    }
    virtual osg::Vec4f& GetColor(float fValue)
    {
         int num =this->m_vValue.size();
         if(num<2) return m_colorDefault;

         if(fabs(fValue)<0.0001)return m_colorDefault;


        int i=0;
        for(i;i<num-1;i++)
        {
            if(fValue<=m_vValue[i]) break;
        }

        double dScale = (fValue - m_vValue[i-1]) / (m_vValue[i]-m_vValue[i-1]); // 计算分割比例
        dScale = std::max(0.0,std::min(dScale,1.0));

        return ColorInterpolators(dScale,m_vColor[i-1],m_vColor[i]);

    }

    osg::Vec4f& ColorInterpolators(double dScale,const osg::Vec4f& vS,const osg::Vec4f& vE)
    {
        m_color = osg::Vec4f( vS.x() + dScale* ( vE.x() - vS.x()),
                              vS.y() + dScale* ( vE.y() - vS.y()),
                              vS.z() + dScale* ( vE.z() - vS.z()),155.0/255);
        return m_color;
    }
protected:
    std::vector<double> m_vValue;
    std::vector<osg::Vec4f> m_vColor;
    osg::Vec4f m_color;
    osg::Vec4f m_colorDefault;
};
class CVBF_ValueToColorOceanCurrent : public CVBF_ValueToColorPiecewiseLinear
{
public:
    CVBF_ValueToColorOceanCurrent()
    {
        m_vValue.push_back(0);
        m_vValue.push_back(0.15);
        m_vValue.push_back(0.4);
        m_vValue.push_back(0.65);
        m_vValue.push_back(1.0);
        m_vValue.push_back(1.5);

        m_vColor.push_back(osg::Vec4f( 10/255.0,  25/255.0,  68/255.0, 155/255.0));
        m_vColor.push_back(osg::Vec4f( 10/255.0,  25/255.0, 250/255.0, 155/255.0));
        m_vColor.push_back(osg::Vec4f( 24/255.0, 255/255.0,  93/255.0, 155/255.0));
        m_vColor.push_back(osg::Vec4f(255/255.0, 233/255.0, 102/255.0, 155/255.0));
        m_vColor.push_back(osg::Vec4f(255/255.0, 233/255.0,  15/255.0, 155/255.0));
        m_vColor.push_back(osg::Vec4f(255/255.0,  15/255.0,  15/255.0, 155/255.0));
    }

};

class CVBF_ValueToColorOceanTraffic : public CVBF_ValueToColorPiecewiseLinear
{
public:
    CVBF_ValueToColorOceanTraffic()
    {
        m_vColor.push_back(osg::Vec4f(10/255.0,25/255.0,68/255.0,155/255.0));
        m_vColor.push_back(osg::Vec4f(10/255.0,25/255.0,250/255.0,155/255.0));
 //       vec_color.push_back(osg::Vec4f(255,233,102,155));
        m_vColor.push_back(osg::Vec4f(128/255.0,15/255.0,15/255.0,155/255.0));
        m_vColor.push_back(osg::Vec4f(255/255.0,0,0,155/255.0));
    }
    // 设置数据的最小值、最大值、标准差
    virtual void SetStandardDeviation(double dMinValue,double dMaxValue,double dMean,double dStandardDeviation)
    {
        m_vValue.clear();

        m_vValue.push_back(dMinValue);
//        m_vValue.push_back(dMean-dStandardDeviation);
        m_vValue.push_back(dMean);
        m_vValue.push_back(dMean+dStandardDeviation);
        m_vValue.push_back(dMaxValue);

    }
};


/*
class VBF_MATH_EXPORT CVBF_ValueToColor
{
public:
};
*/
#endif
