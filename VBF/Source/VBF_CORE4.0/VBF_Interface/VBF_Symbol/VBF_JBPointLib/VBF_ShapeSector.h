#ifndef _SECTOR_H
#define _SECTOR_H

#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>
#include <Types/Vec2f>

class VBF_JBPOINTLIB_EXPORT CVBF_ShapeSector : public CVBF_Shape  
{
public:
        CVBF_ShapeSector();
        ~CVBF_ShapeSector();

		CVBF_ShapeSector(osg::Vec2i ptCenter,int nRadius,int nBeginAngle,int nSweepAngle) ;

public:

        virtual void CalcBoundaryPts();
        virtual vector<osg::Vec2i> GetBoundaryPts() ;
        virtual void DrawSelf();
        virtual void Read(FILE* fp);
		CVBF_Shape* Clone() ;

public:
         void GetArcPoints(osg::Vec2i Origin,float Radius,float beginAngle,float endAngle,vector<osg::Vec2i>&vpt) ;
		 void GetArcPoints(osg::Vec2f Origin,float Radius,float beginAngle,float endAngle,int nPresion,vector<osg::Vec2f>&vpt) ;

public:

	 bool m_bMirrorSelf;
	
};

#endif 
