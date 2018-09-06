#ifndef VBF_MANIPULATOR_COMMON_H
#define VBF_MANIPULATOR_COMMON_H

#include <VBF_3DMapAux/VBF_3DManipulator/VBF_3DManipulator_Global.h>
#include <string>

extern VBF_3DMANIPULATORSHARED_EXPORT float g_fFirstLockXDelta;
extern VBF_3DMANIPULATORSHARED_EXPORT float g_fFirstLockYDelta;

extern VBF_3DMANIPULATORSHARED_EXPORT std::string g_strFirstLockNode; // 第一人称时，锁定的节点名称。
extern VBF_3DMANIPULATORSHARED_EXPORT std::string g_strThirdLockNode; // 第三人称时，锁定的节点名称。

#endif // VBF_MANIPULATOR_COMMON_H

