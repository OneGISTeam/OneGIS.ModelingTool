//*******************************************************************
// FileName：  IVBF_STObjectDisplayModel.h
// Function：  多粒度时空对象的显示模型接口基类
// Author:     
// Date:       2018-02-26
//*******************************************************************

#ifndef __IVBF_ST_OBJECT_DISPLAY_MODEL_H__
#define __IVBF_ST_OBJECT_DISPLAY_MODEL_H__

#include <VBF_Base/VBF_Referenced.h>

class IVBF_STObjectDisplayModel : public virtual CVBF_Referenced
{
public:
    virtual void Update(){}
};

#endif
