//  文件名： VBF_Rect.h
//  描述：   定义模板类CVBF_Rect，
//           用于记录各种类型的(int, TYPE,double等)矩形
//  时间：   2004.10.27
//  作者：   杜莹 
//**********************************************************************

#ifndef __VBF_RECT_H__
#define __VBF_RECT_H__

#include "VBF_2DPoint.h"
#include "VBF_Size.h"

template <class TYPE>
class CVBF_Rect
{
public:
	TYPE  left;    // 注意：这四个成员的顺序不能颠倒
	TYPE  top;
	TYPE  right;
	TYPE  bottom;

public:
	CVBF_Rect();
	CVBF_Rect(TYPE l, TYPE t, TYPE r, TYPE b);
	CVBF_Rect(const CVBF_Rect<TYPE>& srcRect);
	CVBF_Rect(const CVBF_Rect<TYPE>* lpSrcRect);
	CVBF_Rect(const CVBF_2DPoint<TYPE>& point, const CVBF_Size<TYPE>& size);
	CVBF_Rect(const CVBF_2DPoint<TYPE>& topLeft, const CVBF_2DPoint<TYPE>&  bottomRight);
	
	virtual ~CVBF_Rect();

	TYPE                       Width()        const;	
	TYPE                       Height()       const;
	CVBF_Size<TYPE>            Size()         const;
	CVBF_2DPoint<TYPE>&        TopLeft();
	CVBF_2DPoint<TYPE>&        BottomRight();
	const CVBF_2DPoint<TYPE>&  TopLeft()      const;
	const CVBF_2DPoint<TYPE>&  BottomRight()  const;
	CVBF_2DPoint<TYPE>         CenterPoint()  const;
	void                       SwapLeftRight();
	static void                SwapLeftRight(const CVBF_Rect<TYPE>* lpRect);	
	
	bool   IsRectEmpty() const;   // returns true if rectangle has no area	
	bool   IsRectNull()  const;   // returns true if rectangle is at (0,0) and has no area
	bool   PtInRect(const CVBF_2DPoint<TYPE>& point) const;  // returns true if point is within rectangle

	void   SetRect(TYPE x1, TYPE y1, TYPE x2, TYPE y2);
	void   SetRect(const CVBF_2DPoint<TYPE>& topLeft, const CVBF_2DPoint<TYPE>& bottomRight);
	void   SetRectEmpty();	
	void   CopyRect(const CVBF_Rect<TYPE>* lpSrcRect);

	virtual bool EqualRect(const CVBF_Rect<TYPE>* lpRect) const
		{ return (left==lpRect->left && top==lpRect->top && right==lpRect->right && bottom==lpRect->bottom); }

	// Inflate rectangle's width and height without moving its top or left
	void   InflateRect(TYPE x, TYPE y);
	void   InflateRect(const CVBF_Size<TYPE>& size);
	void   InflateRect(const CVBF_Rect<TYPE>* lpRect);
	void   InflateRect(TYPE l, TYPE t, TYPE r, TYPE b);

	// Deflate the rectangle's width and height without moving its top or left
	void   DeflateRect(TYPE x, TYPE y);
	void   DeflateRect(const CVBF_Size<TYPE>& size);
	void   DeflateRect(const CVBF_Rect<TYPE>* lpRect);
	void   DeflateRect(TYPE l, TYPE t, TYPE r, TYPE b);

	// Translate the rectangle by moving its top and left
	void   OffsetRect(TYPE x, TYPE y);
	void   OffsetRect(const CVBF_Size<TYPE>& size);
	void   OffsetRect(const CVBF_2DPoint<TYPE>& point);
	void   NormalizeRect();

	// Set this rectangle to intersection of two others
	bool   IntersectRect( CVBF_Rect<TYPE>* lpRect1, CVBF_Rect<TYPE>* lpRect2);

	// Set this rectangle to bounding union of two others
	bool   UnionRect(const CVBF_Rect<TYPE>* lpRect1, const CVBF_Rect<TYPE>* lpRect2);

	// Set this rectangle to minimum of two others
	bool   SubtractRect(const CVBF_Rect<TYPE>* lpRectSrc1, const CVBF_Rect<TYPE>* lpRectSrc2);

