#ifndef  _DTIS_ZHWR_MATHBASE_H_
#define  _DTIS_ZHWR_MATHBASE_H_


#include "VBF_Array.h"

#include "Types/VBF_2DPoint.h"
#include "Types/VBF_Rect.h"

typedef CVBF_2DPoint<long>  CPoint;
typedef CVBF_Rect<long>		CRect;


#ifndef PI
#define PI                    (3.14159265358979323846)  // 圆周率
#endif

#ifndef PI_2
#define PI_2                  (1.57079632679489661923)
#endif

#ifndef PI12
#define PI12                  (PI/2.0)
#endif
#ifndef PI32
#define PI32                  (PI*3/2.0)
#endif

#ifndef TwoPI
#define TwoPI                  (6.28318530717958647692)
#endif


#define dtoi(x) ((int)floor(x+0.499999))

// 乘方
int DtisMt_nSquare( int x );
double DtisMt_fSquare( float x );
double DtisMt_dSquare( double x );


// 距离
double DtisMt_nDis( int x1,int y1,int x2,int y2 );
double DtisMt_dDis( double x1,double y1,double x2,double y2);
double DtisMt_ptDis( CPoint pt1,CPoint pt2 );


#ifndef SQR
#define SQR(x)                (double(x)*double(x))                     // 平方
#endif


#define DIS(pt1,pt2) (sqrt(1.0* SQR(pt1.x - pt2.x)+SQR(pt1.y - pt2.y)))

/*
typedef struct tagSEG 
{	  
	DWORD dwPos;
	LPPOINT lpPoints; 
}PTS;


void CALLBACK AddSegment(int x, int y, PTS *pts);
void CALLBACK CountPoints(int x, int y, LPDWORD lpdwNumPts);
class CPointsFromLine
{ 
public:
	CPointsFromLine(int x1,int y1,int x2,int y2)
	{   
		if(x1==x2&&y1==y2)
		{	
			pts.lpPoints = new POINT[1];
			dwNumPts=1;
			pts.lpPoints[0].x=x1;
			pts.lpPoints[0].y=y1;
			return;
		}
		dwNumPts = 0;
		LineDDA(x1,y1,x2,y2,(LINEDDAPROC)CountPoints, (LPARAM)&dwNumPts);
		pts.lpPoints = new POINT[dwNumPts+1];
		pts.dwPos = 0;
		LineDDA(x1,y1,x2,y2, (LINEDDAPROC)AddSegment, (LPARAM)&pts);
		pts.lpPoints[dwNumPts].x=x2;
		pts.lpPoints[dwNumPts].y=y2;
	}
	~CPointsFromLine()
	{   delete pts.lpPoints;
	}
	
	PTS pts;
	DWORD dwNumPts;
};

inline void CALLBACK AddSegment(int x, int y, PTS *pts)
{
	pts->lpPoints[pts->dwPos].x = x;
	pts->lpPoints[pts->dwPos].y = y;
	pts->dwPos++;
} 

inline void CALLBACK CountPoints(int x, int y, LPDWORD lpdwNumPts)
{
	   (*lpdwNumPts)++;
	   
	   UNREFERENCED_PARAMETER(x);
	   UNREFERENCED_PARAMETER(y);
}
*/

class CMathbase
{
public:
	CMathbase();
	
public:
	
        bool ThreePointInLine(CPoint pt1,CPoint pt2,CPoint pt3);
	
	// 获取角度系列
	float GetAzimuthAngle( CPoint ptB,CPoint ptE );
	float GetAzimuthAngle(float dx,float dy );
	float GetInclination(CPoint ptB,CPoint ptCenter,CPoint ptE);
	
	
	// 点与直线	
	int  GetDirectionPttoLine(CPoint ptSrc,CPoint ptB,CPoint ptE);
	int  GetDirectionPttoLine(int x1,int y1,int x2,int y2,int X,int Y);
	int  GetDirectionPttoLine_Vec(CPoint ptSrc,CPoint ptB,CPoint ptVec);
	int	 IsRightD(int X,int Y,double A,double B,double C,double D,int nFunFlag);
        CPoint GetVerticalVecToLine( CPoint ptB,CPoint ptE,bool bRight=TRUE ) ;
	
        bool IsPointInPoly(CPoint *pPoints,int nPoint,CPoint point);
	
	
	// 判断线段相交及求交点
        bool IsTwoLinesegmentIntersect( CPoint ptB0,CPoint ptE0, CPoint ptB1,CPoint ptE1 );
        bool intersection(CPoint pt1,CPoint pt2,CPoint pt3,CPoint pt4,CPoint& ptDst);
        bool intersection_Vec(CPoint pt1,CPoint ptVec1,CPoint pt2,CPoint ptVec2,CPoint& ptDst);
	
	// 依据起点和直线求直线上的点位
	void GetPointInLine(CPoint ptB,CPoint ptE,int len,CPoint& ptDst);
	
	// 点到直线及线段的距离
	int DisPtToLine(CPoint ptSrc,CPoint ptB,CPoint ptE);
	int DisPtToLine_Vec(CPoint ptSrc,CPoint ptB,CPoint ptVec);
	int DisPtToLineSegment(CPoint ptSrc,CPoint ptB,CPoint ptE,CPoint& ptVert );
		

};


void AdjustAngleToIV(float& fSrc,float fSrcB,float fSrcE) ;

#endif
