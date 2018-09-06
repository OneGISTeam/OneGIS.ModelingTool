//*******************************************************************
// FileName��VBF_SurfaceFunction.h
// Function�����溯��
// Author:   ��Ө
// Date:     2017-04-01
//*******************************************************************

#ifndef __VBF_SURFACE_FUNCTION_H__
#define __VBF_SURFACE_FUNCTION_H__


#include <VBF_Plot/Common/VBF_GridMapping.h>


class CVBF_SurfaceFunction : public CVBF_GridMapping
{
public:
    CVBF_SurfaceFunction() : CVBF_GridMapping()
    {
        m_pData =  NULL;
        m_zMin  = -DBL_MAX;
        m_zMax  =  DBL_MAX;
    }

    virtual ~CVBF_SurfaceFunction()
    {
        Release();
    }

    // �ͷ��ڴ�
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

    // �û��������ظú���������z=f(x, y)֮��ĺ�����ϵ
    virtual double operator()(double x, double y)=0;

    // ���غ���
    virtual void SetMesh(int nNumRows, int nNumCols)
    {
        // ע�⣺���ͷ��ϴε�����
        Release();
        CVBF_GridMapping::SetMesh(nNumRows, nNumCols);
    }

    void SetMinZ(double val) { m_zMin = val; }
    void SetMaxZ(double val) { m_zMax = val; }

    // ע�⣺�û��������Create()���������ɶ�������
    bool Create()
    {
        if((m_nNumCols<=2) || (m_nNumRows<=2)) return false;

        int row, col;

        // Ϊ�������ݷ����ڴ�
        m_pData = new osg::Vec3d*[m_nNumRows];
        for(row=0; row<m_nNumRows; row++)
        {
            m_pData[row] = new osg::Vec3d[m_nNumCols];
        }

        double dx = (m_dMaxU - m_dMinU) / (m_nNumCols - 1);
        double dy = (m_dMaxV - m_dMinV) / (m_nNumRows - 1);

        // ����ʵ�ʵİ�Χ��
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
                osg::Vec3d& data = m_pData[row][col];

                data.x() = m_dMinU + col*dx;
                data.y() = m_dMinV + row*dy;
                data.z() = operator()(data.x(), data.y());

                // ��zֵ�޶����û�ָ���ķ�Χ��
                if(data.z() < m_zMin)      data.z() = m_zMin;
                else if(data.z() > m_zMax) data.z() = m_zMax;

                // ����ʵ�ʵİ�Χ��
                if(data.x() < xMin) xMin = data.x();
                if(data.x() > xMax) xMax = data.x();
                if(data.y() < yMin) yMin = data.y();
                if(data.y() > yMax) yMax = data.y();
                if(data.z() < zMin) zMin = data.z();
                if(data.z() > zMax) zMax = data.z();
            }

            // ��¼ʵ�ʵİ�Χ��
            m_BoundingBox.set(xMin, yMin, zMin, xMax, yMax, zMax);
        }

        return true;
    }

    // ��ȡ��������
    osg::Vec3d** GetData() { return m_pData; }

protected:
    osg::Vec3d**  m_pData;  // �������꣬��������
    double        m_zMin, m_zMax;
};

#endif
