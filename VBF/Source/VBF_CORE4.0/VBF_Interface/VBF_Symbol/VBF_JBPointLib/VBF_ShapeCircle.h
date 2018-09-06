#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>

class VBF_JBPOINTLIB_EXPORT CVBF_ShapeCircle : public CVBF_Shape  
{
public:
        CVBF_ShapeCircle();
        ~CVBF_ShapeCircle();

		CVBF_ShapeCircle(osg::Vec2i begPT,osg::Vec2i endPT);
		CVBF_ShapeCircle(osg::Vec2i begPT,double radius);

public:

        virtual void CalcBoundaryPts();
        virtual vector<osg::Vec2i> GetBoundaryPts() ;
        virtual void DrawSelf();
        virtual void Read(FILE* fp);
		CVBF_Shape* Clone() ;

public:
	double m_radius;
};

#endif 
