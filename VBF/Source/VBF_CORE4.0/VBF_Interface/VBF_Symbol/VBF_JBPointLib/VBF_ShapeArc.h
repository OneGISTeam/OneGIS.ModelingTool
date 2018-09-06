#ifndef _ARC_H
#define _ARC_H


#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>

class VBF_JBPOINTLIB_EXPORT CVBF_ShapeArc : public CVBF_Shape  
{
public:
        CVBF_ShapeArc();
        ~CVBF_ShapeArc();

		CVBF_ShapeArc(osg::Vec2i ptCenter, int nRadius,int nBeginAngle, int nSweepAngle);

public:

        virtual void CalcBoundaryPts();
        virtual vector<osg::Vec2i> GetBoundaryPts() ;
        virtual void DrawSelf();
        virtual void Read(FILE* fp);
		virtual CVBF_Shape * Clone();    //得到图形的拷贝   

public:

        void GetArcPoints(osg::Vec2i Origin,float Radius,float beginAngle,float endAngle,vector<osg::Vec2i>&vpt) ;
		void GetArcPoints(osg::Vec2f Origin,float Radius,float beginAngle,float endAngle,int nPresion,vector<osg::Vec2f>&vpt) ;

private:
	 bool m_bMirrorSelf;
};

#endif 
