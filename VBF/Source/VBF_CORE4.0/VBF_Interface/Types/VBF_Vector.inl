//*******************************************************************
// 文件： VBF_Vector.inl
// 描述： 实现3DMath中使用的基本数据类型：向量
// 作者： 杜莹
// 时间： 2012-11-06
//*******************************************************************

#ifndef __VBF_VECTOR_INL__
#define __VBF_VECTOR_INL__

#include <memory.h>
#include "VBF_Macros.h"

#define VBF_DEBUG  _DEBUG


//--------------------------------------------------------------------------
// 结构体VBFVECTOR2<TYPE>的实现部分
//--------------------------------------------------------------------------
template <class TYPE>
inline VBFVECTOR2<TYPE>::VBFVECTOR2(const TYPE* pd)
{
#ifdef VBF_DEBUG
    if(!pd)  return;
#endif

    x = pd[0];
    y = pd[1];
}

template <class TYPE>
inline VBFVECTOR2<TYPE>::VBFVECTOR2(TYPE dx, TYPE dy)
{

    x = dx;
    y = dy;
}

// 强制转换 (casting)
template <class TYPE>
inline VBFVECTOR2<TYPE>::operator TYPE*()
{
    return (TYPE*) &x;
}

template <class TYPE>
inline VBFVECTOR2<TYPE>::operator const TYPE*() const
{
    return (const TYPE*) &x;
}

