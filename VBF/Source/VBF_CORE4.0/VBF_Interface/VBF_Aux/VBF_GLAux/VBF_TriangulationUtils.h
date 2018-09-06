//*******************************************************************
// FileName��VBF_TriangulationUtils.h
// Function�������ʷֹ���
// Author��  ��Ө
// Date��    2014-12-23
//*******************************************************************

#ifndef __VBF_TRIANGULATION_UTILS_H__
#define __VBF_TRIANGULATION_UTILS_H__



#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Macros.h>
#include <Types/Vec3d>
#include <vector>



// �ж��Ƿ���Ҫ�ʷ֣����ֻ���������ĸ����㣬ֱ�����ö����������ɣ�����Ҫ�ʷ֣�
VBF_GLAUX_EXPORT bool NeedTriangulate(const std::vector<osg::Vec3d>& vPoints, bool& bClosed, int& nNumTriangles, WORD*& pIndices);


// osg�ṩ�������ʷ֣�Ŀǰ����
VBF_GLAUX_EXPORT bool VBF_Triangulate(const std::vector<osg::Vec3d>& vPoints, int& nNumTriangles, WORD*& pIndices);


// �����ʷ֣�ʹ�õ��������ṩ���ʷַ�����
VBF_GLAUX_EXPORT bool VBF_Triangulate_Extern(const std::vector<osg::Vec3d>& vPoints, int& nNumTriangles, WORD*& pIndices);


#endif
