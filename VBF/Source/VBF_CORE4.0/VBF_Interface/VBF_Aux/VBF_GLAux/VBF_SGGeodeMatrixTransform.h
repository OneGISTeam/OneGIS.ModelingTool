//**********************************************************************************
// FileName：VBF_SGGeodeMatrixTransform.h
// Function：矩阵变换叶节点，改编自osg::Billboard，可完成模型坐标系下的矩阵变换功能
// Author:   杜莹
// Date:     2015-11-29
//**********************************************************************************

#ifndef __VBF_SG_GEODE_MATRIX_TRANSFORM_H__
#define __VBF_SG_GEODE_MATRIX_TRANSFORM_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformImpl.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGeometryBillboard.h>


class VBF_GLAUX_EXPORT CVBF_SGGeodeMatrixTransform : public osg::Billboard
{
private:
    typedef osg::Billboard BaseClass;

public:
    CVBF_SGGeodeMatrixTransform();
    CVBF_SGGeodeMatrixTransform(const CVBF_SGGeodeMatrixTransform&, const CopyOp& copyop=CopyOp::SHALLOW_COPY) {}

    META_Node(VBF, CVBF_SGGeodeMatrixTransform)

    // 设置/获取变换矩阵
    void setMatrix(const osg::Matrix& mat) { m_matrix = mat; dirtyBound(); }
    const osg::Matrix& getMatrix() const { return m_matrix; }

    // 重载函数，计算某个Drawable的布告牌矩阵
    virtual bool computeMatrix(Matrix& modelview, const Vec3& eye_local, const Vec3& pos_local) const;


protected:
    osg::Matrix     m_matrix;
};



#endif
