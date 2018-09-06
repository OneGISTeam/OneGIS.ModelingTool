#ifndef __IVBF_TRIANGULATION_H__
#define __IVBF_TRIANGULATION_H__


#include <VBF_Common/VBF_Triangulation/VBF_TriangulationExport.h>
#include <vector>
#include <Types/Vec2d>



#ifndef _WORD_DEFINED
	#define _WORD_DEFINED
	typedef unsigned short WORD;
#endif


class IVBF_Triangulation
{
public:	
	virtual ~IVBF_Triangulation() {}

public:		
	virtual void Triangulate(const std::vector<osg::Vec2d>& aPt, const std::vector<int>& aSize,
		                     int& nNumTriangles, WORD*& pIndices)=0;
};


// 声明全局函数
VBF_TRIANGULATION_EXPORT IVBF_Triangulation*   VBF_CreateTriangulation();
VBF_TRIANGULATION_EXPORT void                  VBF_ReleaseTriangulation(IVBF_Triangulation*& pITriangulation);


#endif
