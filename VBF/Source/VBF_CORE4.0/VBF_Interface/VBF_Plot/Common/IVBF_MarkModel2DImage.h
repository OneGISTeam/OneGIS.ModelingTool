//*******************************************************************
// FileName��IVBF_MarkModel2DImage.h
// Function��ʵ��ģ�ͽӿڣ�2Dͼ��ʹ����Ļ����
// Author:   ��Ө
// Date:     2014-02-25
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_IMAGE2D_H__
#define __IVBF_MARK_MODEL_IMAGE2D_H__


#include <VBF_Plot/Common/IVBF_MarkModel2D.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <string>
#include <VBF_Engine/VBF_SceneGraph/Image>



//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModel2DImage
// �ӿ�������2Dͼ��ʹ����Ļ����
//--------------------------------------------------------------------
class IVBF_MarkModel2DImage : public IVBF_MarkModel2D
{
public:
    virtual ~IVBF_MarkModel2DImage() {}

	// ����/��ȡ����ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// ����/��ȡ�����͸���ȣ�ֵ��Ϊ[0.0, 1.0]��Ĭ��ֵΪ0.6��
	virtual void  SetTexAlpha(float fAlpha)=0;
	virtual float GetTexAlpha()=0;

	// ����/��ȡ�Ƿ�����ͼƬԭ�е��ݺ�ȣ�Ĭ��Ϊtrue
    virtual void SetLockAspect(bool bLockAspect)=0;
    virtual bool IsLockAspect()=0;

};


#endif 
