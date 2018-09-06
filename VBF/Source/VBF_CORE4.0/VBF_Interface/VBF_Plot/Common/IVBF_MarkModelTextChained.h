//*******************************************************************
// FileName��IVBF_MarkModelTextChained.h
// Function������ʵ��ģ�ͽӿڣ�ɢ��ʽ
// Author:   ��Ө
// Date:     2013-12-04
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_TEXT_CHAINED_H__
#define __IVBF_MARK_MODEL_TEXT_CHAINED_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <string>
#include <vector>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelTextChained
// �ӿ�������ɢ��ʽ�ı�
//--------------------------------------------------------------------
class IVBF_MarkModelTextChained : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelTextChained() {}

	// ����/��ȡ�ı�����
    virtual void			   SetText(const std::string& strText, const std::vector<osg::Vec3d>& vPointsGeo)=0;
	virtual const std::string& GetText()=0;

	// ��ȡ�ı���Ӧ�����괮
	virtual const std::vector<osg::Vec3d>& GetPointsGeo()=0;

	// ����/��ȡ�ı���ʽ
	virtual void                 SetTextStyle(const VBF_TEXTSTYLE& style)=0;
	virtual const VBF_TEXTSTYLE& GetTextStyle()=0;
};


#endif 
