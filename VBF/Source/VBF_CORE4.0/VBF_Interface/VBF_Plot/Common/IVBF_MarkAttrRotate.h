//*******************************************************************
// FileName��IVBF_MarkAttrRotate.h
// Function��ģ�����Խӿڣ�������ת
// Author:
// Date:     2013-10-22
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_ROTATE_H__
#define __IVBF_MARK_ATTR_ROTATE_H__


#include <VBF_Plot/IVBF_MarkAttr.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_ROTATE_TYPE
// ö��������������ת�ķ�ʽ
//--------------------------------------------------------------------
enum EVBF_ROTATE_TYPE
{
	VBF_ROTATE_TYPE_CIRCLE		= 0,	// ѭ��
	VBF_ROTATE_TYPE_SWING		= 1,	// �ڶ�
	VBF_ROTATE_TYPE_POSITIVE	= 2,	// ������ת������
	VBF_ROTATE_TYPE_NEGATIVE	= 3,	// ������ת������
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkAttrRotate
// �ӿ�������ģ�����ԽӿڵĻ��ࣺ��ĳ������ת
//--------------------------------------------------------------------
class IVBF_MarkAttrRotate : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrRotate() {}

	// ����/��ȡ��ת��ʽ
	virtual void			 SetRotateType(EVBF_ROTATE_TYPE nType)=0;
	virtual EVBF_ROTATE_TYPE GetRotateType()=0;

	// ����/��ȡ��ת�ĽǶȷ�Χ
	virtual void SetAngleRange(float fAngleMin, float fAngleMax)=0;
	virtual void GetAngleRange(float& fAngleMin, float& fAngleMax)=0;
	
	// ����/��ȡ��ת���ٶȣ���λ����/�룩
	virtual void  SetSpeedAnglePerSecond(float fSpeed)=0;
	virtual float GetSpeedAnglePerSecond()=0;

	// ����/��ȡ��ÿ��λ��ͣ����֡����Ĭ��ֵΪ0������ͣ����
	virtual void SetNumPausalFrames(int num)=0;
	virtual int  GetNumPausalFrames()=0;

	// ����/��ȡ��ǰ����ת��
	virtual void  SetAngleCurr(float fAngle)=0;
	virtual float GetAngleCurr()=0;
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkAttrRotateX
// �ӿ�������ģ�����Խӿڣ���X����ת
//--------------------------------------------------------------------
class IVBF_MarkAttrRotateX : public IVBF_MarkAttrRotate
{
public:
	virtual ~IVBF_MarkAttrRotateX() {}
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkAttrRotateY
// �ӿ�������ģ�����ԣ���Y����ת
//--------------------------------------------------------------------
class IVBF_MarkAttrRotateY : public IVBF_MarkAttrRotate
{
public:
	virtual ~IVBF_MarkAttrRotateY() {}
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkAttrRotateZ
// �ӿ�������ģ�����ԣ���Z����ת
//--------------------------------------------------------------------
class IVBF_MarkAttrRotateZ : public IVBF_MarkAttrRotate
{
public:
	virtual ~IVBF_MarkAttrRotateZ() {}
};

#endif 
