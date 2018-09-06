//*******************************************************************
// �ļ��� VBF_Vector.h
// ������ ����3DMath��ʹ�õĻ����������ͣ�����
// ���ߣ� ��Ө
// ʱ�䣺 2012-11-06
//*******************************************************************

#ifndef __VBF_VECTOR_H__
#define __VBF_VECTOR_H__

#include <math.h>
#include "VBF_Macros.h"


#if _MSC_VER >= 1200
	#pragma warning(push)
#endif

#pragma warning(disable:4201) // anonymous unions warning


// �����ֽڶ��뷽ʽ��8�ֽڶ���
#include <pshpack8.h>


//--------------------------------------------------------------------------
// �ṹ��VBFVECTOR2<TYPE>�Ķ��岿��
//--------------------------------------------------------------------------
template <class TYPE>
class VBFVECTOR2
{
public:
	TYPE x, y;

public:
    VBFVECTOR2() {};
    VBFVECTOR2( const TYPE* );    
    VBFVECTOR2( TYPE x, TYPE y );

    // ǿ��ת�� (casting)
    operator TYPE*();
    operator const TYPE*() const;

    // ��ֵ������ (assignment operators)
    VBFVECTOR2& operator+=( const VBFVECTOR2<TYPE>& );
    VBFVECTOR2& operator-=( const VBFVECTOR2<TYPE>& );
    VBFVECTOR2& operator*=( TYPE );
    VBFVECTOR2& operator/=( TYPE );

    // һԪ������ (unary operators)
    VBFVECTOR2 operator+() const;
    VBFVECTOR2 operator-() const;

    // ��Ԫ������ (binary operators)
    VBFVECTOR2 operator+(const VBFVECTOR2<TYPE>&) const;
    VBFVECTOR2 operator-(const VBFVECTOR2<TYPE>&) const;
    VBFVECTOR2 operator*(TYPE ) const;
    VBFVECTOR2 operator/(TYPE ) const;

    friend VBFVECTOR2<TYPE> operator*(TYPE, const VBFVECTOR2<TYPE>&);

    friend TYPE operator*(const VBFVECTOR2<TYPE>& v1, const VBFVECTOR2<TYPE>& v2)
	{
		return v1.x*v2.x + v1.y*v2.y;
	}

    bool operator==(const VBFVECTOR2<TYPE>&) const;
    bool operator!=(const VBFVECTOR2<TYPE>&) const; 

	TYPE Module()
	{
		return sqrt( x*x + y*y );
	}
	TYPE Length()
	{
		return sqrt( x*x + y*y );
	}
};


//--------------------------------------------------------------------------
// �ṹ��VBFVECTOR3�Ķ��岿��
//--------------------------------------------------------------------------
template <class TYPE>
class VBFVECTOR3 
{
public:
	TYPE x, y, z;

public:
    VBFVECTOR3() {};
    VBFVECTOR3(const TYPE*);      
    VBFVECTOR3(TYPE x, TYPE y, TYPE z);

    // ǿ��ת�� (casting)
    operator TYPE*();
    operator const TYPE*() const;

    // ��ֵ������ (assignment operators)
    VBFVECTOR3& operator+=(const VBFVECTOR3&);
    VBFVECTOR3& operator-=(const VBFVECTOR3&);
    VBFVECTOR3& operator*=(TYPE);
    VBFVECTOR3& operator/=(TYPE);

    // һԪ������ (unary operators)
    VBFVECTOR3 operator+() const;
    VBFVECTOR3 operator-() const;

    // ��Ԫ������ VBFVECTOR2(binary operators)
    VBFVECTOR3 operator+(const VBFVECTOR3&) const;
    VBFVECTOR3 operator-(const VBFVECTOR3&) const;
    VBFVECTOR3 operator*(TYPE) const;
    VBFVECTOR3 operator/(TYPE) const;

    friend VBFVECTOR3<TYPE> operator*(TYPE, const VBFVECTOR3<TYPE>&);

    bool operator==(const VBFVECTOR3&) const;
    bool operator!=(const VBFVECTOR3&) const;

	TYPE Length()
	{
		return sqrt(x * x + y * y + z * z);
	}
	TYPE Length2()
	{
		return x * x + y * y + z * z;
	}
	void Set(TYPE xT, TYPE yT, TYPE zT)
	{
		x = xT; y = yT; z = zT;
	}
	void Normalize()
	{
		TYPE r = Length();
		if(r==0.0) r = 1.0;

		x /= r;
		y /= r;
		z /= r;

	}
};


