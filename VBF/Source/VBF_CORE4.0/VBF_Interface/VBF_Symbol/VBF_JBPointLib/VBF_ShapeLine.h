#ifndef __VBF_LINE_H__
#define __VBF_LINE_H__

#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>

class VBF_JBPOINTLIB_EXPORT CVBF_ShapeLine : public CVBF_Shape
{
public:
        CVBF_ShapeLine();
		CVBF_ShapeLine(osg::Vec2i begPT,osg::Vec2i endPT);
        ~CVBF_ShapeLine();

public:

        virtual void CalcBoundaryPts();
        virtual vector<osg::Vec2i> GetBoundaryPts() ;
        virtual void DrawSelf();
        virtual void Read(FILE* fp);
		CVBF_Shape* Clone() ;


};

#endif
