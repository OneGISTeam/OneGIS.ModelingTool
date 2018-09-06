//*******************************************************************
// FileName��IVBF_MarkModelShapeSector.h
// Function������ʵ��ģ�ͣ�����
// Author:   ��Ө
// Date:     2015-08-17
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_SECTOR_H__
#define __IVBF_MARK_MODEL_SHAPE_SECTOR_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_SECTOR_PART
// ö�����������εĸ�������
//--------------------------------------------------------------------
enum EVBF_SECTOR_PART
{
	VBF_SECTOR_PART_BODY		= 0,	// ����
	VBF_SECTOR_PART_CONE_INNER	= 1,	// ��׶��
	VBF_SECTOR_PART_CONE_OUTER	= 2,	// ��׶��
	VBF_SECTOR_PART_SIDE_START	= 3,	// ��ʼ����
	VBF_SECTOR_PART_SIDE_END	= 4,	// ��ֹ����
	VBF_SECTOR_PART_COUNT				// ����
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeSector
// �ӿ�����������
//--------------------------------------------------------------------
class IVBF_MarkModelShapeSector : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeSector() {}

public:

	// ����/��ȡ����ˮƽ�ʹ�ֱ�������ʼ�Ǻ���ֹ�ǣ�ֵ��ֱ�Ϊ[0, 360],[0, 180]
	// ˵������ֱ��Ϊ0�ȱ�ʾ��������ֱ��Ϊ180�ȱ�ʾ�ϼ���Ĭ������£�ԭ��λ�����ģ��뾶Ϊ1��
	virtual void SetTess(float fAngleH0, float fAngleH1, float fAngleV0, float fAngleV1)=0;
	virtual void GetTess(float& fAngleH0, float& fAngleH1, float& fAngleV0, float& fAngleV1)=0;

	// �����ݺ᷽��ķָ�����Ĭ��ֵ��Ϊ18, 36
	virtual void SetNumSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSplit(int& nNumSplitRow, int& nNumSplitCol)=0;

	// ����/��ȡ����׶���Բ���ָ�����Ĭ��ֵΪ6
	virtual void SetNumConeSplit(int nNumSplit)=0;
	virtual int  GetNumConeSplit()=0;

	// ����/��ȡ����Բ���ָ�����Ĭ��ֵΪ6
	virtual void SetNumSideSplit(int nNumSplit)=0;
	virtual int  GetNumSideSplit()=0;

	// ����/��ȡ���ε��泤����İ뾶���߶ȣ�������ȫ���ʱ��ʾ���壬Ĭ��ֵ��Ϊ1.0��
	virtual void SetSize(float fSizeX, float fSizeY, float fSizeZ)=0;
	virtual void GetSize(float& fSizeX, float& fSizeY, float& fSizeZ)=0;
};


#endif 
