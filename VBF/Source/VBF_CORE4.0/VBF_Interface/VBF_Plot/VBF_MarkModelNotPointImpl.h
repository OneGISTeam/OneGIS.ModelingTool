#ifndef __VBF_MARK_MODEL_NOT_POINT_IMPL_H__
#define __VBF_MARK_MODEL_NOT_POINT_IMPL_H__


#include <VBF_Plot/IVBF_MarkModelNotPoint.h>
#include <VBF_Plot/VBF_MarkModelImpl.h>
#include <VBF_Plot/JB/VBF_3DPlotInnerDataTypes_JB.h>
#include <VBF_Common/VBF_GeomMath/VBF_GeomMath.h>


//=======================================================================================
// 定义模板类：CVBF_MarkModelNotPointImpl
// 模板类描述：非点状实体模型的实现
//=======================================================================================
template<class T>
class CVBF_MarkModelNotPointImpl : public CVBF_MarkModelImpl<T>
{
private:
	typedef CVBF_MarkModelImpl<T> BaseClass;

public:	
    CVBF_MarkModelNotPointImpl() {}
    CVBF_MarkModelNotPointImpl(const std::string& strMarkID);
    CVBF_MarkModelNotPointImpl(const CVBF_MarkModelNotPointImpl& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
    virtual ~CVBF_MarkModelNotPointImpl();

    // 设置/获取控制点的地理坐标，用于编辑
    virtual void SetCtrlPointsGeo(const std::vector<osg::Vec3d>& vPointsGeo)
    {
        m_vCtrlPointsGeo = vPointsGeo;
        this->DirtyModel();
    }
    virtual std::vector<osg::Vec3d>& GetCtrlPointsGeo() { return m_vCtrlPointsGeo; }

    //对于需要设置整体高度的模型来说，需要这个接口
    virtual void   setHeight(double dHeight);
    virtual double getHeight() { return m_dHeight; }
    virtual bool   IsSameHeight() { return true; }

    // 获得全局编辑的控制点（经纬度坐标）
    virtual osg::Vec3d GetLocationGeoPoint();

	// 执行json脚本
	virtual void ExecuteScript(const CVBF_Config& conf);

protected:
	bool CreateContours();

protected:
    double						m_dHeight; // 高度
    std::vector<osg::Vec3d>		m_vCtrlPointsGeo;// 控制点的地理坐标

    float						m_fBufferDist; // 军标线宽度
    bool						m_bContourInit;

    std::vector< ref_ptr<VBF_JBCONTOUR> >	m_vContours;		// 符号中所有的图元组合（并设置宽度）后的轮廓
    std::vector< ref_ptr<CVBF_JbPolygon> >	m_vFillPolygons;	// 符号中需要填充图元的原始几何数据，仅用于判断轮廓是否填充
    std::vector<CVBF_GeosShape>             m_vShapeOrigin;		// 符号中所有的图元的原始几何数据
};

//-----------------------------------------------------------------------------
// 函数：CVBF_MarkModelNotPointImpl()
// 描述：构造函数
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelNotPointImpl<T>::CVBF_MarkModelNotPointImpl(const std::string& strMarkID)
    : CVBF_MarkModelImpl<T>(strMarkID)
{
    m_bContourInit = false;
    m_fBufferDist  = 0.3;		// 军标宽度
}

//-----------------------------------------------------------------------------
// 函数：~CVBF_MarkModelNotPointImpl()
// 描述：析构函数
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelNotPointImpl<T>::~CVBF_MarkModelNotPointImpl()
{
}

template<class T>
osg::Vec3d CVBF_MarkModelNotPointImpl<T>::GetLocationGeoPoint()
{
    double minX=0.0, minY=0.0, maxX=0.0, maxY=0.0;
    for (unsigned int i=0;i<m_vCtrlPointsGeo.size();++i)
    {
        if (i==0)
        {
            minX = m_vCtrlPointsGeo[i].x();
            minY = m_vCtrlPointsGeo[i].y();
            maxX = m_vCtrlPointsGeo[i].x();
            maxY = m_vCtrlPointsGeo[i].y();
        }
        else
        {
            minX = min(minX, m_vCtrlPointsGeo[i].x());
            minY = min(minY, m_vCtrlPointsGeo[i].y());
            maxX = max(maxX, m_vCtrlPointsGeo[i].x());
            maxY = max(maxY, m_vCtrlPointsGeo[i].y());
        }
    }
    return osg::Vec3d((minX+maxX)/2, (minY+maxY)/2, m_dHeight);
}
template<class T>
void CVBF_MarkModelNotPointImpl<T>::setHeight( double dHeight )
{
    m_dHeight = dHeight;
    for (unsigned int i=0; i<m_vCtrlPointsGeo.size(); ++i)
    {
        m_vCtrlPointsGeo[i].z() = m_dHeight;
    }

    this->DirtyModel();
}
bool CreateContours(std::vector< ref_ptr<VBF_JBCONTOUR> >& vContours,std::vector<CVBF_GeosShape>& vShapePoints, float fBufferDist,int nEndCapStyle=2);

template<class T>
bool CVBF_MarkModelNotPointImpl<T>::CreateContours()
{
    if(m_vShapeOrigin.size()==0) return false;

    m_vContours.clear();

    ::CreateContours(m_vContours, m_vShapeOrigin, m_fBufferDist, 1);

    // 使模型节点和渲染状态失效
    this->DirtyModel();
    this->DirtyStateSet();

    m_bContourInit = true;
    return true;
}

//----------------------------------------------------------------------------
// 函数：ExecuteScript()
// 描述：执行json脚本
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelNotPointImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
	BaseClass::ExecuteScript(conf);

	// 读取：控制点的地理坐标，用于编辑
	const CVBF_Config& confPointsGeo = conf.child("CtrlPointsGeo");
	if( !confPointsGeo.isEmpty() )
	{
		std::vector<osg::Vec3d> vPointsGeo = GetCtrlPointsGeo();
		::VBF_ReadFromJson(confPointsGeo, vPointsGeo);
		SetCtrlPointsGeo(vPointsGeo);
	}

    // 读取：整体高度
	double dHeight = getHeight();
	if( conf.getIfSet("Height", dHeight) )
	{
		setHeight(dHeight); 
	}
}

#endif 
