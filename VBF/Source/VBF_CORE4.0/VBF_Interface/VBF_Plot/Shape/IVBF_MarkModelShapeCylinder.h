//*******************************************************************
// FileName��IVBF_MarkModelShapeCylinder.h
// Function������ʵ��ģ�ͣ�Բ����/��Բ����
// Author:   ��Ө
// Date:     2013-09-03
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_CYLINDER_H__
#define __IVBF_MARK_MODEL_SHAPE_CYLINDER_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_CYLINDER_PART
// ö��������Բ����ĸ�������
//--------------------------------------------------------------------
enum EVBF_CYLINDER_PART
{
	VBF_CYLINDER_PART_BODY			= 0,	// ����
	VBF_CYLINDER_PART_TOP			= 1,	// ����
	VBF_CYLINDER_PART_BOTTOM		= 2,	// ����
	VBF_CYLINDER_PART_SIDE_START	= 3,	// ��ʼ����
	VBF_CYLINDER_PART_SIDE_END		= 4,	// ��ֹ����
	VBF_CYLINDER_PART_COUNT					// ����
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeCylinder
// �ӿ�������Բ����
//--------------------------------------------------------------------
class IVBF_MarkModelShapeCylinder : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeCylinder() {}

public:

	/*
	* ����Բ���壨Ĭ������£�ԭ��λ��Բ����ײ�������뾶�͸߶Ⱦ�Ϊ1��
	* ����: fStratAngle -- ����Բ������ʼ�Ƕȣ�ֵ��Ϊ[0, 360]��Ĭ��ֵΪ0
	*       fEndAngle   -- ����Բ������ֹ�Ƕȣ�ֵ��Ϊ[fStratAngle, 360]��Ĭ��ֵΪ360
	*/
	virtual void SetTess(float fStartAngle, float fEndAngle)=0;
	virtual void GetTess(float& fStartAngle, float& fEndAngle)=0;

	/* ����/��ȡԲ�����Բ�ָܷ�����Ĭ��ֵΪ36 */
	virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;

	/* ����/��ȡԲ����Ķ���Բ���ָ�����Ĭ��ֵΪ6 */
	virtual void SetNumTopSplit(int nNumSplit)=0;
	virtual int  GetNumTopSplit()=0;

	/* ����/��ȡԲ����Ĳ���Բ���ָ�����Ĭ��ֵΪ6 */
	virtual void SetNumSideSplit(int nNumSplit)=0;
	virtual int  GetNumSideSplit()=0;
	
	/* ����/��ȡԲ������泤����İ뾶�����߲���ȱ�ʾ��Բ���壬������ȱ�ʾԲ���� */
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;

	/* ����/��ȡԲ����߶� */
	virtual void  SetHeight(float fHeight)=0;
	virtual float GetHeight()=0;
};


#endif 
