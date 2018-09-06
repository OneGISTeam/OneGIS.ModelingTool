#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>

class VBF_JBPOINTLIB_EXPORT CVBF_ShapeRectangle : public CVBF_Shape  
{
public:
	CVBF_ShapeRectangle();
	CVBF_ShapeRectangle(osg::Vec2i pt1,osg::Vec2i pt2,osg::Vec2i pt3,osg::Vec2i pt4);  
	virtual ~CVBF_ShapeRectangle();
	
public:

        virtual void CalcBoundaryPts();
        virtual vector<osg::Vec2i> GetBoundaryPts() ;
        virtual void DrawSelf();  //Õº–Œ÷ÿª„
        virtual void Read(FILE* fp);
		CVBF_Shape* Clone() ;
	
};

#endif 
