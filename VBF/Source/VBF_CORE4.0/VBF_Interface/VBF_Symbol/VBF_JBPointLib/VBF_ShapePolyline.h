#ifndef _POLYLINE_H
#define _POLYLINE_H

#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>

class VBF_JBPOINTLIB_EXPORT CVBF_ShapePolyline : public CVBF_Shape  
{
public:
        CVBF_ShapePolyline();
        ~CVBF_ShapePolyline();

		CVBF_ShapePolyline(osg::Vec2i *point,int ptcount);

public:
         virtual void CalcBoundaryPts();
        virtual vector<osg::Vec2i> GetBoundaryPts() ;
         virtual void DrawSelf();
         virtual void Read(FILE* fp);
		 CVBF_Shape* Clone() ;

};

#endif 
