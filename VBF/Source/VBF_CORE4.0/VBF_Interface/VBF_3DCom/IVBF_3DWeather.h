//***************************************************************************************
// FileName： VBF_3DWeather.h
// Function： 三维环境中的气象接口，包括雨、雪、雾等
// Author:    杜莹
// Date:      2015-04-14
//***************************************************************************************

#ifndef __IVBF_3DWEATHER_H__
#define __IVBF_3DWEATHER_H__


//#include <VBF_3DCom/IVBF_Snow.h>
#include <VBF_3DCom/IVBF_Rain_Snow.h>
#include <VBF_3DCom/IVBF_Fog.h>


// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DWEATHER[]	= "三维气象";

// 定义命令ID号
const char VBF_COMMAND_SHOWDIALOG_WEATHER[] = "Command: Show Dialog Weather";     // 显示对话框：调整气象参数


class IVBF_3DWeather
{
public:	
    virtual ~IVBF_3DWeather() {}

    virtual IVBF_Rain_Snow* GetRain()=0;     // 获取接口：雨
    virtual IVBF_Rain_Snow* GetSnow()=0;     // 获取接口：雪
    virtual IVBF_Fog*  GetFog()=0;      // 获取接口：雾
};

#endif 
