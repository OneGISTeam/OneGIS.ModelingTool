//*******************************************************************
// FileName��  VBF_MathAPI.h
// Function��  ��װ3D�㷨�ĳ��ú���(.h�ļ�)
// Author:     ��Ө
// Date:       2003.12.13
//*******************************************************************


#ifndef __VBF_MATH_API_H__
#define __VBF_MATH_API_H__

#include "VBF_UtilExport.h"
#include "Types/VBF_Rect.h"
#include <assert.h>

//******************* ����Ϊģ�庯�� *************************************************


//----------------------------------------------------------------------------
// ģ�庯����VBF_BitsLeft
// ������������λ����
//----------------------------------------------------------------------------
template <class TYPE> 
TYPE VBF_BitsLeft(const TYPE& number, unsigned char numBits)
{
	return (TYPE)(number<<numBits);
}

//----------------------------------------------------------------------------
// ģ�庯����VBF_BitsRight
// ������������λ����
//----------------------------------------------------------------------------
template <class TYPE>
TYPE VBF_BitsRight(const TYPE& number, unsigned char numBits)
{
	return (TYPE)(number>>numBits);
}	

//----------------------------------------------------------------------------
// ģ�庯����VBF_DevideExactly()
// ������������ȷ����
//----------------------------------------------------------------------------
template<class TYPE0,class TYPE1>
inline int VBF_DevideExactly(TYPE0 a, TYPE1 b)
{
	double dR = (double)a/b;
	int    nR = (int)dR;

	if(dR>nR) return (nR+1);
	return nR;
}

//----------------------------------------------------------------------------
// ģ�庯����VBF_MultiplyExactly()
// ������������ȷ�˷�
//----------------------------------------------------------------------------
template<class TYPE0, class TYPE1>
inline int VBF_MultiplyExactly(TYPE0 a, TYPE1 b)
{
	double dR = (double)a*b;
	int    nR = (int)dR;

	if(dR>nR) return nR+1;
	return nR;
}

//-------------------------------------------------------------------
// ģ�庯����VBF_Clamp()
// ������������һ�����޶���ָ��������
//-------------------------------------------------------------------
template<class TYPE> 
void VBF_Clamp(TYPE& num, TYPE minValue, TYPE maxValue)
{
	assert( minValue <= maxValue );

	if( num < minValue )  num = minValue;
	if( num > maxValue )  num = maxValue;
}

//-------------------------------------------------------------------
// ģ�庯����VBF_IsIn()
// �����������ж�һ�����Ƿ���ָ��������
// ����˵�������Ҿ�Ϊ������
//-------------------------------------------------------------------
template<class TYPE> 
BOOL VBF_IsIn(TYPE& num, TYPE minValue, TYPE maxValue)
{
	ASSERT( minValue <= maxValue );

	return (num>=minValue && num<=maxValue);
}

//-----------------------------------------------------------------------------
// ģ�庯��: GetBoundRect()
// ��������: ��һ�����ε���С��Ӿ���
//-----------------------------------------------------------------------------
template<class TYPE>
void GetBoundRect(CVBF_Rect<TYPE>& rect, const CVBF_2DPoint<TYPE>& pt1,const CVBF_2DPoint<TYPE>& pt2, const CVBF_2DPoint<TYPE>& pt3, const CVBF_2DPoint<TYPE>& pt4)
{
	// ��ȡ�ĸ����е�x,y��Сֵ���Ա㹹����С��Ӿ���
	TYPE fLeft1   = min(pt1.x, pt2.x);
	TYPE fLeft2   = min(pt3.x, pt4.x);
	TYPE fLeft    = min(fLeft1, fLeft2);
    
	TYPE fRight1  = max(pt1.x, pt2.x);
	TYPE fRight2  = max(pt3.x, pt4.x);
	TYPE fRight   = max(fRight1, fRight2);

	TYPE fTop1    = min(pt1.y, pt2.y);
	TYPE fTop2    = min(pt3.y, pt4.y);
	TYPE fTop     = min(fTop1, fTop2);
    
	TYPE fBottom1 = max(pt1.y, pt2.y);
	TYPE fBottom2 = max(pt3.y, pt4.y);
	TYPE fBottom  = max(fBottom1, fBottom2);

    rect.SetRect(fLeft, fTop, fRight, fBottom);
}