//--------------------------------------------------------------------------
// �ṹ��VBFVECTOR4�Ķ��岿��
//--------------------------------------------------------------------------
template <class TYPE>
class VBFVECTOR4
{
public:
	TYPE x, y, z, w;

public:
    VBFVECTOR4() {};
    VBFVECTOR4( const TYPE* );    
    VBFVECTOR4( TYPE x, TYPE y, TYPE z, TYPE w );

    // ǿ��ת�� (casting)
    operator TYPE* ();
    operator const TYPE* () const;

    // ��ֵ������ (assignment operators)
    VBFVECTOR4& operator += ( const VBFVECTOR4& );
    VBFVECTOR4& operator -= ( const VBFVECTOR4& );
    VBFVECTOR4& operator *= ( TYPE );
    VBFVECTOR4& operator /= ( TYPE );

    // һԪ������ (unary operators)
    VBFVECTOR4 operator + () const;
    VBFVECTOR4 operator - () const;

    // ��Ԫ������ (binary operators)
    VBFVECTOR4 operator + ( const VBFVECTOR4& ) const;
    VBFVECTOR4 operator - ( const VBFVECTOR4& ) const;
    VBFVECTOR4 operator * ( TYPE ) const;
    VBFVECTOR4 operator / ( TYPE ) const;

    friend VBFVECTOR4<TYPE> operator * ( TYPE, const VBFVECTOR4<TYPE>& );

    bool operator == ( const VBFVECTOR4& ) const;
    bool operator != ( const VBFVECTOR4& ) const;
};

//--------------------------------------------------------------------------
// ��ṹ��VBFVECTOR2<TYPE>�йصĺ�����������
//--------------------------------------------------------------------------
template <class TYPE>
TYPE VBFVec2Length( const VBFVECTOR2<TYPE> *pV );

template <class TYPE>
TYPE VBFVec2LengthSq( const VBFVECTOR2<TYPE> *pV );

template <class TYPE>
TYPE VBFVec2Dot( const VBFVECTOR2<TYPE> *pV1, const VBFVECTOR2<TYPE> *pV2 );

// Z component of ((x1,y1,0) cross (x2,y2,0))
template <class TYPE>
TYPE VBFVec2CCW( const VBFVECTOR2<TYPE> *pV1, const VBFVECTOR2<TYPE> *pV2 );

template <class TYPE>
VBFVECTOR2<TYPE>* VBFVec2Add( VBFVECTOR2<TYPE> *pOut, const VBFVECTOR2<TYPE> *pV1, const VBFVECTOR2<TYPE> *pV2 );

template <class TYPE>
VBFVECTOR2<TYPE>* VBFVec2Subtract( VBFVECTOR2<TYPE> *pOut, const VBFVECTOR2<TYPE> *pV1, const VBFVECTOR2<TYPE> *pV2 );

// Minimize each component.  x = min(x1, x2), y = min(y1, y2)
template <class TYPE>
VBFVECTOR2<TYPE>* VBFVec2Minimize( VBFVECTOR2<TYPE> *pOut, const VBFVECTOR2<TYPE> *pV1, const VBFVECTOR2<TYPE> *pV2 );

// Maximize each component.  x = max(x1, x2), y = max(y1, y2)
template <class TYPE>
VBFVECTOR2<TYPE>* VBFVec2Maximize( VBFVECTOR2<TYPE> *pOut, const VBFVECTOR2<TYPE> *pV1, const VBFVECTOR2<TYPE> *pV2 );

template <class TYPE>
VBFVECTOR2<TYPE>* VBFVec2Scale( VBFVECTOR2<TYPE> *pOut, const VBFVECTOR2<TYPE> *pV, TYPE s );

// Linear interpolation. V1 + s(V2-V1)
template <class TYPE>
VBFVECTOR2<TYPE>* VBFVec2Lerp( VBFVECTOR2<TYPE> *pOut, const VBFVECTOR2<TYPE> *pV1, const VBFVECTOR2<TYPE> *pV2, TYPE s );

