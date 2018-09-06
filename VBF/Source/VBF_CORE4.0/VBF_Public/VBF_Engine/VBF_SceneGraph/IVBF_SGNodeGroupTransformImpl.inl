
using namespace osg;

template<class T>
IVBF_SGNodeGroupTransformImpl<T>::IVBF_SGNodeGroupTransformImpl()
{
	T::m_dwTypeID = 0x11010000; //类型标识

    _referenceFrame = T::RELATIVE_RF;
}

template<class T>
IVBF_SGNodeGroupTransformImpl<T>::IVBF_SGNodeGroupTransformImpl(const IVBF_SGNodeGroupTransformImpl& transform,const CopyOp& copyop):
    IVBF_SGNodeGroupImpl<T>(transform,copyop),
    _referenceFrame(transform._referenceFrame)
{   
	T::m_dwTypeID = 0x11010000; //类型标识
}

template<class T>
IVBF_SGNodeGroupTransformImpl<T>::~IVBF_SGNodeGroupTransformImpl()
{
}

template<class T>
void IVBF_SGNodeGroupTransformImpl<T>::setReferenceFrame(IVBF_SGNodeGroupTransform::ReferenceFrame rf)
{
    if (_referenceFrame == rf) return;
    
    _referenceFrame = rf;
    
    // switch off culling if transform is absolute.
    _Base::setCullingActive(_referenceFrame==T::RELATIVE_RF);
}

template<class T>
BoundingSphere IVBF_SGNodeGroupTransformImpl<T>::computeBound() const
{
    BoundingSphere bsphere = _Base::computeBound();
    if (!bsphere.valid()) return bsphere;
    
    // note, NULL pointer for NodeVisitor, so compute's need
    // to handle this case gracefully, normally this should not be a problem.
    Matrix l2w;

    computeLocalToWorldMatrix(l2w,NULL);

    osg::BoundingSphere::vec_type xdash = bsphere._center;
    xdash.x() += bsphere._radius;
    xdash = xdash*l2w;

    osg::BoundingSphere::vec_type ydash = bsphere._center;
    ydash.y() += bsphere._radius;
    ydash = ydash*l2w;

    osg::BoundingSphere::vec_type zdash = bsphere._center;
    zdash.z() += bsphere._radius;
    zdash = zdash*l2w;

    bsphere._center = bsphere._center*l2w;

    xdash -= bsphere._center;
    osg::BoundingSphere::value_type len_xdash = xdash.length();

    ydash -= bsphere._center;
    osg::BoundingSphere::value_type len_ydash = ydash.length();

    zdash -= bsphere._center;
    osg::BoundingSphere::value_type len_zdash = zdash.length();

    bsphere._radius = len_xdash;
    if (bsphere._radius<len_ydash) bsphere._radius = len_ydash;
    if (bsphere._radius<len_zdash) bsphere._radius = len_zdash;

    return bsphere;

}
