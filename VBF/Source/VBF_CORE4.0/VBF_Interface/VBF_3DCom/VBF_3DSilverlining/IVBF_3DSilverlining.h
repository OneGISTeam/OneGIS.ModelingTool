//***************************************************************************************
// FileName： VBF_3DMotion.h
// Function： yun
// Author:    w00024
// Date:      2016-05-28
//***************************************************************************************

#ifndef __IVBF_3DSILVERLINING_H__
#define __IVBF_3DSILVERLINING_H__

// 定义该组件的ID号
const char VBF_COMPONENT_3DSILVERLINING[]				= "Component: 3DSilverlining";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DSILVERLINING[]	= "天气效果";

class IVBF_3DSilverlining
{
public:
    virtual ~IVBF_3DSilverlining() {}

public:
    virtual void Enable(bool bEnable) = 0;
    virtual bool IsEnable() = 0;

    //风速
    virtual void SetWindSpeed(double metersPerSecond) = 0;
    virtual double GetWindSpeed() = 0;

    //风向
    virtual void SetWindDirection(double degreesFromNorth) = 0;
    virtual double GetWindDirection() = 0;

    //设置云类型
    virtual void SetCloudType(int nCloudType) = 0;
    virtual int  GetCloudType() = 0;

    //云层密度
    virtual void SetCloudsDensity(double dDensity) = 0;
    virtual double GetCloudsDensity() = 0;
};

#endif