// 赋值操作符 (assignment operators)
template <class TYPE>
inline VBFVECTOR2<TYPE>& VBFVECTOR2<TYPE>::operator+=(const VBFVECTOR2<TYPE>& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

template <class TYPE>
inline VBFVECTOR2<TYPE>& VBFVECTOR2<TYPE>::operator-=(const VBFVECTOR2<TYPE>& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

template <class TYPE>
inline VBFVECTOR2<TYPE>& VBFVECTOR2<TYPE>::operator*=(TYPE d)
{
    x *= d;
    y *= d;
    return *this;
}

template <class TYPE>
inline VBFVECTOR2<TYPE>& VBFVECTOR2<TYPE>::operator/=(TYPE d)
{
    TYPE dInv = 1.0 / d;
    x *= dInv;
    y *= dInv;
    return *this;
}

// 一元操作符 (unary operators)
template <class TYPE>
inline VBFVECTOR2<TYPE> VBFVECTOR2<TYPE>::operator+() const
{
    return *this;
}

template <class TYPE>
inline VBFVECTOR2<TYPE> VBFVECTOR2<TYPE>::operator-() const
{
    return VBFVECTOR2<TYPE>(-x, -y);
}

// 二元操作符 (binary operators)
template <class TYPE>
inline VBFVECTOR2<TYPE> VBFVECTOR2<TYPE>::operator+(const VBFVECTOR2<TYPE>& v) const
{
    return VBFVECTOR2<TYPE>(x+v.x, y+v.y);
}

template <class TYPE>
inline VBFVECTOR2<TYPE> VBFVECTOR2<TYPE>::operator-(const VBFVECTOR2<TYPE>& v) const
{
    return VBFVECTOR2<TYPE>(x-v.x, y-v.y);
}

template <class TYPE>
inline VBFVECTOR2<TYPE> VBFVECTOR2<TYPE>::operator*(TYPE d) const
{
    return VBFVECTOR2<TYPE>(x*d, y*d);
}

template <class TYPE>
inline VBFVECTOR2<TYPE> VBFVECTOR2<TYPE>::operator/(TYPE d) const
{
    TYPE dInv = 1.0 / d;
    return VBFVECTOR2<TYPE>(x*dInv, y*dInv);
}

template <class TYPE>
inline VBFVECTOR2<TYPE> operator*(TYPE d, const VBFVECTOR2<TYPE>& v)
{
    return VBFVECTOR2<TYPE>(d*v.x, d*v.y);
}

template <class TYPE>
inline bool VBFVECTOR2<TYPE>::operator==(const VBFVECTOR2<TYPE>& v) const
{
	if( fabs(this->x - v.x) < DBL_ZERO && 
		fabs(this->y - v.y) < DBL_ZERO )
		return true;
	else
		return false;
}

template <class TYPE>
inline bool VBFVECTOR2<TYPE>::operator!=(const VBFVECTOR2<TYPE>& v) const
{
    return !(*this==v);
}

//--------------------------------------------------------------------------
// 结构体VBFVECTOR3<TYPE>的实现部分
//--------------------------------------------------------------------------
template <class TYPE>
inline VBFVECTOR3<TYPE>::VBFVECTOR3(const TYPE* pd)
{
#ifdef VBF_DEBUG
    if(!pd) return;        
#endif

    x = pd[0];
    y = pd[1];
    z = pd[2];
}

template <class TYPE>
inline VBFVECTOR3<TYPE>::VBFVECTOR3(TYPE dx, TYPE dy, TYPE dz)
{
    x = dx;
    y = dy;
    z = dz;
}

// 强制转换 (casting)
template <class TYPE>
inline VBFVECTOR3<TYPE>::operator TYPE*()
{
    return (TYPE*)&x;
}

template <class TYPE>
inline VBFVECTOR3<TYPE>::operator const TYPE*() const
{
    return (const TYPE*)&x;
}

// 赋值操作符 (assignment operators)
template <class TYPE>
inline VBFVECTOR3<TYPE>& VBFVECTOR3<TYPE>::operator+=(const VBFVECTOR3<TYPE>& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

template <class TYPE>
inline VBFVECTOR3<TYPE>& VBFVECTOR3<TYPE>::operator-=(const VBFVECTOR3<TYPE>& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

template <class TYPE>
inline VBFVECTOR3<TYPE>& VBFVECTOR3<TYPE>::operator*=(TYPE d)
{
    x *= d;
    y *= d;
    z *= d;
    return *this;
}

template <class TYPE>
inline VBFVECTOR3<TYPE>& VBFVECTOR3<TYPE>::operator/=(TYPE d)
{
    TYPE dInv = 1.0 / d;
    x *= dInv;
    y *= dInv;
    z *= dInv;
    return *this;
}

// 一元操作符 (unary operators)
template <class TYPE>
inline VBFVECTOR3<TYPE> VBFVECTOR3<TYPE>::operator+() const
{
    return *this;
}

template <class TYPE>
inline VBFVECTOR3<TYPE> VBFVECTOR3<TYPE>::operator-() const
{
    return VBFVECTOR3<TYPE>(-x, -y, -z);
}

// 二元操作符 (binary operators)
template <class TYPE>
inline VBFVECTOR3<TYPE> VBFVECTOR3<TYPE>::operator+(const VBFVECTOR3<TYPE>& v) const
{
    return VBFVECTOR3<TYPE>(x+v.x, y+v.y, z+v.z);
}

template <class TYPE>
inline VBFVECTOR3<TYPE> VBFVECTOR3<TYPE>::operator-(const VBFVECTOR3<TYPE>& v) const
{
    return VBFVECTOR3<TYPE>(x-v.x, y-v.y, z-v.z);
}

template <class TYPE>
inline VBFVECTOR3<TYPE> VBFVECTOR3<TYPE>::operator*(TYPE d) const
{
    return VBFVECTOR3<TYPE>(x*d, y*d, z*d);
}

template <class TYPE>
inline VBFVECTOR3<TYPE> VBFVECTOR3<TYPE>::operator/(TYPE d) const
{
    TYPE dInv = 1.0 / d;
    return VBFVECTOR3<TYPE>(x*dInv, y*dInv, z*dInv);
}

template <class TYPE>
inline VBFVECTOR3<TYPE> operator*(TYPE d, const VBFVECTOR3<TYPE>& v)
{
    return VBFVECTOR3<TYPE>(d*v.x, d*v.y, d*v.z);
}

template <class TYPE>
inline bool VBFVECTOR3<TYPE>::operator==(const VBFVECTOR3<TYPE>& v) const
{
    if( fabs(this->x - v.x) < DBL_ZERO && 
		fabs(this->y - v.y) < DBL_ZERO && 
		fabs(this->z - v.z) < DBL_ZERO )
		return true;
	else
		return false;
}

template <class TYPE>
inline bool VBFVECTOR3<TYPE>::operator!=(const VBFVECTOR3<TYPE>& v) const
{
    return !(*this==v);
}

//--------------------------------------------------------------------------
// 结构体VBFVECTOR4<TYPE>的实现部分
//--------------------------------------------------------------------------
template <class TYPE>
inline VBFVECTOR4<TYPE>::VBFVECTOR4(const TYPE* pd)
{
#ifdef VBF_DEBUG
    if(!pd) return;
#endif

    x = pd[0];
    y = pd[1];
    z = pd[2];
    w = pd[3];
}

template <class TYPE>
inline VBFVECTOR4<TYPE>::VBFVECTOR4(TYPE dx, TYPE dy, TYPE dz, TYPE dw)
{
    x = dx;
    y = dy;
    z = dz;
    w = dw;
}

// 强制转换 (casting)
template <class TYPE>
inline VBFVECTOR4<TYPE>::operator TYPE*()
{
    return (TYPE*)&x;
}

template <class TYPE>
inline VBFVECTOR4<TYPE>::operator const TYPE*() const
{
    return (const TYPE*)&x;
}

// 赋值操作符 (assignment operators)
template <class TYPE>
inline VBFVECTOR4<TYPE>& VBFVECTOR4<TYPE>::operator+=(const VBFVECTOR4<TYPE>& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

template <class TYPE>
inline VBFVECTOR4<TYPE>& VBFVECTOR4<TYPE>::operator-=(const VBFVECTOR4<TYPE>& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

template <class TYPE>
inline VBFVECTOR4<TYPE>& VBFVECTOR4<TYPE>::operator*=(TYPE d)
{
    x *= d;
    y *= d;
    z *= d;
    w *= d;
    return *this;
}

template <class TYPE>
inline VBFVECTOR4<TYPE>& VBFVECTOR4<TYPE>::operator/=(TYPE d)
{
    TYPE dInv = 1.0 / d;
    x *= dInv;
    y *= dInv;
    z *= dInv;
    w *= dInv;
    return *this;
}


// 一元操作符 (unary operators)
template <class TYPE>
inline VBFVECTOR4<TYPE> VBFVECTOR4<TYPE>::operator+() const
{
    return *this;
}

template <class TYPE>
inline VBFVECTOR4<TYPE> VBFVECTOR4<TYPE>::operator-() const
{
    return VBFVECTOR4<TYPE>(-x, -y, -z, -w);
}

// 二元操作符 (binary operators)
template <class TYPE>
inline VBFVECTOR4<TYPE> VBFVECTOR4<TYPE>::operator+(const VBFVECTOR4<TYPE>& v) const
{
    return VBFVECTOR4<TYPE>(x+v.x, y+v.y, z+v.z, w+v.w);
}

template <class TYPE>
inline VBFVECTOR4<TYPE> VBFVECTOR4<TYPE>::operator-(const VBFVECTOR4<TYPE>& v) const
{
    return VBFVECTOR4<TYPE>(x-v.x, y-v.y, z-v.z, w-v.w);
}

template <class TYPE>
inline VBFVECTOR4<TYPE> VBFVECTOR4<TYPE>::operator*(TYPE d) const
{
    return VBFVECTOR4<TYPE>(x*d, y*d, z*d, w*d);
}

template <class TYPE>
inline VBFVECTOR4<TYPE> VBFVECTOR4<TYPE>::operator/(TYPE d) const
{
    TYPE dInv = 1.0 / d;
    return VBFVECTOR4<TYPE>(x*dInv, y*dInv, z*dInv, w*dInv);
}

template <class TYPE>
inline VBFVECTOR4<TYPE> operator*(TYPE d, const VBFVECTOR4<TYPE>& v)
{
    return VBFVECTOR4<TYPE>(d * v.x, d * v.y, d * v.z, d * v.w);
}

template <class TYPE>
inline bool VBFVECTOR4<TYPE>::operator==(const VBFVECTOR4<TYPE>& v) const
{
    return (x==v.x && y==v.y && z==v.z && w==v.w);
}

template <class TYPE>
inline bool VBFVECTOR4<TYPE>::operator !=(const VBFVECTOR4<TYPE>& v) const
{
    return (x!=v.x || y!=v.y || z!=v.z || w!=v.w);
}


//**************************************************************************
// 以下为与上述结构体有关的全局函数
//**************************************************************************


//--------------------------------------------------------------------------
// 与结构体VBFVECTOR2<TYPE>有关的函数实现部分
//--------------------------------------------------------------------------

template <class TYPE>
inline TYPE VBFVec2Length(const VBFVECTOR2<TYPE> *pV)
{
#ifdef VBF_DEBUG
    if(!pV) return 0.0;
#endif

    return sqrt(pV->x*pV->x + pV->y*pV->y);
}

template <class TYPE>
inline TYPE VBFVec2LengthSq(const VBFVECTOR2<TYPE> *pV)
{
#ifdef VBF_DEBUG
    if(!pV) return 0.0;        
#endif

    return (pV->x * pV->x + pV->y * pV->y);
}

template <class TYPE>
inline TYPE VBFVec2Dot(const VBFVECTOR2<TYPE>* pV1, const VBFVECTOR2<TYPE>* pV2)
{
#ifdef VBF_DEBUG
    if(!pV1 || !pV2) return 0.0;        
#endif

    return (pV1->x * pV2->x + pV1->y * pV2->y);
}

template <class TYPE>
inline TYPE VBFVec2CCW( const VBFVECTOR2<TYPE>* pV1, const VBFVECTOR2<TYPE>* pV2 )
{
#ifdef VBF_DEBUG
    if(!pV1 || !pV2) return 0.0;        
#endif

    return (pV1->x * pV2->y - pV1->y * pV2->x);
}

template <class TYPE>
inline VBFVECTOR2<TYPE>* VBFVec2Add(VBFVECTOR2<TYPE>* pOut, const VBFVECTOR2<TYPE>* pV1, const VBFVECTOR2<TYPE>* pV2)
{
#ifdef VBF_DEBUG
    if(!pOut || !pV1 || !pV2) return NULL;        
#endif

    pOut->x = pV1->x + pV2->x;
    pOut->y = pV1->y + pV2->y;
    return pOut;
}

template <class TYPE>
inline VBFVECTOR2<TYPE>* VBFVec2Subtract(VBFVECTOR2<TYPE>* pOut, const VBFVECTOR2<TYPE>* pV1, const VBFVECTOR2<TYPE>* pV2)
{
#ifdef VBF_DEBUG
    if(!pOut || !pV1 || !pV2) return NULL;        
#endif

    pOut->x = pV1->x - pV2->x;
    pOut->y = pV1->y - pV2->y;
    return pOut;
}

template <class TYPE>
inline VBFVECTOR2<TYPE>* VBFVec2Minimize(VBFVECTOR2<TYPE>* pOut, const VBFVECTOR2<TYPE>* pV1, const VBFVECTOR2<TYPE>* pV2)
{
#ifdef VBF_DEBUG
    if(!pOut || !pV1 || !pV2) return NULL;        
#endif

    pOut->x = (pV1->x < pV2->x) ? pV1->x : pV2->x;
    pOut->y = (pV1->y < pV2->y) ? pV1->y : pV2->y;
    return pOut;
}

template <class TYPE>
inline VBFVECTOR2<TYPE>* VBFVec2Maximize(VBFVECTOR2<TYPE>* pOut, const VBFVECTOR2<TYPE>* pV1, const VBFVECTOR2<TYPE>* pV2)
{
#ifdef VBF_DEBUG
    if(!pOut || !pV1 || !pV2) return NULL;        
#endif

    pOut->x = (pV1->x > pV2->x) ? pV1->x : pV2->x;
    pOut->y = (pV1->y > pV2->y) ? pV1->y : pV2->y;
    return pOut;
}

template <class TYPE>
inline VBFVECTOR2<TYPE>* VBFVec2Scale(VBFVECTOR2<TYPE>* pOut, const VBFVECTOR2<TYPE>* pV, TYPE s)
{
#ifdef VBF_DEBUG
    if(!pOut || !pV) return NULL;       
#endif

    pOut->x = pV->x * s;
    pOut->y = pV->y * s;
    return pOut;
}

template <class TYPE>
inline VBFVECTOR2<TYPE>* VBFVec2Lerp(VBFVECTOR2<TYPE>* pOut, const VBFVECTOR2<TYPE>* pV1, const VBFVECTOR2<TYPE>* pV2, TYPE s)
{
#ifdef VBF_DEBUG
    if(!pOut || !pV1 || !pV2) return NULL; 
#endif

    pOut->x = pV1->x + s * (pV2->x - pV1->x);
    pOut->y = pV1->y + s * (pV2->y - pV1->y);
    return pOut;
}

//--------------------------------------------------------------------------
// 与结构体VBFVECTOR3<TYPE>有关的函数实现部分
//--------------------------------------------------------------------------

template <class TYPE>
inline TYPE VBFVec3Length(const VBFVECTOR3<TYPE>* pV)
{
#ifdef VBF_DEBUG
    if(!pV)  return 0.0;        
#endif

    return sqrt(pV->x * pV->x + pV->y * pV->y + pV->z * pV->z);
}

template <class TYPE>
inline TYPE VBFVec3LengthSq(const VBFVECTOR3<TYPE>* pV)
{
#ifdef _DEBUG
    if(!pV) return 0.0;
#endif

    return (pV->x * pV->x + pV->y * pV->y + pV->z * pV->z);
}

template <class TYPE>
inline TYPE VBFVec3Dot(const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2)
{
#ifdef VBF_DEBUG
    if(!pV1 || !pV2) return 0.0;        
#endif

    return (pV1->x * pV2->x + pV1->y * pV2->y + pV1->z * pV2->z);
}

template <class TYPE>
inline VBFVECTOR3<TYPE>* VBFVec3Cross(VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2)
{
#ifdef VBF_DEBUG
    if(!pOut || !pV1 || !pV2) return NULL;        
#endif

	VBFVECTOR3<TYPE> v;
    v.x = pV1->y * pV2->z - pV1->z * pV2->y;
    v.y = pV1->z * pV2->x - pV1->x * pV2->z;
    v.z = pV1->x * pV2->y - pV1->y * pV2->x;

    *pOut = v;
    return pOut;
}

template <class TYPE>
inline VBFVECTOR3<TYPE>* VBFVec3Add(VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2)
{
#ifdef VBF_DEBUG
    if(!pOut || !pV1 || !pV2) return NULL; 
#endif

    pOut->x = pV1->x + pV2->x;
    pOut->y = pV1->y + pV2->y;
    pOut->z = pV1->z + pV2->z;
    return pOut;
}

template <class TYPE>
inline VBFVECTOR3<TYPE>* VBFVec3Subtract(VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2)
{
#ifdef VBF_DEBUG
    if(!pOut || !pV1 || !pV2) return NULL;        
#endif

    pOut->x = pV1->x - pV2->x;
    pOut->y = pV1->y - pV2->y;
    pOut->z = pV1->z - pV2->z;
    return pOut;
}

template <class TYPE>
inline VBFVECTOR3<TYPE>* VBFVec3Minimize(VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2)
{
#ifdef VBF_DEBUG
    if(!pOut || !pV1 || !pV2) return NULL;        
#endif

    pOut->x = (pV1->x < pV2->x) ? pV1->x : pV2->x;
    pOut->y = (pV1->y < pV2->y) ? pV1->y : pV2->y;
    pOut->z = (pV1->z < pV2->z) ? pV1->z : pV2->z;
    return pOut;
}

template <class TYPE>
inline VBFVECTOR3<TYPE>* VBFVec3Maximize(VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2)
{
#ifdef VBF_DEBUG
    if(!pOut || !pV1 || !pV2) return NULL;        
#endif

    pOut->x = (pV1->x > pV2->x) ? pV1->x : pV2->x;
    pOut->y = (pV1->y > pV2->y) ? pV1->y : pV2->y;
    pOut->z = (pV1->z > pV2->z) ? pV1->z : pV2->z;
    return pOut;
}

template <class TYPE>
inline VBFVECTOR3<TYPE>* VBFVec3Scale(VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV, TYPE s)
{
#ifdef VBF_DEBUG
    if(!pOut || !pV) return NULL;
#endif

    pOut->x = pV->x * s;
    pOut->y = pV->y * s;
    pOut->z = pV->z * s;
    return pOut;
}

template <class TYPE>
inline VBFVECTOR3<TYPE>* VBFVec3Lerp(VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2, TYPE s)
{
#ifdef VBF_DEBUG
    if(!pOut || !pV1 || !pV2) return NULL;        
#endif

    pOut->x = pV1->x + s * (pV2->x - pV1->x);
    pOut->y = pV1->y + s * (pV2->y - pV1->y);
    pOut->z = pV1->z + s * (pV2->z - pV1->z);
    return pOut;
}

template <class TYPE>
inline VBFVECTOR3<TYPE>* VBFVec3Normalize(VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV)
{
	TYPE r = VBFVec3Length(pV);
	if(r==0.0) r = 1.0;

	pOut->x = pV->x / r;
	pOut->y = pV->y / r;
	pOut->z = pV->z / r;
	return pOut;
}

//--------------------------------------------------------------------------
// 全局函数：operator<()
// 函数描述：判断两个之间的大小关系
//--------------------------------------------------------------------------
template <class TYPE>
inline bool operator<(const VBFVECTOR2<TYPE>& c1, const VBFVECTOR2<TYPE>& c2)
{
	if( fabs(c1.x - c2.x) > DBL_ZERO )
	{
		return ( c1.x + DBL_ZERO < c2.x );
	}
	else
	{
		if( fabs(c1.y - c2.y) > DBL_ZERO )
		{
			return ( c1.y + DBL_ZERO < c2.y );
		}
		else
		{
			return false;
		}
	}
}


#endif 
