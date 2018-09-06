//*******************************************************************
// FileName��IVBF_MarkModelText.h
// Function������ʵ��ģ�ͽӿڣ��ı�
// Author:   ��Ө
// Date:     2013-12-04
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_TEXT_H__
#define __IVBF_MARK_MODEL_TEXT_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <string>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_TEXTPOS_TYPE
// ö���������ı��Ķ�λ��ʽ
//--------------------------------------------------------------------
enum EVBF_TEXTPOS_TYPE
{
	VBF_TEXTPOS_GEO					= 0,	// �û����õĵ�������
	VBF_TEXTPOS_WORLD				= 1,	// �û����õ���������
	VBF_TEXTPOS_SCREEN				= 2,	// �û����õ���Ļ����
	VBF_TEXTPOS_PARENTGEO			= 3,	// ��ģ�͵ĵ������꣨Ĭ��ֵ��
    VBF_TEXTPOS_PARENTBOXTOPCENTER	= 4,	// ��ģ�Ͱ�Χ�ж������ĵĵ������꣨ע�⣺��ʱҪ��ģ�ͱ���ΪRaster�ࣩ
    VBF_TEXTPOS_PARENTBOXBOTTOMCENTER= 5,   // ��ģ�Ͱ�Χ�ж������ĵĵ������꣨ע�⣺��ʱҪ��ģ�ͱ���ΪRaster�ࣩ
    VBF_TEXTPOS_PARENTBOXCENTERRIGHT = 6    // ��ģ�Ͱ�Χ�ж������ĵĵ������꣨ע�⣺��ʱҪ��ģ�ͱ���ΪRaster�ࣩ
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelText
// �ӿ��������ı��;���ʵ��ģ��
//--------------------------------------------------------------------
class IVBF_MarkModelText : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelText() {}

	// ����/��ȡ�ı�����
	virtual void			   SetText(const std::string& strText)=0;
	virtual const std::string& GetText()=0;

	// ����/��ȡ�ı���ʽ
	virtual void                 SetTextStyle(const VBF_TEXTSTYLE& style)=0;
	virtual const VBF_TEXTSTYLE& GetTextStyle()=0;

	// ����/��ȡ�ı�������Ŀɼ���
	virtual void SetFrameVisible(bool bVisible)=0;
	virtual bool IsFrameVisible()=0;

	// ����/��ȡ�ı����������ʽ
	virtual void                      SetFrameStyle(const VBF_POLYGON2DSTYLE& style)=0;
	virtual const VBF_POLYGON2DSTYLE& GetFrameStyle()=0;

	// ����/��ȡ�Ƿ���Ʊ������еĶ�λ��ʶ�������ı�������ߵ�С�����Σ�Ĭ��Ϊtrue��
	virtual void SetIndicatorVisible(bool bVisible)=0;
	virtual bool IsIndicatorVisible()=0;

	// ����/��ȡ��λ��ʽ
    virtual void              SetPosType(EVBF_TEXTPOS_TYPE nPosType)=0;
    virtual EVBF_TEXTPOS_TYPE GetPosType()=0;

	// ������������ϵ�µ�����
	virtual void SetWorldPos(const osg::Vec3d& vPos)=0;

	// ����/��ȡ��Ļ����ϵ�µ����꣨��λ�����أ�Ĭ��ֵΪ(0,0,-1)��
	virtual void       SetScreenPos(const osg::Vec3d& vPos)=0;
	virtual osg::Vec3d GetScreenPos()=0;

	// ����/��ȡ��Ļ����ϵ�µ�ƫ��������λ�����أ�Ĭ��ֵ��Ϊ0��
	virtual void SetScreenOffset(float fOffsetX, float fOffsetY)=0;
	virtual void GetScreenOffset(float& fOffsetX, float& fOffsetY)=0;

    // ��ȡ�ı���ǰռ�ݵ���Ļλ�ã�ע�⣺x0<x1, y0<y1��
    virtual void GetScreenRect(float& x0, float& y0, float& x1, float& y1)=0;
};


#endif 
