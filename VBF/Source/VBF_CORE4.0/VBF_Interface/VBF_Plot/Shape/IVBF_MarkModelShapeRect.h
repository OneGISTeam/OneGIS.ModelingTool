//*******************************************************************
// FileName��IVBF_MarkModelRect.h
// Function��ʵ��ģ�ͣ���ά����ά�ռ��еľ���
// Author:   ��Ө
// Date:     2017-08-05
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RECT_H__
#define __IVBF_MARK_MODEL_RECT_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_RECT_PART
// ö�����������εĸ�������
//--------------------------------------------------------------------
enum EVBF_RECT_PART
{
    VBF_RECT_PART_LINE		= 0,	// ��
    VBF_RECT_PART_FILL		= 1,	// ��
    VBF_RECT_PART_COUNT				// ����
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeRect2D
// �ӿ���������ά�ռ��еľ���
//--------------------------------------------------------------------
class IVBF_MarkModelShapeRect2D : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeRect2D() {}

	// ����/��ȡ����ԭ���Ƿ�λ����Ļ���Ͻǣ�Ĭ��Ϊtrue��
	virtual void SetOriginTopLeft(bool bTopLeft)=0;
	virtual bool IsOriginTopLeft()=0;

	// ����/��ȡ���ε���Ļ���귶Χ
	virtual void SetClientRect(float x0, float x1, float y0, float y1)=0;
	virtual void GetClientRect(float& x0, float& x1, float& y0, float& y1)=0;

	// ���þ����ݺ᷽��ķָ�����Ĭ��Ϊ6*6
	virtual void SetNumSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSplit(int& nNumSplitRow, int& nNumSplitCol)=0;
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeRect3D
// �ӿ���������ά�ռ��еľ���
//--------------------------------------------------------------------
class IVBF_MarkModelShapeRect3D : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeRect3D() {}

	// ����/��ȡ���εĳ��Ϳ�������ȱ�ʾ������
	// ��Ĭ������£�ԭ��λ�ھ��εļ������ģ�
	virtual void SetSize(float length, float width)=0;
	virtual void GetSize(float& length, float& width)=0;

	// ����/��ȡ�����ݺ᷽��ķָ�����Ĭ��Ϊ6*6
	virtual void SetNumSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSplit(int& nNumSplitRow, int& nNumSplitCol)=0;
};

#endif 
