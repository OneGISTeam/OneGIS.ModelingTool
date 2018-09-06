//**********************************************************************
//  文件名： VBF_Size.h
//  描述：   定义模板类CVBF_Size，
//           用于记录Size
//  时间：   2004.11.3
//  作者：   杜莹 
//**********************************************************************

#ifndef __VBF_SIZE_H__
#define __VBF_SIZE_H__

#include "VBF_2DPoint.h"

template <class TYPE>
class CVBF_Size  
{
	class CVBF_Rect;  // 需要使用的外部类

public:
	TYPE  cx;
	TYPE  cy;

public:
	CVBF_Size();	
	CVBF_Size(TYPE initCX, TYPE initCY);
	CVBF_Size(const CVBF_Size<TYPE>& initSize);
	CVBF_Size(const CVBF_2DPoint<TYPE>& initPt);
	CVBF_Size(DWORD dwSize);

	virtual ~CVBF_Size();
	
	// 由于int型与float/double型数的比较方法不同，所以这两个比较函数必须为虚函数
	virtual bool operator==(const CVBF_Size<TYPE>& size) const { return (cx==size.cx && cy==size.cy); }
	virtual bool operator!=(const CVBF_Size<TYPE>& size) const { return (cx!=size.cx || cy!=size.cy); }

	void      operator+=(const CVBF_Size<TYPE>& size);
	void      operator-=(const CVBF_Size<TYPE>& size);

	CVBF_Size<TYPE>	     operator+(const CVBF_Size<TYPE>& size)     const;
	CVBF_Size<TYPE>	     operator-(const CVBF_Size<TYPE>& size)     const;
	CVBF_Size<TYPE>      operator-()                          const;
	CVBF_2DPoint<TYPE>   operator+(const CVBF_2DPoint<TYPE>& point) const;
	CVBF_2DPoint<TYPE>   operator-(const CVBF_2DPoint<TYPE>& point) const;
	
   /* wuyuguo
	// 由于模板不能嵌套定义，所以下面两个函数只能在类体内定义
    CVBF_Rect<TYPE> operator+(const CVBF_Rect* lpRect) const
		{ return CVBF_Rect<TYPE>(lpRect) + *this; }

    CVBF_Rect operator-(const CVBF_Rect* lpRect) const
		{ return CVBF_Rect<TYPE>(lpRect) - *this; }
     */
};

//--------------------------------------------------------------------------------
// 以下为模板类CVBF_Size的函数实现部分
//--------------------------------------------------------------------------------
template <class TYPE>
inline CVBF_Size<TYPE>::CVBF_Size()
	{}

template <class TYPE>
inline CVBF_Size<TYPE>::~CVBF_Size()
	{}

template <class TYPE>	
inline CVBF_Size<TYPE>::CVBF_Size(TYPE initCX, TYPE initCY)
	{ cx=initCX; cy=initCY; }

template <class TYPE>	
inline CVBF_Size<TYPE>::CVBF_Size(const CVBF_Size<TYPE>& initSize)
	{ cx=initSize.cx; cy=initSize.cy; }

template <class TYPE>	
inline CVBF_Size<TYPE>::CVBF_Size(const CVBF_2DPoint<TYPE>& initPt)
	{ cx=initPt.x; cy=initPt.y; }

template <class TYPE>	
inline CVBF_Size<TYPE>::CVBF_Size(DWORD dwSize)
	{ cx=(short)LOWORD(dwSize); cy=(short)HIWORD(dwSize);}

template <class TYPE>	
inline void CVBF_Size<TYPE>::operator+=(const CVBF_Size<TYPE>& size)
	{ cx+=size.cx; cy+=size.cy; }

template <class TYPE>	
inline void CVBF_Size<TYPE>::operator-=(const CVBF_Size<TYPE>& size)
	{ cx-=size.cx; cy-=size.cy; }

template <class TYPE>	
inline CVBF_Size<TYPE> CVBF_Size<TYPE>::operator+(const CVBF_Size<TYPE>& size) const
	{ return CVBF_Size<TYPE>(cx+size.cx, cy+size.cy); }

template <class TYPE>	
inline CVBF_Size<TYPE> CVBF_Size<TYPE>::operator-(const CVBF_Size<TYPE>& size) const
	{ return CVBF_Size<TYPE>(cx-size.cx, cy-size.cy); }

template <class TYPE>	
inline CVBF_Size<TYPE> CVBF_Size<TYPE>::operator-() const
	{ return CVBF_Size<TYPE>(-cx, -cy); }

template <class TYPE>	
inline CVBF_2DPoint<TYPE> CVBF_Size<TYPE>::operator+(const CVBF_2DPoint<TYPE>& point) const
	{ return CVBF_2DPoint<TYPE>(cx+point.x, cy+point.y); }

template <class TYPE>	
inline CVBF_2DPoint<TYPE> CVBF_Size<TYPE>::operator-(const CVBF_2DPoint<TYPE>& point) const
	{ return CVBF_2DPoint<TYPE>(cx-point.x, cy-point.y); }


//--------------------------------------------------------------------------------
// 以下为模板特例函数：
//--------------------------------------------------------------------------------
template <>
inline bool CVBF_Size<float>::operator==(const CVBF_Size<float>& size) const
{
	return ( fabs(this->cx - size.cx) < FLT_MAX_PRECISION && 
		     fabs(this->cy - size.cy) < FLT_MAX_PRECISION );
}
template <>
inline bool CVBF_Size<double>::operator==(const CVBF_Size<double>& size) const
{
	return ( fabs(this->cx - size.cx) < DBL_MAX_PRECISION && 
		     fabs(this->cy - size.cy) < DBL_MAX_PRECISION );
}
template <>
inline bool CVBF_Size<float>::operator!=(const CVBF_Size<float>& size) const
{
	return !(*this==size);
}
template <>
inline bool CVBF_Size<double>::operator!=(const CVBF_Size<double>& size) const
{
	return !(*this==size);
}

//--------------------------------------------------------------------------------
// 定义特化类型
//--------------------------------------------------------------------------------
typedef CVBF_Size<double>  CVBF_SizeD;

#endif 
