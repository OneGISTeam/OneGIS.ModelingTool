//**********************************************************************
//  �ļ����� VBF_Size.h
//  ������   ����ģ����CVBF_Size��
//           ���ڼ�¼Size
//  ʱ�䣺   2004.11.3
//  ���ߣ�   ��Ө 
//**********************************************************************

#ifndef __VBF_SIZE_H__
#define __VBF_SIZE_H__

#include "VBF_2DPoint.h"

template <class TYPE>
class CVBF_Size  
{
	class CVBF_Rect;  // ��Ҫʹ�õ��ⲿ��

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
	
	// ����int����float/double�����ıȽϷ�����ͬ�������������ȽϺ�������Ϊ�麯��
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
	// ����ģ�岻��Ƕ�׶��壬����������������ֻ���������ڶ���
    CVBF_Rect<TYPE> operator+(const CVBF_Rect* lpRect) const
		{ return CVBF_Rect<TYPE>(lpRect) + *this; }

    CVBF_Rect operator-(const CVBF_Rect* lpRect) const
		{ return CVBF_Rect<TYPE>(lpRect) - *this; }
     */
};

//--------------------------------------------------------------------------------
// ����Ϊģ����CVBF_Size�ĺ���ʵ�ֲ���
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
// ����Ϊģ������������
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
// �����ػ�����
//--------------------------------------------------------------------------------
typedef CVBF_Size<double>  CVBF_SizeD;

#endif 
