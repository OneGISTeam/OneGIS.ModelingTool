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
    * @note ��Ч��ʼ��
    * @param intensity [in] ���ڳ�ʼ�����Ũ�ȡ�
    */
    virtual void rain(float intensity) = 0;

    /**
    * @note ѩЧ��ʼ��
    * @param intensity [in] ���ڳ�ʼ��ѩ��Ũ�ȡ�
    */
    virtual void snow(float intensity) = 0;

    // ��ȡ��ѩ�ĵ�ǰŨ��
    virtual float GetDensity()=0;

    /**
    * @note ����������λ�õľ�γ���Լ���������İ뾶
    * @param pos [in] λ����Ϣ���ֱ�����ȡ�γ�ȡ��뾶 ��
    * @param isLocal [in] �Ƿ�Ϊ������ѩ�������������Ĭ���ǡ�
    */
    virtual void setPosition(const osg::Vec3& pos) = 0;

    ///�������������ĸ߶ȼ��Ƶĸ߶�
    virtual void SetWeatherHeight(float height) = 0;

    ///�����Ƿ�Ϊȫ����ѩ
    virtual void SetWorld(bool isWorld) = 0;

    virtual void Locate(double duration_s = 1.0 ) = 0;
};

#endif 
