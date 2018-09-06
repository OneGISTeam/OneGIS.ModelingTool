#ifndef HG_MANIPULATOR_COMMON_H
#define HG_MANIPULATOR_COMMON_H

#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <string>

namespace FeKit
{
    extern VBF_MAPAUX_EXPORT float g_fFirstLockXDelta;
    extern VBF_MAPAUX_EXPORT float g_fFirstLockYDelta;

    extern VBF_MAPAUX_EXPORT std::string g_strFirstLockNode; // ��һ�˳�ʱ�������Ľڵ����ơ�
    extern VBF_MAPAUX_EXPORT std::string g_strThirdLockNode; // �����˳�ʱ�������Ľڵ����ơ�
}

#endif // HG_MANIPULATOR_COMMON_H

