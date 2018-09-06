#ifndef __IVBF_SPACE_BASE_H__
#define __IVBF_SPACE_BASE_H__
namespace Space
{
    enum
    {
        Mercury = 0,// ˮ��
        Venus = 1,  // ����
        Earth = 2,  // ����
        Mars = 3,   // ����
        Jupiter = 4,// ľ��
        Saturn = 5, // ����
        Uranus = 6, // ������
        Neptune = 7,// ������
        Pluto = 8,  // ڤ����
        Moon = 9,   // ����
        Sun = 10    // ̫��
    };
}

#include <VBF_Base/VBF_Referenced.h>
class IVBF_SpaceOption:public CVBF_Referenced
{
public:
    // ����/��ȡ����ϵ�Ƿ�ɼ�
    virtual bool getMilkywayVisible() const=0;
    virtual void setMilkywayVisible(bool v)=0;

    // ����/��ȡ���������Ƿ�ɼ�
    virtual bool getPlanetNamesVisible() const=0;
    virtual void setPlanetNamesVisible(bool v)=0;

    // ����/��ȡ���������Ƿ�ɼ�
    virtual bool getStarNamesVisible() const=0;
    virtual void setStarNamesVisible(bool v)=0;

    // ����/��ȡ����/���������Ƿ�ɼ�
    virtual bool getConstellationNamesVisible() const=0;
    virtual void setConstellationNamesVisible(bool v)=0;
    virtual bool getConstellationLinesVisible() const=0;
    virtual void setConstellationLinesVisible(bool v)=0;

    // ����/��ȡ�����Ƿ�ɼ�
    virtual bool getBoundariesVisible() const=0;
    virtual void setBoundariesVisible(bool v)=0;

    // ����/��ȡ�����Ƿ�ɼ�
    virtual bool getEquatorVisible() const=0;
    virtual void setEquatorVisible(bool v)=0;

    // ����/��ȡ���ǹ��
    virtual bool getPlanetOrbitVisible() const=0;
    virtual void setPlanetOrbitVisible(bool v)=0;

    // ����/��ȡ���������Ƿ�ɼ�
    virtual bool getCelestialSphereVisible() const=0;
    virtual void setCelestialSphereVisible(bool v)=0;

};

#endif 