//-----------------------------------------------------------------------------
// ģ�庯��: RotatePoint()
// ��������: ʹһ������ָ������ת
// ����������COS��SIN�ֱ�Ϊ��ת�ǵ����Һ�����ֵ
//-----------------------------------------------------------------------------
template <class TYPE>
void RotatePoint(CVBF_2DPoint<TYPE>& pt, const CVBF_2DPoint<TYPE>& ptRef, double COS, double SIN)
{
	pt -= ptRef;
	CVBF_2DPoint<TYPE> ptBak = pt;
	pt.x = (TYPE)(ptBak.x*COS - ptBak.y*SIN);
	pt.y = (TYPE)(ptBak.x*SIN + ptBak.y*COS);
	pt += ptRef;
}

//-----------------------------------------------------------------------------
// ģ�庯��: RotateRect()
// ��������: ʹһ��������ָ������ת�����ֵΪ��ת����ε��ĸ�����
//-----------------------------------------------------------------------------
template <class TYPE>
void RotateRect(const CVBF_Rect<TYPE>& rect, const CVBF_2DPoint<TYPE>& ptRef, double fAngle, CVBF_2DPoint<TYPE>& ptTL, CVBF_2DPoint<TYPE>& ptTR, CVBF_2DPoint<TYPE>& ptBL, CVBF_2DPoint<TYPE>& ptBR)
{
	double COS = cos(fAngle);
	double SIN = sin(fAngle);

	ptTL = rect.TopLeft();                     // ���Ͻ�
	RotatePoint(ptTL, ptRef, COS, SIN);

	ptTR = CVBF_2DPoint<TYPE>(rect.right, rect.top);   // ���Ͻ�
	RotatePoint(ptTR, ptRef, COS, SIN);

	ptBL = CVBF_2DPoint<TYPE>(rect.left, rect.bottom); // ���½�
	RotatePoint(ptBL, ptRef, COS, SIN);

	ptBR = rect.BottomRight();                 // ���½�
	RotatePoint(ptBR, ptRef, COS, SIN);	
}

//----------------------------------------------------------------------------
// ģ�庯����LinearInsert()
// �������������Բ�ֵ
//----------------------------------------------------------------------------
template <class TYPE> 
TYPE LinearInsert(const TYPE& X0, const TYPE& X1, double dU0, double dU1, double dU)
{	
	return (TYPE)( (dU-dU0)/(dU1-dU0) * (X1-X0)+X0 );
}

//----------------------------------------------------------------------------
// ģ�庯����BiLinearInsert()
// ����������˫���Բ�ֵ����˳��00 01 11 10
//----------------------------------------------------------------------------
template <class TYPE> 
void BiLinearInsert(TYPE* in, TYPE* out, int num,
					int nU0, int nU1, int nV0, int nV1, double dU, double dV)
{	
	double u  = dU  - nU0; 
	double v  = dV  - nV0; 
	double uu = nU1 - dU; 
	double vv = nV1 - dV;
	
	for(int i=0; i<num; i++)
	{
		int pos = i;
		TYPE h0 = in[pos]; pos += num;
		TYPE h1 = in[pos]; pos += num;
		TYPE h2 = in[pos]; pos += num;
		TYPE h3 = in[pos];	
		out[i] =  (TYPE)( uu*(v*h3 + vv*h0) + u*(v*h2 + vv*h1) );
	}
}

