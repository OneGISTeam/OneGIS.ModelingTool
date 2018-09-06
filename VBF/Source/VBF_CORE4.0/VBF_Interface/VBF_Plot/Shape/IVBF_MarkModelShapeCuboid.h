//*******************************************************************
// FileName��IVBF_MarkModelShapeCuboid.h
// Function������ʵ��ģ�ͣ�������
// Author:   ��Ө
// Date:     2013-10-12
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_IMPL_H__
#define __IVBF_MARK_MODEL_SHAPE_IMPL_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_CUBOID_PART
// ö��������������ĸ�������
//--------------------------------------------------------------------
enum EVBF_CUBOID_PART
{
	VBF_CUBOID_PART_TOP		= 0,	// ����
	VBF_CUBOID_PART_BOTTOM	= 1,	// ����
	VBF_CUBOID_PART_LEFT	= 2,	// ����
	VBF_CUBOID_PART_RIGHT	= 3,	// ����
	VBF_CUBOID_PART_FRONT	= 4,	// ǰ��
	VBF_CUBOID_PART_BACK	= 5,	// ����
	VBF_CUBOID_PART_COUNT			// ����
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeCuboid
// �ӿ�������������
//--------------------------------------------------------------------
class IVBF_MarkModelShapeCuboid : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeCuboid() {}

public:

	// ����/��ȡ������ĳ���ߣ�������ȱ�ʾ������
	// ��Ĭ������£�ԭ��λ�ڳ�����ļ������ģ�
	virtual void SetTess(float length, float width, float height)=0;
	virtual void GetTess(float& length, float& width, float& height)=0;

	// ����/��ȡ�����ݺ᷽��ķָ�����Ĭ��Ϊ6*6
	virtual void SetNumSideSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSideSplit(int& nNumSplitRow, int& nNumSplitCol)=0;

	// ����/��ȡ����᷽��ķָ�����Ĭ��Ϊ6
	virtual void SetNumTopSplit(int nNumSplit)=0;
	virtual int  GetNumTopSplit()=0;
};


#endif 