template <class TYPE>
VBFVECTOR2<TYPE>* VBFVec2Normalize( VBFVECTOR2<TYPE> *pOut, const VBFVECTOR2<TYPE> *pV );

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
template <class TYPE>
VBFVECTOR2<TYPE>* VBFVec2Hermite( VBFVECTOR2<TYPE> *pOut, const VBFVECTOR2<TYPE> *pV1, const VBFVECTOR2<TYPE> *pT1, const VBFVECTOR2<TYPE> *pV2, const VBFVECTOR2<TYPE> *pT2, TYPE s );

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
template <class TYPE>
VBFVECTOR2<TYPE>* VBFVec2CatmullRom( VBFVECTOR2<TYPE> *pOut, const VBFVECTOR2<TYPE> *pV0, const VBFVECTOR2<TYPE> *pV1, const VBFVECTOR2<TYPE> *pV2, const VBFVECTOR2<TYPE> *pV3, TYPE s );

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
template <class TYPE>
VBFVECTOR2<TYPE>* VBFVec2BaryCentric( VBFVECTOR2<TYPE> *pOut, const VBFVECTOR2<TYPE> *pV1, const VBFVECTOR2<TYPE> *pV2, const VBFVECTOR2<TYPE> *pV3, TYPE f, TYPE g);


//--------------------------------------------------------------------------
// ��ṹ��VBFVECTOR3�йصĺ�����������
//--------------------------------------------------------------------------

template <class TYPE>
TYPE VBFVec3Length( const VBFVECTOR3<TYPE>* pV );

template <class TYPE>
TYPE VBFVec3LengthSq( const VBFVECTOR3<TYPE>* pV );

template <class TYPE>
TYPE VBFVec3Dot( const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2 );

template <class TYPE>
VBFVECTOR3<TYPE>* VBFVec3Cross( VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2 );

template <class TYPE>
VBFVECTOR3<TYPE>* VBFVec3Add( VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2 );

template <class TYPE>
VBFVECTOR3<TYPE>* VBFVec3Subtract( VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2 );

// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
template <class TYPE>
VBFVECTOR3<TYPE>* VBFVec3Minimize( VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2 );

// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
template <class TYPE>
VBFVECTOR3<TYPE>* VBFVec3Maximize( VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2 );

template <class TYPE>
VBFVECTOR3<TYPE>* VBFVec3Scale( VBFVECTOR3<TYPE> *pOut, const VBFVECTOR3<TYPE> *pV, TYPE s);

// Linear interpolation. V1 + s(V2-V1)
template <class TYPE>
VBFVECTOR3<TYPE>* VBFVec3Lerp( VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2, TYPE s );

template <class TYPE>
VBFVECTOR3<TYPE>* VBFVec3Normalize( VBFVECTOR3<TYPE> *pOut, const VBFVECTOR3<TYPE> *pV );

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).

template <class TYPE>
VBFVECTOR3<TYPE>* VBFVec3Hermite( VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pT1, const VBFVECTOR3<TYPE>* pV2, const VBFVECTOR3<TYPE>* pT2, TYPE s );

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)

template <class TYPE>
VBFVECTOR3<TYPE>*  VBFVec3CatmullRom( VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV0, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2, const VBFVECTOR3<TYPE>* pV3, TYPE s );

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
template <class TYPE>
VBFVECTOR3<TYPE>*  VBFVec3BaryCentric( VBFVECTOR3<TYPE>* pOut, const VBFVECTOR3<TYPE>* pV1, const VBFVECTOR3<TYPE>* pV2, const VBFVECTOR3<TYPE>* pV3, TYPE f, TYPE g);



// �ж�����֮��Ĵ�С��ϵ
template <class TYPE>
bool operator<(const VBFVECTOR2<TYPE>& c1, const VBFVECTOR2<TYPE>& c2);


//----------------------------------------------------------------------------
// ģ���ػ���
//----------------------------------------------------------------------------
typedef VBFVECTOR2<float>		VBFVECTOR2F;
typedef VBFVECTOR2<double>		VBFVECTOR2D;

typedef VBFVECTOR3<float>		VBFVECTOR3F;
typedef VBFVECTOR3<double>		VBFVECTOR3D;

typedef VBFVECTOR4<float>		VBFVECTOR4F;
typedef VBFVECTOR4<double>		VBFVECTOR4D;


//-------------------------------------------------------------------------
// ����������ʵ���ļ�
#include "VBF_Vector.inl"
//-------------------------------------------------------------------------


// ע�⣺ȡ���ֽڶ��������
#include <poppack.h>  


#if _MSC_VER >= 1200
	#pragma warning(pop)
#else
	#pragma warning(default:4201)
#endif

#endif 

