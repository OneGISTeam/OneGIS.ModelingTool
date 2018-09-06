#ifndef __DTIS_TEMPLATE_H__
#define __DTIS_TEMPLATE_H__


#include <vector>
#include <math.h>


template <class TYPE> 
class CVBF_Array:public std::vector<TYPE>
{	
    typedef std::vector<TYPE>    _MyBase;
    typedef typename _MyBase::iterator  iterator_vector;
public:
	CVBF_Array() {}

public:
    CVBF_Array( const CVBF_Array<TYPE>& a ) ;
     CVBF_Array<TYPE>& operator=( const CVBF_Array<TYPE>& a ) ;


    int GetSize()const { return _MyBase::size(); }
    void SetSize(int nSize) { _MyBase::resize(nSize); }
    void Set( const CVBF_Array<TYPE>& a ) ;
	void Invert();
    void Append(CVBF_Array<TYPE>& a);
    void AppendEx(CVBF_Array<TYPE>& a,bool bInverted=false);
    TYPE GetAt(int idx)const { return (*this)[idx];}
    void SetAt(int idx,TYPE t) { (*this)[idx] = t;}
    void RemoveAll() { _MyBase::clear(); }
    void Add(const TYPE& t) { _MyBase::push_back(t);}
    void RemoveAt(int idx) { _MyBase::erase(_MyBase::begin() + idx);}
    void RemoveAt(int idx,int num) { _MyBase::erase(_MyBase::begin() + idx,_MyBase::begin() + idx+num);}

    TYPE* GetData() { return &((*this)[0]); }

    void InsertAt(int idx, TYPE t)
    {
        _MyBase::insert(_MyBase::begin() + idx,t);
    }

};


template <class TYPE> 
CVBF_Array<TYPE>::CVBF_Array( const CVBF_Array<TYPE>& a )
{
	Set( a ) ;
}

template <class TYPE> 
CVBF_Array<TYPE>& CVBF_Array<TYPE>::operator=( const CVBF_Array<TYPE>& a )
{
    Set( a ) ;
	return *this ;
}


template <class TYPE> 
void CVBF_Array<TYPE>::Set( const CVBF_Array<TYPE>& a )
{
    RemoveAll() ;
	
    int nSize = a.GetSize() ;
    this->reserve(nSize);

	for( int i=0;i<nSize;i++ )
	{
        Add(a[i]);
	}
}

template <class TYPE> 
void CVBF_Array<TYPE>::Invert()
{
	TYPE t;
	int num = GetSize();
	for( int k=0; k<num/2; k++ )
	{	
        t = GetAt( k );
        SetAt( k, GetAt(num-1-k) );
		SetAt( num-1-k, t );
	}

}
template <class TYPE> 
void CVBF_Array<TYPE>::Append(CVBF_Array<TYPE>& a)
{
	int nCount = a.GetSize() ;
    for(int i=0; i<nCount; i++)
    {
        Add(a[i]) ;
    }

}
template <class TYPE>
void CVBF_Array<TYPE>::AppendEx(CVBF_Array<TYPE>& a,bool bInverted)
{
    int nCount = a.GetSize() ;
    if( bInverted )
    {
        for(int i=nCount-1 ; i>=0 ; i--)
        {
            Add(a[i]) ;
        }
    }
    else
    {
        for(int i=0; i<nCount; i++)
        {
            Add(a[i]) ;
        }
    }
}

#endif



