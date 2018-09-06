//*******************************************************************
// FileName��IVBF_MarkModelShapeCircle.h
// Function������ʵ��ģ�ͣ�
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_CIRCLE_H__
#define __IVBF_MARK_MODEL_SHAPE_CIRCLE_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_CYLINDER_PART
// ö��������Բ����ĸ�������
//--------------------------------------------------------------------
enum EVBF_CIRCLE_PART
{
    VBF_CIRCLE_PART_LINE			= 0,	// ��
    VBF_CIRCLE_PART_FILL			= 1,	// ��
    VBF_CIRCLE_PART_COUNT					// ����
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeCircle
// �ӿ�������Բ����
//--------------------------------------------------------------------
class IVBF_MarkModelShapeCircle : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeCircle() {}

    // ����/��ȡԲ�ָܷ�����Ĭ��ֵΪ36
    virtual void SetNumSplit(int numSplit)=0;
	virtual int  GetNumSplit()=0;
	
    // ���ð뾶������ʱΪ��Բ
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;
};


#endif 
