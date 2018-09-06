//*******************************************************************
// FileName：VBF_GraphicsFactory.h
// Function：
// Author:
// Date:
//*******************************************************************

#ifndef __VBF_GRAPHICS_FACTORY_H__
#define __VBF_GRAPHICS_FACTORY_H__

#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Base/VBF_Referenced.h>
#include "VBF_Common/VBF_XML/tinyxml.h"

class IVBF_GraphicsFactory: public CVBF_Referenced
{
protected:
    ~IVBF_GraphicsFactory(){}
    virtual bool FromXML(TiXmlElement* pElem)=0;   // 读取(1个？多个？)


};
VBF_HUDAUX_EXPORT IVBF_GraphicsFactory* VBF_GetGraphicsFactory();


//=============================================================================
// 定义类：CVBF_Graphics
// 类描述：所有2D图形的基类
//=============================================================================
class VBF_HUDAUX_EXPORT CVBF_GraphicsFactory : public IVBF_GraphicsFactory
{
public:
    CVBF_GraphicsFactory();
    virtual ~CVBF_GraphicsFactory();
    static CVBF_GraphicsFactory* instance();
    virtual bool FromXML(TiXmlElement* pElem);
};



#endif
