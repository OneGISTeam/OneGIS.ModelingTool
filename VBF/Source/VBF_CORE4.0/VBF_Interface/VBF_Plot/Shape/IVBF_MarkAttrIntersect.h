//*******************************************************************
// FileName��IVBF_MarkAttrIntersect.h
// Function�����ԣ�ģ�������Ľ��ߣ�Ŀǰֻ��Shape��ģ�Ϳ�����Ӵ�����
// Author:   ��Ө
// Date:     2015-03-20
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_INTERSECT_H__
#define __IVBF_MARK_ATTR_INTERSECT_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <Types/VBF_3DStyles.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkAttrIntersect
// �ӿ����������ԣ�ģ�������Ľ��ߣ�Ŀǰֻ��Shape��ģ�Ϳ�����Ӵ�����
//--------------------------------------------------------------------
class IVBF_MarkAttrIntersect : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrIntersect() {}

	// ����/��ȡ�Ƿ���������α��ֵ��潻�ߣ�Ĭ��ֵΪfalse���ö���λ�Ӱ������ٶȣ�
	virtual void SetUsePolygon(bool bPolygon)=0;
	virtual bool IsPolygonUsed()=0;

	// ����/��ȡ�Ƿ�ֻ��������ˮ׼�棨����ƽ�棬�߳�Ϊ0���Ľ��㣬Ĭ��ֵΪfalse
	//������һ�ָ��Լ��㣬������������Dem�߳�ֵ��Ϊ0ʱ��������Ϊtrue���Ա���߼����ٶȣ�
	virtual void SetOnlyOnGeoid(bool bOnGeoid)=0;
	virtual bool IsOnlyOnGeoid()=0;

	// ����/��ȡ֡������������֡����һ�ν��ߣ����⽻������������Ĭ��ֵΪ2��
	virtual void SetNumFrameInterval(int num)=0;
	virtual int  GetNumFrameInterval()=0;

	// ����/��ȡ�Ƿ������潻�ߵ���Ȳ��ԣ�Ĭ��Ϊfalse���Ա���z-buffer�������⣩
	virtual void EnableLineDepthTest(bool bEnable)=0;
	virtual bool IsLineDepthTestEnabled()=0;

	// ����/��ȡ���潻�ߵĸ߶ȵ���ֵ��Ĭ�ϵ���ֵΪ0.1�ף��Ա���z-buffer�������⣩
	virtual void  SetLineHeightAdjust(float fHeightAdjust)=0;
	virtual float GetLineHeightAdjust()=0;

	// ����/��ȡ����潻�ߵ���ʽ
	virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;

	// ����/��ȡ���潻�߶���ε������ʽ
	virtual void                      SetPolygonStyle(const VBF_POLYGON3DSTYLE& style)=0;
	virtual const VBF_POLYGON3DSTYLE& GetPolygonStyle()=0;

	// ��ʼ/�������������Ľ���
	virtual void BeginCal()=0;
	virtual void EndCal()=0;

	// ������н���
	virtual void Clear()=0;
};


#endif 
