#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Base/VBF_Notify.h>

#include <stdio.h>
#include <math.h>



using namespace osg;

template<class T>
IVBF_SGNodeGeometryImpl<T>::IVBF_SGNodeGeometryImpl()
{
	T::m_dwTypeID = 0x12000000; //类型标识
}

template<class T>
IVBF_SGNodeGeometryImpl<T>::IVBF_SGNodeGeometryImpl(const IVBF_SGNodeGeometryImpl& geode,const CopyOp& copyop):
    IVBF_SGNodeImpl<T>(geode,copyop)
{
	T::m_dwTypeID = 0x12000000; //类型标识

    for(IVBF_SGNodeGeometry::DrawableList::const_iterator itr=geode._drawables.begin(); itr!=geode._drawables.end(); ++itr)
    {
        Drawable* drawable = (Drawable*)copyop(itr->get());
        if (drawable) addDrawable(drawable);
    }
}

template<class T>
IVBF_SGNodeGeometryImpl<T>::~IVBF_SGNodeGeometryImpl()
{
    // remove reference to this from children's parent lists.
    for(IVBF_SGNodeGeometry::DrawableList::iterator itr=_drawables.begin(); itr!=_drawables.end(); ++itr)
    {
       (*itr)->removeParent(this);
    }
}

template<class T>
bool IVBF_SGNodeGeometryImpl<T>::addDrawable( Drawable *drawable )
{
    if (drawable /* && !containsDrawable(drawable)*/)
    {
        // note ref_ptr<> automatically handles incrementing drawable's reference count.
        _drawables.push_back(drawable);
        
        // register as parent of drawable.
        drawable->addParent(this);
        
        if (drawable->requiresUpdateTraversal())
        {
            _Base::setNumChildrenRequiringUpdateTraversal(_Base::getNumChildrenRequiringUpdateTraversal()+1);
        }
        
        if (drawable->requiresEventTraversal())
        {
            _Base::setNumChildrenRequiringEventTraversal(_Base::getNumChildrenRequiringEventTraversal()+1);
        }

        _Base::dirtyBound();
        
        return true;
    }
    else return false;
}


template<class T>
bool IVBF_SGNodeGeometryImpl<T>::removeDrawable( Drawable *drawable )
{
    return removeDrawables(getDrawableIndex(drawable),1);
}

template<class T>
bool IVBF_SGNodeGeometryImpl<T>::removeDrawables(unsigned int pos,unsigned int numDrawablesToRemove)
{
    if (pos<_drawables.size() && numDrawablesToRemove>0)
    {
        unsigned int endOfRemoveRange = pos+numDrawablesToRemove;
        if (endOfRemoveRange>_drawables.size())
        {
            OSG_DEBUG<<"Warning: IVBF_SGNodeGeometryImpl::removeDrawable(i,numDrawablesToRemove) has been passed an excessive number"<<std::endl;
            OSG_DEBUG<<"         of drawables to remove, trimming just to end of drawable list."<<std::endl;
            endOfRemoveRange=_drawables.size();
        }

        unsigned int updateCallbackRemoved = 0;
        unsigned int eventCallbackRemoved = 0;
        for(unsigned i=pos;i<endOfRemoveRange;++i)
        {
            // remove this IVBF_SGNodeGeometryImpl from the child parent list.
            _drawables[i]->removeParent(this);
            // update the number of app callbacks removed
            if (_drawables[i]->requiresUpdateTraversal()) ++updateCallbackRemoved;
            if (_drawables[i]->requiresEventTraversal()) ++eventCallbackRemoved;
        }

        _drawables.erase(_drawables.begin()+pos,_drawables.begin()+endOfRemoveRange);

        if (updateCallbackRemoved)
        {
            _Base::setNumChildrenRequiringUpdateTraversal(_Base::getNumChildrenRequiringUpdateTraversal()-updateCallbackRemoved);
        }
        
        if (eventCallbackRemoved)
        {
            _Base::setNumChildrenRequiringEventTraversal(_Base::getNumChildrenRequiringEventTraversal()-eventCallbackRemoved);
        }

        _Base::dirtyBound();
        
        return true;
    }
    else return false;
}

