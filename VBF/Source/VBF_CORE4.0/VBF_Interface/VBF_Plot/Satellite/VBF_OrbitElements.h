#ifndef __VBF_ORBIT_ELEMENTS_H__
#define __VBF_ORBIT_ELEMENTS_H__

#include <string>
#include <VBF_Common/VBF_Utils/VBF_XmlUtils.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
//----------------------------------------------------------------
// 定义结构体：VBF_ORBIT_ELEMENTS
// 结构体描述：卫星轨道根数
//----------------------------------------------------------------
typedef struct _tagVBFOrbitElements
{
    std::string		strNoradNo;	// 卫星星历编号

    // 轨道的形状参数
    double			da;			// 半长轴（轨道的形状参数，单位：公里）
    double			de;			// 偏心率（轨道的形状参数）

    // 轨道的位置参数
    double			dIncl;		// 轨道倾角（轨道与赤道面的二面角，单位：角度）
    double			dRAAN;		// 升交点赤经（春分点、地心、升交点三者在地心构成的夹角，单位：角度）
    double			dw;			// 近地点幅角（轨道近地点、地心、升交点三者在地心构成的夹角，单位：角度）

    // 卫星在轨道上的位置
    double			dTA;		// 过近地点时刻（儒略日，单位：天）

    _tagVBFOrbitElements()
    {
		strNoradNo	= "0000";
		da			= 6878.145;
		de			= 0.0;
		dIncl		= 40.0;
		dRAAN		= 0.0;
		dw			= 0.0;
		dTA			= 0.0;
    }

    _tagVBFOrbitElements& operator=(const _tagVBFOrbitElements& src)
    {
		if(this==&src) return *this;

		strNoradNo	= src.strNoradNo;
		da			= src.da;
		de			= src.de;
		dIncl		= src.dIncl;
		dRAAN		= src.dRAAN;
		dw			= src.dw;
		dTA			= src.dTA;

		return *this;
    }

} VBF_ORBIT_ELEMENTS;

inline void VBF_WriteToXML(TiXmlElement* pElem, const VBF_ORBIT_ELEMENTS& orbit)
{
    if(NULL==pElem) return;

    ::VBF_SetAttribute(pElem, "a",	orbit.da);
    ::VBF_SetAttribute(pElem, "e",	orbit.de);
    ::VBF_SetAttribute(pElem, "Incl",orbit.dIncl);
    ::VBF_SetAttribute(pElem, "RAAN",orbit.dRAAN);
    ::VBF_SetAttribute(pElem, "w",	orbit.dw);
    ::VBF_SetAttribute(pElem, "TA",	orbit.dTA);
}
inline void VBF_ReadFromXML(TiXmlElement* pElem, VBF_ORBIT_ELEMENTS& orbit)
{
    if(NULL==pElem) return;

    ::VBF_QueryAttribute(pElem, "a",	orbit.da);
    ::VBF_QueryAttribute(pElem, "e",	orbit.de);
    ::VBF_QueryAttribute(pElem, "Incl",orbit.dIncl);
    ::VBF_QueryAttribute(pElem, "RAAN",orbit.dRAAN);
    ::VBF_QueryAttribute(pElem, "w",	orbit.dw);
    ::VBF_QueryAttribute(pElem, "TA",	orbit.dTA);
}
inline void VBF_ReadFromJson(const CVBF_Config& confOrbit, VBF_ORBIT_ELEMENTS& orbit)
{
    // 读取：轨道六根数
    confOrbit.getIfSet("NoradNo",	orbit.strNoradNo);
    confOrbit.getIfSet("da",		orbit.da);
    confOrbit.getIfSet("de",		orbit.de);
    confOrbit.getIfSet("dIncl",		orbit.dIncl);
    confOrbit.getIfSet("dRAAN",		orbit.dRAAN);
    confOrbit.getIfSet("dw",		orbit.dw);
    confOrbit.getIfSet("dTA",		orbit.dTA);
}

#endif
