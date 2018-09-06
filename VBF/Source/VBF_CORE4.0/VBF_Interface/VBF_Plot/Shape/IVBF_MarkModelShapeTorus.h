//*******************************************************************
// FileName��IVBF_MarkModelShapeTorus.h
// Function������ʵ��ģ�ͣ�Բ��
// Author:   ��Ө
// Date:     2013-10-10
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_TORUS_H__
#define __IVBF_MARK_MODEL_SHAPE_TORUS_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>

//--------------------------------------------------------------------
// ����ö�٣�EVBF_TORUS_PART
// ö��������Բ���ĸ�������
//--------------------------------------------------------------------
enum EVBF_TORUS_PART
{
	VBF_TORUS_PART_BODY	= 0,		// ����
	VBF_TORUS_PART_COUNT			// ����
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeTorus
// �ӿ�������Բ��
//--------------------------------------------------------------------
class IVBF_MarkModelShapeTorus : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeTorus() {}

public:

	// ����/��ȡԲ��������뾶��Ĭ��ֵ�ֱ�Ϊ��1.0, 4.0
	virtual void SetTess(float fRadiusInner, float fRadiusOuter)=0;
	virtual void GetTess(float& fRadiusInner, float& fRadiusOuter)=0;

	// ����Բ���ݺ᷽��ķָ�����Ĭ��ֵ��Ϊ12, 36
	virtual void SetNumSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSplit(int& nNumSplitRow, int& nNumSplitCol)=0;
};


#endif 
