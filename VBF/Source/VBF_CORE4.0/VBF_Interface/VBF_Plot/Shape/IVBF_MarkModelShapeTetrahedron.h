//*******************************************************************
// FileName：IVBF_MarkModelShapeTetrahedron.h
// Function：军标实体模型：四面体
// Author:   杜莹
// Date:     2013-10-15
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_TETRAHEDRON_H__
#define __IVBF_MARK_MODEL_SHAPE_TETRAHEDRON_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_TETRAHEDRON_PART
// 枚举描述：四面体的各个部分
//--------------------------------------------------------------------
enum EVBF_TETRAHEDRON_PART
{
	VBF_TETRAHEDRON_PART_BODY	= 0,	// 主体
	VBF_TETRAHEDRON_PART_COUNT			// 总数
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeTetrahedron
// 接口描述：四面体（默认情况下：原点位于四面体的几何中心，与4个顶点的距离均为1.0）
//--------------------------------------------------------------------
class IVBF_MarkModelShapeTetrahedron : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeTetrahedron() {}
};



#endif 
