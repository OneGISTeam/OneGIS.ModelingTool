//*******************************************************************
// FileName��IVBF_MarkModelShapeCube.h
// Function������ʵ��ģ�ͣ�������
// Author:   ��Ө
// Date:     2013-10-12
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_CUBE_H__
#define __IVBF_MARK_MODEL_SHAPE_CUBE_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShapeCuboid.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeCube
// �ӿ�������������
//--------------------------------------------------------------------
class IVBF_MarkModelShapeCube : public IVBF_MarkModelShapeCuboid
{
public:
	virtual ~IVBF_MarkModelShapeCube() {}

public:

    // ����/��ȡ������ı߳�����ʱIVBF_MarkModelShapeCuboid::SetTess()����ʧЧ��
	// ��Ĭ������£�ԭ��λ�������弸�����ģ��߳�Ϊ1��
	virtual void  SetSize(float fSize)=0;
	virtual float GetSize()=0;
};


#endif 
