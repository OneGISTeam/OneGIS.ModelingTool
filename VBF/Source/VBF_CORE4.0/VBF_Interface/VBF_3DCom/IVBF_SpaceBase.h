#ifndef __IVBF_SPACE_BASE_H__
#define __IVBF_SPACE_BASE_H__
namespace Space
{
    enum
    {
        Mercury = 0,// 水星
        Venus = 1,  // 金星
        Earth = 2,  // 地球
        Mars = 3,   // 火星
        Jupiter = 4,// 木星
        Saturn = 5, // 土星
        Uranus = 6, // 天王星
        Neptune = 7,// 海王星
        Pluto = 8,  // 冥王星
        Moon = 9,   // 月球
        Sun = 10    // 太阳
    };
}

#include <VBF_Base/VBF_Referenced.h>
class IVBF_SpaceOption:public CVBF_Referenced
{
public:
    // 设置/获取银河系是否可见
    virtual bool getMilkywayVisible() const=0;
    virtual void setMilkywayVisible(bool v)=0;

    // 设置/获取行星名称是否可见
    virtual bool getPlanetNamesVisible() const=0;
    virtual void setPlanetNamesVisible(bool v)=0;

    // 设置/获取恒星名称是否可见
    virtual bool getStarNamesVisible() const=0;
    virtual void setStarNamesVisible(bool v)=0;

    // 设置/获取星座/星座名称是否可见
    virtual bool getConstellationNamesVisible() const=0;
    virtual void setConstellationNamesVisible(bool v)=0;
    virtual bool getConstellationLinesVisible() const=0;
    virtual void setConstellationLinesVisible(bool v)=0;

    // 设置/获取天区是否可见
    virtual bool getBoundariesVisible() const=0;
    virtual void setBoundariesVisible(bool v)=0;

    // 设置/获取天赤道是否可见
    virtual bool getEquatorVisible() const=0;
    virtual void setEquatorVisible(bool v)=0;

    // 设置/获取行星轨道
    virtual bool getPlanetOrbitVisible() const=0;
    virtual void setPlanetOrbitVisible(bool v)=0;

    // 设置/获取天球网格是否可见
    virtual bool getCelestialSphereVisible() const=0;
    virtual void setCelestialSphereVisible(bool v)=0;

};

#endif 