	// 判断两个矩形相等与否
	bool operator==(const CVBF_Rect<TYPE>& rect) const;
	bool operator!=(const CVBF_Rect<TYPE>& rect) const;

	// Additional Operations
	void   operator=(const CVBF_Rect<TYPE>& srcRect);
	void   operator+=(const CVBF_2DPoint<TYPE>& point);	
	void   operator+=(const CVBF_Size<TYPE>& size);	
	void   operator+=(const CVBF_Rect<TYPE>* lpRect);
	void   operator-=(const CVBF_2DPoint<TYPE>& point);
	void   operator-=(const CVBF_Size<TYPE>& size);
	void   operator-=(const CVBF_Rect<TYPE>* lpRect);
	void   operator&=(const CVBF_Rect<TYPE>& rect);
	void   operator|=(const CVBF_Rect<TYPE>& rect);

	// Operators returning CVBF_Rect values
	CVBF_Rect<TYPE>   operator+(const CVBF_2DPoint<TYPE>& point) const;
	CVBF_Rect<TYPE>   operator+(const CVBF_Size<TYPE>& size) const;
	CVBF_Rect<TYPE>   operator-(const CVBF_2DPoint<TYPE>& point) const;
	CVBF_Rect<TYPE>   operator-(const CVBF_Size<TYPE>& size) const;
	CVBF_Rect<TYPE>   operator+(const CVBF_Rect<TYPE>* lpRect) const;
	CVBF_Rect<TYPE>   operator-(const CVBF_Rect<TYPE>* lpRect) const;
	CVBF_Rect<TYPE>   operator&(const CVBF_Rect<TYPE>& rect2) const;
	CVBF_Rect<TYPE>   operator|(const CVBF_Rect<TYPE>& rect2) const;
	CVBF_Rect<TYPE>   MulDiv(TYPE nMultiplier, TYPE nDivisor) const;
};

//--------------------------------------------------------------------------------
// 以下为模板类CVBF_Rect的函数实现部分
//--------------------------------------------------------------------------------

template <class TYPE>
CVBF_Rect<TYPE>::CVBF_Rect()
	{}

template <class TYPE>
CVBF_Rect<TYPE>::~CVBF_Rect()
	{}

template <class TYPE>
inline CVBF_Rect<TYPE>::CVBF_Rect(TYPE l, TYPE t, TYPE r, TYPE b)
	{ left=l; top=t; right=r; bottom=b; }

template <class TYPE>
inline CVBF_Rect<TYPE>::CVBF_Rect(const CVBF_Rect<TYPE>& srcRect)
	{ left=srcRect.left; top=srcRect.top; right=srcRect.right; bottom=srcRect.bottom; }

template <class TYPE>
inline CVBF_Rect<TYPE>::CVBF_Rect(const CVBF_Rect<TYPE>* lpSrcRect)
	{ left=lpSrcRect->left; top=lpSrcRect->top; right=lpSrcRect->right; bottom=lpSrcRect->bottom; }

template <class TYPE>
inline CVBF_Rect<TYPE>::CVBF_Rect(const CVBF_2DPoint<TYPE>& point, const CVBF_Size<TYPE>& size)
	{ right=(left=point.x)+size.cx; bottom=(top=point.y)+size.cy; }

template <class TYPE>
inline CVBF_Rect<TYPE>::CVBF_Rect(const CVBF_2DPoint<TYPE>& topLeft, const CVBF_2DPoint<TYPE>& bottomRight)
	{ left=topLeft.x; top=topLeft.y; right=bottomRight.x; bottom=bottomRight.y; }

template <class TYPE>
inline TYPE CVBF_Rect<TYPE>::Width() const
	{ return (right-left); }

template <class TYPE>
inline TYPE CVBF_Rect<TYPE>::Height() const
	{ return (bottom-top); }

template <class TYPE>
inline CVBF_Size<TYPE> CVBF_Rect<TYPE>::Size() const
	{ return CVBF_Size<TYPE>(right-left, bottom-top); }

// 求矩形的左上角点
template <class TYPE>
inline CVBF_2DPoint<TYPE>& CVBF_Rect<TYPE>::TopLeft()
	{ return *( (CVBF_2DPoint<TYPE>*)this ); }

// 求矩形的右下角点
template <class TYPE>
inline CVBF_2DPoint<TYPE>& CVBF_Rect<TYPE>::BottomRight()
	{ return *( (CVBF_2DPoint<TYPE>*)((TYPE*)this+2) ); }

