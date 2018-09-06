#include <memory.h>
//=============================================
//
//  ����ṹ��
//
//============================================

#if !defined(_GEOSTRUCT_H_INCLUDED_)
#define _GEOSTRUCT_H_INCLUDED_

struct CGridDataInfo
{
	int rows;
	int cols;
    double xMin;
    double xMax;
    double yMin;
    double yMax;
    double zMin;
    double zMax;

	CGridDataInfo(){memset(this,0,sizeof(CGridDataInfo));}	
};

struct CGeoPoint
{
    double x;
    double y;

	CGeoPoint(){x=y=0;}
    CGeoPoint(double _x,double _y):x(_x),y(_y){}
};
/***
struct CGeoRect
{
	//����y�����ϵ�����ϵ
    double    left;
    double    top;
    double    right;  //right > left
    double    bottom; // top > bottom
    
	CGeoRect(){memset(this,0,sizeof(CGeoRect));}
    CGeoRect(double l, double b, double r, double t){left=l;right=r;bottom=b;top=t;}
	CGeoRect(const CGeoRect& rhs){left=rhs.left;right=rhs.right;bottom=rhs.bottom;top=rhs.top;}

    double Height()const{return top-bottom;}
    double Width()const{return right-left;}
    double Area()const { return Height()*Width();}
	

	CGeoPoint CenterPoint(){return CGeoPoint((right+left)/2,(top+bottom)/2);}
    void Scale(double ratio)
	{//ration < 1 �Ŵ�,raion > 1 ѹ��
		left /= ratio; right /= ratio; top /= ratio; bottom /= ratio;           
	}
    void Translate(double x, double y)
	{//ƽ��
		left += x; right += x; top += y; bottom += y;
	}

	const CGeoPoint& TopLeft()	{ return *((CGeoPoint*)this);}
	const CGeoPoint& BottomRight()	{ return *((CGeoPoint*)this+1);}
	
};
*/
#include <vector>
#include <list>
typedef std::vector<CGeoPoint> CCurve; //һ����ֵ�����ߵĵ㼯������
typedef std::list< CCurve*> CCurveList; //��ֵ����������(����ĳֵ�ĵ�ֵ�߲�����һ��)
typedef std::vector<CCurveList*> CContourArray;

#endif
