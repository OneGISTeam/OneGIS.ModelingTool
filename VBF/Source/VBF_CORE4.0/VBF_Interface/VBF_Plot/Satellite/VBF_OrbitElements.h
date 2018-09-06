#ifndef __VBF_ORBIT_ELEMENTS_H__
#define __VBF_ORBIT_ELEMENTS_H__

#include <string>
#include <VBF_Common/VBF_Utils/VBF_XmlUtils.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
//----------------------------------------------------------------
// ����ṹ�壺VBF_ORBIT_ELEMENTS
// �ṹ�����������ǹ������
//----------------------------------------------------------------
typedef struct _tagVBFOrbitElements
{
    std::string		strNoradNo;	// �����������

    // �������״����
    double			da;			// �볤�ᣨ�������״��������λ�����
    double			de;			// ƫ���ʣ��������״������

    // �����λ�ò���
    double			dIncl;		// �����ǣ����������Ķ���ǣ���λ���Ƕȣ�
    double			dRAAN;		// ������ྭ�����ֵ㡢���ġ������������ڵ��Ĺ��ɵļнǣ���λ���Ƕȣ�
    double			dw;			// ���ص���ǣ�������ص㡢���ġ������������ڵ��Ĺ��ɵļнǣ���λ���Ƕȣ�

    // �����ڹ���ϵ�λ��
    double			dTA;		// �����ص�ʱ�̣������գ���λ���죩

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
    // ��ȡ�����������
    confOrbit.getIfSet("NoradNo",	orbit.strNoradNo);
    confOrbit.getIfSet("da",		orbit.da);
    confOrbit.getIfSet("de",		orbit.de);
    confOrbit.getIfSet("dIncl",		orbit.dIncl);
    confOrbit.getIfSet("dRAAN",		orbit.dRAAN);
    confOrbit.getIfSet("dw",		orbit.dw);
    confOrbit.getIfSet("dTA",		orbit.dTA);
}

#endif
