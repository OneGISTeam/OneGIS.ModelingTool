//*******************************************************************
// FileName：VBF_GridMapping.h
// Function：矩形网格的映射
// Author:   杜莹
// Date:     2017-04-01
//*******************************************************************

#ifndef __VBF_GRID_MAPPING_H__
#define __VBF_GRID_MAPPING_H__


#include <VBF_Base/VBF_Referenced.h>
#include <Types/VBF_BoundingBox.h>
#include <float.h>


class CVBF_GridMapping : public ::CVBF_Referenced
{
public:
    CVBF_GridMapping()
    {
        SetMesh(0, 0);
        SetDomain(0, 0, 0, 0);
        SetBoundingBox( osg::BoundingBoxd(-DBL_MAX, -DBL_MAX, -DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX) );
    }

    virtual ~CVBF_GridMapping()
    {
    }

    // 注意：用户必须调用SetMesh()函数，设置行列数
    virtual void SetMesh(int nNumRows, int nNumCols)   { m_nNumCols = nNumCols; m_nNumRows = nNumRows; }
    virtual void GetMesh(int& nNumRows, int& nNumCols) { nNumCols = m_nNumCols; nNumRows = m_nNumRows; }

    // 注意：用户必须调用SetDomain()函数，设置自变量(u, v)的取值范围
    virtual void SetDomain(double minU, double maxU, double minV, double maxV)
    {
        m_dMinU = minU;
        m_dMaxU = maxU;
        m_dMinV = minV;
        m_dMaxV = maxV;
    }

    // 获取自变量(u, v)的取值范围
    virtual void GetDomain(double& minU, double& maxU, double& minV, double& maxV)
    {
        minU = m_dMinU;
        maxU = m_dMaxU;
        minV = m_dMinV;
        maxV = m_dMaxV;
    }

    // 设置/获取包围盒（由因变量生成）
    virtual void SetBoundingBox(const osg::BoundingBoxd& box)
    {
        m_BoundingBox = box;
    }
    virtual osg::BoundingBoxd GetBoundingBox() { return m_BoundingBox; }


protected:
    osg::BoundingBoxd   m_BoundingBox;
    int                 m_nNumRows;         // 行数
    int                 m_nNumCols;         // 列数
    double              m_dMinU, m_dMaxU;   // 横向的自变量取值范围（列方向）
    double              m_dMinV, m_dMaxV;   // 纵向的自变量取值范围（行方向）
};

#endif



