#ifndef __IVBF_3DSKY_H__
#define __IVBF_3DSKY_H__

#include <Types/Vec3d>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h>

// 定义该组件的ID号
const char VBF_COMPONENT_3DSKY[]	= "Component: 3DSky";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DSKY[]	= "三维天空";

namespace osg
{
    class IVBF_ViewBrief;
}

class IVBF_3DSky
{
public:	
	virtual ~IVBF_3DSky() {}

    // 设置/获取是否开启三维天空
    virtual void Enable(bool bEnable)=0;
    virtual bool IsEnabled()=0;

    virtual void AdjustAmbience()=0;

    // 设置/获取天空的时间
    virtual bool SetDateTime( int year, int month, int date, double hoursUTC)=0;
    virtual bool GetDateTime( int &year, int &month, int &date, double &hoursUTC)=0;

    // 设置/获取没有阳光照射的区域的最小亮度
    virtual void  SetAmbientBrightness(float value, osg::IVBF_ViewBrief* pIView=0L)=0;
    virtual float GetAmbientBrightness(osg::IVBF_ViewBrief* pIView=0L) const =0;

    // 设置/获取是否根据视点自动计算环境光（默认值为true）
    virtual void SetAutoAmbience(bool value)=0;
    virtual bool GetAutoAmbience() const=0;

    // 根据公历时间，计算太阳在地固系下的世界坐标，如果计算失败，返回false
    virtual bool CalSunPosECF(osg::Vec3d& vSunPos)=0;

    // 设置/获取太阳是否可见
    virtual void setSunVisible( bool value, osg::IVBF_ViewBrief* view =0L )=0;
    virtual bool getSunVisible( osg::IVBF_ViewBrief* view =0L ) const=0;

    // 设置/获取月亮是否可见
    virtual void setMoonVisible( bool value, osg::IVBF_ViewBrief* view =0L )=0;
    virtual bool getMoonVisible( osg::IVBF_ViewBrief* view =0L ) const=0;

    // 设置/获取星星是否可见
    virtual void setStarsVisible( bool value, osg::IVBF_ViewBrief* view =0L )=0;
    virtual  bool getStarsVisible( osg::IVBF_ViewBrief* view =0L ) const=0;



    // 设置/获取地球光影是否可见（默认值为false）
    virtual void SetLightVisible(bool bVisible)=0;
    virtual bool IsLightVisible()=0;

    // 返回各个节点
    virtual osg::IVBF_SGNode* GetSun()=0;
    virtual osg::IVBF_SGNode* GetMoon()=0;
    virtual osg::IVBF_SGNode* GetStars()=0;
    virtual osg::IVBF_SGNode* GetAtmosphere()=0;
};

#endif 
