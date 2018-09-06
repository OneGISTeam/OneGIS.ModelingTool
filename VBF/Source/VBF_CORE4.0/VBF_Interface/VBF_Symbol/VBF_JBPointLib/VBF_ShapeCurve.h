#ifndef _CURVE_H
#define _CURVE_H

#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>

class VBF_JBPOINTLIB_EXPORT CVBF_ShapeCurve : public CVBF_Shape  
{
public:
        CVBF_ShapeCurve();
        ~CVBF_ShapeCurve();

		CVBF_ShapeCurve(osg::Vec2i *point,int ptcount);

public:

        virtual void CalcBoundaryPts();
        virtual vector<osg::Vec2i> GetBoundaryPts() ;
        virtual void DrawSelf();
        virtual void Read(FILE* fp);
		CVBF_Shape* Clone() ;

        //输入已知点及个数，输出曲线点集
        int Bezier(vector<osg::Vec2i> points,double presion,vector<osg::Vec2i>& vbezierPts);
        osg::Vec2i GetBezierCtrlPt(osg::Vec2i p1,osg::Vec2i p2,osg::Vec2i p3) ;
        osg::Vec2i ComputePtOnBezier(double t,osg::Vec2i p1,osg::Vec2i p2,osg::Vec2i p3) ;
        osg::Vec2i ComputePtOnBezier(double t,osg::Vec2i p1,osg::Vec2i p2,osg::Vec2i p3,osg::Vec2i p4) ;
        bool IsSamePt(osg::Vec2i OriginPt,osg::Vec2i InPutPt,int distance) ;

public:


		//输入已知点及个数，输出曲线点集
        int Bezier(vector<osg::Vec2f> points,double presion,vector<osg::Vec2f>& vbezierPts);
        osg::Vec2f GetBezierCtrlPt(osg::Vec2f p1,osg::Vec2f p2,osg::Vec2f p3) ;
        osg::Vec2f ComputePtOnBezier(double t,osg::Vec2f p1,osg::Vec2f p2,osg::Vec2f p3) ;
        osg::Vec2f ComputePtOnBezier(double t,osg::Vec2f p1,osg::Vec2f p2,osg::Vec2f p3,osg::Vec2f p4) ;
        bool IsSamePt(osg::Vec2f OriginPt,osg::Vec2f InPutPt,double distance) ;

public:
		int TensionSpline(vector<osg::Vec2f>& aSrc,vector<osg::Vec2f>& aDst,int step,double Standartcoef) ;
		
		double DtisMt_dSquare(double x) ;
		double DtisMt_ptDis(osg::Vec2f pt1,osg::Vec2f pt2);
		double DtisMt_dDis(double x1,double y1,double x2,double y2);

public:

	 float fTension;  //曲线张力 取值>0
};

#endif 
