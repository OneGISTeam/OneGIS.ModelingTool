//*******************************************************************
// FileName��IVBF_MarkModelShapeTetrahedron.h
// Function������ʵ��ģ�ͣ�������
// Author:   ��Ө
// Date:     2013-10-15
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_TETRAHEDRON_H__
#define __IVBF_MARK_MODEL_SHAPE_TETRAHEDRON_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_TETRAHEDRON_PART
// ö��������������ĸ�������
//--------------------------------------------------------------------
enum EVBF_TETRAHEDRON_PART
{
	VBF_TETRAHEDRON_PART_BODY	= 0,	// ����
	VBF_TETRAHEDRON_PART_COUNT			// ����
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeTetrahedron
// �ӿ������������壨Ĭ������£�ԭ��λ��������ļ������ģ���4������ľ����Ϊ1.0��
//--------------------------------------------------------------------
class IVBF_MarkModelShapeTetrahedron : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeTetrahedron() {}
};



#endif 
