//***************************************************************************************
// FileName�� VBF_3DWeather.h
// Function�� ��ά�����е�����ӿڣ������ꡢѩ�����
// Author:    ��Ө
// Date:      2015-04-14
//***************************************************************************************

#ifndef __IVBF_3DWEATHER_H__
#define __IVBF_3DWEATHER_H__


//#include <VBF_3DCom/IVBF_Snow.h>
#include <VBF_3DCom/IVBF_Rain_Snow.h>
#include <VBF_3DCom/IVBF_Fog.h>


// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DWEATHER[]	= "��ά����";

// ��������ID��
const char VBF_COMMAND_SHOWDIALOG_WEATHER[] = "Command: Show Dialog Weather";     // ��ʾ�Ի��򣺵����������


class IVBF_3DWeather
{
public:	
    virtual ~IVBF_3DWeather() {}

    virtual IVBF_Rain_Snow* GetRain()=0;     // ��ȡ�ӿڣ���
    virtual IVBF_Rain_Snow* GetSnow()=0;     // ��ȡ�ӿڣ�ѩ
    virtual IVBF_Fog*  GetFog()=0;      // ��ȡ�ӿڣ���
};

#endif 
