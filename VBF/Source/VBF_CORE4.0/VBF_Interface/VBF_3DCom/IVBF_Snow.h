#ifndef __IVBF_SNOW_H__
#define __IVBF_SNOW_H__

#include <VBF_Base/VBF_Referenced.h>

class IVBF_Snow : public CVBF_Referenced
{
public:	
    virtual ~IVBF_Snow() {}

   virtual void Enable(bool bEnable)=0;
   virtual bool IsEnabled()=0;
   virtual void SetIntensity(float fIntensity)=0;
};

#endif 
