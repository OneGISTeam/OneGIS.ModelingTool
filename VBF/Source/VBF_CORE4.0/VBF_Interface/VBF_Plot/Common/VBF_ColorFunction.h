//*******************************************************************
// FileName：VBF_ColorFunction.h
// Function：颜色函数
// Author:   杜莹
// Date:     2017-04-01
//*******************************************************************

#ifndef __VBF_COLOR_FUNCTION_H__
#define __VBF_COLOR_FUNCTION_H__


#include <VBF_Base/VBF_Referenced.h>
#include <Types/VBF_BoundingBox.h>
#include <Types/Vec4f>
#include <vector>


typedef std::vector<osg::Vec4f>  CVBF_ColorVector;

class CVBF_ColorFunction : public ::CVBF_Referenced
{
public:
    CVBF_ColorFunction()
    {
    }

    virtual ~CVBF_ColorFunction()
    {
    }

    // 用户必须重载该函数，建立color=f(x, y, z)的函数关系
    virtual osg::Vec4f operator()(double x, double y, double z) const = 0;
    virtual osg::Vec4f operator()(const osg::Vec3d& pt) const { return this->operator()(pt.x(), pt.y(), pt.z()); }

    // Should create a color vector usable by ColorLegend. The default implementation returns his argument
    virtual CVBF_ColorVector& CreateVector(CVBF_ColorVector& vec) { return vec; }

    void Destroy() const { delete this;}
};

// 单一颜色函数
class CVBF_ColorFunctionSingle : public CVBF_ColorFunction
{
public:
    CVBF_ColorFunctionSingle(osg::Vec4f color)
                : m_color(color)
    {
    }

    osg::Vec4f operator()(double x, double y, double z) const
    {
        return m_color;
    }

    osg::Vec4f GetColor() { return m_color; }

private:
    osg::Vec4f  m_color;
};

// 标准颜色函数
class CVBF_ColorFunctionStandard : public CVBF_ColorFunction
{
public:
    CVBF_ColorFunctionStandard(int size, double zMin, double zMax)
                : m_zMin(zMin), m_zMax(zMax)
    {
        Reset(size);
    }

    void Reset(int size)
    {
        m_vColors.clear();
        m_vColors.resize(size);

        double dsize = size;

        for(unsigned int i=0; i<size; ++i)
        {
            m_vColors[i].x() = i / dsize;
            m_vColors[i].y() = i / dsize / 4;
            m_vColors[i].z() = 1 - i/dsize;
            m_vColors[i].w() = 1.0;
        }
    }

    /**
        Assigns a new CVBF_ColorVector (Also overwrites the constructors size argument)
    */
    void SetColorVector(const CVBF_ColorVector& cv)
    {
        m_vColors = cv;
    }

    void SetAlpha(float alpha)
    {
        if(alpha<0 || alpha>1) return;

        for(unsigned int i=0; i<m_vColors.size(); i++)
        {
            m_vColors[i].w() = alpha;
        }
    }

    osg::Vec4f operator()(double x, double y, double z) const
    {
        if( (m_zMax-m_zMin)==0 ) return osg::Vec4f(0, 0, 0, 1);

        int index = (int)((m_vColors.size()-1) * (z - m_zMin) / (m_zMax-m_zMin));
        if (index < 0)
            index = 0;
        if ((unsigned int)index > m_vColors.size() - 1)
            index = (int)(m_vColors.size() - 1);

        return m_vColors[index];
    }

    /**
        \brief Creates color vector

        Creates a color vector used by ColorLegend. This is essentially a copy from the internal used vector.
        \return The vector created
    */
    CVBF_ColorVector& CreateVector(CVBF_ColorVector& vec)
    {
        vec = m_vColors;
        return vec;
    }

protected:
    CVBF_ColorVector    m_vColors;
    double              m_zMin, m_zMax;
};

#endif
