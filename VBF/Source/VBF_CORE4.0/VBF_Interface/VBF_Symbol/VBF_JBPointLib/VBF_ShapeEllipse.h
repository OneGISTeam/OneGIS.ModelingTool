#ifndef _ELLIPSE_H_
#define _ELLIPSE_H_

#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>

class VBF_JBPOINTLIB_EXPORT CVBF_ShapeEllipse : public CVBF_Shape  
{

public:
        CVBF_ShapeEllipse();
        ~CVBF_ShapeEllipse();

		CVBF_ShapeEllipse(osg::Vec2i begpt,osg::Vec2i endpt);

public:
        virtual void CalcBoundaryPts();
        virtual vector<osg::Vec2i> GetBoundaryPts() ;
        virtual void DrawSelf();
        virtual void Read(FILE* fp);
		CVBF_Shape* Clone() ;

		void CalcSelf() ;

		void GetEllipePts(vector<osg::Vec2f>& pointFs,double presion) ;
        osg::Vec2f ComputePtOnBezier(double t,osg::Vec2f p1,osg::Vec2f p2,osg::Vec2f p3,osg::Vec2f p4) ;

private:

	osg::Vec2i m_upper_left ;
	osg::Vec2i m_bottom_right ;

};

#endif 
