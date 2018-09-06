//***************************************************************************************
// FileName： IVBF_Fog.h
// Function： 雾化效果接口
// Author:    杜莹
// Date:      2015-04-14
//***************************************************************************************

#ifndef __IVBF_FOG_H__
#define __IVBF_FOG_H__


#include <VBF_Base/VBF_Referenced.h>
#include <Types/Vec4f>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttribute.h>

class IVBF_Fog : public osg::StateSet::Callback
{
public:	
    virtual ~IVBF_Fog() {}

    // 设置/获取是否开启雾化效果（默认值为false）
    virtual void Enable(bool bEnable)=0;
    virtual bool IsEnabled()=0;

    // 设置/获取雾的颜色（默认值为(0.66f, 0.7f, 0.81f, 1.0f)）
    virtual void              SetColor(const osg::Vec4f& color)=0;
    virtual const osg::Vec4f& GetColor()=0;

    // 设置/获取雾化浓度
    virtual void  SetDensity(float fDensity)=0;
    virtual float GetDensity()=0;
};

#endif 
