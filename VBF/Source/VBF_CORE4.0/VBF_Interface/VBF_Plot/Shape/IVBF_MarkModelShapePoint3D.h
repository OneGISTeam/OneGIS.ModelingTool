//*******************************************************************
// FileName��IVBF_MarkModelShapePoint3D.h
// Function������ʵ��ģ�ͽӿڣ������㣨ʹ����ά�ռ��е����꣩
// Author:   ��Ө
// Date:     2014-01-07
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_POINT3D_H__
#define __IVBF_MARK_MODEL_SHAPE_POINT3D_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>
#include <Types/VBF_3DStyles.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapePoint3D
// �ӿ������������㣨ʹ����ά�ռ��е����꣩
//--------------------------------------------------------------------
class IVBF_MarkModelShapePoint3D : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelShapePoint3D() {}

    // ����/��ȡ�����ʽ
    virtual void                  SetPointStyle(const VBF_POINTSTYLE& style)=0;
    virtual const VBF_POINTSTYLE& GetPointStyle()=0;

	// ����/��ȡ�����ɫ��ʽ��Ĭ��Ϊ��ֻʹ����ɫ
	virtual void             SetShadeStyle(EVBF_SHADE_STYLE nStyle)=0;
	virtual EVBF_SHADE_STYLE GetShadeStyle()=0;

	// ����/��ȡ����ͼ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// ����/��ȡ�����͸���ȣ�ֵ��Ϊ[0.0, 1.0]��Ĭ��ֵΪ1.0��
	virtual void  SetTexAlpha(float fAlpha)=0;
	virtual float GetTexAlpha()=0;
};


#endif 
