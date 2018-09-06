#ifndef __VBF_MARK_MODEL_NOT_POINT_IMPL_H__
#define __VBF_MARK_MODEL_NOT_POINT_IMPL_H__


#include <VBF_Plot/IVBF_MarkModelNotPoint.h>
#include <VBF_Plot/VBF_MarkModelImpl.h>
#include <VBF_Plot/JB/VBF_3DPlotInnerDataTypes_JB.h>
#include <VBF_Common/VBF_GeomMath/VBF_GeomMath.h>


//=======================================================================================
// ����ģ���ࣺCVBF_MarkModelNotPointImpl
// ģ�����������ǵ�״ʵ��ģ�͵�ʵ��
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

    // ����/��ȡ���Ƶ�ĵ������꣬���ڱ༭
    virtual void SetCtrlPointsGeo(const std::vector<osg::Vec3d>& vPointsGeo)
    {
        m_vCtrlPointsGeo = vPointsGeo;
        this->DirtyModel();
    }
    virtual std::vector<osg::Vec3d>& GetCtrlPointsGeo() { return m_vCtrlPointsGeo; }

    //������Ҫ��������߶ȵ�ģ����˵����Ҫ����ӿ�
    virtual void   setHeight(double dHeight);
    virtual double getHeight() { return m_dHeight; }
    virtual bool   IsSameHeight() { return true; }

    // ���ȫ�ֱ༭�Ŀ��Ƶ㣨��γ�����꣩
    virtual osg::Vec3d GetLocationGeoPoint();

	// ִ��json�ű�
	virtual void ExecuteScript(const CVBF_Config& conf);

protected:
	bool CreateContours();

protected:
    double						m_dHeight; // �߶�
    std::vector<osg::Vec3d>		m_vCtrlPointsGeo;// ���Ƶ�ĵ�������

    float						m_fBufferDist; // �����߿��
    bool						m_bContourInit;

    std::vector< ref_ptr<VBF_JBCONTOUR> >	m_vContours;		// ���������е�ͼԪ��ϣ������ÿ�ȣ��������
    std::vector< ref_ptr<CVBF_JbPolygon> >	m_vFillPolygons;	// ��������Ҫ���ͼԪ��ԭʼ�������ݣ��������ж������Ƿ����
    std::vector<CVBF_GeosShape>             m_vShapeOrigin;		// ���������е�ͼԪ��ԭʼ��������
};

//-----------------------------------------------------------------------------
// ������CVBF_MarkModelNotPointImpl()
// ���������캯��
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelNotPointImpl<T>::CVBF_MarkModelNotPointImpl(const std::string& strMarkID)
    : CVBF_MarkModelImpl<T>(strMarkID)
{
    m_bContourInit = false;
    m_fBufferDist  = 0.3;		// ������
}

//-----------------------------------------------------------------------------
// ������~CVBF_MarkModelNotPointImpl()
// ��������������
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

    // ʹģ�ͽڵ����Ⱦ״̬ʧЧ
    this->DirtyModel();
    this->DirtyStateSet();

    m_bContourInit = true;
    return true;
}

//----------------------------------------------------------------------------
// ������ExecuteScript()
// ������ִ��json�ű�
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelNotPointImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
	BaseClass::ExecuteScript(conf);

	// ��ȡ�����Ƶ�ĵ������꣬���ڱ༭
	const CVBF_Config& confPointsGeo = conf.child("CtrlPointsGeo");
	if( !confPointsGeo.isEmpty() )
	{
		std::vector<osg::Vec3d> vPointsGeo = GetCtrlPointsGeo();
		::VBF_ReadFromJson(confPointsGeo, vPointsGeo);
		SetCtrlPointsGeo(vPointsGeo);
	}

    // ��ȡ������߶�
	double dHeight = getHeight();
	if( conf.getIfSet("Height", dHeight) )
	{
		setHeight(dHeight); 
	}
}

#endif 
