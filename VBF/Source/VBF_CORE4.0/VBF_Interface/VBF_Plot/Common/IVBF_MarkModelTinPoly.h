//*******************************************************************
// FileName��IVBF_MarkModelTinPoly.h
// Function��ʵ��ģ�ͽӿڣ�ʹ�ò������������ļ����壬��״��λ
//           Ҳ����PrimitiveSetMode=GL_TRIANGLES�ļ�����
// Author:   ��Ө
// Date:     2014-09-09
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_TINPOLY_H__
#define __IVBF_MARK_MODEL_TINPOLY_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Common/IVBF_MarkModelGeometry.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec3d>
#include <Types/Vec4f>
#include <vector>



class IVBF_MarkModelTinPoly : public IVBF_MarkModelGeometry
{
public:
    virtual ~IVBF_MarkModelTinPoly() {}

    // ���һ������������AddPrimitiveSetIndexed()�������ػ���nMode=GL_TRIANGLES��
    // ������vIndices -- �������ͼԪ�Ķ����������
    virtual void AddTriangles(const std::vector<unsigned int>& vIndices)=0;
};

#endif 
