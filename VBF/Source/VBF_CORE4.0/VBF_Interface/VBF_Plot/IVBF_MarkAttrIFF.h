//*******************************************************************
// FileName：IVBF_MarkAttrIFF.h
// Function：模型属性：模型的敌我识别 ("我方"、"敌方"、"友方")
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_IFF_H__
#define __IVBF_MARK_ATTR_IFF_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <string>
#include <VBF_Plot/IVBF_MarkStyleManager.h>

// 敌我标识属性
class IVBF_MarkAttrIFF : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrIFF() {}

	// 设置/获取模型的敌我识别名称	
	virtual void        SetIFFName(const std::string& strName)=0;
	virtual std::string GetIFFName()=0;

	// 获取模型的敌我识别样式
	virtual bool   GetIFFStyle(VBF_MARKIFFSTYLE& style)=0;
};

#endif 
