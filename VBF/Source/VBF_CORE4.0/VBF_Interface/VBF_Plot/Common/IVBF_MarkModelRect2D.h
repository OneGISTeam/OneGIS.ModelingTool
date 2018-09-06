//*******************************************************************
// FileName��IVBF_MarkModelRect2D.h
// Function��ʵ��ģ�ͽӿڣ�2D���Σ�ʹ����Ļ����
// Author:   ��Ө
// Date:     2014-12-26
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RECT2D_H__
#define __IVBF_MARK_MODEL_RECT2D_H__


#include <VBF_Plot/Common/IVBF_MarkModel2D.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <string>
#include <Types/VBF_3DStyles.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRect2D
// �ӿ�������2D���Σ�ʹ����Ļ����
//--------------------------------------------------------------------
class IVBF_MarkModelRect2D : public IVBF_MarkModel2D
{
public:
	virtual ~IVBF_MarkModelRect2D() {}

	// ����/��ȡ���εļ�����ʽ��Ĭ��Ϊ��ʵ��+����
	virtual void                SetGeometryStyle(EVBF_GEOMETRY_STYLE nStyle)=0;
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle()=0;

	// ����/��ȡ���ε�ʵ����ɫ
	virtual void              SetSolidColor(const osg::Vec4f& color)=0;
	virtual const osg::Vec4f& GetSolidColor()=0;

	// ����/��ȡ���εı�����ʽ
	virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;
};


#endif 