template<class T>
bool IVBF_SGNodeGeometryImpl<T>::replaceDrawable( Drawable *origDrawable, Drawable *newDrawable )
{
    if (newDrawable==NULL || origDrawable==newDrawable) return false;

    unsigned int pos = getDrawableIndex(origDrawable);
    if (pos<_drawables.size())
    {
        return setDrawable(pos,newDrawable);
    }
    return false;
}

template<class T>
bool IVBF_SGNodeGeometryImpl<T>::setDrawable( unsigned  int i, Drawable* newDrawable )
{
    if (i<_drawables.size() && newDrawable)
    {
    
        Drawable* origDrawable = _drawables[i].get();

        int deltaUpdate = 0;
        if (origDrawable->requiresUpdateTraversal()) --deltaUpdate;
        if (newDrawable->requiresUpdateTraversal()) ++deltaUpdate;
        if (deltaUpdate!=0)
        {
            _Base::setNumChildrenRequiringUpdateTraversal(_Base::getNumChildrenRequiringUpdateTraversal()+deltaUpdate);
        }

        int deltaEvent = 0;
        if (origDrawable->requiresEventTraversal()) --deltaEvent;
        if (newDrawable->requiresEventTraversal()) ++deltaEvent;
        if (deltaEvent!=0)
        {
            _Base::setNumChildrenRequiringEventTraversal(_Base::getNumChildrenRequiringEventTraversal()+deltaEvent);
        }


        // remove from origDrawable's parent list.
        origDrawable->removeParent(this);
        
        // note ref_ptr<> automatically handles decrementing origGset's reference count,
        // and incrementing newGset's reference count.
        _drawables[i] = newDrawable;

        // register as parent of child.
        newDrawable->addParent(this);


        _Base::dirtyBound();
        
        return true;
    }
    else return false;

}

template<class T>
BoundingSphere IVBF_SGNodeGeometryImpl<T>::computeBound() const
{
    BoundingSphere bsphere;

    _bbox.init();

    IVBF_SGNodeGeometry::DrawableList::const_iterator itr;
    for(itr=_drawables.begin(); itr!=_drawables.end(); ++itr)
    {
        _bbox.expandBy((*itr)->getBound());
    }

    if (_bbox.valid())
    {
        bsphere.expandBy(_bbox);
    }
    return bsphere;
}

template<class T>
void IVBF_SGNodeGeometryImpl<T>::compileDrawables(RenderInfo& renderInfo)
{
    for(IVBF_SGNodeGeometry::DrawableList::iterator itr = _drawables.begin(); itr!=_drawables.end(); ++itr)
    {
        (*itr)->compileGLObjects(renderInfo);
    }
}

template<class T>
void IVBF_SGNodeGeometryImpl<T>::setThreadSafeRefUnref(bool threadSafe)
{
    IVBF_SGNodeImpl<T>::setThreadSafeRefUnref(threadSafe);
    
    for(IVBF_SGNodeGeometry::DrawableList::const_iterator itr=_drawables.begin(); itr!=_drawables.end(); ++itr)
    {
        (*itr)->setThreadSafeRefUnref(threadSafe);
    }
}

template<class T>
void IVBF_SGNodeGeometryImpl<T>::resizeGLObjectBuffers(unsigned int maxSize)
{
    IVBF_SGNodeImpl<T>::resizeGLObjectBuffers(maxSize);

    for(IVBF_SGNodeGeometry::DrawableList::const_iterator itr=_drawables.begin(); itr!=_drawables.end(); ++itr)
    {
        (*itr)->resizeGLObjectBuffers(maxSize);
    }
}

template<class T>
void IVBF_SGNodeGeometryImpl<T>::releaseGLObjects(osg::State* state) const
{
    IVBF_SGNodeImpl<T>::releaseGLObjects(state);

    for(IVBF_SGNodeGeometry::DrawableList::const_iterator itr=_drawables.begin(); itr!=_drawables.end(); ++itr)
    {
        (*itr)->releaseGLObjects(state);
    }
}
