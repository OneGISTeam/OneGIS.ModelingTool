//*******************************************************************
// FileName��IVBF_MarkModelLinkRing.h
// Function��ʵ��ģ�ͽӿڣ���ͨ�ߣ�����ά�ռ��еĻ�+����ʵ�֣�
// Author:   ��Ө
// Date:     2013-11-13 
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_LINK_RING_H__
#define __IVBF_MARK_MODEL_LINK_RING_H__

#include <VBF_Plot/ElecMag/IVBF_MarkModelLink.h>


class IVBF_MarkModelLinkRing : public IVBF_MarkModelLink
{
public:
	virtual ~IVBF_MarkModelLinkRing() {}

	// ����/��ȡ��ͨ�ߵ�������ʽ
	virtual void                    SetTextureStyle(bool bForLink, const VBF_LINETEXSTYLE& style)=0;
	virtual const VBF_LINETEXSTYLE& GetTextureStyle(bool bForLink)=0;

	// ����/��ȡ�߶��Ƿ�ɼ���������Բ���м䣬Ĭ��Ϊfalse��
	virtual void SetLineVisible(bool bVisible)=0;
	virtual bool IsLineVisible()=0;

	// ����/��ȡ��ͨ�ߵ��߶���ʽ
	virtual void				 SetLineStyle(bool bForLink, const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle(bool bForLink)=0;

	// ����/��ȡ���ε����߶ȣ�Ĭ��ֵΪ0
	virtual void   SetArcMaxHeight(double dHeight)=0;
	virtual double GetArcMaxHeight()=0;

	// ����/��ȡԲ�ָܷ���
	virtual void SetNumSplitCircle(int num)=0;
	virtual int  GetNumSplitCircle()=0;
};

#endif 
