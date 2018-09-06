//#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLODImpl.h>
#include <VBF_Engine/VBF_SceneGraph/CullStack>

#include <algorithm>

using namespace osg;

template<class T>
IVBF_SGNodeGroupLODImpl<T>::IVBF_SGNodeGroupLODImpl():
    _centerMode(T::USE_BOUNDING_SPHERE_CENTER),
    _radius(-1.0f),
    _rangeMode(T::DISTANCE_FROM_EYE_POINT)
{
	T::m_dwTypeID = 0x110A0000; //类型标识
}

template<class T>
IVBF_SGNodeGroupLODImpl<T>::IVBF_SGNodeGroupLODImpl(const IVBF_SGNodeGroupLODImpl& lod,const CopyOp& copyop):
        IVBF_SGNodeGroupImpl<T>(lod,copyop),
        _centerMode(lod._centerMode),
        _userDefinedCenter(lod._userDefinedCenter),
        _radius(lod._radius),
        _rangeMode(lod._rangeMode),
        _rangeList(lod._rangeList)
{
	T::m_dwTypeID = 0x110A0000; //类型标识
}


template<class T>
void IVBF_SGNodeGroupLODImpl<T>::traverse(NodeVisitor& nv)
{
    switch(nv.getTraversalMode())
    {
        case(NodeVisitor::TRAVERSE_ALL_CHILDREN):
            std::for_each(_Base::_children.begin(),_Base::_children.end(),NodeAcceptOp(nv));
            break;
        case(NodeVisitor::TRAVERSE_ACTIVE_CHILDREN):
        {
            float required_range = 0;
            if (_rangeMode==T::DISTANCE_FROM_EYE_POINT)
            {
                required_range = nv.getDistanceToViewPoint(getCenter(),true);
            }
            else
            {
                osg::CullStack* cullStack = dynamic_cast<osg::CullStack*>(&nv);
                if (cullStack && cullStack->getLODScale())
                {
                    required_range = cullStack->clampedPixelSize(_Base::getBound()) / cullStack->getLODScale();
                }
                else
                {
                    // fallback to selecting the highest res tile by
                    // finding out the max range
                    for(unsigned int i=0;i<_rangeList.size();++i)
                    {
                        required_range = osg::maximum(required_range,_rangeList[i].first);
                    }
                }
            }
            
            unsigned int numChildren = _Base::_children.size();
            if (_rangeList.size()<numChildren) numChildren=_rangeList.size();

            for(unsigned int i=0;i<numChildren;++i)
            {    
                if (_rangeList[i].first<=required_range && required_range<_rangeList[i].second)
                {
                    _Base::_children[i]->accept(nv);
                }
            }
           break;
        }
        default:
            break;
    }
}

template<class T>
BoundingSphere IVBF_SGNodeGroupLODImpl<T>::computeBound() const
{
    if (_centerMode==T::USER_DEFINED_CENTER && _radius>=0.0f)
    {
        return BoundingSphere(_userDefinedCenter,_radius);
    }
    else
    {
        return IVBF_SGNodeGroupImpl<T>::computeBound();
    }
}

template<class T>
bool IVBF_SGNodeGroupLODImpl<T>::addChild( IVBF_SGNode *child )
{
    if (IVBF_SGNodeGroupImpl<T>::addChild(child))
    {

        if (_Base::_children.size()>_rangeList.size())
        {
            float maxRange = !_rangeList.empty() ? _rangeList.back().second : 0.0f;

            _rangeList.resize(_Base::_children.size(),IVBF_SGNodeGroupLOD::MinMaxPair(maxRange,maxRange));
        }

        return true;
    }
    return false;
}


template<class T>
bool IVBF_SGNodeGroupLODImpl<T>::addChild(IVBF_SGNode *child, float min, float max)
{
    if (IVBF_SGNodeGroupImpl<T>::addChild(child))
    {
        if (_Base::_children.size()>_rangeList.size()) _rangeList.resize(_Base::_children.size(),IVBF_SGNodeGroupLOD::MinMaxPair(min,min));
        _rangeList[_Base::_children.size()-1].first = min;
        _rangeList[_Base::_children.size()-1].second = max;
        return true;
    }
    return false;
}

template<class T>
bool IVBF_SGNodeGroupLODImpl<T>::removeChildren( unsigned int pos,unsigned int numChildrenToRemove)
{
    if (pos<_rangeList.size()) _rangeList.erase(_rangeList.begin()+pos, osg::minimum(_rangeList.begin()+(pos+numChildrenToRemove), _rangeList.end()) );

    return IVBF_SGNodeGroupImpl<T>::removeChildren(pos,numChildrenToRemove);
}

template<class T>
void IVBF_SGNodeGroupLODImpl<T>::setRange(unsigned int childNo, float min,float max)
{
    if (childNo>=_rangeList.size()) _rangeList.resize(childNo+1,IVBF_SGNodeGroupLOD::MinMaxPair(min,min));
    _rangeList[childNo].first=min;
    _rangeList[childNo].second=max;
}
