//*******************************************************************
// FileName��IVBF_MarkModelShapeDome.h
// Function������ʵ��ģ�ͣ�Բ���壬������Բ�ݶ�
// Author:   ��Ө
// Date:     2013-09-05
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_DOME_H__
#define __IVBF_MARK_MODEL_SHAPE_DOME_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_DOME_PART
// ö��������Բ����ĸ�������
//--------------------------------------------------------------------
enum EVBF_DOME_PART
{
	VBF_DOME_PART_BODY			= 0,	// ����
	VBF_DOME_PART_CONE_INNER	= 1,	// ��׶��
	VBF_DOME_PART_CONE_OUTER	= 2,	// ��׶��
	VBF_DOME_PART_SIDE_START	= 3,	// ��ʼ����
	VBF_DOME_PART_SIDE_END		= 4,	// ��ֹ����
	VBF_DOME_PART_PARALLEL		= 5,	// γ��Ȧ
	VBF_DOME_PART_MERIDIAN		= 6,	// ����Ȧ
	VBF_DOME_PART_COUNT					// ����
};


//--------------------------------------------------------------------
// ����ö�٣�EVBF_DOME_ORIGIN_TYPE
// ö��������Բ�����ԭ���������е�λ��
//--------------------------------------------------------------------
enum EVBF_DOME_ORIGIN_TYPE
{
	VBF_DOME_ORIGIN_CENTER		= 0,	// ԭ��λ�����ģ�Ĭ��ֵ��
	VBF_DOME_ORIGIN_BOTTOM		= 1,	// ԭ��λ����ײ�
	VBF_DOME_ORIGIN_TOP			= 2,	// ԭ��λ���򶥲�
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeDome
// �ӿ�������Բ����
//--------------------------------------------------------------------
class IVBF_MarkModelShapeDome : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeDome() {}

public:

	// ����/��ȡԲ����ˮƽ�ʹ�ֱ�������ʼ�Ǻ���ֹ�ǣ�ֵ��ֱ�Ϊ[0, 360],[0, 180]
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

	// ����/��ȡγ��Ȧ������Ĭ��ֵΪ1������Ϊ�������Գ��Ϊ�Գ��ᣩ
	virtual void SetNumParallels(int num)=0;
	virtual int  GetNumParallels()=0;

	// ����/��ȡ����Ȧ������Ĭ��ֵΪ1
	virtual void SetNumMeridians(int num)=0;
	virtual int  GetNumMeridians()=0;
	
	// ����/��ȡԲ������泤����İ뾶���߶ȣ�������ȫ���ʱ��ʾ���壬Ĭ��ֵ��Ϊ1.0��
	virtual void SetSize(float fSizeX, float fSizeY, float fSizeZ)=0;
	virtual void GetSize(float& fSizeX, float& fSizeY, float& fSizeZ)=0;

    // ����/��ȡԲ�����Ƿ������һ�£�Ĭ��ֵΪfalse
    virtual void SetAxisAccordWithEarth(bool bAccordWithEarth)=0;
    virtual bool IsAxisAccordWithEarth()=0;

    // ����/��ȡģ��ԭ���������е�λ�ã�Ĭ��ΪVBF_DOME_ORIGIN_CENTER��
    virtual void                  SetOriginType(EVBF_DOME_ORIGIN_TYPE nOrigin)=0;
    virtual EVBF_DOME_ORIGIN_TYPE GetOriginType()=0;
};


#endif 