//----------------------------------------------------------------------------------------
// ����������BiLinearInsert()
// ����������˫���Բ�ֵ (������Dem��ֵ)
//----------------------------------------------------------------------------------------
inline void BiLinearInsert(const CVBF_RectD& rectGeoSrc, int nRowsSrc, int nColsSrc, float** pDemSrc, 
					       const CVBF_RectD& rectGeoDst, int nRowsDst, int nColsDst, float**& pDemDst)
{
	int i=0;

	pDemDst = new float*[nRowsDst];
	for(i=0; i<nRowsDst; i++)
	{
		pDemDst[i] = new float[nColsDst];
	}

	double ddx = rectGeoDst.Width()/(nColsDst-1);
	double ddy = rectGeoDst.Height()/(nRowsDst-1);

	double dRectWSrc = rectGeoSrc.Width();
	double dRectHSrc = rectGeoSrc.Height();

	for(i=0; i<nRowsDst; i++)
	{
		for(int j=0; j<nColsDst; j++)
		{
			double L = j*ddx + rectGeoDst.left;
			double B = i*ddy + rectGeoDst.top;			

			// ��˫���Բ�ֵ������ԭʼDem��ȡ�߳�ֵ
			double dU = (L - rectGeoSrc.left)/dRectWSrc;
			double dV = (B - rectGeoSrc.top)/dRectHSrc;

			dU *= (nColsSrc-1);
			dV *= (nRowsSrc-1);

			if( dU>=nColsSrc-1 )  dU = nColsSrc-1 - 0.001;  	
			if( dV>=nRowsSrc-1 )  dV = nRowsSrc-1 - 0.001;  

			int nU0 = (int)dU, nU1 = nU0 + 1;
			int nV0 = (int)dV, nV1 = nV0 + 1;

			::VBF_Clamp<int>(nU0, 0, nColsSrc-1);
			::VBF_Clamp<int>(nU1, 0, nColsSrc-1);
			::VBF_Clamp<int>(nV0, 0, nRowsSrc-1);
			::VBF_Clamp<int>(nV1, 0, nRowsSrc-1);
				
			// ��ȡ�ĸ�����(���̵߳�)�����ݣ��Ա����˫���Բ�ֵ
			float pFourPixelData[4];
			ZeroMemory( pFourPixelData, sizeof(pFourPixelData) );
			
			for(int k=0; k<4; k++)
			{
				int nRowNo, nColNo;  // ��������ԭʼDem�е��кź��к�	
				if(k==0)		{ nRowNo = nV0;  nColNo = nU0; }
				else if(k==1)	{ nRowNo = nV0;  nColNo = nU1; }
				else if(k==2)	{ nRowNo = nV1;  nColNo = nU1; }
				else if(k==3)	{ nRowNo = nV1;  nColNo = nU0; }

				pFourPixelData[k] = pDemSrc[nRowNo][nColNo];
			}

			// ���������ĸ�����(���̵߳�)�����ݣ�ͨ��˫���Բ�ֵ�õ�ָ��λ�ô�����(���̵߳�)������
			float H = 0.0f;
			::BiLinearInsert<float>(pFourPixelData, &H, 1, nU0, nU1, nV0, nV1, dU, dV);

			pDemDst[i][j] = H;
		}
	}
}

