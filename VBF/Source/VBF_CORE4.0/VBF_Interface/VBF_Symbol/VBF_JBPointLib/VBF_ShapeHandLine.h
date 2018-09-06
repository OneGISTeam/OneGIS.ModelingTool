#ifndef _HANDLINE_H_
#define _HANDLINE_H_

#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>


class VBF_JBPOINTLIB_EXPORT CVBF_ShapeHandLine : public CVBF_Shape  
{

public:
	CVBF_ShapeHandLine();
	virtual ~CVBF_ShapeHandLine();

	CVBF_ShapeHandLine(osg::Vec2i* point,int ptcount);

public:

        virtual void CalcBoundaryPts();
        virtual vector<osg::Vec2i> GetBoundaryPts() ;
        virtual void DrawSelf();
        virtual void Read(FILE* fp);
		CVBF_Shape* Clone() ;


};

#endif
