//*******************************************************************
// FileName��IVBF_MarkModelShapeSphere.h
// Function������ʵ��ģ�ͣ����壬ʵ����ΪDome��һ����������
// Author:   ��Ө
// Date:     2013-07-12
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_SPHERE_H__
#define __IVBF_MARK_MODEL_SHAPE_SPHERE_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShapeDome.h>

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeSphere
// �ӿ�����������
//--------------------------------------------------------------------
class IVBF_MarkModelShapeSphere : public IVBF_MarkModelShapeDome
{
public:
	virtual ~IVBF_MarkModelShapeSphere() {}

public:

	// ����/��ȡ����뾶��Ĭ������£�ԭ��λ�����ģ��뾶Ϊ1.0��
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeHemiSphere
// �ӿ�������������
//--------------------------------------------------------------------
class IVBF_MarkModelShapeHemiSphere : public IVBF_MarkModelShapeSphere
{
public:
	virtual ~IVBF_MarkModelShapeHemiSphere() {}
};


#endif 