//----------------------------------------------------------------------------------------
// ����������BiLinearInsert()
// ����������˫���Բ�ֵ (������Dem��ֵ)
// ����˵����Dem����ʹ��һά���� (��Ө��ӣ�2011-07-21)
//----------------------------------------------------------------------------------------
inline void BiLinearInsert(const CVBF_RectD& rectGeoSrc, int nRowsSrc, int nColsSrc, float* pDemSrc, 
					       const CVBF_RectD& rectGeoDst, int nRowsDst, int nColsDst, float*& pDemDst)
{
	pDemDst = new float[nRowsDst*nColsDst];

	double ddx = rectGeoDst.Width()/(nColsDst-1);
	double ddy = rectGeoDst.Height()/(nRowsDst-1);

	double dRectWSrc = rectGeoSrc.Width();
	double dRectHSrc = rectGeoSrc.Height();

	for(int i=0; i<nRowsDst; i++)
	{
		for(int j=0; j<nColsDst; j++)
		{
			double L = j*ddx + rectGeoDst.left;
			double B = i*ddy + rectGeoDst.top;			

			// ��˫���Բ�ֵ������ԭʼDem��ȡ�߳�ֵ
			double dU = (L - rectGeoSrc.left)/dRectWSrc;
			double dV = (B - rectGeoSrc.top)/dRectHSrc;

			dU *= (nColsSrc-1);
			dV *= (nRowsSrc-1);

			if( dU>=nColsSrc-1 )  dU = nColsSrc-1 - 0.001;  	
			if( dV>=nRowsSrc-1 )  dV = nRowsSrc-1 - 0.001;  

			int nU0 = (int)dU, nU1 = nU0 + 1;
			int nV0 = (int)dV, nV1 = nV0 + 1;

			::VBF_Clamp<int>(nU0, 0, nColsSrc-1);
			::VBF_Clamp<int>(nU1, 0, nColsSrc-1);
			::VBF_Clamp<int>(nV0, 0, nRowsSrc-1);
			::VBF_Clamp<int>(nV1, 0, nRowsSrc-1);
				
			// ��ȡ�ĸ�����(���̵߳�)�����ݣ��Ա����˫���Բ�ֵ
			float pFourPixelData[4];
			ZeroMemory( pFourPixelData, sizeof(pFourPixelData) );
			
			for(int k=0; k<4; k++)
			{
				int nRowNo, nColNo;  // ��������ԭʼDem�е��кź��к�	
				if(k==0)		{ nRowNo = nV0;  nColNo = nU0; }
				else if(k==1)	{ nRowNo = nV0;  nColNo = nU1; }
				else if(k==2)	{ nRowNo = nV1;  nColNo = nU1; }
				else if(k==3)	{ nRowNo = nV1;  nColNo = nU0; }
				
				int noPtSrc = nRowNo * nColsSrc + nColNo;
				pFourPixelData[k] = pDemSrc[noPtSrc];
			}

			// ���������ĸ�����(���̵߳�)�����ݣ�ͨ��˫���Բ�ֵ�õ�ָ��λ�ô�����(���̵߳�)������
			float H = 0.0f;
			::BiLinearInsert<float>(pFourPixelData, &H, 1, nU0, nU1, nV0, nV1, dU, dV);

			int noPtDst = i * nColsDst + j;
			pDemDst[noPtDst] = H;
		}
	}
}

//--------------------------------------------------------------------
// ģ�庯����CalTriangleBound()
// �������������������ε���С��Χ��
//--------------------------------------------------------------------
template <class TYPE>
void CalTriangleBound(const CVBF_2DPoint<TYPE>& point1, const CVBF_2DPoint<TYPE>& point2,
					  const CVBF_2DPoint<TYPE>& point3, CVBF_Rect<TYPE>& rect)
{
	rect.left  = point1.x  < point2.x ? point1.x: point2.x;
	rect.left  = rect.left < point3.x ? rect.left  : point3.x;

	rect.right = point1.x   > point2.x ? point1.x: point2.x;
	rect.right = rect.right > point3.x ? rect.right : point3.x;

	rect.top   = point1.y < point2.y ? point1.y: point2.y;
	rect.top   = rect.top < point3.y ? rect.top   : point3.y;

	rect.bottom= point1.y    > point2.y ? point1.y: point2.y;
	rect.bottom= rect.bottom > point3.y ? rect.bottom: point3.y;
}

