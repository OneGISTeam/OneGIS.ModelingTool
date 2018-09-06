//*******************************************************************
// FileName��IVBF_MarkAttrLabelChained.h
// Function��ģ�����Խӿڣ�ɢ��ʽ��ǩ���������߱�ע������ģ��
// Author:   ��Ө
// Date:     2014-09-01
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_LABEL_CHAINED_H__
#define __IVBF_MARK_ATTR_LABEL_CHAINED_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <VBF_Plot/Common/IVBF_MarkModelText.h>



class IVBF_MarkAttrLabelChained : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrLabelChained() {}

    // ���һ������ɢ�е��ı�
    virtual void AddText(const std::string& strText, const std::vector<osg::Vec3d>& vPointsGeo)=0;

	// ����/��ȡ�ı���ʽ
	virtual void                 SetTextStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetTextStyle()=0;
};


#endif 
