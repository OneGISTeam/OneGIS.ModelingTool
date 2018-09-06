//*******************************************************************
// FileName��IVBF_MarkModelShapeCylinderS.h
// Function���ֲ��Բ��
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_CYLINDERS_H__
#define __IVBF_MARK_MODEL_SHAPE_CYLINDERS_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_CYLINDER_PART
// ö��������Բ����ĸ�������
//--------------------------------------------------------------------
enum EVBF_CYLINDERS_PART
{
    VBF_CYLINDERS_PART_TOP			= 0,	// ����
    VBF_CYLINDERS_PART_BOTTOM		= 1,	// ����
    VBF_CYLINDERS_PART_BODY       	= 2,	// ��ʼ����
    VBF_CYLINDERS_PART_COUNT				// ����
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeCylinderS
// �ӿ�������Բ����
//--------------------------------------------------------------------
class IVBF_MarkModelShapeCylinderS : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeCylinderS() {}

public:

	/* ����/��ȡԲ�����Բ�ָܷ�����Ĭ��ֵΪ36 */
	virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;

	/* ����/��ȡԲ����Ķ���Բ���ָ�����Ĭ��ֵΪ6 */
	virtual void SetNumTopSplit(int nNumSplit)=0;
	virtual int  GetNumTopSplit()=0;

	
	/* ����/��ȡԲ������泤����İ뾶�����߲���ȱ�ʾ��Բ���壬������ȱ�ʾԲ���� */
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;

    virtual void SetTopEdgeHeights(vector<double>& vHeight)=0;
    virtual void SetBottomEdgeHeights(vector<double>& vHeight)=0;
    virtual void SetTopHeights(vector<double>& vHeight)=0;


	/* ����/��ȡԲ����߶� */
	virtual void  SetHeight(float fHeight)=0;
	virtual float GetHeight()=0;
};


#endif 
