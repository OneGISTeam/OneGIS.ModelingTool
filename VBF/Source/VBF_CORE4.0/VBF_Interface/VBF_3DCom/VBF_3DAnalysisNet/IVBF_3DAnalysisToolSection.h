//*******************************************************************
// FileName��IVBF_3DAnalysisToolSection.h
// Function����ά�������ߣ�����֮����������
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_SECTION_H__
#define __IVBF_3DANALYSIS_TOOL_SECTION_H__


#include <VBF_3DCom/VBF_3DAnalysisNet/IVBF_3DAnalysisTool.h>


class IVBF_3DAnalysisToolSection : public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolSection() {}

	// ����/��ȡ���������ǽ�Ķ�����ɫ
	virtual void SetWallColor(const osg::Vec4f& colorTop, const osg::Vec4f& colorBottom)=0;
	virtual void GetWallColor(osg::Vec4f& colorTop, osg::Vec4f& colorBottom)=0;

	// ����/��ȡ���������ǽ�Ķ���������ɫ
	virtual void                 SetWallLineStyleTop(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetWallLineStyleTop()=0;

	// ����/��ȡ���������ǽ�ĵײ�������ɫ
	virtual void                 SetWallLineStyleBottom(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetWallLineStyleBottom()=0;

	// ����/��ȡ��������д��ߵ���ʽ
	virtual void                 SetVertLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetVertLineStyle()=0;

	// ����/��ȡ������������/�յ�/�����С�̵߳����ʽ
	virtual void                  SetMinMaxPointStyle(const VBF_POINTSTYLE& style)=0;
	virtual const VBF_POINTSTYLE& GetMinMaxPointStyle()=0;

	// ����/��ȡ��������е�ǰѡ�е����ʽ
	virtual void                  SetSelectedPointStyle(const VBF_POINTSTYLE& style)=0;
	virtual const VBF_POINTSTYLE& GetSelectedPointStyle()=0;
};

#endif
