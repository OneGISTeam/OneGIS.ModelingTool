//*******************************************************************
// FileName��IVBF_MarkModelCrossQuad.h
// Function��ʮ�ֽ���ģ�ͣ�����ʵ�ֵ���β�桢ʮ�ֽ�������
// Author:   ��Ө
// Date:     2014-11-24
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_CROSS_QUAD_H__
#define __IVBF_MARK_MODEL_CROSS_QUAD_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <Types/Vec3f>
#include <string>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelCrossQuad
// �ӿ�������ʮ�ֽ���ģ�ͣ�����ʵ�ֵ���β�桢ʮ�ֽ�������
//--------------------------------------------------------------------
class IVBF_MarkModelCrossQuad : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkModelCrossQuad() {}

    // ����/��ȡ�����ı��εĿ�Ⱥ͸߶ȣ���λ���ף�
    virtual void SetSize(float fWidth, float fHeight)=0;
    virtual void GetSize(float& fWidth, float& fHeight)=0;

    // ����/��ȡ������
    virtual void              SetAxis(const osg::Vec3f& vAxis)=0;
    virtual const osg::Vec3f& GetAxis()=0;

	// ����/��ȡ����ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;
};


#endif 
