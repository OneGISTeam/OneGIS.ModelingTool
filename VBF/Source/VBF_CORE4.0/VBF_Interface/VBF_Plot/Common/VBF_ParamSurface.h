//*******************************************************************
// FileName：VBF_ParamSurface.h
// Function：参数化的曲面，如圆锥、圆环等
// Author:   杜莹
// Date:     2017-04-11
//*******************************************************************

#ifndef __VBF_PARAM_SURFACE_H__
#define __VBF_PARAM_SURFACE_H__


#include <VBF_Plot/Common/VBF_GridMapping.h>


//-------------------------------------------------------------------
// 定义类：CVBF_ParamSurface
// 类描述：所有参数曲面的基类
//-------------------------------------------------------------------
class CVBF_ParamSurface : public CVBF_GridMapping
{
public:
    CVBF_ParamSurface() : CVBF_GridMapping()
    {
        m_pData      = NULL;
        m_bPeriodicU = false;
        m_bPeriodicV = false;
    }

    virtual ~CVBF_ParamSurface()
    {
        Release();
    }

    // 释放内存
    void Release()
    {
        if(m_pData!=NULL)
        {
            for(int row=0; row<m_nNumRows; row++)
            {
                delete[] m_pData[row];
            }
            delete[] m_pData;
            m_pData = NULL;
        }
    }

    // 用户必须重载该函数，建立(x,y,z)=f(u, v)之间的函数关系
    virtual osg::Vec3d operator()(double u, double v) = 0;

    // 重载函数
    virtual void SetMesh(int nNumRows, int nNumCols)
    {
        // 注意：先释放上次的数据
        Release();
        CVBF_GridMapping::SetMesh(nNumRows, nNumCols);
    }

    // 设置横纵方向是否闭合（决定着起点和终点的法线是否一致）
    void SetPeriodic(bool u, bool v) { m_bPeriodicU = u; m_bPeriodicV = v; }

    // 注意：用户必须调用Create()函数，生成顶点坐标
    bool Create()
    {
        if((m_nNumCols<=2) || (m_nNumRows<=2)) return false;

        int row, col;

        // 为顶点数据分配内存
        m_pData = new osg::Vec3d*[m_nNumRows];
        for(row=0; row<m_nNumRows; row++)
        {
            m_pData[row] = new osg::Vec3d[m_nNumCols];
        }

        // 自变量步长
        double du = (m_dMaxU - m_dMinU) / (m_nNumCols - 1);
        double dv = (m_dMaxV - m_dMinV) / (m_nNumRows - 1);

        // 计算实际的包围盒
        double xMin =  DBL_MAX;
        double xMax = -DBL_MAX;
        double yMin =  DBL_MAX;
        double yMax = -DBL_MAX;
        double zMin =  DBL_MAX;
        double zMax = -DBL_MAX;

        for(row=0; row<m_nNumRows; row++)
        {
            for(col=0; col<m_nNumCols; col++)
            {
                // 自变量
                double u = m_dMinU + col*du;
                double v = m_dMinV + row*dv;

                // 因变量
                osg::Vec3d& data = m_pData[row][col];
                data = operator()(u, v);

                // 计算实际的包围盒
                if(data.x() < xMin) xMin = data.x();
                if(data.x() > xMax) xMax = data.x();
                if(data.y() < yMin) yMin = data.y();
                if(data.y() > yMax) yMax = data.y();
                if(data.z() < zMin) zMin = data.z();
                if(data.z() > zMax) zMax = data.z();
            }
        }

        // 记录实际的包围盒
        m_BoundingBox.set(xMin, yMin, zMin, xMax, yMax, zMax);

        return true;
    }

    // 获取顶点数据
    osg::Vec3d** GetData() { return m_pData; }

protected:
    osg::Vec3d**    m_pData;            // 顶点坐标，行序优先
    bool            m_bPeriodicU;       // 横方向是否闭合（决定着起点和终点的法线是否一致）
    bool            m_bPeriodicV;       // 纵方向是否闭合（决定着起点和终点的法线是否一致）
};


#endif
