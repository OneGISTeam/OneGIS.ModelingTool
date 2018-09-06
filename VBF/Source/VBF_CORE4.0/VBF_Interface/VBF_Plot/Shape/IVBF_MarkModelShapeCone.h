//*******************************************************************
// FileName��IVBF_MarkModelShapeCone.h
// Function������ʵ��ģ�ͣ�Բ׶��
// Author:   ��Ө
// Date:     2013-08-02
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_CONE_H__
#define __IVBF_MARK_MODEL_SHAPE_CONE_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


// ����Բ׶����Žǵ���С���ֵ����λ���Ƕȣ�
#define VBF_CONE_HALFANGLE_MIN		0.000001f
#define VBF_CONE_HALFANGLE_MAX		89.999999f


//--------------------------------------------------------------------
// ����ö�٣�EVBF_CONE_PART
// ö��������Բ׶��ĸ�������
//--------------------------------------------------------------------
enum EVBF_CONE_PART
{
	VBF_CONE_PART_BODY		= 0,	// ����
	VBF_CONE_PART_HEAD		= 1,	// ����
	VBF_CONE_PART_SCANLINE	= 2,	// ��̬ɨ����
	VBF_CONE_PART_COUNT				// ����
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeCone
// �ӿ�������Բ׶��
//--------------------------------------------------------------------
class IVBF_MarkModelShapeCone : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeCone() {}

public:

	// ����/��ȡԲ׶�Žǵ�һ�룬Ĭ��ֵΪ30�ȣ�Ĭ������£�ԭ��λ��׶�⣬����뾶Ϊ1��
	virtual void SetTess(float fHalfAngle)=0;
	virtual void GetTess(float& fHalfAngle)=0;

	// ����/��ȡԲ׶��ͷ���Ƿ�Ϊ��ƽ״��Ĭ��Ϊtrue����Ϊfalseʱ��ʾͷ��Ϊ��״
	virtual void SetHeadFlat(bool bFlat)=0;
	virtual bool IsHeadFlat()=0;

	/* ����/��ȡԲ׶��Բ�ָܷ�����Ĭ��ֵΪ36 */
	virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;

	/* ����/��ȡԲ׶����׶��ָ�����Ĭ��ֵΪ6 */
	virtual void SetNumBodySplit(int nNumSplit)=0;
	virtual int  GetNumBodySplit()=0;

	/* ����/��ȡԲ׶�Ķ���/����Բ���ָ�����Ĭ��ֵΪ6 */
	virtual void SetNumTopSplit(int nNumSplit)=0;
	virtual int  GetNumTopSplit()=0;

	// ����/��ȡԲ׶�����뾶
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;
	
	// ����/��ȡԲ׶��߶�
	virtual void  SetHeight(float fHeight)=0;
	virtual float GetHeight()=0;

	// ����/��ȡ�Ƿ�����̬ɨ�裨Ĭ��Ϊfalse��
	virtual void EnableScan(bool bEnable)=0;
	virtual bool IsScanEnabled()=0;

	// ����/��ȡ��̬ɨ����ٶȣ���λ����/�룬Ĭ��ֵΪ0.3��
	virtual void  SetScanSpeed(float fSpeed)=0;
	virtual float GetScanSpeed()=0;

	// ����/��ȡɨ������Բ���ĸ�����Ĭ��ֵΪ5��
	virtual void SetNumScanLines(int num)=0;
	virtual int  GetNumScanLines()=0;

	// ����/��ȡɨ���߸߶�ռ������Բ׶�ĸ߶ȱ�����Ĭ��ֵΪ0.2��ֵ��Ϊ[0.0, 1.0]��
	virtual void  SetScanLineHeightRatio(float fRatio)=0;
	virtual float GetScanLineHeightRatio()=0;
};


#endif 
