//*******************************************************************
// FileName��VBF_MarkModelShapeArc.h
// Function��ʵ��ģ�ͣ���ά����ά�ռ��еĻ��Σ����̰������ʱΪԲ���Σ�
// Author:   ��Ө
// Date:     2017-08-04
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_ARC_H__
#define __IVBF_MARK_MODEL_SHAPE_ARC_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_ARC_PART
// ö�����������εĸ�������
//--------------------------------------------------------------------
enum EVBF_ARC_PART
{
    VBF_ARC_PART_LINE			= 0,	// ��
    VBF_ARC_PART_FILL			= 1,	// ��
    VBF_ARC_PART_COUNT					// ����
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeArc2D
// �ӿ���������ά�ռ��еĻ���
//--------------------------------------------------------------------
class IVBF_MarkModelShapeArc2D : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeArc2D() {}

	// ����/��ȡ����ԭ���Ƿ�λ����Ļ���Ͻǣ�Ĭ��Ϊtrue��
	virtual void SetOriginTopLeft(bool bTopLeft)=0;
	virtual bool IsOriginTopLeft()=0;

	// ����/��ȡ���ε�Բ�����꣨���ӿ��е����꣩
	virtual void			  SetCenter(const osg::Vec3f& vPos)=0;
	virtual const osg::Vec3f& GetCenter()=0;
	
    // ����/��ȡ���εĳ��̰��ᣬ�������ʱΪԲ����λ�����أ�
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;

	// ����/��ȡ���ε���ʼ�Ǻ���ֹ�ǣ���λ���Ƕȣ�
    // ������fAngleStart, fAngleEnd -- ��ʼ����ֹ�Ƕȣ�����������ļнǣ���λ���Ƕȣ�
    virtual void SetTess(float fAngleStart, float fAngleEnd)=0;
    virtual void GetTess(float& fAngleStart, float& fAngleEnd)=0;

	// ����/��ȡ���ηָ�����Ĭ��ֵΪ36
    virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeArc3D
// �ӿ���������ά�ռ��еĻ���
//--------------------------------------------------------------------
class IVBF_MarkModelShapeArc3D : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeArc3D() {}
	
    // ���û��εĳ��̰��ᣬ�������ʱΪԲ����λ���ף�
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;

	// ����/��ȡ���ε���ʼ�Ǻ���ֹ�ǣ���λ���Ƕȣ�
    // ������fAngleStart, fAngleEnd -- ��ʼ����ֹ�Ƕȣ�����������ļнǣ���λ���Ƕȣ�
    virtual void SetTess(float fAngleStart, float fAngleEnd)=0;
    virtual void GetTess(float& fAngleStart, float& fAngleEnd)=0;

	// ����/��ȡ���ηָ�����Ĭ��ֵΪ36
    virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;
};


#endif 
