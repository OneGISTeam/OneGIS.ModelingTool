//*******************************************************************
// FileName��VBF_MarkModelShapeEllipse.h
// Function��ʵ��ģ�ͣ���ά����ά�ռ��е���Բ�����̰������ʱΪԲ��
// Author:   ��Ө
// Date:     2017-08-04
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_ELLIPSE_H__
#define __IVBF_MARK_MODEL_SHAPE_ELLIPSE_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_ELLIPSE_PART
// ö����������Բ�ĸ�������
//--------------------------------------------------------------------
enum EVBF_ELLIPSE_PART
{
    VBF_ELLIPSE_PART_LINE			= 0,	// ��
    VBF_ELLIPSE_PART_FILL			= 1,	// ��
    VBF_ELLIPSE_PART_COUNT					// ����
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeEllipse2D
// �ӿ���������ά�ռ��е���Բ
//--------------------------------------------------------------------
class IVBF_MarkModelShapeEllipse2D : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeEllipse2D() {}

	// ����/��ȡ����ԭ���Ƿ�λ����Ļ���Ͻǣ�Ĭ��Ϊtrue��
	virtual void SetOriginTopLeft(bool bTopLeft)=0;
	virtual bool IsOriginTopLeft()=0;

	// ����/��ȡ��Բ��Բ�����꣨���ӿ��е����꣩
	virtual void			  SetCenter(const osg::Vec3f& vPos)=0;
	virtual const osg::Vec3f& GetCenter()=0;
	
    // ����/��ȡ��Բ�ĳ��̰��ᣬ�������ʱΪԲ����λ�����أ�
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;

	// ����/��ȡԲ�ָܷ�����Ĭ��ֵΪ36
    virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeEllipse3D
// �ӿ���������ά�ռ��е���Բ
//--------------------------------------------------------------------
class IVBF_MarkModelShapeEllipse3D : public IVBF_MarkModelShape
{
public:
    virtual ~IVBF_MarkModelShapeEllipse3D() {}
	
    // ������Բ�ĳ��̰��ᣬ�������ʱΪԲ����λ���ף�
	virtual void SetRadius(float fRadiusX, float fRadiusY)=0;
	virtual void GetRadius(float& fRadiusX, float& fRadiusY)=0;

	// ����/��ȡԲ�ָܷ�����Ĭ��ֵΪ36
    virtual void SetNumSplit(int nNumSplit)=0;
	virtual int  GetNumSplit()=0;
};


#endif 
