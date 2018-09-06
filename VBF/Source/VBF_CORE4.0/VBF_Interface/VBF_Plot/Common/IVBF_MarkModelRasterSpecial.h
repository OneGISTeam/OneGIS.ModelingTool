//*******************************************************************
// FileName��IVBF_MarkModelRasterSpecial.h
// Function�����������դ���;���ʵ��ģ�ͽӿ�
// Author:   ��Ө
// Date:     2015-12-01
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RASTER_SPECIAL_H__
#define __IVBF_MARK_MODEL_RASTER_SPECIAL_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <string>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRasterSpecial
// �ӿ����������������դ���;���ʵ��ģ��
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSpecial : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelRasterSpecial() {}

	// ����/��ȡģ�͵ĳߴ���Ϣ��ע�⣺����˴����õĳ���Ȳ�����ԭʼ����ȣ��ᵼ��ͼ�����
	virtual void SetSize(bool bFixedSizeInPixels, float fWidth, float fHeight)=0;
	virtual void GetSize(bool& bFixedSizeInPixels, float& fWidth, float& fHeight)=0;
	
	// ����/��ȡ����ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

    // ����/��ȡ�����͸���ȣ�Ĭ��ֵΪ1.0��
    virtual void  SetTexAlpha(float fAlpha)=0;
    virtual float GetTexAlpha()=0;

	// ����/��ȡ����ԭ����λͼ�е����λ�� (��������½ǣ�ֵ��Ϊ[0.0, 1.0])
	virtual void SetTexOrign(float fTexOrignX, float fTexOrignY)=0;
	virtual void GetTexOrign(float& fTexOrignX, float& fTexOrignY)=0;
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRasterBoardH
// �ӿ�������դ���;���ʵ��ģ�ͣ�ʹ��ˮƽ������
//--------------------------------------------------------------------
class IVBF_MarkModelRasterBoardH : public IVBF_MarkModelRasterSpecial
{
public:
	virtual ~IVBF_MarkModelRasterBoardH() {}
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRasterBoardV
// �ӿ�������դ���;���ʵ��ģ�ͣ�ʹ�ô�ֱ������
//--------------------------------------------------------------------
class IVBF_MarkModelRasterBoardV : public IVBF_MarkModelRasterSpecial
{
public:
	virtual ~IVBF_MarkModelRasterBoardV() {}
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRasterBoardHV
// �ӿ�������դ���;���ʵ��ģ�ͣ�ʹ����ȫ������
//--------------------------------------------------------------------
class IVBF_MarkModelRasterBoardHV : public IVBF_MarkModelRasterSpecial
{
public:
	virtual ~IVBF_MarkModelRasterBoardHV() {}
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRasterHorizon
// �ӿ�������դ���;���ʵ��ģ�ͣ���ʹ�ò����ƣ�ƽ���ڵ��棬�ҽ�����Z����ת
//--------------------------------------------------------------------
class IVBF_MarkModelRasterHorizon : public IVBF_MarkModelRasterSpecial
{
public:
	virtual ~IVBF_MarkModelRasterHorizon() {}
};

#endif 
