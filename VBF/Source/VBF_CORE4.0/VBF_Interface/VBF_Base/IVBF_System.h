#ifndef VBF_SYSTEM_H
#define VBF_SYSTEM_H 1

#include <VBF_Base/VBF_BaseExport.h>
#include <string>

class IVBF_System
{
protected:
    virtual ~IVBF_System() {}
public:
    virtual std::string GetSyssetPath()=0;
    virtual std::string GetApplicationPath()=0;
    virtual std::string GetDataPath()=0;

    virtual void SetSyssetPath(std::string& sPath)=0;
    virtual void SetApplicationPath(std::string& sPath)=0;
    virtual void SetDataPath(std::string& sPath)=0;
    virtual void SetData(std::string sKey,void* ptr)=0;
    virtual void* GetData(std::string sKey)=0;
};
VBF_BASE_EXPORT IVBF_System* VBF_GetSystem();

#endif