//-------------------------------------------------------------------
// ģ�庯����RelationOfPointAndTriangle()
// �����������жϵ��������εĹ�ϵ
//           -1Ϊ����������  0Ϊ����������
//            1Ϊ���1�غ�   2Ϊ���2�غ�    3Ϊ���3�غ�
//            12Ϊ�ڱ�12��   23Ϊ�ڱ�23��    13Ϊ�ڱ�13��
//-------------------------------------------------------------------
template <class TYPE>
int RelationOfPointAndTriangle(const CVBF_2DPoint<TYPE>& point1, const CVBF_2DPoint<TYPE>& point2,
							   const CVBF_2DPoint<TYPE>& point3, const CVBF_2DPoint<TYPE>& point0)
{
	double x01 = point0.x - point1.x;
	double y01 = point0.y - point1.y;
	double x02 = point0.x - point2.x;
	double y02 = point0.y - point2.y;
	double x03 = point0.x - point3.x;
	double y03 = point0.y - point3.y;

	// ��Ө�޸ģ�2004-12-7
//	if( x01 == 0 && y01 == 0 ) return 1;
//	if( x02 == 0 && y02 == 0 ) return 2;
//	if( x03 == 0 && y03 == 0 ) return 3;
	if( fabs(x01) < DBL_MAX_PRECISION && fabs(y01) < DBL_MAX_PRECISION ) return 1;
	if( fabs(x02) < DBL_MAX_PRECISION && fabs(y02) < DBL_MAX_PRECISION ) return 2;
	if( fabs(x03) < DBL_MAX_PRECISION && fabs(y03) < DBL_MAX_PRECISION ) return 3;

	double x21 = point2.x - point1.x;
	double y21 = point2.y - point1.y;
	double x31 = point3.x - point1.x;
	double y31 = point3.y - point1.y;

	double dT3 = ( x01*y21 - y01*x21 ) * ( x31*y21 - y31*x21 );//�ж��Ƿ���3�ŵ���ͬ��
	if(dT3<0) return -1;

	double dT2 = ( x01*y31 - y01*x31 ) * ( x21*y31 - y21*x31 );//�ж��Ƿ���2�ŵ���ͬ��
	if(dT2<0) return -1;

	double x12 = -x21;
	double y12 = -y21;
	double x32 = point3.x - point2.x;
	double y32 = point3.y - point2.y;

	double dT1 = ( x02*y32 - y02*x32 ) * ( x12*y32 - y12*x32 );//�ж��Ƿ���1�ŵ���ͬ��
	if(dT1<0) return -1;

	// ��Ө�޸ģ�2004-12-7
//	if( dT1 == 0 ) return 23;
//	if( dT2 == 0 ) return 13;
//	if( dT3 == 0 ) return 12;
	if( fabs(dT1) < DBL_MAX_PRECISION ) return 23;
	if( fabs(dT2) < DBL_MAX_PRECISION ) return 13;
	if( fabs(dT3) < DBL_MAX_PRECISION ) return 12;

	return 0;
}

//-------------------------------------------------------------------
// ģ�庯����IsRectIntersectTriangle()
// �����������жϾ����Ƿ����������ཻ
//-------------------------------------------------------------------
template <class TYPE>
BOOL IsRectIntersectTriangle(const TYPE& left, const TYPE& top, const TYPE& right, const TYPE& bottom,
							 const CVBF_2DPoint<TYPE>& point1,const CVBF_2DPoint<TYPE>& point2,const CVBF_2DPoint<TYPE>& point3)
{
	if( IsHLineSegIntersectTriangle(left,right,top,   point1,point2,point3) ) return TRUE;
	if( IsHLineSegIntersectTriangle(left,right,bottom,point1,point2,point3) ) return TRUE;
	if( IsVLineSegIntersectTriangle(top,bottom,left,  point1,point2,point3) ) return TRUE;
	if( IsVLineSegIntersectTriangle(top,bottom,right, point1,point2,point3) ) return TRUE;
	return FALSE;
}


//-------------------------------------------------------------------
// ģ�庯����IsVLineSegIntersectTriangle()
// �����������жϴ�ֱ�߶��Ƿ����������ཻ
//-------------------------------------------------------------------
template <class TYPE>
BOOL IsVLineSegIntersectTriangle(const TYPE& y1, const TYPE& y2, const TYPE& x,
								 const CVBF_2DPoint<TYPE>& point1,const CVBF_2DPoint<TYPE>& point2,const CVBF_2DPoint<TYPE>& point3)
{
	if( IsLineSegIntersectVLineSeg(y1,y2,x,point1.x,point1.y,point2.x,point2.y) ) return TRUE;
	if( IsLineSegIntersectVLineSeg(y1,y2,x,point2.x,point2.y,point3.x,point3.y) ) return TRUE;
	if( IsLineSegIntersectVLineSeg(y1,y2,x,point1.x,point1.y,point3.x,point3.y) ) return TRUE;
	return FALSE;
}

//-------------------------------------------------------------------
// ģ�庯����IsHLineSegIntersectTriangle()
// �����������ж�ˮƽ�߶��Ƿ����������ཻ
//-------------------------------------------------------------------
template <class TYPE>
BOOL IsHLineSegIntersectTriangle(const TYPE& x1, const TYPE& x2, const TYPE& y,
								 const CVBF_2DPoint<TYPE>& point1,const CVBF_2DPoint<TYPE>& point2,const CVBF_2DPoint<TYPE>& point3)
{
	if( IsLineSegIntersectHLineSeg(x1,x2,y,point1.x,point1.y,point2.x,point2.y) ) return TRUE;
	if( IsLineSegIntersectHLineSeg(x1,x2,y,point2.x,point2.y,point3.x,point3.y) ) return TRUE;
	if( IsLineSegIntersectHLineSeg(x1,x2,y,point1.x,point1.y,point3.x,point3.y) ) return TRUE;
	return FALSE;
}

