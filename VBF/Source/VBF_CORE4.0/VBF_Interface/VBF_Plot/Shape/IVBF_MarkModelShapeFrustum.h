//*******************************************************************
// FileName��IVBF_MarkModelShapeFrustum.h
// Function������ʵ��ģ�ͣ�ƽ��ͷ�壨ԭ��λ��׶�⴦��
// Author:   ��Ө
// Date:     2013-09-05
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_FRUSTUM_H__
#define __IVBF_MARK_MODEL_SHAPE_FRUSTUM_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>
#include <Types/Vec3f>



//--------------------------------------------------------------------
// ����ö�٣�EVBF_FRUSTUM_DOME_PART
// ö��������Բ��״ƽ��ͷ��ĸ�������
//--------------------------------------------------------------------
enum EVBF_FRUSTUM_DOME_PART
{
	VBF_FRUSTUM_DOME_PART_HEAD		= 0,	// ͷ��
	VBF_FRUSTUM_DOME_PART_LEFT		= 1,	// ����
	VBF_FRUSTUM_DOME_PART_RIGHT		= 2,	// ����
	VBF_FRUSTUM_DOME_PART_FRONT		= 3,	// ǰ��
	VBF_FRUSTUM_DOME_PART_BACK		= 4,	// ����
	VBF_FRUSTUM_DOME_PART_COUNT				// ����
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeFrustum
// �ӿ�������ƽ��ͷ��
//--------------------------------------------------------------------
class IVBF_MarkModelShapeFrustum : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeFrustum() {}

public:

	// ����/��ȡƽ��ͷ��ˮƽ/��ֱ�Žǵ�һ�룬ֵ��ֱ�Ϊ[0, 90], [0, 180]
	// ��Ĭ������£�ԭ��λ��׶�⣬���������=0����
	virtual void SetTess(float fHalfAngleH, float fHalfAngleV)=0;
	virtual void GetTess(float& fHalfAngleH, float& fHalfAngleV)=0;

	// ����/��ȡƽ��ͷ�����ת�ᣬĬ��Ϊ(0,0,1)
	virtual void SetAxis(const osg::Vec3f& vAxis)=0;
	virtual osg::Vec3f GetAxis()=0;

	// ����/��ȡ����᷽��ķָ�����Ĭ��Ϊ6*6
	virtual void SetNumHeadSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumHeadSplit(int& nNumSplitRow, int& nNumSplitCol)=0;

	// ����/��ȡ�����ݺ᷽��ķָ�����Ĭ��Ϊ6
	virtual void SetNumSideSplitRow(int nNumSplit)=0;
	virtual int  GetNumSideSplitRow()=0;
};


//--------------------------------------------------------------------
// ����ö�٣�EVBF_FRUSTUM_FLAT_PART
// ö����������ƽ״ƽ��ͷ��ĸ�������
//--------------------------------------------------------------------
enum EVBF_FRUSTUM_FLAT_PART
{
	VBF_FRUSTUM_FLAT_PART_TOP		= 0,	// ���棨�����ü��棩
	VBF_FRUSTUM_FLAT_PART_BOTTOM	= 1,	// ���棨��Զ�ü��棩
	VBF_FRUSTUM_FLAT_PART_LEFT		= 2,	// ����
	VBF_FRUSTUM_FLAT_PART_RIGHT		= 3,	// ����
	VBF_FRUSTUM_FLAT_PART_FRONT		= 4,	// ǰ��
	VBF_FRUSTUM_FLAT_PART_BACK		= 5,	// ����
	VBF_FRUSTUM_FLAT_PART_COUNT				// ����
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeFrustumFlat
// �ӿ���������ƽ״ƽ��ͷ��
//--------------------------------------------------------------------
class IVBF_MarkModelShapeFrustumFlat : public IVBF_MarkModelShapeFrustum
{
public:
	virtual ~IVBF_MarkModelShapeFrustumFlat() {}

	// ����/��ȡ��ƽ״ƽ��ͷ���Զ���ü��棬Ĭ��ֵ�ֱ�Ϊ0, 1
	virtual void SetNearFar(float fNear, float fFar)=0;
	virtual void GetNearFar(float& fNear, float& fFar)=0;
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeFrustumDome
// �ӿ�������Բ��״ƽ��ͷ��
//--------------------------------------------------------------------
class IVBF_MarkModelShapeFrustumDome : public IVBF_MarkModelShapeFrustum
{
public:
	virtual ~IVBF_MarkModelShapeFrustumDome() {}

	// ����/��ȡԲ��״ƽ��ͷ��İ뾶
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;
};


#endif 