template <class TYPE>
inline const CVBF_2DPoint<TYPE>& CVBF_Rect<TYPE>::TopLeft() const
	{ return *( (CVBF_2DPoint<TYPE>*)this ); }

template <class TYPE>
inline const CVBF_2DPoint<TYPE>& CVBF_Rect<TYPE>::BottomRight() const
	{ return *( (CVBF_2DPoint<TYPE>*)((TYPE*)this+2) ); }

template <class TYPE>
inline CVBF_2DPoint<TYPE> CVBF_Rect<TYPE>::CenterPoint() const
	{ return CVBF_2DPoint<TYPE>((left+right)/2, (top+bottom)/2); }

// 交换矩形的左边和右边
template <class TYPE>
inline void CVBF_Rect<TYPE>::SwapLeftRight()
	{ SwapLeftRight(this); }

template <class TYPE>
inline void CVBF_Rect<TYPE>::SwapLeftRight(const CVBF_Rect<TYPE>* lpRect)
	{ TYPE temp=lpRect->left; lpRect->left=lpRect->right; lpRect->right=temp; }

// 判断矩形是否为空，即面积为0
template <class TYPE>
inline bool CVBF_Rect<TYPE>::IsRectEmpty() const
	{ return (right<=left || bottom<=top); }

// 判断矩形是否为Null，即四个角都位于原点(0,0)
template <class TYPE>
inline bool CVBF_Rect<TYPE>::IsRectNull() const
	{ return (left==0 && right==0 && top==0 && bottom==0); }

template <class TYPE>
inline void CVBF_Rect<TYPE>::SetRect(TYPE x1, TYPE y1, TYPE x2, TYPE y2)
	{ left=x1; top=y1; right=x2; bottom=y2; }


template <class TYPE>
inline void CVBF_Rect<TYPE>::SetRect(const CVBF_2DPoint<TYPE>& topLeft, const CVBF_2DPoint<TYPE>& bottomRight)
	{ SetRect(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y); }

template <class TYPE>
inline void CVBF_Rect<TYPE>::SetRectEmpty()
	{ left=0; right=0; top=0; bottom=0; }

template <class TYPE>
inline void CVBF_Rect<TYPE>::CopyRect(const CVBF_Rect<TYPE>* lpSrcRect)
	{ left=lpSrcRect->left; top=lpSrcRect->top; right=lpSrcRect->right; bottom=lpSrcRect->bottom; }
/*
template <class TYPE>
inline bool CVBF_Rect<TYPE>::EqualRect(const CVBF_Rect<TYPE>* lpRect) const
	{ return (left==lpRect->left && top==lpRect->top && right==lpRect->right && bottom==lpRect->bottom); }
*/

// 扩大矩形
template <class TYPE>
inline void CVBF_Rect<TYPE>::InflateRect(TYPE x, TYPE y)
	{ left-=x; top-=y; right+=x; bottom+=y; }

template <class TYPE>
inline void CVBF_Rect<TYPE>::InflateRect(const CVBF_Size<TYPE>& size)
	{ InflateRect(size.cx, size.cy); }

// 缩小矩形
template <class TYPE>
inline void CVBF_Rect<TYPE>::DeflateRect(TYPE x, TYPE y)
	{ InflateRect(-x, -y); }

template <class TYPE>
inline void CVBF_Rect<TYPE>::DeflateRect(const CVBF_Size<TYPE>& size)
	{ InflateRect(-size.cx, -size.cy); }

// 沿x,y方向平移矩形
template <class TYPE>
inline void CVBF_Rect<TYPE>::OffsetRect(TYPE x, TYPE y)
	{ left+=x; top+=y; right+=x; bottom+=y; }

template <class TYPE>
inline void CVBF_Rect<TYPE>::OffsetRect(const CVBF_2DPoint<TYPE>& point)
	{ OffsetRect(point.x, point.y); }


