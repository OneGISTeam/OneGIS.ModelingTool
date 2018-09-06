//*******************************************************************
// FileName��IVBF_MarkModelLink2DDualWork.h
// Function��ʵ��ģ�ͽӿڣ���ͨ�ߣ��ö�ά�ռ��еľ���+����ʵ�֣�
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_LINK_2D_DUAL_WORK_H__
#define __IVBF_MARK_MODEL_LINK_2D_DUAL_WORK_H__

#include <VBF_Plot/ElecMag/IVBF_MarkModelLink.h>

class IVBF_MarkModelLink2DDualWork : public IVBF_MarkModelLink
{
public:

    virtual ~IVBF_MarkModelLink2DDualWork() {}

	// ����/��ȡ��ͨ�ߵ�������ʽ
    virtual void                    SetTextureStyle(bool bForLink, const VBF_LINETEXSTYLE& style)=0;
    virtual const VBF_LINETEXSTYLE& GetTextureStyle(bool bForLink)=0;

	// ����/��ȡ�Ƿ�����Ĭ��ֵΪtrue��
    virtual void  SetDirectionLeft(bool bLeft)=0;
	virtual bool  IsDirectionLeft()=0;
};

#endif 
