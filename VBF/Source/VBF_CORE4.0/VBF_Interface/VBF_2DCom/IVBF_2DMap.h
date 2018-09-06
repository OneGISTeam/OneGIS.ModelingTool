#ifndef __IVBF_2DMAP_H__
#define __IVBF_2DMAP_H__

#include <string>

// 二维地图接口
class IVBF_2DMap : public CVBF_Referenced
{
protected:
    ~IVBF_2DMap(){}
public:
    virtual void Locate(double dScale,double dL,double dB)=0;
    virtual std::string GetName()=0;

};

#endif
