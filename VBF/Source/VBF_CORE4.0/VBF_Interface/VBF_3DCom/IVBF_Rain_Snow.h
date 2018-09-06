#ifndef __IVBF_RAIN_SNOW_H__
#define __IVBF_RAIN_SNOW_H__

//#include <VBF_Base/VBF_Referenced.h>
#include <Types/Vec3>

class IVBF_Rain_Snow //: public CVBF_Referenced
{
public:	
    virtual ~IVBF_Rain_Snow() {}

//    virtual void Enable(bool bEnable)=0;
//    virtual bool IsEnabled()=0;
//    virtual void SetIntensity(float fIntensity)=0;
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual bool IsHide() const = 0;

    /**
    * @note 雨效初始化
    * @param intensity [in] 用于初始化雨的浓度。
    */
    virtual void rain(float intensity) = 0;

    /**
    * @note 雪效初始化
    * @param intensity [in] 用于初始化雪的浓度。
    */
    virtual void snow(float intensity) = 0;

    // 获取雨雪的当前浓度
    virtual float GetDensity()=0;

    /**
    * @note 设置天气的位置的经纬度以及天气区域的半径
    * @param pos [in] 位置信息，分别代表经度、纬度、半径 。
    * @param isLocal [in] 是否为区域雨雪，如果不设置则默认是。
    */
    virtual void setPosition(const osg::Vec3& pos) = 0;

    ///设置天气产生的高度即云的高度
    virtual void SetWeatherHeight(float height) = 0;

    ///设置是否为全局雨雪
    virtual void SetWorld(bool isWorld) = 0;

    virtual void Locate(double duration_s = 1.0 ) = 0;
};

#endif 
