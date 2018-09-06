//*******************************************************************
// FileName��IVBF_MarkAttrIFF.h
// Function��ģ�����ԣ�ģ�͵ĵ���ʶ�� ("�ҷ�"��"�з�"��"�ѷ�")
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_IFF_H__
#define __IVBF_MARK_ATTR_IFF_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <string>
#include <VBF_Plot/IVBF_MarkStyleManager.h>

// ���ұ�ʶ����
class IVBF_MarkAttrIFF : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrIFF() {}

	// ����/��ȡģ�͵ĵ���ʶ������	
	virtual void        SetIFFName(const std::string& strName)=0;
	virtual std::string GetIFFName()=0;

	// ��ȡģ�͵ĵ���ʶ����ʽ
	virtual bool   GetIFFStyle(VBF_MARKIFFSTYLE& style)=0;
};

#endif 
