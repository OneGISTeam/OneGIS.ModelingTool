//*******************************************************************
// FileName��IVBF_MarkAttrHintLine.h
// Function��ģ�����Խӿڣ��߶��ߣ�������ʾ�û�ģ�͵�ǰ��λ��
// Author:   ��Ө
// Date:     2013-12-05
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_HINTLINE_H__
#define __IVBF_MARK_ATTR_HINTLINE_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <Types/VBF_3DStyles.h>


class IVBF_MarkAttrHintLine : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrHintLine() {}

	// ����/��ȡ�߶��ߵ���ʽ
	virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;
};


#endif 
