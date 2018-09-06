//*******************************************************************
// FileName：VBF_TriangulationUtils.h
// Function：三角剖分工具
// Author：  杜莹
// Date：    2014-12-23
//*******************************************************************

#ifndef __VBF_TRIANGULATION_UTILS_H__
#define __VBF_TRIANGULATION_UTILS_H__



#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Macros.h>
#include <Types/Vec3d>
#include <vector>



// 判断是否需要剖分（如果只有三个或四个顶点，直接设置顶点索引即可，不需要剖分）
VBF_GLAUX_EXPORT bool NeedTriangulate(const std::vector<osg::Vec3d>& vPoints, bool& bClosed, int& nNumTriangles, WORD*& pIndices);


// osg提供的三角剖分，目前有误
VBF_GLAUX_EXPORT bool VBF_Triangulate(const std::vector<osg::Vec3d>& vPoints, int& nNumTriangles, WORD*& pIndices);


// 三角剖分（使用第三方库提供的剖分方法）
VBF_GLAUX_EXPORT bool VBF_Triangulate_Extern(const std::vector<osg::Vec3d>& vPoints, int& nNumTriangles, WORD*& pIndices);


#endif
