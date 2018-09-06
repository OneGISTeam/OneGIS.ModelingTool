//*******************************************************************
// FileName��VBF_ParamSurface.h
// Function�������������棬��Բ׶��Բ����
// Author:   ��Ө
// Date:     2017-04-11
//*******************************************************************

#ifndef __VBF_PARAM_SURFACE_H__
#define __VBF_PARAM_SURFACE_H__


#include <VBF_Plot/Common/VBF_GridMapping.h>


//-------------------------------------------------------------------
// �����ࣺCVBF_ParamSurface
// �����������в�������Ļ���
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

    // �û��������ظú���������(x,y,z)=f(u, v)֮��ĺ�����ϵ
    virtual osg::Vec3d operator()(double u, double v) = 0;

    // ���غ���
    virtual void SetMesh(int nNumRows, int nNumCols)
    {
        // ע�⣺���ͷ��ϴε�����
        Release();
        CVBF_GridMapping::SetMesh(nNumRows, nNumCols);
    }

    // ���ú��ݷ����Ƿ�պϣ������������յ�ķ����Ƿ�һ�£�
    void SetPeriodic(bool u, bool v) { m_bPeriodicU = u; m_bPeriodicV = v; }

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

        // �Ա�������
        double du = (m_dMaxU - m_dMinU) / (m_nNumCols - 1);
        double dv = (m_dMaxV - m_dMinV) / (m_nNumRows - 1);

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
                // �Ա���
                double u = m_dMinU + col*du;
                double v = m_dMinV + row*dv;

                // �����
                osg::Vec3d& data = m_pData[row][col];
                data = operator()(u, v);

                // ����ʵ�ʵİ�Χ��
                if(data.x() < xMin) xMin = data.x();
                if(data.x() > xMax) xMax = data.x();
                if(data.y() < yMin) yMin = data.y();
                if(data.y() > yMax) yMax = data.y();
                if(data.z() < zMin) zMin = data.z();
                if(data.z() > zMax) zMax = data.z();
            }
        }

        // ��¼ʵ�ʵİ�Χ��
        m_BoundingBox.set(xMin, yMin, zMin, xMax, yMax, zMax);

        return true;
    }

    // ��ȡ��������
    osg::Vec3d** GetData() { return m_pData; }

protected:
    osg::Vec3d**    m_pData;            // �������꣬��������
    bool            m_bPeriodicU;       // �᷽���Ƿ�պϣ������������յ�ķ����Ƿ�һ�£�
    bool            m_bPeriodicV;       // �ݷ����Ƿ�պϣ������������յ�ķ����Ƿ�һ�£�
};


#endif