//-------------------------------------------------------------------
// ģ�庯����IsLineSegIntersectVLineSeg()
// �����������ж��߶��Ƿ��봹ֱ�߶��ཻ
//-------------------------------------------------------------------
template <class TYPE>
BOOL IsLineSegIntersectVLineSeg(const TYPE& y1, const TYPE& y2, const TYPE& x,
								const TYPE& x3, const TYPE& y3, const TYPE& x4, const TYPE& y4)
{
	if(x>x3 && x>x4) return FALSE;
	if(x<x3 && x<x4) return FALSE;

	// ��Ө�޸ģ�2004-12-7
//	if(x3==x4) return FALSE; // �߶�Ϊ��ֱ�ģ�ƽ�л򲿷��غ϶���Ϊ���ཻ
	double dx = (double)(x3 - x4);
	if( fabs(dx)<DBL_MAX_PRECISION ) return FALSE;
	
	double y = 1.0*(x-x3)*(y4-y3)/(x4-x3) + y3;
	if( (y>y1 && y>y2) || (y<y1 && y<y2) ) return FALSE;

	return TRUE;
}

//-------------------------------------------------------------------
// ģ�庯����IsLineSegIntersectHLineSeg()
// �����������ж��߶��Ƿ���ˮƽ�߶��ཻ
//-------------------------------------------------------------------
template <class TYPE>
BOOL IsLineSegIntersectHLineSeg(const TYPE& x1,const TYPE& x2,const TYPE& y,
								const TYPE& x3,const TYPE& y3,const TYPE& x4,const TYPE& y4)
{
	if(y>y3 && y>y4) return FALSE;
	if(y<y3 && y<y4) return FALSE;

	// ��Ө�޸ģ�2004-12-7
//	if( y3==y4) return FALSE; // �߶�Ϊˮƽ�ģ�ƽ�л򲿷��غ϶���Ϊ���ཻ
	double dy = (double)(y3-y4);
	if( fabs(dy)<DBL_MAX_PRECISION ) return FALSE;
	
	double x = 1.0*(y-y3)*(x4-x3)/(y4-y3) + x3;
	if( (x>x1 && x>x2) || (x<x1 && x<x2) ) return FALSE;

	return TRUE;
}
//------------------------------------------------------------------------------
// ģ�庯����VBF_ShearPoint()
// ������������Ĵ��б任
// ����������ptRef   -- ���еĲο���
//           ptShear -- �����еĵ�

// ����˵�����μ�MSDN�й���Shear()������˵��
//           ��fShearY==0ʱ����ԭʼ���ε��±�Եˮƽ�ƶ����θ߶ȵ�fShearX����
//           ��fShearX==0ʱ����ԭʼ���ε��ұ�Ե��ֱ�ƶ����ο�ȵ�fShearY����
//------------------------------------------------------------------------------
template <class TYPE>
void VBF_ShearPoint(const CVBF_2DPoint<TYPE>& ptRef, CVBF_2DPoint<TYPE>& ptShear, float fShearX, float fShearY)
{
	ptShear.Offset(-ptRef);	

	bool bShearX = CVBF_3DMath::IsShearing(fShearX);
	bool bShearY = CVBF_3DMath::IsShearing(fShearY);

	if(bShearX && bShearY)
	{
		CVBF_2DPoint<TYPE> ptBak = ptShear;
		ptShear.x = ptBak.x + fShearX * ptBak.y;
		ptShear.y = ptBak.y + fShearY * ptBak.x;
	}
	else if(bShearX)
	{
		ptShear.x = ptShear.x + fShearX * ptShear.y;
	}
	else if(bShearY)
	{
		ptShear.y = ptShear.y + fShearY * ptShear.x;
	}	

	ptShear.Offset(ptRef);
}

#endif 
