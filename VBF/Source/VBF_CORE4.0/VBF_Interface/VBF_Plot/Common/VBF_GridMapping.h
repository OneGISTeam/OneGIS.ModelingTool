//*******************************************************************
// FileName��VBF_GridMapping.h
// Function�����������ӳ��
// Author:   ��Ө
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

    // ע�⣺�û��������SetMesh()����������������
    virtual void SetMesh(int nNumRows, int nNumCols)   { m_nNumCols = nNumCols; m_nNumRows = nNumRows; }
    virtual void GetMesh(int& nNumRows, int& nNumCols) { nNumCols = m_nNumCols; nNumRows = m_nNumRows; }

    // ע�⣺�û��������SetDomain()�����������Ա���(u, v)��ȡֵ��Χ
    virtual void SetDomain(double minU, double maxU, double minV, double maxV)
    {
        m_dMinU = minU;
        m_dMaxU = maxU;
        m_dMinV = minV;
        m_dMaxV = maxV;
    }

    // ��ȡ�Ա���(u, v)��ȡֵ��Χ
    virtual void GetDomain(double& minU, double& maxU, double& minV, double& maxV)
    {
        minU = m_dMinU;
        maxU = m_dMaxU;
        minV = m_dMinV;
        maxV = m_dMaxV;
    }

    // ����/��ȡ��Χ�У�����������ɣ�
    virtual void SetBoundingBox(const osg::BoundingBoxd& box)
    {
        m_BoundingBox = box;
    }
    virtual osg::BoundingBoxd GetBoundingBox() { return m_BoundingBox; }


protected:
    osg::BoundingBoxd   m_BoundingBox;
    int                 m_nNumRows;         // ����
    int                 m_nNumCols;         // ����
    double              m_dMinU, m_dMaxU;   // ������Ա���ȡֵ��Χ���з���
    double              m_dMinV, m_dMaxV;   // ������Ա���ȡֵ��Χ���з���
};

#endif