// 求两个矩形的交集，有待修改
template <class TYPE>
inline bool CVBF_Rect<TYPE>::IntersectRect(CVBF_Rect<TYPE>* lpRect1, CVBF_Rect<TYPE>* lpRect2)
{
	lpRect1->NormalizeRect();
	lpRect2->NormalizeRect();
	left   = max(lpRect1->left, lpRect2->left);
	top    = max(lpRect1->top, lpRect2->top);
	right  = min(lpRect1->right, lpRect2->right);
	bottom = min(lpRect1->bottom, lpRect2->bottom);
	
	return !IsRectEmpty();
}

// 操作符重载
template <class TYPE>
inline bool CVBF_Rect<TYPE>::operator==(const CVBF_Rect<TYPE>& rect) const
		{ return EqualRect(&rect); }

template <class TYPE>
inline bool CVBF_Rect<TYPE>::operator!=(const CVBF_Rect<TYPE>& rect) const
		{ return !EqualRect(&rect); }

template <class TYPE>
inline void CVBF_Rect<TYPE>::operator=(const CVBF_Rect<TYPE>& srcRect)
	{ left=srcRect.left; top=srcRect.top; right=srcRect.right; bottom=srcRect.bottom; }

template <class TYPE>
inline void CVBF_Rect<TYPE>::operator+=(const CVBF_2DPoint<TYPE>& point)
	{ OffsetRect(point.x, point.y); }

template <class TYPE>
inline void CVBF_Rect<TYPE>::operator+=(const CVBF_Size<TYPE>& size)
	{ OffsetRect(size.cx, size.cy); }

template <class TYPE>
inline void CVBF_Rect<TYPE>::operator+=(const CVBF_Rect<TYPE>* lpRect)
	{ InflateRect(lpRect); }

template <class TYPE>
inline void CVBF_Rect<TYPE>::operator-=(const CVBF_2DPoint<TYPE>& point)
	{ OffsetRect(-point.x, -point.y); }

template <class TYPE>
inline void CVBF_Rect<TYPE>::operator-=(const CVBF_Size<TYPE>& size)
	{ OffsetRect(-size.cx, -size.cy); }

template <class TYPE>
inline void CVBF_Rect<TYPE>::operator-=(const CVBF_Rect<TYPE>* lpRect)
	{ DeflateRect(lpRect); }

//template <class TYPE>
//inline void CVBF_Rect<TYPE>::operator&=(const CVBF_Rect<TYPE>& rect)
//	{ ::IntersectRect(this, this, &rect); }

//template <class TYPE>
//inline void CVBF_Rect<TYPE>::operator|=(const CVBF_Rect<TYPE>& rect)
//	{ ::UnionRect(this, this, &rect); }

template <class TYPE>
inline CVBF_Rect<TYPE> CVBF_Rect<TYPE>::operator+(const CVBF_2DPoint<TYPE>& pt) const
	{ CVBF_Rect<TYPE> rect(*this); rect.OffsetRect(pt.x, pt.y); return rect; }

template <class TYPE>
inline CVBF_Rect<TYPE> CVBF_Rect<TYPE>::operator-(const CVBF_2DPoint<TYPE>& pt) const
	{ CVBF_Rect<TYPE> rect(*this); rect.OffsetRect(-pt.x, -pt.y); return rect; }

template <class TYPE>
inline CVBF_Rect<TYPE> CVBF_Rect<TYPE>::operator+(const CVBF_Size<TYPE>& size) const
	{ CVBF_Rect<TYPE> rect(*this); rect.OffsetRect(size.cx, size.cy); return rect; }

template <class TYPE>
inline CVBF_Rect<TYPE> CVBF_Rect<TYPE>::operator-(const CVBF_Size<TYPE>& size) const
	{ CVBF_Rect<TYPE> rect(*this); rect.OffsetRect(-size.cx, -size.cy); return rect; }

template <class TYPE>
inline CVBF_Rect<TYPE> CVBF_Rect<TYPE>::operator+(const CVBF_Rect<TYPE>* lpRect) const
	{ CVBF_Rect<TYPE> rect(this); rect.InflateRect(lpRect); return rect; }

template <class TYPE>
inline CVBF_Rect<TYPE> CVBF_Rect<TYPE>::operator-(const CVBF_Rect<TYPE>* lpRect) const
	{ CVBF_Rect<TYPE> rect(this); rect.DeflateRect(lpRect); return rect; }

//template <class TYPE>
//inline CVBF_Rect<TYPE> CVBF_Rect<TYPE>::operator&(const CVBF_Rect<TYPE>& rect2) const
//	{ CVBF_Rect<TYPE> rect; ::IntersectRect(&rect, this, &rect2); return rect; }

