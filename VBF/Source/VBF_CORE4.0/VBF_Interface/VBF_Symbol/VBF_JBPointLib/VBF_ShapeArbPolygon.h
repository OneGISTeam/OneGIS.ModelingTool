#ifndef _ANYPOLYGON_H
#define _ANYPOLYGON_H

#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>

class VBF_JBPOINTLIB_EXPORT CVBF_ShapeArbPolygon : public CVBF_Shape  
{
public:
        CVBF_ShapeArbPolygon();
        ~CVBF_ShapeArbPolygon();
		CVBF_ShapeArbPolygon(osg::Vec2i *point,int ptcount);

public:

        virtual void CalcBoundaryPts();
        virtual vector<osg::Vec2i> GetBoundaryPts() ;

        virtual void DrawSelf();
        virtual void Read(FILE* fp);
		CVBF_Shape* Clone() ;

};

#endif 
