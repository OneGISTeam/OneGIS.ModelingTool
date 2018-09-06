//**********************************************************************
//  �ļ����� VBF_2DPoint.h
//  ������   ����ģ����CVBF_2DPoint��
//           ���ڼ�¼��ά��
//  ʱ�䣺   2004.11.3
//  ���ߣ�   ��Ө 
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

template <class TYPE> class CVBF_Size;  // ��Ҫʹ�õ��ⲿ��

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

	// ����int����float/double�����ıȽϷ�����ͬ�������������ȽϺ�������Ϊ�麯��
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


    // ����ģ�岻��Ƕ�׶��壬�������溯��ֻ���������ڶ���
    CVBF_Size<TYPE>  operator-(const CVBF_2DPoint<TYPE>& point) const { return CVBF_Size<TYPE>(x-point.x, y-point.y); }
};

//--------------------------------------------------------------------------------
// ����Ϊģ����CVBF_2DPoint�ĺ���ʵ�ֲ���
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
// ����Ϊģ������������
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
// �����ػ�����
//--------------------------------------------------------------------------------
typedef CVBF_2DPoint<float>   CVBF_2DPointF;
typedef CVBF_2DPoint<double>  CVBF_2DPointD;

#endif 



