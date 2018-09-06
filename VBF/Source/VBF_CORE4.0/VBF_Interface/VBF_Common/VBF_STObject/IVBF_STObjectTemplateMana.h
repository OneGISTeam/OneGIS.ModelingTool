//*******************************************************************
// FileName：  IVBF_STObjectTemplateMana.h
// Function：  对象模板管理
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __IVBF_ST_OBJECT_TEMPLATE_MANAGER_H__
#define __IVBF_ST_OBJECT_TEMPLATE_MANAGER_H__

#include <string>
#include <vector>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Common/VBF_STObject/VBF_Export.h>
class CVBF_STObject;
class IVBF_STObjectTemplateMana:public CVBF_Referenced
{
public:
    virtual void FilledSTObjectByTemplate(CVBF_STObject* pObject,std::string& sTemplateID)=0;
    virtual std::vector<std::string> GetTemplateIDs()=0;
};
VBF_STOBJECT_EXPORT IVBF_STObjectTemplateMana* VBF_GetSTObjectTemplateMana();

#endif
