//*******************************************************************
// FileName：IVBF_MarkModelTinPoly.h
// Function：实体模型接口：使用不规则三角网的几何体，面状定位
//           也即：PrimitiveSetMode=GL_TRIANGLES的几何体
// Author:   杜莹
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

    // 添加一组三角网（即AddPrimitiveSetIndexed()函数的特化，nMode=GL_TRIANGLES）
    // 参数：vIndices -- 参与该组图元的顶点的索引号
    virtual void AddTriangles(const std::vector<unsigned int>& vIndices)=0;
};

#endif 
