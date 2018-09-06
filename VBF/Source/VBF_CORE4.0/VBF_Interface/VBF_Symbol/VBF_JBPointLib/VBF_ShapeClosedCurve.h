#ifndef _CLOSEDCURVE_H
#define _CLOSEDCURVE_H

#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>

class VBF_JBPOINTLIB_EXPORT CVBF_ShapeClosedCurve : public CVBF_Shape  
{
public:
        CVBF_ShapeClosedCurve();
        ~CVBF_ShapeClosedCurve();

		CVBF_ShapeClosedCurve(osg::Vec2i *point,int ptcount);

public:

        virtual void CalcBoundaryPts();
        virtual vector<osg::Vec2i> GetBoundaryPts() ;
        virtual void DrawSelf();
        virtual void Read(FILE* fp);
		CVBF_Shape* Clone() ;

public:

        int ClosedTensionSpline(vector<osg::Vec2i>& aSrc,vector<osg::Vec2i>& aDst,int step,double Standartcoef) ;
		int ClosedTensionSpline(vector<osg::Vec2f>& aSrc,vector<osg::Vec2f>& aDst,int step,double Standartcoef) ;

private:

		double DtisMt_ptDis(osg::Vec2i pt1,osg::Vec2i pt2);
		double DtisMt_ptDis(osg::Vec2f pt1,osg::Vec2f pt2);
	
        double DtisMt_dDis(double x1,double y1,double x2,double y2);
        double DtisMt_dSquare(double x) ;

        float fTension;
};

#endif 