//template <class TYPE>
//inline CVBF_Rect<TYPE> CVBF_Rect<TYPE>::operator|(const CVBF_Rect<TYPE>& rect2) const
//	{ CVBF_Rect<TYPE> rect; ::UnionRect(&rect, this, &rect2); return rect; }

//inline bool CVBF_Rect<TYPE>::SubtractRect(const CVBF_Rect<TYPE>* lpRectSrc1, const CVBF_Rect<TYPE>* lpRectSrc2)
//	{ return ::SubtractRect(this, lpRectSrc1, lpRectSrc2); }

// 矩形标准化
template <class TYPE>
inline void CVBF_Rect<TYPE>::NormalizeRect()
{
	TYPE nTemp;
	if(left > right)
	{
		nTemp = left;
		left  = right;
		right = nTemp;
	}
	if(top > bottom)
	{
		nTemp  = top;
		top    = bottom;
		bottom = nTemp;
	}
}

// 扩大矩形
template <class TYPE>
inline void CVBF_Rect<TYPE>::InflateRect(const CVBF_Rect<TYPE>* lpRect)
{
	left   -= lpRect->left;
	top    -= lpRect->top;
	right  += lpRect->right;
	bottom += lpRect->bottom;
}

template <class TYPE>
inline void CVBF_Rect<TYPE>::InflateRect(TYPE l, TYPE t, TYPE r, TYPE b)
{
	left   -= l;
	top    -= t;
	right  += r;
	bottom += b;
}

// 缩小矩形
template <class TYPE>
inline void CVBF_Rect<TYPE>::DeflateRect(const CVBF_Rect<TYPE>* lpRect)
{
	left   += lpRect->left;
	top    += lpRect->top;
	right  -= lpRect->right;
	bottom -= lpRect->bottom;
}

template <class TYPE>
inline void CVBF_Rect<TYPE>::DeflateRect(TYPE l, TYPE t, TYPE r, TYPE b)
{
	left   += l;
	top    += t;
	right  -= r;
	bottom -= b;
}

// 求两个矩形的并集
template <class TYPE>
inline bool CVBF_Rect<TYPE>::UnionRect(const CVBF_Rect<TYPE>* lpRect1, const CVBF_Rect<TYPE>* lpRect2)
{
	this->left   = min( lpRect1->left,   lpRect2->left );
	this->top    = min( lpRect1->top,    lpRect2->top );
	this->right  = max( lpRect1->right,  lpRect2->right );
	this->bottom = max( lpRect1->bottom, lpRect2->bottom );

	return (this->IsRectEmpty()) ? false : true;
}

// 判断点是否在矩形中，有待修改
template <class TYPE>
inline bool CVBF_Rect<TYPE>::PtInRect(const CVBF_2DPoint<TYPE>& point) const
{ 
	return (point.x>=left && point.x<=right && point.y>=top && point.y<=bottom);
}

//--------------------------------------------------------------------------------
// 以下为模板特例函数：
//--------------------------------------------------------------------------------
template<>
inline bool CVBF_Rect<float>::EqualRect(const CVBF_Rect<float>* lpRect) const
{
	return ( fabs(this->left   - lpRect->left)   < FLT_MAX_PRECISION && 
		     fabs(this->top    - lpRect->top)    < FLT_MAX_PRECISION && 
		     fabs(this->right  - lpRect->right)  < FLT_MAX_PRECISION && 
		     fabs(this->bottom - lpRect->bottom) < FLT_MAX_PRECISION );
}
template<>
inline bool CVBF_Rect<double>::EqualRect(const CVBF_Rect<double>* lpRect) const
{
	return ( fabs(this->left   - lpRect->left)   < DBL_MAX_PRECISION && 
		     fabs(this->top    - lpRect->top)    < DBL_MAX_PRECISION && 
		     fabs(this->right  - lpRect->right)  < DBL_MAX_PRECISION && 
		     fabs(this->bottom - lpRect->bottom) < DBL_MAX_PRECISION );
}


//--------------------------------------------------------------------------------
// 定义特化类型
//-------------------------------------------------------------------------------
typedef CVBF_Rect<double>		CVBF_RectD;


#endif 
