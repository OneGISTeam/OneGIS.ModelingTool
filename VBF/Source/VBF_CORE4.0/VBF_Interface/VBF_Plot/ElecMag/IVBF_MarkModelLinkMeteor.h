//*******************************************************************
// FileName��IVBF_MarkModelLinkMeteor.h
// Function��ʵ��ģ�ͽӿڣ���ͨ�ߣ��������߷�ʽʵ�֣�
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_LINK_METEOR_H__
#define __IVBF_MARK_MODEL_LINK_METEOR_H__


#include <VBF_Plot/ElecMag/IVBF_MarkModelLink.h>
#include <VBF_Common/VBF_Math/VBF_Math.h>


class IVBF_MarkModelLinkMeteor : public IVBF_MarkModelLink
{
public:
    virtual ~IVBF_MarkModelLinkMeteor() {}

	// ����/��ȡ��ͨ�ߵ��߶���ʽ
	virtual void				 SetLineStyle(bool bForLink, const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetLineStyle(bool bForLink)=0;

    // ����/��ȡ�����ߵ��߶���ʽ
    virtual void				 SetBkLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetBkLineStyle()=0;

    virtual void SetTexImage(osg::Image* pImage)=0;
};

#endif 
