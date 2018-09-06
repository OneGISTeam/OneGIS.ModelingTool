//*******************************************************************
// FileName��VBF_TrailInfo.h
// Function���뺽����Ϣ�йصĹ�����������
// Author:   ��Ө
// Date:     2016-11-09
//*******************************************************************

#ifndef __VBF_TRAIL_INFO_INFO_H__
#define __VBF_TRAIL_INFO_INFO_H__


#include <VBF_OS.h>
#include <Types/Vec3d>
#include <string>
#include <vector>


//--------------------------------------------------------
// ����ṹ�壺VBF_TRAIL_POINTINFO
// �ṹ����������������Ϣ
//--------------------------------------------------------
struct VBF_TRAIL_POINTINFO
{
    osg::Vec3d  ptGeo;      // ��������
    double      dSpeed;     // �Ե��ٶ�
    long        nUTC;       // UTCʱ�䣨��λ���룩

    VBF_TRAIL_POINTINFO()
    {
        ptGeo   = osg::Vec3d(0.0, 0.0, 0.0);
        dSpeed  = 0.0;
        nUTC    = 0;
    }

    // �������캯��
    VBF_TRAIL_POINTINFO& operator=(const VBF_TRAIL_POINTINFO& src)
    {
        if(this==&src) return *this;

        ptGeo   = src.ptGeo;
        dSpeed  = src.dSpeed;
        nUTC    = src.nUTC;

        return *this;
    }
};


//--------------------------------------------------------
// ����ṹ�壺VBF_TRAIL_INFO
// �ṹ��������������Ϣ
//--------------------------------------------------------
struct VBF_TRAIL_INFO
{
    int                              nCode;      // ������Ψһ����
    std::vector<VBF_TRAIL_POINTINFO> vPoints;    // �����ϵ����е�

    VBF_TRAIL_INFO()
    {
        nCode  = -1;
    }

    // �������캯��
    VBF_TRAIL_INFO& operator=(const VBF_TRAIL_INFO& src)
    {
        if(this==&src) return *this;

        nCode = src.nCode;
        if(src.vPoints.size()>0)
        {
            vPoints.clear();
            vPoints.assign(src.vPoints.begin(), src.vPoints.end());
        }

        return *this;
    }
};


typedef std::vector<std::string>   CVBF_UserValueVector;


//-------------------------------------------------------------------------------
// ����ṹ�壺VBF_TRAIL_EXTINFO
// �ṹ����������������չ��Ϣ����Ҫ���ⲿģ�����󣨱�����ϵͳ�ڲ��洢��ռ���ڴ棬����Ϣͨ������չʾ��Ϣ���ݣ�
//-------------------------------------------------------------------------------
struct VBF_TRAIL_EXTINFO
{
public:
    int                                 nCode;              // Ψһ���루��ϵͳ�ڲ��ṩ��
    CVBF_UserValueVector                vValuesStatic;      // ��̬��չ��Ϣ����Ҫ�ⲿģ�鸳ֵ��
    std::vector<CVBF_UserValueVector>   vValuesDynamic;     // ��̬��չ��Ϣ����ÿ�����������չ��Ϣ����Ҫ�ⲿģ�鸳ֵ��

    // �������캯��
    VBF_TRAIL_EXTINFO& operator=(const VBF_TRAIL_EXTINFO& src)
    {
        if(this==&src) return *this;

        nCode         = src.nCode;
        vValuesStatic = src.vValuesStatic;

        vValuesDynamic.clear();
        for(int i=0; i<src.vValuesDynamic.size(); i++)
        {
            vValuesDynamic.push_back( src.vValuesDynamic[i] );
        }

        return *this;
    }

    // �������
    void Clear()
    {
        vValuesStatic.clear();
        vValuesDynamic.clear();
    }
};


#endif
