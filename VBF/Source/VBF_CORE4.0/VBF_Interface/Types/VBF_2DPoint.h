//**********************************************************************
//  文件名： VBF_2DPoint.h
//  描述：   定义模板类CVBF_2DPoint，
//           用于记录二维点
//  时间：   2004.11.3
//  作者：   杜莹 
//**********************************************************************

#ifndef __VBF_2DPOINT_H__
#define __VBF_2DPOINT_H__

#include "VBF_Macros.h"
#include "float.h"

#ifndef LOWORD
        #define LOWORD(l)   ((WORD)(l))
#endif

#ifndef HIWORD
        #define HIWORD(l)   ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#endif

template <class TYPE> class CVBF_Size;  // 需要使用的外部类

template <class TYPE>
class CVBF_2DPoint
{


public:
	TYPE  x;
	TYPE  y;

public:
	
	CVBF_2DPoint();	
	CVBF_2DPoint(TYPE initX, TYPE initY);
	CVBF_2DPoint(const CVBF_2DPoint<TYPE>& initPt);	
    CVBF_2DPoint(const CVBF_Size<TYPE>& initSize);
	CVBF_2DPoint(DWORD dwPoint);

	virtual ~CVBF_2DPoint();
	
	void Offset(TYPE xOffset, TYPE yOffset);
	void Offset(const CVBF_2DPoint<TYPE>& point);
    void Offset(const CVBF_Size<TYPE>& size);

	// 由于int型与float/double型数的比较方法不同，所以这两个比较函数必须为虚函数
	virtual bool operator==(const CVBF_2DPoint<TYPE>& point) const { return (x==point.x && y==point.y); }
	virtual bool operator!=(const CVBF_2DPoint<TYPE>& point) const { return (x!=point.x || y!=point.y); }

    void operator+=(const CVBF_Size<TYPE>& size);
    void operator-=(const CVBF_Size<TYPE>& size);
	void operator+=(const CVBF_2DPoint<TYPE>& point);
	void operator-=(const CVBF_2DPoint<TYPE>& point);

    CVBF_2DPoint<TYPE> operator+(const CVBF_Size<TYPE>& size)     const;
    CVBF_2DPoint<TYPE> operator-(const CVBF_Size<TYPE>& size)     const;
	CVBF_2DPoint<TYPE> operator-()                          const;
	CVBF_2DPoint<TYPE> operator+(const CVBF_2DPoint<TYPE>& point) const;


    // 由于模板不能嵌套定义，所以下面函数只能在类体内定义
    CVBF_Size<TYPE>  operator-(const CVBF_2DPoint<TYPE>& point) const { return CVBF_Size<TYPE>(x-point.x, y-point.y); }
};

//--------------------------------------------------------------------------------
// 以下为模板类CVBF_2DPoint的函数实现部分
//--------------------------------------------------------------------------------

template <class TYPE>
inline CVBF_2DPoint<TYPE>::CVBF_2DPoint()
	{}

template <class TYPE>
inline CVBF_2DPoint<TYPE>::~CVBF_2DPoint()
	{}

template <class TYPE>
inline CVBF_2DPoint<TYPE>::CVBF_2DPoint(TYPE initX, TYPE initY)
	{ x = initX; y = initY; }

#if !defined(_AFX_CORE_IMPL) || !defined(_AFXDLL) || defined(_DEBUG)
template <class TYPE>
inline CVBF_2DPoint<TYPE>::CVBF_2DPoint(const CVBF_2DPoint<TYPE>& initPt)
	{ x=initPt.x; y=initPt.y; }
#endif

template <class TYPE>
inline CVBF_2DPoint<TYPE>::CVBF_2DPoint(const CVBF_Size<TYPE>& initSize)
	{ x=initSize.cx; y=initSize.cy; }

template <class TYPE>
inline CVBF_2DPoint<TYPE>::CVBF_2DPoint(DWORD dwPoint)
	{ x =(short)LOWORD(dwPoint); y=(short)HIWORD(dwPoint); }

template <class TYPE>
inline void CVBF_2DPoint<TYPE>::Offset(TYPE xOffset, TYPE yOffset)
	{ x+=xOffset; y+=yOffset; }

template <class TYPE>
inline void CVBF_2DPoint<TYPE>::Offset(const CVBF_2DPoint<TYPE>& point)
	{ x+=point.x; y+=point.y; }

template <class TYPE>
inline void CVBF_2DPoint<TYPE>::Offset(const CVBF_Size<TYPE>& size)
	{ x+=size.cx; y+=size.cy; }

template <class TYPE>
inline void CVBF_2DPoint<TYPE>::operator+=(const CVBF_Size<TYPE>& size)
	{ x+=size.cx; y+=size.cy; }

template <class TYPE>
inline void CVBF_2DPoint<TYPE>::operator-=(const CVBF_Size<TYPE>& size)
	{ x-=size.cx; y-=size.cy; }

template <class TYPE>
inline void CVBF_2DPoint<TYPE>::operator+=(const CVBF_2DPoint<TYPE>& point)
	{ x+=point.x; y+=point.y; }

template <class TYPE>
inline void CVBF_2DPoint<TYPE>::operator-=(const CVBF_2DPoint<TYPE>& point)
	{ x-=point.x; y-=point.y; }

template <class TYPE>
inline CVBF_2DPoint<TYPE> CVBF_2DPoint<TYPE>::operator+(const CVBF_Size<TYPE>& size) const
	{ return CVBF_2DPoint<TYPE>(x+size.cx, y+size.cy); }

template <class TYPE>
inline CVBF_2DPoint<TYPE> CVBF_2DPoint<TYPE>::operator-(const CVBF_Size<TYPE>& size) const
	{ return CVBF_2DPoint<TYPE>(x-size.cx, y-size.cy); }

template <class TYPE>
inline CVBF_2DPoint<TYPE> CVBF_2DPoint<TYPE>::operator-() const
	{ return CVBF_2DPoint<TYPE>(-x, -y); }

template <class TYPE>
inline CVBF_2DPoint<TYPE> CVBF_2DPoint<TYPE>::operator+(const CVBF_2DPoint<TYPE>& point) const
	{ return CVBF_2DPoint<TYPE>(x+point.x, y+point.y); }


//--------------------------------------------------------------------------------
// 以下为模板特例函数：
//--------------------------------------------------------------------------------
template <>
inline bool CVBF_2DPoint<float>::operator==(const CVBF_2DPoint<float>& point) const
{
    return ( fabs(this->x - point.x) < FLT_MAX_PRECISION &&
		     fabs(this->y - point.y) < FLT_MAX_PRECISION );
}
template <>
inline bool CVBF_2DPoint<double>::operator==(const CVBF_2DPoint<double>& point) const
{
    return ( fabs(this->x - point.x) < DBL_MAX_PRECISION &&
             fabs(this->y - point.y) < DBL_MAX_PRECISION );
}
template <>
inline bool CVBF_2DPoint<float>::operator!=(const CVBF_2DPoint<float>& point) const
{
	return !(*this==point);
}
template <>
inline bool CVBF_2DPoint<double>::operator!=(const CVBF_2DPoint<double>& point) const
{
	return !(*this==point);
}

//--------------------------------------------------------------------------------
// 定义特化类型
//--------------------------------------------------------------------------------
typedef CVBF_2DPoint<float>   CVBF_2DPointF;
typedef CVBF_2DPoint<double>  CVBF_2DPointD;

#endif 



