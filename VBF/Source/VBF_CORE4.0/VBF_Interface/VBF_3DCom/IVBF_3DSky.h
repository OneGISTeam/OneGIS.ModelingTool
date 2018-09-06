#ifndef __IVBF_3DSKY_H__
#define __IVBF_3DSKY_H__

#include <Types/Vec3d>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h>

// ����������ID��
const char VBF_COMPONENT_3DSKY[]	= "Component: 3DSky";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DSKY[]	= "��ά���";

namespace osg
{
    class IVBF_ViewBrief;
}

class IVBF_3DSky
{
public:	
	virtual ~IVBF_3DSky() {}

    // ����/��ȡ�Ƿ�����ά���
    virtual void Enable(bool bEnable)=0;
    virtual bool IsEnabled()=0;

    virtual void AdjustAmbience()=0;

    // ����/��ȡ��յ�ʱ��
    virtual bool SetDateTime( int year, int month, int date, double hoursUTC)=0;
    virtual bool GetDateTime( int &year, int &month, int &date, double &hoursUTC)=0;

    // ����/��ȡû������������������С����
    virtual void  SetAmbientBrightness(float value, osg::IVBF_ViewBrief* pIView=0L)=0;
    virtual float GetAmbientBrightness(osg::IVBF_ViewBrief* pIView=0L) const =0;

    // ����/��ȡ�Ƿ�����ӵ��Զ����㻷���⣨Ĭ��ֵΪtrue��
    virtual void SetAutoAmbience(bool value)=0;
    virtual bool GetAutoAmbience() const=0;

    // ���ݹ���ʱ�䣬����̫���ڵع�ϵ�µ��������꣬�������ʧ�ܣ�����false
    virtual bool CalSunPosECF(osg::Vec3d& vSunPos)=0;

    // ����/��ȡ̫���Ƿ�ɼ�
    virtual void setSunVisible( bool value, osg::IVBF_ViewBrief* view =0L )=0;
    virtual bool getSunVisible( osg::IVBF_ViewBrief* view =0L ) const=0;

    // ����/��ȡ�����Ƿ�ɼ�
    virtual void setMoonVisible( bool value, osg::IVBF_ViewBrief* view =0L )=0;
    virtual bool getMoonVisible( osg::IVBF_ViewBrief* view =0L ) const=0;

    // ����/��ȡ�����Ƿ�ɼ�
    virtual void setStarsVisible( bool value, osg::IVBF_ViewBrief* view =0L )=0;
    virtual  bool getStarsVisible( osg::IVBF_ViewBrief* view =0L ) const=0;



    // ����/��ȡ�����Ӱ�Ƿ�ɼ���Ĭ��ֵΪfalse��
    virtual void SetLightVisible(bool bVisible)=0;
    virtual bool IsLightVisible()=0;

    // ���ظ����ڵ�
    virtual osg::IVBF_SGNode* GetSun()=0;
    virtual osg::IVBF_SGNode* GetMoon()=0;
    virtual osg::IVBF_SGNode* GetStars()=0;
    virtual osg::IVBF_SGNode* GetAtmosphere()=0;
};

#endif 
