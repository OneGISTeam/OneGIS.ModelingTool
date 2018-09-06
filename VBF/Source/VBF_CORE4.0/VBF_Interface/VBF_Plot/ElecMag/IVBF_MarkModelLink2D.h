//*******************************************************************
// FileName��IVBF_MarkModelLink2D.h
// Function��ʵ��ģ�ͽӿڣ���ͨ�ߣ��ö�ά�ռ��еľ���+����ʵ�֣�
// Author:   ��Ө
// Date:     2013-11-13
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_LINK_2D_H__
#define __IVBF_MARK_MODEL_LINK_2D_H__

#include <VBF_Plot/ElecMag/IVBF_MarkModelLink.h>

class IVBF_MarkModelLink2D : public IVBF_MarkModelLink
{
public:
	virtual ~IVBF_MarkModelLink2D() {}

	// ����/��ȡ��ͨ�ߵ�������ʽ
	virtual void                    SetTextureStyle(bool bForLink, const VBF_LINETEXSTYLE& style)=0;
	virtual const VBF_LINETEXSTYLE& GetTextureStyle(bool bForLink)=0;
};

#endif 
