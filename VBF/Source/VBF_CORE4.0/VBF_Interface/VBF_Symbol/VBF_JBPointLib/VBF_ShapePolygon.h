#ifndef _POLYGON_H
#define _POLYGON_H

#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>

class VBF_JBPOINTLIB_EXPORT CVBF_ShapePolygon : public CVBF_Shape  
{
public:
        CVBF_ShapePolygon();
		CVBF_ShapePolygon(osg::Vec2i& begPos,osg::Vec2i& endPos,int num);
        ~CVBF_ShapePolygon();

public:

        virtual void CalcBoundaryPts();
        virtual vector<osg::Vec2i> GetBoundaryPts() ;
        virtual void DrawSelf();
        virtual void Read(FILE* fp);
		CVBF_Shape* Clone() ;

public:
     int m_polycount;

};

#endif 
