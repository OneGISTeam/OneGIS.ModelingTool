//*******************************************************************
// FileName��IVBF_MarkModelRaster.h
// Function��դ���;���ʵ��ģ�ͽӿ�
// Author:
// Date:     2009-4-10
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RASTER_H__
#define __IVBF_MARK_MODEL_RASTER_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <string>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRaster
// �ӿ�������դ���;���ʵ��ģ��
//--------------------------------------------------------------------
class IVBF_MarkModelRaster : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelRaster() {}
	
	// ����/��ȡ����ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

    // ����/��ȡ�����͸���ȣ�Ĭ��ֵΪ1.0��
    virtual void  SetTexAlpha(float fAlpha)=0;
    virtual float GetTexAlpha()=0;
    virtual void  SetTexColor(osg::Vec4f color)=0;

	// ����/��ȡ����ԭ����λͼ�е����λ�� (��������½ǣ�ֵ��Ϊ[0.0, 1.0])
	virtual void SetTexOrign(float fTexOrignX, float fTexOrignY)=0;
    virtual void GetTexOrign(float& fTexOrignX, float& fTexOrignY)=0;

	// ����/��ȡͼ�񾭹����ź��ʵ�ʳߴ磨��λ���ף�����������EnableFixedSizeInPixels(false)�����
	// ע�⣺����˴����õĳ���Ȳ�����ԭʼ����ȣ��ᵼ��ͼ�����
	virtual void SetSizeInMeters(float fWidth, float fHeight)=0;
	virtual void GetSizeInMeters(float& fWidth, float& fHeight)=0;

	virtual void  SetAutoEnlarge(float fScaleMax, float fDelta, bool bMultify)=0;
};


#endif 
