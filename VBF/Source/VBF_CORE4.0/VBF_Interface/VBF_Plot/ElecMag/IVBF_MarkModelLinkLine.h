//*******************************************************************
// FileName��IVBF_MarkModelLinkLine.h
// Function��ʵ��ģ�ͽӿڣ���ͨ�ߣ�����ά�ռ��ֱ��ʵ�֣�
// Author:   ��Ө
// Date:     2013-11-13
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_LINK_LINE_H__
#define __IVBF_MARK_MODEL_LINK_LINE_H__


#include <VBF_Plot/ElecMag/IVBF_MarkModelLink.h>
#include <VBF_Common/VBF_Math/VBF_Math.h>


class IVBF_MarkModelLinkLine : public IVBF_MarkModelLink
{
public:
	virtual ~IVBF_MarkModelLinkLine() {}	

	// ����/��ȡ��ͨ�ߵ��߶���ʽ
	virtual void				 SetLineStyle(bool bForLink, const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetLineStyle(bool bForLink)=0;
};

#endif 
