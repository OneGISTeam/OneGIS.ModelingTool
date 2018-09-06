//**********************************************************************************
// FileName��VBF_SGGeodeMatrixTransform.h
// Function������任Ҷ�ڵ㣬�ı���osg::Billboard�������ģ������ϵ�µľ���任����
// Author:   ��Ө
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

    // ����/��ȡ�任����
    void setMatrix(const osg::Matrix& mat) { m_matrix = mat; dirtyBound(); }
    const osg::Matrix& getMatrix() const { return m_matrix; }

    // ���غ���������ĳ��Drawable�Ĳ����ƾ���
    virtual bool computeMatrix(Matrix& modelview, const Vec3& eye_local, const Vec3& pos_local) const;


protected:
    osg::Matrix     m_matrix;
};



#endif
