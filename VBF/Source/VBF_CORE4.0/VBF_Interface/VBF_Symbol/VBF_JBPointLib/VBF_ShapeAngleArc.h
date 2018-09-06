#ifndef _ANGLEARC_H
#define _ANGLEARC_H

#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>

//ор
class VBF_JBPOINTLIB_EXPORT CVBF_ShapeAngleArc : public CVBF_Shape  
{
public:
        CVBF_ShapeAngleArc();
        ~CVBF_ShapeAngleArc();

		CVBF_ShapeAngleArc(osg::Vec2i ptCenter, int nRadius,int nBeginAngle, int nSweepAngle);

public:

		CVBF_Shape* Clone() ;

        virtual void CalcBoundaryPts();
        virtual vector<osg::Vec2i> GetBoundaryPts() ;
        virtual void DrawSelf();
        virtual void Read(FILE* fp);

public:
 
		void GetArcPoints(osg::Vec2i Origin,float Radius,float beginAngle,float endAngle,vector<osg::Vec2i>&vpt);
		void GetArcPoints(osg::Vec2f Origin,float Radius,float beginAngle,float endAngle,int nPresion,vector<osg::Vec2f>&vpt);

private:
	 bool m_bMirrorSelf;
};

#endif 
